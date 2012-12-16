import socket
import struct

def client_thread(socket):
    verifyinfo = socket.recv(4+4+16)
    print len(verifyinfo)
    print bytes(verifyinfo)
    result = struct.unpack(verifyinfo, "iiiiii")
    print result


def test():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 8011))
    s.listen(1)
    (c, addr) = s.accept()
    client_thread(c)
    while True:
        pass

test()
