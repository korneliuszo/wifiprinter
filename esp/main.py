import ConnectWiFi
ConnectWiFi.connect()

from machine import UART, Pin

uart = UART(1)
uart.init(50000, bits=8, parity=None, stop=1)

busy = Pin(0, Pin.IN, Pin.PULL_UP)

import socket

s = socket.socket()
s.bind(("0.0.0.0", 9100))
s.listen(1)

while True:
    cl, addr = s.accept()
    print('client connected from', addr)
    while True:
        while busy.value() == 0:
            pass
        data=cl.read(10)
        if data == b'':
            break
        uart.write(data)
