
import ctypes
from socket import *

myISO = ctypes.CDLL("d:\\EnterFinace\\bin\\iso8583.dll")
port  = 5002
HEADER='6007140000602200000000'
DAISHOU='0210703e00800ac18001164063651210000127190000000000007588894678115051022210011018813131353035313835323431313030323130323334303139393934343031343831323030303000315041474131333931323334353637382020202020202020203230303730362331353669b949011de99845'
BIZ = DAISHOU

def hexToByte(hexStr,Ztype):
    """arg:hexStr,Ztype(Zero type)
    return:string"""
    szOutBuf = ctypes.create_string_buffer('\0'*1024)
    phexStr = ctypes.c_char_p()
    phexStr.value = hexStr
    retLen = myISO.hexToByte(phexStr,ctypes.byref(szOutBuf),len(hexStr),Ztype)
    return szOutBuf[0:retLen]

def byteToHex(Bytes):
    '''
    @param Bytes:
    '''
    szOutBuf = ctypes.create_string_buffer('\0'*1024)
    pBytes = ctypes.c_char_p()
    pBytes.value = Bytes
    myISO.byteToHex(pBytes , ctypes.byref(szOutBuf) , len(Bytes))
    return szOutBuf.value

def main():
    '''
    Main Function!
    '''
    sock = socket(AF_INET,SOCK_STREAM)
    la   = ('' , port )
    sock.bind(la)
    sock.listen(100)
    sendData = hexToByte(HEADER + BIZ , 0)
    sendLen  = hex(len(sendData))[2:].zfill(4)
    sendLen  = hexToByte(sendLen,0)
    sendData = sendLen + sendData
    print 'Send:\n%s' % byteToHex(sendData)
    while(1):
        cs,ca = sock.accept()
        print 'Connection from %s : %d'%(ca[0],ca[1])
        recvData = cs.recv(2)
        cs.send(sendData)
        cs.close()

if __name__ == '__main__' :
    main()