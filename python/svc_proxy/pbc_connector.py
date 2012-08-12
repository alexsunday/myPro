#encoding : utf-8
__author__ = 'Sunday'

from twisted.internet import protocol,reactor
from proxy import bank2local,local2bank

class pbc_server(protocol.Protocol):
    def connectionMade(self):
        self.buffer = ''
        pass
    def connectionLost(self, reason):
        pass
    def dataReceived(self, data):
        self.buffer += data
        self.stan   =  ''
        self.body   =  ''
        self.bankid =  ''
        bank2local(self.bankid , self.stan , self.body , )
        #TODO:#首先需要得到一个完整的数据包
        #然后取出数据包唯一识别序列号
        #而后将之想办法转发出去
class pbc_client(protocol.Protocol):
    def connectionMade(self):
        pass
    def connectionLost(self, reason=connectionDone):
        pass
    def sendData(self,data):
        self.transport.write(data)
