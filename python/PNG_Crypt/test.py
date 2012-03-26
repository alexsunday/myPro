from socket import *
import sys,os,struct,threading,select

def proc_(sock):
	readdr = sock.getpeername()[0]
	s2 = socket(AF_INET,SOCK_STREAM,0)
	s2.connect(readdr,52222)
	

if __name__ == '__main__' :
	s=socket(AF_INET,SOCK_STREAM,0)
	la=('',52222)
	s.bind(la)
	s.listen(SOMAXCONN)
	ts = []
	while True:
		infds,outfds,errfds = select( [s,] ,[] , [] , 5) # wait 5 sec'
		if infds:
			clsock , cla = s.accept()
			t = threading.Thread(target = proc_, args = (clsock,) )
			ts.append(t)
			t.start()
		print "wait ... ... "
	for t in ts:
		t.join()
	s.close()
			