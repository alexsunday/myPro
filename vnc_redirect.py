#!/usr/bin/env python
# encoding: utf-8
'''@author: Administrator'''

import threading
import socket

port = 5910


def main():
    interface = '192.168.0.12'
    sock = socket.socket()
    sock.bind((interface, port))
    sock.listen(socket.SOMAXCONN)
    while True:
        cs, co = sock.accept()
        print 'Connection from %s:%d' % co
        t1 = threading.Thread(target=Server, args=(cs, ))
        t1.start()


def Server(sock):
    client = socket.socket()
    client.connect(('127.0.0.1', port))
    print 'Connected to 127.0.0.1:5910'
    t1 = threading.Thread(target=Client, args=(sock, client))
    t1.start()
    while True:
        data = sock.recv(100)
        if data:
            print 'Client send: %d' % len(data)
            client.send(data)


def Client(sock, client):
    print 'Server: %r, Client: %r' % (sock, client)
    while True:
        data = client.recv(100)
        if data:
            print 'Server send: %d' % len(data)
        sock.send(data)


if __name__ == '__main__':
    main()

