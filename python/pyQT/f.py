# -*- coding: utf-8 -*-
import sys
from PyQt4.QtGui import *
 
class TestWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self, windowTitle=u"A Simple Example for PyQt.")
        self.outputArea=QTextBrowser(self)
        self.helloButton=QPushButton(self.trUtf8("问候(&S)"), self)
        self.setLayout(QVBoxLayout())
        self.layout().addWidget(self.outputArea)
        self.layout().addWidget(self.helloButton)
 
        self.helloButton.clicked.connect(self.sayHello)
 
    def sayHello(self):
        yourName, okay=QInputDialog.getText(self, self.trUtf8("请问你的名字是?"), self.trUtf8(b"名字"))
        if not okay or yourName==u"": #用户没有输入名字，或者是点了取消
            self.outputArea.append(self.trUtf8("你好，陌生人！"))
        else:
            self.outputArea.append(self.trUtf8("你好，<b>%1</b>。").arg(yourName))
 
app=QApplication(sys.argv)
testWidget=TestWidget()
testWidget.show()
sys.exit(app.exec_())

