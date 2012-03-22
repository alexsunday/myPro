#coding=utf-8
"""
Created on Tue Dec 20 20:26:03 2011
@author: sunday
"""
import sys,threading,time,re,urllib2,httplib,urlparse,chardet,random,socket
#for database
from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import sessionmaker
from sqlalchemy.exc import IntegrityError
from sqlalchemy.orm.exc import NoResultFound


gl_var={ "sDeep":2,"DBFile":"D:\\Sunday\\hURL\\data\\global.db",
        "countN":10,"countM":100,"countO":500,"IgList":[],
        'DEBUG':True,"DBGFILE":".\\this.log","threadCount":1000,
        "Agent":['Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0',                                               #IE 7.0
            'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.6 (KHTML, like Gecko) Chrome/16.0.897.0 Safari/535.6',    #chrome 16.0.897.0
            'Mozilla/5.0 (Windows; U; Windows NT 6.0; en-GB; rv:1.9.2.9) Gecko/20100824 Firefox/3.6.9 ( .NET CLR 3.5.30729; .NET CLR 4.0.20506)',
            'Mozilla/5.0 (Windows NT 5.1; U; en; rv:1.8.1) Gecko/20061208 Firefox/5.0 Opera 11.11'],
        'AllSite':{},'pAllSite':threading.Lock(),  #访问AllSite一定要有一个锁
        'AvaURL':[],'pAvaURL':threading.Lock(),      #扫描结果置入
        'plock':threading.Lock(),'myPrintHandle':sys.stdout,
        "hURLList":[],'version':'0.0.1','logFile':'d:\\Sunday\\hURL\\other\scanner.log'}
Base = declarative_base()
#end for database
gl_db = None
#global lambda Function
getUserAgent = lambda : random.choice(gl_var['Agent'])
getPageEncoding = lambda txt : chardet.detect(txt)['encoding']
getPage      = lambda req : urllib2.urlopen(req).read()

class Test():
    """应用程序自检"""
    def __init__(self):
        pass
    def baidu_count(self):
        return True
        pass
    def google_count(self):
        return True
        pass
    def baidu_item(self):
        return True
        pass
    def google_item(self):
        return True
        pass
    def TEST(self):
        return True
        pass

class thread_manage():
    """线程管理类"""
    def __init__(self):
        #threading.Thread.__init__(self)
        global gl_var
        global gl_db
        self.db   = gl_db
        self.list = gl_var['AvaURL']
        self.lock = gl_var['pAvaURL']
    def checklist(self):
        """检查列表中是否存在东东"""
        if self.lock.acquire() and len(self.list) != 0:
            tmp_li = map(lambda x : [x,'normal'],self.list)
            self.list = []
            self.lock.release()     #因数据库操作较耗时，故清空后立即释放锁
            gl_db.add_AvaURL(tmp_li)
    def wait(self):
        """"""
        LiveThread = threading.activeCount()
        if LiveThread <10:
            print "Scanning will done..."
            return True
        else:
            print "Live thread count : %d"%LiveThread
            return False
        time.sleep(5)
    def run(self):
        while True:
            self.checklist()
            if self.wait():
                break

            
class myRobot(threading.Thread):
    """这玩意儿负责与搜索引擎打交道，给他一个word，
    它可以直接写数据库，如此则实现多线程很简单，但逻辑稍显复杂
    他也可以返回给你一坨的list，不过初期扫描比较耗时。"""
    def __init__(self,word,engine,deep):
        threading.Thread.__init__(self)
        self.word = word
        self.engine = engine
        self.deep = deep
        pass
    def run(self):
        if self.engine == 'baidu' :
            self.search_baidu()
        else:
            self.search_google()

    def search_baidu(self):
        baidu_li = [ "http://www.baidu.com",
                    "http://www.google.com",
                    "http://chengcheng.info"]
        return baidu_li
    def search_google(self):
        google_li = [ "http://www.baidu.com",
                    "http://www.google.com",
                    "http://chengcheng.info"]
        return google_li
