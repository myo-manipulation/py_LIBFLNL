import socket
import time
import random
import struct
from datetime import datetime

# DEBUG: NOT WORKING
class Client:
    def __init__(self, address, port):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((address, port))
        self.connected = True

    def send(self, data):
        self.client_socket.send(str(data).encode())

    def receive(self):
        try:
            data = self.client_socket.recv(255)  # MESSAGE_SIZE
            if len(data) % 8 == 0:  # Check if the data length is a multiple of EXPECTED_DOUBLE_SIZE
                num_doubles = len(data) // 8
                format_str = '<' + 'd' * num_doubles
                return struct.unpack(format_str, data)
            else:
                # Handle the case where the data does not align with expected double sizes
                return None
        except socket.error:
            return None

    def close(self):
        self.client_socket.close()
        self.connected = False

def main():
    time.sleep(2)
    monClient = Client("127.0.0.1", 2048)

    i = [0, 0, 0]
    m = 0
    a = [0] * 6
    t = 0
    t0 = datetime.now()

    while monClient.connected:
        t1 = datetime.now()
        t = (t1 - t0).total_seconds()
        i[0] = t

        received_values = monClient.receive()
        if received_values:
            a = [float(val) for val in received_values.split()]
            print(f"{t} =? {a[0]} {t - a[0]}")

        m += 0.00
        i[2] = -4 * a[5]
        monClient.send(i)

        if random.randint(0, 1000) == 1:
            monClient.send("GTNS 2.56")

        time.sleep(0.01)

    print("Closing...")
    monClient.close()

if __name__ == "__main__":
    main()
