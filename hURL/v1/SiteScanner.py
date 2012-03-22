#coding=utf-8
"""
Created on Tue Dec 20 20:26:03 2011
@author: sunday
"""
import sys,threading,re,urllib2,urlparse


import Defines
from Defines import gl_var,gl_db
from Defines import myPrint 

class SiteScanner(threading.Thread):
    """挖掘机主类，传入站点域名，默认http协议
    全局变量获取hURL，匹配"""
    def __init__(self,schema,site):
        threading.Thread.__init__(self)
        self.site = site
        self.schema = schema
        #self.sltime = 5   #两次连接中的等待时间，用来规避服务器设定
    def run(self):
        #myPrint('将扫描网站：%s'%self.site)
        li = Defines.hURL2ThreeTuple(self.schema,self.site,gl_var['hURLList'])
        for el in li:
            #myPrint('Scanning :%s'%el[0])  #stdout的io太慢了。
            if Defines.DigShell(el[0],el[1],el[2]) == True:
                myPrint('%s\n%80s'%(el[0],'[OK]'))
                Defines.pushAvaURL(el[0])
    def getDict(self):
        """获得网站的部分目录，较快实现的只能是部分"""
        pass

def scanURL(url):
    """此函数扫描url，将获得的所有的可用的url返回list，https?://[^/]+$"""
    s = 'https?://[^/]+$'
    pattern = re.compile(s)  
    #如果是只有网址部分，且最后没有斜杠，则手工加上
    if re.match(pattern,url) != None:
        url = url + '/'
    try:
        req = Defines._makeREQ(url)
        txt = Defines.getPage(req)
        s   = """<a.+?href=["'](.+?)['"]"""
        pat = re.compile(s)
        f   = re.findall(pat,txt)
        if not f :
            return []
        for i,element in enumerate(f):
            if element.find('#') != -1:
                f[i] = url
            elif Defines.isURL(element) == None:
                #不符合URL规则，则是相对链接
                f[i] = url + f[i]
        return {}.fromkeys(f).keys()  #去除重复元素
    except urllib2.HTTPError,e:
        sys.stderr.write("ERROR!\n%s"%e)
        return None
    except urllib2.URLError,e:
        sys.stderr.write("ERROR!\n%s"%e)
        return None
    
def Baidu(word,page):
    """百度的，返回结果URL"""
    pattern = re.compile(r'\)" href="(https?://.+?)"')
    word = urllib2.quote(word)
    baidu_url = "http://www.baidu.com/s?wd=%s&pn=%d" %(word,(page-1)*10)
    req = Defines._makeREQ(baidu_url)
    txt = Defines.getPage(req)
    f = re.findall(pattern,txt)
    if not f : return None
    return f

def scanBaiduSite(word,page):
    """参数：关键词，第几页
    返回该页结果中所有的域名"""
    li = Baidu(word,page)  #他返回的是URL
    global gl_var
    #变成域名
    ret_li = map(lambda el: urlparse.urlparse(el).netloc,li)
    #过滤ignoreList列表中的网站
    tmp_li = []
    for element in ret_li:
        for site in gl_var['IgList']:
            if Defines.isChildDomain(element,site) == True: break
            tmp_li.append(element)
    return {}.fromkeys(tmp_li).keys()
    
def scanBaiduURL(word,page):
    return Baidu(word,page)

def scanBaiduAllSite(word):
    """多线程获取，结果最好能装入队列。
    线程数：如果关键词页面大于1000，取100，其余的取数量/10"""
    data = []
    lock = threading.Lock()
    def scanBaiduSite_Wrapper(word,page):
        """给百度站点扫描加个封装，以便被多线程使用。"""
        tmp_li = scanBaiduSite(word,page)
        myPrint("Baidu Scanning, page %s scanning finished" % page)
        tmp_li = map(lambda el:(el,0),tmp_li)
        if lock.acquire():
            data.extend(tmp_li)
            lock.release()
    n = getBaiduResultCount(word)
    print "Keyword baidu page number is %d" %n
    nCount = 0
    if n >= 1000:
        nCount =100
    else:
        nCount = int(n/10)
    ts = []
    for i in range(nCount):
        t = threading.Thread(target = scanBaiduSite_Wrapper,args = (word,i+1))
        ts.append(t)
    for t in ts:
        t.setDaemon(True)
        t.start()
    for i,t in enumerate(ts):
        t.join(timeout = 60)    #每个百度页面允许60秒下载时间
    gl_db.add_Site(data)

def getBaiduResultCount(word):
    """返回某个关键词目前在百度最多有多少条结果"""
    s = '>找到相关.+?([\d]{1}.*?)个</span>'
    s = s.decode('UTF-8').encode('GB2312')         #本文件UTF-8编码，百度网页以GB2312编码
    pattern = re.compile(s)
    word = urllib2.quote(word)
    url = "http://www.baidu.com/s?wd=%s" %word
    req = Defines._makeREQ(url)
    txt = Defines.getPage(req)
        
    f   = re.findall(pattern,txt)
    if not f :
        return None
    if f[0] != '' and f[0].find(',') != -1:
        f[0] = f[0].replace(',','')
    return int(f[0])


def KeywordScanner():
    """执行扫描进程，此函数扫描关键词"""
    try:
        myPrint('输入需要扫描的关键词，回车确认') #此处用户键入控制字符的处理
        word = ''
        word = raw_input()
        if len(word) == 0:
            raise ValueError
        scanBaiduAllSite(word)
    except KeyboardInterrupt:
        print "Bye!"
        exit(0)
    except EOFError,e:
        exit(0)
    except ValueError:
        print "ERROR for your input!"
        print 'Bye'
        exit(0)

def Start_Scanner(threadnumber):
    """启动多个SiteScanner线程开始扫描"""
    try:
        myPrint('确认开始扫描\n按Ctrl-C退出，按任意键继续... ... ... ...')
        raw_input()
    except KeyboardInterrupt:
        print "Bye!"
        exit(0)
    ts = []    #线程容器

    for i in range(threadnumber):
        tsite = Defines.getSeqSite()
        if not tsite : continue
        t     = SiteScanner('http',tsite)
        ts.append(t)
    if not ts:
        myPrint("All site scanner finished.\nexiting......")
        exit(0)

    for t in ts:
        try:
            t.setDaemon(True)
            t.start()
        except ValueError,e:                #匹配模式错误
            pass

    A=Defines.thread_manage()
    A.run()
    
if __name__ == '__main__':
    """执行单元测试"""
    print '------------------------begin------------------------'
    
    KeywordScanner()
    n = Defines.Update_AllSite()
    Start_Scanner(n - 10)
    print '------------------------over!------------------------'
