r=lambda a,b,c:(a<<5&255&224)|(b<<3&255&24)|(c&7)
w=lambda a,b,c,v:((a&248)|(v>>5),(b&252)|(v>>3&3),(c&248)|(v&7))

if __name__ == '__main__':
    print "Welcome !!!"
    for i in range(1,255):
        array = w(24,235,155,i)
        if i != r(array[0],array[1],array[2]):
            print 'error!'
            print i
    print 'Over~'