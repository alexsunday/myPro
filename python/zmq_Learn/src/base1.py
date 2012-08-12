'''
Created on 2012-5-26

@author: Sunday
'''
import zmq
import time

def server():
    context = zmq.Context(1)
    socket  = context.socket(zmq.REP)
    socket.bind('tcp://0.0.0.0:12345')
    data    = ''
    while True:
        try:
            data = socket.recv()
            if len(data) != 0:
                print 'recv %s'%(data)
            socket.send(data)
        except ZMQError,e:
            time.sleep(0.01)
            continue
        

if __name__ == '__main__':
    server()