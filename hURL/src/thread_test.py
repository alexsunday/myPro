#! /usr/bin/env python
#coding=utf-8

import threading,time,random,Queue

bs = Queue.Queue()

class func(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        global bs
        self.bs = bs
    def run(self):
        for i in range(10):
            #do something
            rtime = random.randint(1,10)
            time.sleep(rtime)
            #will exit!
            bs.put(1)

def test2(queue):
    for i in range(10):
        rtime = random.randint(1,10)
        time.sleep(rtime)
        queue.put(1)


if __name__ == '__main__':
    ts = []
    q  = Queue.Queue()
    for i in range(5):
        t = threading.Thread(target=test2,args=(q,))
        ts.append(t)
    for t in ts:
        t.start()
    for t in ts:
        t.join()
    print q.qsize()