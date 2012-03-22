#! /usr/bin/env python
#coding=utf-8

import threading,Queue,time,StringIO,re,thread
import pycurl
from gl_vars import gl_getUserAgent,gl_var,getGlobalFileList,getScanList
from gl_vars import getSitelist
import gl_vars
from gl_func import getPathURL,updateDB,queue2list
from colorTerm import DCC

def getShell(scanList,queue,exitFlag):
    """传入需要扫描的同一网站的URL若干，queue一枚
    一有结果就push到queue中,此处的scanlist应该保证同域名
    scanList形同[ ( url,ftype,code,note),......],且len(scanList) = x
    x = gl_var['PAGECOUNT_OF_CONNECTION']
    """
    c = pycurl.Curl()
    for el in scanList:
        gl_vars.myPrint("Scanning: %s"%el[0])
        c.setopt(pycurl.CONNECTTIMEOUT,30)
        c.setopt(pycurl.TIMEOUT,60)
        #编码问题无处不在。
        c.setopt(pycurl.URL,el[0].encode(gl_vars.getLocalEncoding()))
        c.setopt(pycurl.USERAGENT,gl_getUserAgent())
        s = StringIO.StringIO()
        c.setopt(pycurl.WRITEFUNCTION,s.write)
        c.setopt(pycurl.MAXREDIRS,0)
        c.setopt(pycurl.FOLLOWLOCATION,0)
        #setopts......
        if el[1] == 'regex':
            """"""
            try:
                pattern = re.compile('.*' + el[2])
            except re.error:
                continue
            try:
                c.perform()
            except pycurl.error:
                continue
            m = re.match(pattern,s.getvalue())
            if m is None:
                continue
            else:
                queue.put(el)
        elif el[1] == 'isexists':
            try:
                c.perform()
            except pycurl.error:
                continue
            httpcode = c.getinfo(pycurl.HTTP_CODE)
            if (httpcode - 200) / 100 != 0:
                continue
            if s.len != 0:
                queue.put(el)
        elif el[1] == 'normal':  #code
            code = el[2]
            assert code != ''
            try:
                c.perform()
            except pycurl.error:
                continue
            httpcode = c.getinfo(pycurl.HTTP_CODE)
            #gl_vars.myPrint("Scanning %s,result:%s"%(el[0],httpcode))
            if (httpcode-200) / 100 != 0 or s.len == 0:
                continue  #300?400?500?
            txt = gl_vars.netpage2localencode(s.getvalue())
            if txt.find(code) != -1:   #encoding......
                queue.put(el)#found it!
                #gl_vars.myPrint("Found %s" %el[0])
        else:
            continue
    c.close()
    exitFlag.put(1)

class Scanner(threading.Thread):
    """"""
    def __init__(self,word_li,queue):
        threading.Thread.__init__(self)
        self.list = word_li
        self.queue= queue
        self.wths = []
    def run(self):
        EFlag = 0
        for el  in self.list:
            queue = Queue.Queue()
            t = WordScanner(el,queue)
            t.setDaemon(True)#False?
            self.wths.append( (t,el,queue) )
            t.star()
        threadCount = len(self.wths)
        while 1:
            for el in self.wths:
                if not el[0].isAlive() :
                    EFlag += 1
                if not el[2].empty() :
                    self.queue.put( el[2].get())
            if EFlag >= threadCount:
                break
            time.sleep(1)

class WordScanner(threading.Thread):
    """"""
    def __init__(self,word,queue,exitFlag):
        threading.Thread.__init__(self)
        self.queue = queue
        self.eflag = exitFlag
        self.word  = word
        self.mths  = []
        pass
    def runSingle(self):
        """单线程版本"""
        li_site = getSitelist(self.word)
        queue   = Queue.Queue()
        cflag   = Queue.Queue()
        for site in li_site:
            t = SiteScanner(site,queue,cflag)
            self.mths.append( (t,site,queue) )
            t.start()
            t.join()
            if not queue.empty():
                qsize = queue.qsize()
                for i in range(qsize):
                    self.queue.put(queue.get())
            time.sleep(0.5)
    def runthreads(self):
        #是否需要此处进行过滤
        li_site = getSitelist(self.word)
        #print "将启动%d个线程进行扫描"%(len(li_site))
        queue   = Queue.Queue()
        cflag   = Queue.Queue()
        for site  in li_site:
            t = SiteScanner(site,queue,cflag)
            self.mths.append( (t,site,queue) )
            t.setDaemon(True)#False?
            t.start()
        while 1:
            if cflag.qsize() >= len(self.mths)-1:
                break
            if not queue.empty():
                qsize = queue.qsize()
                for i in range(qsize):
                    self.queue.put(queue.get())
            time.sleep(1)
        self.eflag.put(1)
    def run(self):
        self.runSingle()

