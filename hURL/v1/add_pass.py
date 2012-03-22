# -*- coding: utf-8 -*-
"""
Created on Sat Dec 24 15:24:03 2011

@author: sunday
"""
import re

def main():
    f = open("www.csdn.net.sql")
    f2 =open("pass.sql",'w')
    while True:
        tmps = f.readline()
        tmpli = re.split(re.compile('\s+#\s+'),tmps)
        if len(tmpli) != 3:
            continue
        if tmps == "":
            break
        sql = "insert into pass(user,pass,email) values('%s','%s','%s');\n" %(tmpli[0],tmpli[1],tmpli[2])
        f2.write(sql)

if __name__ == "__main__":
    main()
    
        