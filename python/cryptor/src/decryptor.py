'''
Created on 2012-3-28

@author: Sunday
'''
import struct
r=lambda a,b,c : (a<<5&255&224) | (b<<3&255&24) | (c&7)
w=lambda a,b,c,v: ((a&248)|(v>>5),(b&252)|(v>>3&3),(c&248)|(v&7))

def get_Byte(line):
    '''
    @author: 
    @param line:
    '''
    aline = line.split(' ')
    return r(int(aline[3]) , int(aline[7]) , int(aline[11]))

def decrypt(src_file , dst_file ):
    '''
    @author: 
    @param src:
    @param dst:
    '''
    src = open(src_file , 'r')
    dst = open(dst_file , 'wb')
    dst_len = 0
    for i in range(3):
        src.readline()
    for i in range(4):
        v = get_Byte(src.readline())
        dst_len |= ( v<< (32- (i+1)*8) )
    print 'dst file size: %d' %dst_len
    for i in range(dst_len):
        dst.write(struct.pack('B',get_Byte(src.readline())))
        
if __name__ == '__main__':
    decrypt('image2.ppm', 'dst2.jpg')