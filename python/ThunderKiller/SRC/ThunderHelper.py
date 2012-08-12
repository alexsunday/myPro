'''
Created on 2012-4-22

@author: Sunday
'''
import win32serviceutil
import win32service
import win32event

class ThunderHelper(win32serviceutil.ServiceFramework):
    _svc_name_ = "ThunderHelper"
    _svc_display_name_ = "Thunder downloader helper"
    def __init__(self , args):
        win32serviceutil.ServiceFramework.__init__(self, args)
        self.hWaitStop = win32event.CreateEvent(None , 0 , 0 , None)
    def SvcStop(self):
        self.ReportServiceStatus(win32service.SERVICE_STOP_PENDING)
        win32event.SetEvent(self.hWaitStop)
    def SvcDoRun(self):
        win32event.WaitForSingleObject(self.hWaitStop , win32event.INFINITE)
        hf = open("D:\\a.txt" , "a")
        hf.write("hello,world")

if __name__ == '__main__':
    win32serviceutil.HandleCommandLine(ThunderHelper)