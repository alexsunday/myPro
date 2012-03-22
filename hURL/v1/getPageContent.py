#! /usr/bin/env python
#coding=utf-8

import threading,Queue,os,time,sys,StringIO
import pycurl

def getShell(scanList,queue):
    """传入需要扫描的同一网站的URL若干，queue一枚
    一有结果就push到queue中,此处的scanlist应该保证同域名
    scanList形同[ ( url,ftype,code,note),......],且len(scanList) = x
    x = gl_var['PAGECOUNT_OF_CONNECTION']
    """
    for el in scanList:
        c = pycurl.Curl()
        s = StringIO.StringIO()
        #setopts......
        if el[1] == 'regex':
            """"""
            continue
        elif el[1] == 'isexists':
            continue
        elif el[1] == 'code':
            code = el[2]
            assert code != ''
            try:
                c.perform()
            except pycurl.error:
                continue
            httpcode = c.getinfo(pycurl.HTTP_CODE)
            if (httpcode-200) / 100 != 0 or s.len == 0:
                continue  #300?400?500?
            s.seek(0)
            if s.read().find(code) != -1:
                queue.put(el)#found it!
        else:
            continue
        #1、code判断，是否存在。
    pass

class Scanner(threading.Thread):
    """"""
    def __init__(self,word_li,queue):
        threading.Thread.__init__(self)
        self.list = word_li
        self.queue= queue
        self.wths = []
    def run(self):
        for el  in self.list:
            queue = Queue.Queue()
            t = WordScanner(el,queue)
            t.setDaemon(True)#False?
            self.wths.append( (t,el,queue) )
            t.star()
        while 1:
            if all_thread_is_dead:
                break
            for el in self.wths:
                if not el[2].empty :
                    self.queue.put(el[2].get())
            time.sleep(1)

class WordScanner(threading.Thread):
    """"""
    def __init__(self,word,queue):
        threading.Thread.__init__(self)
        self.queue = queue
        self.word = word
        self.mths = []
        pass
    def run(self):
        li_site = getSitelist(self.word)  #是否需要此处进行过滤
        for site  in li_site:
            queue = Queue.Queue()
            t = SiteScanner(site,queue)
            self.mths.append( (t,site,queue) )
            t.setDaemon(True)#False?
            t.start()
        while 1:
            if all_thread_is_dead:
                break
            for el in self.mths: 
                if not el[2].empty():
                    self.queue.put(el[2].get())
            time.sleep(1)

class SiteScanner(threading.Thread):
    """"""
    def __init__(self,site,queue):
        threading.Thread.__init__(self)
        self.queue = queue
        self.site  = site
        self.sths  = []
    def needIgnore(self):
        """此处对网站进行判断
        是不是那种随意返回状态码的网站。
        """
        c = pycurl.Curl()
        s = StringIO.StringIO()
        #c.setopt(......)
        try:
            c.perform()
        except pycurl.error:
            return True
        httpcode = c.getinfo(pycurl.HTTP_CODE)
        if (httpcode -200) / 100 != 0:
            return True
        return False
    def isScanned(self):
        """"""
        pass
    def run(self):
        if self.isScanned(self.site) or self.needIgnore():
            #threading.exit()

        url_li = getPathURL(self.site)
        queue  = Queue.Queue()
        for el in url_li:
            t = directoryScanner(el,queue)
            self.sths.append( (t,el,queue) )
            t.start()
        while 1:
            if all_thread_is_dead:
                break
            for el in self.sths: 
                if not el[2].empty():
                    self.queue.put(el[2].get())
            time.sleep(1)
            

class directoryScanner(threading.Thread):
    """"""
    def __init__(self,baseURL,queue):
        threading.Thread.__init__(self)
        self.baseURL   = directory
        self.queue     = queue
        #fileList形同:  [ (filename,ftype,code,note),(f2,ft2,c2,n2),......]
        self.fileList  = getGlobalFileList()
        self.scanList  = getScanList(self.baseURL,self.fileList)
        #线程数
        self.tCounts   = 0
        self.dths      = []
        self.eths      = []
    def spiltList(self):
        x = gl_var['PAGECOUNT_OF_CONNECTION']
        n = len(self.scanList) / x
        for i in range(n):
            self.dths.append( self.scanList[x*i: x*(i+1)])
        if n % x != 0:
            self.dths.append( self.scanList[-1* (len(a) % x): ] )
        self.tCounts = len(self.dths)        
    def run(self):
        """"""
        self.spiltList()
        for el in self.dths:
            queue = Queue.Queue()
            t     = threading.Thread(target = getShell,args = (el,queue) )
            self.eths.append( ( t,el,queue) )
            t.start()
        while 1:
            if all_thread_is_dead:
                break
            for el in self.sths: 
                if not el[2].empty():
                    self.queue.put(el[2].get())
            time.sleep(1)

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
