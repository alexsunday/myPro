'''
Created on 2012-3-26

@author: Sunday
'''
r=lambda a,b,c : (a<<5&255&224) | (b<<3&255&24) | (c&7)
w=lambda a,b,c,v: ((a&248)|(v>>5&7),(b&252)|(v>>2&3),(c&248)|(v&7))

if __name__ == '__main__':
    print "Welcome !!!"
    for i in range(1,255):
        array = w(123,189,201,i)
        if i != r(array[0],array[1],array[2]):
            print 'error!'
            print i
    print 'Over~'

def crypto(pngFile , destFile , newPngFile):
    '''
    
    @param pngFile:
    @param destFile:
    @param newPngFile:
    '''
    #转换png到ppm
    #判断文件大小，判断是否能加密
    #加密之
    #转换ppm格式为新的png格式，
    pass

def wByteLine(aline , value):
    '''
    Author     :    Sunday
    @param aline:    从ppm中读入的一行,list形式
    @param value:    需要写入的值
    @return:         newLine ,list形式，修改了第4、8、12的值
    '''
    aline[3] = (aline[3] & 248 ) | (value >> 5 & 7)
    aline[7] = (aline[7] & 252 ) | (value >> 2 & 3)
    aline[11]= (aline[11]& 248 ) | (value & 7 )

def rByteLine(aLine):
    '''
    Author:        Sunday
    @param aLine:  Line,list形式
    @return:       Value，被写入的值
    '''
    pass
    


