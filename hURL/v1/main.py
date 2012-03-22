#coding=utf-8
"""
注意使用多线程
@author: sunday
"""
import sys,os,threading,time
from Defines import *   

global gl_var

def main(word):
    """主函数,三层模型：
    N个线程扫描google、baidu、yahoo、bing等等，获得满足条件的网站Site；
    M个线程对每个符合条件的Site进行分析，抓取所有满足条件的URL
    O个线程对每个符合条件的URL进行分析，符合者放入URLib
    主函数中的代码考虑全部try起来！
    """
    Nts=[]
    Mts=[]
    Ots=[]
    UnitTest()
    r1 = myRobot(word,'baidu',gl_var['sDeep'])
    for i in range(gl_var['countN']):
        nT = threading.Thread(target = r1)
    
if __name__ == '__main__' :
    if Test().TEST() == False:
        print "test ERROR!"
        sys.exit(1)
    try:
        if len(sys.argv[1]) <=2:
            print "system argv ERROR!"
            sys.exit(2)
    except IndexError:
        print "system argv ERROR!"
        sys.exit(2)
    #Global TEST Over!

    word = sys.argv[1]
    try:
        main(word)
    except:
        session.rollback()