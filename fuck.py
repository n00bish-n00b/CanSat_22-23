
from digi.xbee.devices import XBeeDevice

# TODO: Replace with the serial port where your local module is connected to.
PORT = "COM5"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600




def main():
    device = XBeeDevice(PORT, BAUD_RATE)
    device.open()

    while True:
        try:
            data = input('\n')
            
            
            remote = RemoteXBeeDevice(xbee, XBee64BitAddress.from_hex_string("0013A20040B58D1F"))
            xbee.send_data(remote, "Hello XBee!")

            
        except:
            pass


if __name__ == '__main__':
    main()