#数据库实体类
class URLib(Base):
    __tablename__ = 'URLib'
    ID  = Column(Integer,primary_key=True)
    URL = Column(String,unique=True)
    Score=Column(Integer(2))
    def __init__(self,URL,Score):
        self.URL = URL
        self.Score = Score
    def __repr__(self):
        return "<URLib (%s,%s,%s)>" %(self.ID,self.URL,self.Score)

class hURL(Base):
    __tablename__ = 'hURL'
    ID = Column(Integer,primary_key=True)
    PATH= Column(String)
    FILENAME= Column(String)
    CODE= Column(String)
    FTYPE= Column(String)
    NOTE = Column(String)
    def __init__(self,PATH,FILENAME,CODE,FTYPE,NOTE):
        self.PATH = PATH                        #目录名
        self.FILENAME=FILENAME                  #文件名
        self.CODE = CODE                        #关键词
        self.FTYPE = FTYPE                      #匹配模式，正则regex，普通normal
        self.NOTE = NOTE                        #备注
    def __repr__(self):
        return "<hURL (%s,%s,%s,%s,%s,%s)>"  \
            %(self.ID,self.PATH,self.FILENAME,self.CODE,self.FTYPE,self.NOTE)

class AllSite(Base):
    __tablename__ = 'AllSite'
    ID = Column(Integer,primary_key = True)
    Site=Column(String,unique = True)
    STAT=Column(Integer(1))
    def __init__(self,Site,STAT):
        self.Site = Site
        self.STAT = STAT
    def __repr__(self):
        return "<AllSite (%s,%s,%s)>" %(self.ID,self.Site,self.STAT)

class AvailableURL(Base):
    __tablename__ = 'AvailableURL'
    ID  = Column(Integer,primary_key = True)
    URL = Column(String)
    STAT= Column(Integer(1))
    def __init__(self,URL,STAT):
        self.URL = URL
        self.STAT= STAT
    def __repr__(self):
        return "<AvailableURL (%s,%s,%s)>" %(self.ID,self.URL,self.STAT)

class IgnoreSite(Base):
    __tablename__ = 'IgnoreSite'
    ID = Column(Integer,primary_key=True)
    SITE = Column(String(1024),unique=True)
    def __init__(self,site):
        self.SITE = site
    def __repr__(self):
        return "<IgnoreSite (%s)>" %self.SITE

