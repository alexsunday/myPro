import sys,struct,os

try:
	assert(sys.argv[1] and sys.argv[2])
except IndexError:
	print "Usage: %s image.png destfile" %sys.argv[0]
	exit(1)

def get_a_byte(line ):
	aline=line.split(' ')
	x = int(aline[3]) << 5 & 255 & 224
	y = int(aline[7]) << 3 & 255 & 24
	z = int(aline[11])<< 0 & 255 & 7
	return (x | y | z)
	
f = open(sys.argv[1],'r')   
r = open(sys.argv[2],'wb')

for i in range(3):
	f.readline()

tfilesize = 0
for i in range(4):
	n = get_a_byte(f.readline())
	tfilesize |= (n << (32-( (i+1)*8) ))

print tfilesize

for i in range(tfilesize):
	line = f.readline()
	r.write( struct.pack('B',get_a_byte(line) ) )

