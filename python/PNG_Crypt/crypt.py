import struct,os,sys

try:
	assert(sys.argv[1] and sys.argv[2])
except IndexError:
	print "Usage: %s image.png destfile" %sys.argv[0]
	exit(1)

f = open(sys.argv[1],'r')   
t = open(sys.argv[2],'rb')  
r = open("dest.ppm",'w')   

for i in range(3):
	r.write(f.readline())

tfilesize = os.path.getsize(sys.argv[2]) 
ffilesize = os.path.getsize(sys.argv[1])	
print tfilesize

def save_a_byte(n , line ):
	aline = line.split(' ')
	aline[3] = str( (int(aline[3] ) & 248 ) | ( n >> 5 & 7 ) )
	aline[7] = str( (int(aline[7] ) & 252 ) | ( n >> 2 & 3 ) )
	aline[11]= str( (int(aline[11]) & 248 ) | ( n >> 0 & 3 ) )
	line = ' '.join(aline)
	return line

for i in range(4):
	r.write( save_a_byte( int( (tfilesize >> (32-(i+1)*8) ) & 255 ) , f.readline() ) )

for i in range(ffilesize - 9 ):
	line = f.readline()
	if line == '':
		print 'Over~~~'
		break
	tdata=t.read(1)
	if tdata != '' :
		r.write( save_a_byte( struct.unpack('B', t.read(1) )[0] , line) )
	else:
		r.write( line )

	