class myDatabase():
    """不要说了吧"""
    def __init__(self,DBFile):
        #self.engine = create_engine("sqlite:///%s"%DBFile,echo = True)
        self.engine = create_engine("sqlite:///%s"%DBFile)
        self.session = sessionmaker(bind=self.engine) ()
        Base.metadata.create_all(self.engine)
        self.IgnoreSite = IgnoreSite
        self.AllSite = AllSite
        self.hURL    = hURL
        self.AvaURL  = AvailableURL
    def add_AvaURL_one(self,url,STAT):
        """添加一行记录到AvaURL"""
        self.session.add(self.AvaURL(url,STAT))
    def add_AvaURL(self,AvaURL_li):
        """添加很多行到AvaURL"""
        for i,(url,STAT) in enumerate(AvaURL_li):
            try:
                self.add_AvaURL_one(url,STAT)
                self.commit()
            except IntegrityError:
                self.rollback()
    def add_hURL_one(self,path,filename,code,ftype,note):
        """添加一行记录到hURL"""
        self.session.add(self.hURL(path,filename,code,ftype,note))
    def add_hURL(self,hURL_li):
        """小黑们常用的URL"""
        for i,(path,filename,code,ftype,note) in enumerate(hURL_li):
            path = path.strip()
            filename = filename.strip()
            code = code.strip()
            if ftype != 'normal' and ftype != 'regex':
                ftype = 'normal'
            ftype = ftype.strip()
            try:
                self.add_hURL_one(path,filename,code,ftype,note)
                self.commit()
            except IntegrityError:
                #print "%s is already in IgnoreSite" %(s2)
                self.rollback()
    def get_hURL(self):
        """从数据库中获取hURL数据，以供其他函数组成三元组"""
        s = self.session
        li = []
        for el in s.query(self.hURL):
            li.append( [el.PATH,el.FILENAME,el.CODE,el.FTYPE,el.NOTE] )
        return li
    def add_URLib(self,URLib_li):
        pass
    def add_Site_one(self,site,STAT):
        """添加一行记录到allsite"""
        self.session.add(self.AllSite(site,STAT))
    def add_Site(self,Site_li):
        """列表添加，几乎照抄代码"""
        for i,(site,STAT) in enumerate(Site_li):
            s2 = site.strip()
            try:
                self.add_Site_one(s2,STAT)
                self.commit()
            except IntegrityError:
                #print "%s is already in IgnoreSite" %(s2)
                self.rollback()
    def get_AllSite(self):
        """getAllSite，其他函数从中筛选出来干活儿。"""
        s = self.session
        li = []
        for el in s.query(self.AllSite):
            li.append( [el.Site,el.STAT] )
        return li
    def add_Igurl(self,site):
        """单独添加一个忽略site，注意调用参数xxx.xxx，不要有http，也不要斜杠。
        木有返回，不能被其他人调用，相当于私有函数
        不会commit，也没有异常捕捉。"""
        if site.find(':') != -1:
            return None
        elif len(site) < 4: #最小的也要g.cn
            return None
        self.session.add(self.IgnoreSite(site))
    def del_Igsite(self,site):
        """从忽略列表中删除一个网站
        注意只要提供主机名和域名，不要http，也不要后面的/
        形如www.abs.com.cn或者chengcheng.info"""
        try:
            s = self.session.query(self.IgnoreSite).filter_by(SITE = site).one()
            self.session.delete(s)
            self.commit()
        except NoResultFound:
            self.session.rollback()
    def add_IgnoreURL(self,Ignore_li):
        """批量添加忽略网站"""
        for i,element in enumerate(Ignore_li):
            s2 = element.strip()
            try:
                self.add_Igurl(s2)
                self.commit()
            except IntegrityError:
                #print "%s is already in IgnoreSite" %(s2)
                self.rollback()

    def get_ignore(self):
        """返回所有的被忽略的site吧。"""
        s = self.session
        li = []
        for site in s.query(self.IgnoreSite.SITE):
            li.append(site)
        return li
    def commit(self):
        """提交事务"""
        self.session.commit()
    def rollback(self):
        """rollback"""
        self.session.rollback()

class mySiteRobot():
    """嗯，这个机器人主要和某一固定网站打交道，不能给他word
    init函数的参数形同：http(S)://xxx.xxxx.xxxx/，注意最后的斜杠
    座位threadingThread的子类，做线程运行"""
    def __init__(self,Site):
        pass
    def run(self):
        pass
    def getURL(self):
        siteURL=["http://chengcheng.info/abc.asp",
                 "http://chengcheng.info/abd.asp",
                 "http://chengcheng.info/abe.asp"]
        return siteURL
#public function
def siteScan(site):
    """爬站函数，主要是mySiteRobot的getURL函数"""
    pass
    
def getDomain(url):
    """函数从一个URL取得一个域名"""
    pattern = re.compile('https?://(.+?)/')
    f       = re.findall(pattern,url)
    if f :
        return f[0]
    else:
        return None

def stripDomain(url):
    """去除一个URL中的域名部分，保留纯地址部分
    妈逼的，一些黑客马儿中URL里面也会有小数点，坑爹！"""
    s = 'https?://([\w]|[.])+?/(.*$)'
    pattern = re.compile(s)
    m = re.findall(pattern,url)
    if m:
        return m[0][1]
    else:
        return None

def getURLtype(url):
    """知道这个URL是asp，还是php的
    这个随便写的，估计0.0.01都算不上。"""
    if isURL(url) == True:
        tmpType = url[-3:]
        if tmpType == 'asp':
            return tmpType
        elif tmpType == 'php':
            return tmpType
        elif tmpType == 'spx':
            return 'aspx'
        else:
            return 'unknown'
    else:
        return 'unknown'


def pushAvaURL(url):
    """将可用的结果push到全局变量里"""
    global gl_var
    if gl_var['pAvaURL'].acquire():
        gl_var['AvaURL'].append(url)
        gl_var['pAvaURL'].release()
    pass

