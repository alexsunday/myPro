#encoding:UTF-8
'''
Created on 2012-5-6

@author: Sunday
'''
import sys,Image

def pornImageDec(file):
    '''
    @param file: file path ->type : string
    '''
    img = Image.open(file).convert('YCbCr')
    w,h = img.size
    data= img.getdata()
    cnt = 0
    for ycbcr in data:
        y,cb,cr = ycbcr
        #print 'y:[%d] \tCb:[%d] \tCr:[%d]' %( y , cb , cr)
        if 86 <= cb <= 117 and 140 <= cr <= 168:
            cnt += 1
    if cnt > w*h*0.3:
        return True
    return False

def unitTest():
    '''
    ��Ԫ����~
    '''
    if pornImageDec(sys.argv[1]):
        print 'PORN IMAGE!'
    else:
        print 'Normal image!'
    
if __name__ == '__main__':
    unitTest()