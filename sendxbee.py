from digi.xbee.devices import XBeeDevice

# TODO: Replace with the serial port where your local module is connected to.
PORT = "COM4"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600

DATA_TO_SEND = "Hello XBee!/n"
REMOTE_NODE_ID = "REMOTE"


def main():

    device = XBeeDevice(PORT, BAUD_RATE)
    while True:
        try:
            device.open()
            DATA_TO_SEND = "Hello"
        

            device.send_data_broadcast(DATA_TO_SEND + "\n")

            print("Success")

        finally:
            if device is not None and device.is_open():
                device.close()


if __name__ == '__main__':
    main()