def add_AvaURL_to_database():
    """将全局的变量结果导入数据库"""
    global gl_var
    global gl_db
    tmp_li = []
    if gl_var['pAvaURL'].acquire():
        #开始添加到数据库，已经获得锁了
        if not gl_var['AvaURL']:
            return False
        tmp_li = map(lambda x : [x,'normal'],gl_var['AvaURL'])
        gl_db.add_AvaURL(tmp_li)
        gl_var['AvaURL'] = []#清空
        gl_var['pAvaURL'].release()    

def getSeqSite():
    """得到一个排队的Site"""
    global gl_var
    if gl_var['pAllSite'].acquire():
        for (k,v) in gl_var['AllSite'].items():
            if v == 0 or v == '' :
                gl_var['AllSite'][k] = 1        #调节为扫描中
                gl_var['pAllSite'].release()
                return k
        gl_var['pAllSite'].release()
        return None
            

def isURL(url):
    """URL有效性判断，当前只处理http(s)，其他的均无效。"""
    s=r'https?.*'
    pattern = re.compile(s)
    f = re.findall(pattern,url)
    if f == None:
        return False
    else:
        return True

def isChildDomain(child,parent):
    """如果child是parent的子域名，返回True，否则False，特殊的，相等也返回True
    同样注意参数，不要带http，不要带最后的斜杠"""
    s = '\w*[.]' + parent + '$|^' + parent + '$'
    pattern = re.compile(s)    
    if re.match(pattern,child) is None :
        return False
    else:
        return True

def getIgnoreSite():
    """返回一些明显没指望的大站，返回一个不重复的List"""
    global gl_db
    tmp_li = gl_db.get_ignore()
    return map(lambda el:el[0],tmp_li)

def _makeREQ(url):
    """尽量重用一些函数，这个可以生成req，以后还可以免除被屏蔽"""
    req  = urllib2.Request(url)
    global gl_var
    req.add_header('User-Agent',getUserAgent())
    return req

def hURL2ThreeTuple(schema,site,hURL_li):
    """将从数据库中取出的hURL_li和域名合成三元组"""
    li = gl_var['hURLList']
    ret_li = []
    if schema == "" or ( schema != 'http' and schema != 'https') :
        schema = 'http://'
    if schema == 'http' or schema == 'https':
        schema += '://'
    if site == '' :
        return [ ('','','') ]
    for i,el in enumerate(li):
        if el[0][-1] != '/': el[0] += '/'  #path最后一位若不是斜杠，手动加上
        if el[0][0]  != '/': el[0] = '/' + el[0] #第一位也得是'/'
        ret_li.append( (schema + site + el[0] + el[1] ,el[2],el[3]) )
    return ret_li

def myDebug(txt):
    """测试工具，从全局变量gl_var中提取测试变量，将信息选择性的输出"""
    global gl_var
    if gl_var['DEBUG'] is True:
        try:
            file(gl_var['DBGFILE'],'w').write(txt)
        except IOError,e:
            sys.stderr.write(txt)
            


def add_hURL_From_File(file):
    """从文件中添加扫描规则，暂时只添加shell的。"""
    ftxt = open(file,'r')
    txt = ftxt.read()
    fileencoding = getPageEncoding(txt)
    txt  = ftxt.readlines()
    txt.pop(0)                                          #表头

    txt = map(lambda el: el.decode(fileencoding).encode('UTF-8'),txt)  
    txt = map(lambda el: el.split('\t') ,txt)           #分隔
    txt = map(lambda el: [el[0].strip(),el[1].strip(),
                el[2].strip(),el[3].strip()] , txt)  #去掉空格
    txt = map(lambda el: [el[2],
            unicode(el[1],'UTF-8','ignore'),
            unicode(el[0],'UTF-8','ignore'),
            'normal',unicode(el[3],'UTF-8','ignore') ],txt)
    global gl_db
    gl_db.add_hURL(txt)
    ftxt.close()
    
def UnitTest():
    """单元测试"""
    print "---------------TEST of Normal---------------"
    print getSeqSite()
    print getSeqSite()
    print "---------------Normal TEST Over---------------"

