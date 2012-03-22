# -*- coding: utf-8 -*-
"""
Created on Fri Dec 23 11:17:07 2011

@author: Administrator
"""

from Defines import gl_db
import sys

def main(arg,data):
    if arg == "-D":
        gl_db.del_Igsite(data)
    elif arg == "-F":
        li = open(data).readlines()
        for i,element in enumerate(li):
            li[i] = element.strip()
        gl_db.add_IgnoreURL(li)
        print "Ignore site in Database:"
        for site in gl_db.session.query(gl_db.IgnoreSite.SITE):
            print site[0]
    elif arg == "-a":
        gl_db.add_IgnoreURL([data,])
    else:
        print """Usage %s -D | -F | -a
        -D  del ignore site from database
        -F  add ignore sites from file
        -a  add site to database
        """%sys.argv[0]
        exit(2)

#用法xxx -D site /del site
#    xxx -F file /add from file
#    xxx -a site /add url
if __name__ =='__main__' :
    try:
        s = sys.argv[2]
    except IndexError,e:
        print """Usage %s -D | -F | -a
        -D  del ignore site from database
        -F  add ignore sites from file
        -a  add site to database
        """%sys.argv[0]
        exit(2)
    main(sys.argv[1],sys.argv[2])