class SiteScanner(threading.Thread):
    """"""
    def __init__(self,site,queue,exitFlag):
        threading.Thread.__init__(self)
        self.queue = queue
        self.site  = site
        self.sths  = []
        self.eflag = exitFlag
    def needIgnore(self):#是否随意返回状态码
        """此处对网站进行判断
        是不是那种随意返回状态码的网站。
        """
        c = pycurl.Curl()
        s = StringIO.StringIO()
        c.setopt(pycurl.CONNECTTIMEOUT,30)
        c.setopt(pycurl.TIMEOUT,60)
        #编码问题无处不在。
        c.setopt(pycurl.URL,'http://' + self.site + '/adn.d.akn/hello.you')
        c.setopt(pycurl.USERAGENT,gl_getUserAgent())
        c.setopt(pycurl.WRITEFUNCTION,s.write)
        c.setopt(pycurl.MAXREDIRS,0)
        c.setopt(pycurl.FOLLOWLOCATION,0)
        try:
            c.perform()
        except pycurl.error:
            return True
        httpcode = c.getinfo(pycurl.HTTP_CODE)
        print httpcode
        if (httpcode -200) / 100 == 0:
            return True
        if s.len == 0:
            return True
        return False
    def isScanned(self): #是否已被扫描
        """"""
        if self.site in gl_var['finished']:
            return True
        return False
    def run(self):
        if self.isScanned() or self.needIgnore():
            #threading.exit()
            self.eflag.put(1)
            thread.exit()
        print 'SiteScanner init'
        url_li = getPathURL(self.site)
        print url_li
        queue  = Queue.Queue()
        cflags = Queue.Queue()
        for el in url_li:
            t = directoryScanner(el,queue,cflags)
            t.setDaemon(True)
            self.sths.append( (t,el,queue) )
            t.start()
        while 1:
            if cflags.qsize() == len(self.sths):
                break
            if not queue.empty():
                qsize = queue.qsize()
                for i in range(qsize):
                    self.queue.put(queue.get())
            time.sleep(1)
        self.eflag.put(1)
            
class directoryScanner(threading.Thread):
    """"""
    def __init__(self,baseURL,queue,exitFlag):
        threading.Thread.__init__(self)
        self.baseURL   = baseURL
        self.queue     = queue
        #fileList形同:  
        #[ (filename,ftype,code,note),(f2,ft2,c2,n2),......]
        self.fileList  = getGlobalFileList()
        #scanList形同:  
        #[ (URL,ftype,code,note),(U2,ft2,c2,n2),......]        
        self.scanList  = getScanList(self.baseURL,self.fileList)
        self.ceflag    = Queue.Queue()
        self.eflag     = exitFlag
        self.dths      = []
        self.eths      = []
    def spiltList(self):
        x = gl_var['PAGECOUNT_OF_CONNECTION']
        n = len(self.scanList) / x
        for i in range(n):
            self.dths.append( self.scanList[x*i: x*(i+1)])
        if n % x != 0:
            self.dths.append( \
                self.scanList[-1* (len(self.scanList) % x): ] ) 
        #gl_vars.myPrint("Len of threads needed %d"%len(self.dths))
    def run(self):
        """"""
        self.spiltList()
        queue = Queue.Queue()
        #print self.dths
        for el in self.dths:
            t = threading.Thread( \
                target = getShell,args = (el,queue,self.ceflag) )
            t.setDaemon(True)
            self.eths.append( ( t,el,queue) )
            t.start()
        while 1:
            if self.ceflag.qsize() >= len(self.eths):
                #print "succefully exit"
                break
            if not queue.empty():
                qsize = queue.qsize()
                for i in range(qsize):
                    self.queue.put(queue.get())
            time.sleep(1)
        #thread exit.
        self.eflag.put(1)

def main():
    tmpli = file('').readlines()
    queue = Queue.Queue()
    t     = Scanner(tmpli,queue)
    t.start()
    while 1:
        time.sleep(5)
        Avali = queue2list(queue)
        updateDB(Avali)#运行时动态改变此处，数据库和全局变量一并刷新
        del Avali
        if not t.isAlive():
            break  #Finished,&& exit@!

def UnintTEST():
    #directoryTEST()
    #SiteTest()
    WordTest()
    
def directoryTEST():
    """"""
    q = Queue.Queue()
    ef= Queue.Queue()
    t = directoryScanner('http://www.tjzhuozhong.com/',q,ef)
    t.setDaemon(True)
    t.start()
    while 1:
        if ef.qsize() == 1:
            break
        time.sleep(5)
        if not q.empty():
            qsize = q.qsize()
            for i in range(qsize):
                print q.get()

def SiteTest():
    """"""
    #site    = 'www.tjzhuozhong.com'
    #site    = 'www.sxyuan.com'
    site    = 'www.shengjiamei.net'
    queue   = Queue.Queue()
    ceflag  = Queue.Queue()
    t       = SiteScanner(site,queue,ceflag)
    t.setDaemon(True)
    t.start()
    while 1:
        if not queue.empty():
            qsize = queue.qsize()
            for i in range(qsize):
                DCC.setColor(DCC.red)
                print queue.get()[0]
                DCC.resetColor()
        time.sleep(5)
        if ceflag.qsize() == 1:
            break
    
def WordTest():
    word   = raw_input('>')
    queue  = Queue.Queue()
    ceflag = Queue.Queue()
    t      = WordScanner(word,queue,ceflag)
    t.setDaemon(True)
    t.start()
    while 1:
        time.sleep(2)
        if ceflag.qsize() == 1:
            if not queue.empty():
                qsize = queue.qsize()
                for i in range(qsize):
                    r = queue.get()[0]
                    f = open('D:\\sunday\\hurl\\result.log','w')
                    f.write(r+'\n')
                    f.close()
                    DCC.setColor(DCC.red)
                    print r
                    DCC.resetColor()            
            break

if __name__ == '__main__':
    UnintTEST()
    pass