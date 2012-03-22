#! /usr/bin/env python
#coding=utf-8

import threading,time,sys,Queue
from myScanner import getShell
from colorTerm import DCC

g_vars = {'plock':threading.Lock() }

def myPrint(args):
    global gl_var
    g_vars['plock'].acquire()
    localencoding = sys.getfilesystemencoding()
    try:
        print args.decode('UTF-8',errors = 'ignore').encode('cp936')
    except UnicodeEncodeError,e:
        pass
    #print args
    g_vars['plock'].release()


def test():
    for i in range(15):
        time.sleep(1)
        #print 'Threading.HELLO,WORLD'
        #myPrint('hello,world')
        
def main():
    ths = []
    EFlag = 0
    threadCount = 100
    for i in range(threadCount):
        t = threading.Thread(target = test)
        ths.append(t)
        t.start()
    while 1:
        for el in ths:
            if not el.isAlive():
                EFlag += 1
        if EFlag >= threadCount:
            print 'All Done,&& Exit'
            break
        else:
            print 'ALive threading count: %d ' %threading.activeCount()
            print 'ELFag is :%d'%EFlag
        time.sleep(1)

class test2():
    def __init__(self):
        print 'TEST STARTED......'
    def run(self):
        #[ ( url,ftype,code,note),......]
        test_list = [ ('http://www.hengbian.com/cx/','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/cx/images/','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/cx/index.html','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/cx/a.bsp','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/cx/facebook.asp','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/index.html','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/index.asp','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/dvbbs/','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/hello','normal','Webshell','TEST'),
                    ('http://www.hengbian.com/cx/index.asp','normal','Webshell','TEST')]
        queue=Queue.Queue()
        getShell(test_list,queue)
        if queue.qsize == 0:
            print 'Error'
        else:
            print queue.get()
            
if __name__ == '__main__':
    #test2().run()
    DCC.setColor(DCC.red)
    print 'Hello,world'
    DCC.resetColor()
