'''
Created on 2012-4-14

@author: Sunday
'''
import struct
def getUTF8(s):
    b=s.encode('UTF-8')
    li = map(lambda x: str(hex(struct.unpack('B',x)[0]))[2:].upper() , b)
    li.insert(0,'')
    return '='.join(li)

def init(name , tel ):
    cstr = getUTF8(name.decode('GB2312'))
    template = 'BEGIN:VCARD\nVERSION:2.1\nFN;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:%s\nN;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:%s\nTEL;CELL:%sEND:VCARD'%(cstr,cstr,tel)
    print template
    
if __name__ == '__main__':
    f=open('contacts.txt')
    for line in f:
        li = line.split(',')
        init(li[0],li[1])
    pass