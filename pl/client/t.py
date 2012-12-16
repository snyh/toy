import socket
import struct

def test():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('', 8010))

    img = open("./getimage.jpeg").read()
    l = len(img)

    md5 = 1234

    value = struct.pack("I", 3)
    #print value
    s.send(value)
    s.send("1234567890111111")
    #s.send(img)

while(1):
    test()
