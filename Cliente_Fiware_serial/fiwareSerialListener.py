#       INTEROPERABILIDAD
#       FIWARE FOR SERIAL COMMUNICATION
#
#       POST EXAMPLE 'http://68.183.112.17:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=BDTempCasa001#t|30#'
#       GET EXAMPLE  'http://68.183.112.17:1026/v2/entities/urn:ngsd-ld:BDTempCasa:001?options=values&attrs=measure'

import sys
import glob
import serial #pip3 install pyserial
import serial.tools.list_ports
import requests #pip3 install requests
import datetime

# CONST
HEADERS = {'fiware-service': 'openiot', 'fiware-servicepath' : '/'}
HEADER_POST ='http://fiware-iot.ddns.net:7896/iot/d?k='
HEADER_GET = 'http://fiware-iot.ddns.net:1026/v2/entities/'
VERSION = "0.12"

def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    # if sys.platform.startswith('win'):
    #     ports = ['COM%s' % (i + 1) for i in range(50)]
    # elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
    #     # this excludes your current terminal "/dev/tty"
    #     ports = glob.glob('/dev/tty[A-Za-z]*')
    # elif sys.platform.startswith('darwin'):
    #     ports = glob.glob('/dev/tty.*')
    # else:
    #     raise EnvironmentError('Unsupported platform')

    result = serial.tools.list_ports.comports()
    # print(ports)
    # result = []
    # for port in ports:
    #     try:
    #         s = serial.Serial(port)
    #         s.close()
    #         result.append(port)
    #     except (OSError, serial.SerialException):
    #         pass
    return result

def search_ports():
    ports = []
    option = -1
    ports = serial_ports()
    n = 0
    for p in ports:
        print(str(n) + "- " + str(p))
        n += 1
    try:
        option = int(input("Por favor seleccion el puerto -> "))
    except:
        option = -1
    if ( option < n and option >= 0):
        print("Seleccionado: " + str(ports[option].device))
        return ports[option].device
    else:
        return 0

# devuelve
# para POST:
# POST['t|25']
# POST|Error
# para GET
# GET['30']
# GET|Error

def fiware_op( buffer ):
    if( buffer.find(HEADER_POST) >= 0):

        data = buffer[buffer.find('#')+1 : buffer.find('\\') ]
        buffer = buffer[2:buffer.find('#')]
        try:
            r = requests.post(buffer, data)
            pastebin_url = r.text
            if( len(pastebin_url) == 0):
                print(str(datetime.datetime.now()) + " POST  " + str(r) + "   Data: " + data)
                return ("POST['"+ data + "']")
            else:
                print(str(datetime.datetime.now()) + " POST Error: %s" %pastebin_url)
                return "POST|Error"
        except:
            print(str(datetime.datetime.now()) + " Hubo un error en la operación POST")
            return "POST|Error"
    elif( buffer.find(HEADER_GET) >= 0):
        try:
            r = requests.get(url = buffer[2:buffer.find('\\')], headers = HEADERS)
            pastebin_url = str(r.json())
            print(str(datetime.datetime.now()) + " GET  " + str(r) + "   Data:" + pastebin_url)
            if( str(r).find("[200]") >= 0 ):
                return ("GET" + str(pastebin_url))
            else:
                return 'GET|Error'
        except:
            print("Hubo un error en la operación GET")
            return "GET|Error"
    else:
        print("Frame error")
        return "FrameError"


if __name__ == '__main__':

    print("Interoperabilidad\n --Arduino Serial Listener v" + VERSION + "--\n Obteniendo Puertos...")
    # DEBUG
    #devuelve = fiware_op('http://68.183.112.17:7896/iot/d?k=2tggokgpepnvsb2uv4s40d59oc&i=BDTempCasa021#t|30')
    #print("To arduino: "+ devuelve)
    while(1):
        port = 0
        while( port == 0):
            port = search_ports()
        print("Esperando frames\r")
        try:
            serialPort = serial.Serial(port = port, baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
            while(1):
                if(serialPort.in_waiting > 0):
                    serialString = serialPort.readline()
                    try:
                        serialPort.write( fiware_op(str(serialString)).encode() )
                    except Exception:
                        print("Serial timeout")
        except:
            print("Error\n")
        finally:
            print("Buscando puertos")