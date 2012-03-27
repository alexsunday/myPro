'''
Created on 2012-3-27

@author: Sunday
'''
import sys,os,struct

r=lambda a,b,c : (a<<5&255&224) | (b<<3&255&24) | (c&7)
w=lambda a,b,c,v: ((a&248)|(v>>5),(b&252)|(v>>3&3),(c&248)|(v&7))

def save_byte_line(v,line):
    '''
    @author:  
    @param v:
    @param line:
    '''
    aline = line.split(' ')
    a,b,c = int(aline[3]) , int(aline[7]) , int(aline[11])
    x,y,z = w(a,b,c,v)
    aline[3],aline[7],aline[11] = str(x),str(y),str(z)
    return ' '.join(aline)
    
def test(i,j,k,v):
    '''
    @author:  Sunday
    @param i:
    @param j:
    @param k:
    @param v:
    '''
    a,b,c = w(i,j,k,v)
    x     = r(a,b,c)
    return x == v

def cry_to_file(ppm_src, dst_file, tmp_ppm):
    '''
    @author:         Sunday
    @param ppm_src:
    @param dst_file:
    @param tmp_ppm:
    '''
    dst = open(dst_file,'rb')
    ppm = open(ppm_src,'r')
    tmp = open(tmp_ppm,'w')
    for i in range(3):
        tmp.write(ppm.readline())
    dst_len = os.path.getsize(dst_file)
    for i in range(4):
        v = int(dst_len>> (32-(i+1)*8) & 255)
        line = ppm.readline()
        tmp.write(save_byte_line(v,line))
    for i in range(dst_len):
        v = struct.unpack('B',dst.read(1))[0]
        line = ppm.readline()
        tmp.write( save_byte_line(v,line) )
    pass

if __name__ == '__main__':
    #cry_to_file(ppm , dst , tmp)
    cry_to_file('image.ppm','dst.jpg','aaa.ppm')
    print 'Over~'
