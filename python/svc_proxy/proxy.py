#encoding : UTF-8
from twisted.internet import protocol,reactor

gl_dict_local = dict()
gl_dict_bank  = dict()
#{ '860000' : {} , '860001': {} }
#{ stan : protocol , stan1 : protocol1  }

#dict2 { '860000' : protocol , '860001':protocol2 }
def bank2local(bankid , stan , body , peer_protocol):
    gl_dict_bank[bankid] = peer_protocol
    gl_dict_local[bankid][stan].transport.write(body)
    gl_dict_local[bankid][stan].transport.loseConnection()
    gl_dict_local[bankid].remove(stan)

def local2bank(peer_protocol):
    bankid  = peer_protocol.bankid
    stan    = peer_protocol.stan
    body    = peer_protocol.body
    gl_dict_local[bankid][stan] = peer_protocol
    gl_dict_bank[bankid].transport.write(body)

