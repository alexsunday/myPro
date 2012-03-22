#! /usr/bin/env python
#coding=utf-8

import re,pycurl,StringIO,urllib2,sys,random,urlparse
import chardet


CommonAgent = {"Agent": \
    ['Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0',
    #chrome 16.0.897.0
    'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.6 '\
    '(KHTML, like Gecko) Chrome/16.0.897.0 Safari/535.6',
    #Firefox 3.6.9
    'Mozilla/5.0 (Windows; U; Windows NT 6.0; en-GB; rv:1.9.2.9) ' \
    'Gecko/20100824 Firefox/3.6.9 ( .NET CLR 3.5.30729; .NET CLR 4.0.20506)',
    #Opera 11.11
    'Mozilla/5.0 (Windows NT 5.1; U; en; rv:1.8.1) '\
    'Gecko/20061208 Firefox/5.0 Opera 11.11'] }

CommonIgnoreList=[]

getLocalEncoding= lambda     : sys.getfilesystemencoding()
getPageEncoding = lambda txt : chardet.detect(txt)['encoding']
gl_getUserAgent = lambda     : random.choice(CommonAgent['Agent'])
getDomainFromURL= lambda url : urlparse.urlparse(url).netloc




def getPathURL(site):
    """"""
    assert site != ""
    tmp_li = [ 'bbs','admin','admins','manage','upfile', \
                'data','cx','db','js','images', \
                'image','conn','pic','' ]
    return  [ 'http://%s/%s/'%(site,el) for el in tmp_li ]
def all_thread_is_dead(test):
    pass
def updateDB(test):
    pass
def queue2list(test):
    pass
def getGlobalFileList(test):
    pass

def isChildDomain(child,parent):
    """如果child是parent的子域名，返回True，否则False，特殊的，相等也返回True
    同样注意参数，不要带http，不要带最后的斜杠"""
    s = '.*[.]' + parent + '$|^' + parent + '$'
    try:
        pattern = re.compile(s)
    except re.error:
        return False
    if re.match(pattern,child) is None :
        return False
    else:
        return True

def Baidu(word,page):
    """百度的，返回结果URL"""
    pattern = re.compile(r'\)" href="(https?://.+?)"')
    word = urllib2.quote(word)
    baidu_url = "http://www.baidu.com/s?wd=%s&pn=%d" %(word,(page-1)*10)
    txt = getPageContent(baidu_url)
    if txt is None:
        return None
    f = re.findall(pattern,txt)
    if not f : return None
    return f

def Google(word,page):
    """google,page,word"""
    pattern = re.compile(r'<h3 class="r"><a href="(https?://.*?)"')
    word = urllib2.quote(word)
    google_url = "http://www.google.com.hk/search?q=%s&ie=gbk&oe=utf-8&start=%d" \
                %(word,(page-1)*10)
    #print google_url
    txt = getPageContent(google_url)
    file('d:\\sunday\\hurl\\google.log','w').write(txt)
    if txt is None:
        return None
    f = re.findall(pattern,txt)
    if not f : return None
    return f
    
def getPageContent(url):
    assert url != ""
    c = pycurl.Curl()
    c.setopt(pycurl.CONNECTTIMEOUT,30)
    c.setopt(pycurl.TIMEOUT,60)
    #编码问题无处不在。
    c.setopt(pycurl.URL,url)
    c.setopt(pycurl.USERAGENT,gl_getUserAgent())
    s = StringIO.StringIO()
    c.setopt(pycurl.WRITEFUNCTION,s.write)
    c.setopt(pycurl.MAXREDIRS,0)
    c.setopt(pycurl.FOLLOWLOCATION,0)
    try:
        c.perform()
    except pycurl.error:
        return None
    return s.getvalue()

def getBaiduResultCount(word):
    """返回某个关键词目前在百度最多有多少条结果"""
    word = urllib2.quote(word)
    url = "http://www.baidu.com/s?wd=%s" %word
    #print url
    txt = getPageContent(url)
    txtEncoding = getPageEncoding(txt)
    assert txtEncoding != ""
    s = '>找到相关.+?([\d]{1}.*?)个</span>'
    s = s.decode('UTF-8').encode(txtEncoding)         
    pattern = re.compile(s)
    
    f   = re.findall(pattern,txt)
    if not f :
        return None
    if f[0] != '' and f[0].find(',') != -1:
        f[0] = f[0].replace(',','')
    return int(f[0])

def getGoogleResultCount(word):
    """返回某个关键词目前在百度最多有多少条结果"""
    word = urllib2.quote(word)
    url = "http://www.google.com.hk/search?q=%s&ie=gbk&oe=utf-8"%word
    txt = getPageContent(url)
    s = r'<div><div id=resultStats>.*?(\d.*?)[ ]'
    pattern = re.compile(s)
    
    f   = re.findall(pattern,txt)
    if not f :
        return None
    if f[0] != '' and f[0].find(',') != -1:
        f[0] = f[0].replace(',','')
    return int(f[0])
    
def get_word_domain(word):
    """baidu全部抓取，google获取前5页
    此函数太慢，需改善性能。或者改变操作方式
    """
    ret_li = []
    #for i in range(1,6):
        #tmp_li = Google(word,i)
        #for el in tmp_li:
            #ret_li.append(el)
    n = getBaiduResultCount(word)
    if n>1000:
        nCount = 100
    else:
        nCount = int(n/10)
    for i in range(1,nCount+1):
        tmp_li = Baidu(word,i)
        #print "Get baidu page %d"%i
        for el in tmp_li:
            ret_li.append(el)
    ret_li = map(getDomainFromURL,ret_li)
    return {}.fromkeys(ret_li).keys()

if __name__ == '__main__':
    #print Google(raw_input('hello>'),2)
    #print getGoogleResultCount(raw_input('>'))
    #li = get_word_domain(raw_input('>'))
    #for el in li:
        #print el
    print isChildDomain(raw_input('>'),'163.com')
    pass