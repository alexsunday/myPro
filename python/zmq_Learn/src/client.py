'''
Created on 2012-7-1

@author: Sunday
'''
import zmq
import time

def client():
    context = zmq.Context(1)
    sock  = context.socket(zmq.REQ)
    sock.connect("tcp://127.0.0.1:12345")
    while True:
        sock.send(raw_input(">"))
        print(sock.recv())

if __name__ == '__main__':
    client()