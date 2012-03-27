'''
Created on 2012-3-27

@author: Sunday
'''
r=lambda a,b,c : (a<<5&255&224) | (b<<3&255&24) | (c&7)
w=lambda a,b,c,v: ((a&248)|(v>>5&7),(b&252)|(v>>2&3),(c&248)|(v&7))

def test(i,j,k,v):
    '''
    @author:  Sunday
    @param i:
    @param j:
    @param k:
    @param v:
    '''
    try:
        a,b,c = w(i,j,k,v)
        x     = r(a,b,c)
        print "(%d,%d,%d,%d),(%d,%d,%d),%d,%r" %(i,j,k,v,a,b,c,x,x==v)
    except KeyboardInterrupt:
        print 'Bye!'
        return


if __name__ == '__main__':
    for i in range(3,255):
        for j in range(3,255):
            for k in range(3,255):
                for v in range(3,255):
                    test(i,j,k,v)
    print 'Over~'

    