def DigShell(url,code,Ftype='normal'):
    """挖掘机主函数，指定URL，返回True or False
    v0.1已完成，需要增加新功能，包括mdb扫描、存在性扫描"""
    req = _makeREQ(url)
    def getTXT(req):
        try:
            f = urllib2.urlopen(req)
            if f.geturl() != url:
                return False                    
            #被转向了，估计有问题。解决部分误报
            return f.read()
        except urllib2.HTTPError,e:
            #print "urllib2.HTTPError!!!:",e
            #print e.read()
            return False
        except urllib2.URLError,e:
            #print "urllib2.URLError:",e
            return False
        except ValueError,e:
            #print "may be '%s' is not a URL" %req.get_full_url()
            return False
        except socket.error,e:                  
        #socket error，包括链接被重置等等
            return False
        except httplib.BadStatusLine,e:
            return False
        except httplib.IncompleteRead,e:
            #又是啥鸟鸡鸡故障
            return False
    def isShell(txt,Ftype,code):
        """如果使用正则表达式，就引用re，否则简单查找。
        fType可以的取值：normal、regex、isexists、"""
        if not txt: return txt
        encoding = getPageEncoding(txt)
        localencoding = sys.getfilesystemencoding()
        try:
            #统一转换成本地编码，转换过程可能会出错
            txt = txt.decode(encoding,errors='replace').encode(localencoding) 
        except TypeError,e:
            #printlog
            writeLog(e)
            return False
        if Ftype == 'regex':
            try:
                pattern = re.compile(code)
            except re.error,e:
                sys.stderr.write("网站：%s\n正则表达式%s\n错误"%(url,code))
                return False
            if re.match(pattern,txt) is None:
                return False
            else:
                return True
        elif Ftype == 'normal':
            if txt.find(code) == -1:
                return False
            return True
        elif Ftype == 'isexists' :
            """存在性扫描，此处是解决误报的关键之一"""
            upar   = urlparse.urlparse(url)
            rpath  = random.choice( ['xingad/neig.fup','/fuck.you','/fake.asppp',
                        'bucunzai/ddd','path/to/meiyou.de','/haha/mao.txt'] )
            newurl = urlparse.urljoin( upar.scheme + '://' + upar.netloc,rpath)
            txt1   = getTXT(_makeREQ(url))
            time.sleep(5)                   #此处为避免误报，先停几秒
            txt2   = getTXT(_makeREQ(newurl))
            if txt1 and txt2 :
                #选三个随机的地方测试，若一样的。
                if txt1 == txt2:
                    return False
                else:
                    return True
            elif txt1 != False and txt2 == False:
                return True
            else:
                return False
        else:
            raise ValueError,"Ftype cannot be %s" %Ftype            
    txt = getTXT(req)
    return isShell(txt,Ftype,code)

def writeLog(emsg):
    global gl_var
    f = open(gl_var['logFile'],'a')
    f.write(emsg)
    f.close()

def myPrint(args):
    global gl_var
    gl_var['plock'].acquire()
    localencoding = sys.getfilesystemencoding()
    try:
        print args.decode('UTF-8',errors = 'ignore').encode('cp936')
    except UnicodeEncodeError,e:
        pass
    #print args
    gl_var['plock'].release()

def Update_AllSite():
    """将扫描到的网站更新到全局变量"""
    global gl_var,gl_db
    tmpli = gl_db.get_AllSite()
    for el in tmpli:
        gl_var['AllSite'][el[0]] = el[1]        #待扫描网站列表
    return len(gl_var['AllSite'])

def init():
    """init() this package"""
    global gl_var                               #全局变量，储存程序运行的基础
    DBFile =  gl_var['DBFile']
    
    global gl_db 
    gl_db = myDatabase(DBFile)
    gl_var['IgList'] = getIgnoreSite()          #忽略站点列表
    gl_var['hURLList'] = gl_db.get_hURL()       #扫描规则列表
    Update_AllSite()                            #需扫描的网站
    
    reload(sys)
    #编码问题，此处设置系统默认编码，则使用管道重定向时不会出错，python默认ascii
    sys.setdefaultencoding('GBK')              
    socket.setdefaulttimeout(120)
    myPrint('欢迎使用WebShell扫描器\n版本:%s'%gl_var['version'])

#package main.
init()
if __name__ == "__main__":
    UnitTest()
    pass