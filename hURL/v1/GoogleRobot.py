#coding=utf-8
"""
Created on Sat Dec 24 09:21:18 2011

@author: sunday
"""

import sys,os,threading,time,sqlobject,re,Queue,urllib2,urlparse,socket
import Defines
from Defines import getIgnoreSite,gl_var,gl_db

class GoogleRobot(threading.Thread):
    def __init__(self,word):
        threading.Thread.__init__(self)
        self.word = word
        self.Count = 0 #结果数目，getCount的
        self.lock = threading.Lock()
        self.URL  = []
        self.Site = []
        self.Agents =['Mozilla/5.0 (Windows NT 5.1; rv:8.0) Gecko/20100101 Firefox/9.0',
                      'Konqueror/3.0-rc4; (Konqueror/3.0-rc4; i686 Linux;;datecode)',
                      'Lynx/2.8.5rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/0.8.12',
                      'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)',
                      'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1)']
        self.Agent = self.Agents[3] #IE 7.0
        self.urlpattern = re.compile('<h3 class="r"><a href="(https?://.+?)"')        
        pass
    def _makeREQ_(self,word,page):
        """尽量重用一些函数，这个可以生成req，以后还可以免除被屏蔽
        word = urllib2.quote(word)
        http://www.google.com/search?q=%E7%8E%8B%E6%9C%9D%E9%A9%AC%E6%B1%89&ie=utf-8&oe=utf-8&aq=t&rls=org.mozilla:zh-CN:official&client=firefox-a       
        http://www.google.com/search?q=%E7%8E%8B%E6%9C%9D%E9%A9%AC%E6%B1%89&hl=en&newwindow=1&client=firefox-a&hs=GgH&rls=org.mozilla:zh-CN:official&prmd=imvns&ei=0S31Tt2dHpDbiAKEg7CYDQ&start=70&sa=N        
        http://www.google.com/search?q=%E4%B8%AD%E6%96%87&start=30&sa=N&ie=utf-8
        """
        word = urllib2.quote(word)
        url  = 'http://www.google.com.hk/search?q=%s&start=%d&sa=N&ie=gbk' %(word,(page-1)*10)  
        req  = urllib2.Request(url)
        req.add_header('User-Agent',self.Agent)
        return req
    def _getTXT_(self,req):
        """鉴于HTTP获取中经常出现异常和错误，此处一并处理
        若此函数写得好，可变为全局的。"""
        try:
            return urllib2.urlopen(req).read()
        except urllib2.HTTPError,e:
            return ""
        except urllib2.URLError,e:
            return ""
        except socket.error,e:
            return ""            
    def run(self):
        """重写，做线程运行的函数"""
        pass
    def getCount(self):
        """得到关键词的结果数量，页面太过变态，简体和繁体，还有英文，我要哭了！"""
        if self.word ==None or len(self.word) == 0: return 0
        req = self._makeREQ_(self.word,1)
        txt = self._getTXT_(req)
        if txt == "": return 0
        pattern = re.compile('<div id=resultStats>About(.+?)result<nobr>')
        f = re.findall(pattern,txt)
        print f
        if not f: return 0
        print self.word
        print f[0]
    def getURL(self,page=1):
        """得到结果URL，page为页面，不存在时返回最后一页，不判断"""
        req = self._makeREQ_(self.word,page)
        txt = self._getTXT_(req)
        f   = re.findall(self.urlpattern,txt)
        if not f:
            return None
        return f
    def getSite(self,page=1):
        """同上，只是返回域名，并去除了一些明显的大站"""
        url_li = self.getURL(page)
        if url_li == None :return None
        tmp_li = map(lambda url:urlparse.urlparse(url).netloc,url_li)
        ret_li = []
        for element in tmp_li:
            for site in gl_var['IgList']:
                if Defines.isChildDomain(element,site) == True: break
                ret_li.append(element)
        return {}.fromkeys(ret_li).keys()
    def getURLAll(self):
        """返回所有的URL，考虑使用多线程
        因为google结果数量函数编写受阻，故此处暂取10页。"""
        nPage = 10
        pass
    def getSiteAll(self):
        """返回所有的站点列表"""
        pass
    
def init():
    """模块初始化，这个文件应该不需要什么初始化"""
    pass

def UnintTest():
    """执行单元测试"""
    word = raw_input("请输入关键词\n")
    r1 = GoogleRobot(word)
    li = r1.getSite(page=3)
    print li
    
init()
if __name__ == '__main__' :
    UnintTest()