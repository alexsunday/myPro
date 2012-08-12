#encoding : UTF-8
from twisted.internet import protocol,reactor
import ConfigParser
__author__ = 'Sunday'

class bank_proxy(protocol.Protocol):
    def __init__(self):
        self.buffer = ''
        self.stan   = ''
    def connectionMade(self):
        pass
    def connectionLost(self, reason):
        pass
    def dataReceived(self, data):
        self.buffer += data
        while len(self.buffer) >= 8:
            length = 0
            try:
                length = int(self.buffer[:8])
            except ValueError ,e:
                print '%s:%s protocol Error!\n'%(self.transport.getPeer().host , self.transport.getPeer().port)
                self.transport.loseConnection()
            body   = self.buffer[8:8+length]
            if len(body) == length :
                self.stan   = body[:24]
                self.body   = body[24:]
                self.buffer = ''
                pass
            elif len(body) > length:
                self.buffer = self.buffer[8+length : ]
            elif len(body) < length :
                break
class proxy_factory(protocol.ServerFactory):
    protocol = bank_proxy

def getPort(bank):
    cf = ConfigParser.ConfigParser()
    ini_file = 'proxy_config.ini'
    l1 = cf.read(ini_file)
    if l1:
        return cf.getint(bank , "port0")
    print 'Error read %s'%ini_file
    return  ""

def listen(port):
    reactor.listenTCP(port , proxy_factory())

if __name__ == '__main__':
    listen(getPort("ICBC"))
    reactor.run()
