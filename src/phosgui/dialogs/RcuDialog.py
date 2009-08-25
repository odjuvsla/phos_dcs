from PyQt4 import QtCore, QtGui
from RcuGeneralInfoWidget import *
from RcuRegistersWidget import *

class RcuDialog(QtGui.QDialog):
    """RCU dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(640, 480)
        
        self.initGeneralInfoFrame()
        self.initRegistersFrame()
        self.initRdoInfoFrame()
        self.initCloseButton()

        self.initWidgets()
    
    def initGeneralInfoFrame(self): 
        
        self.infoFrame = QtGui.QFrame(self)
        self.infoFrame.setGeometry(10, 10, self.width()/2 - 10, self.height() - 60)
        self.infoFrame.setFixedSize(self.width()/2 - 20, self.height()/4)
        self.infoFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.infoFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    
    def initRegistersFrame(self):
                
        self.regFrame = QtGui.QFrame(self)
        self.regFrame.setGeometry(self.width()/2 + 10, 10, self.width()/2 - 10, self.height() - 10)
        self.regFrame.setFixedSize(self.width()/2 - 20, self.height() - 20)
        self.regFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.regFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    def initRdoInfoFrame(self):
        
        
        self.rdoFrame = QtGui.QFrame(self)
        self.rdoFrame.setGeometry(10, self.infoFrame.y() + self.infoFrame.height() + 10, self.width()/2 - 10, self.height() - 60)
#        self.rdoFrame.setGeometry(10, 10 + self.infoFrame.height() + 10, self.width()/2 - 10, self.height() - 60)
        self.rdoFrame.setFixedSize(self.width()/2 - 20,  self.height()/4)
        self.rdoFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.rdoFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    def initCloseButton(self):
        
        print 'init close button'
        
    def initWidgets(self):
        
        self.genInfoWidget = RcuGeneralInfoWidget(self.infoFrame.width() - 10, self.infoFrame.height() - 10, self.infoFrame)
        self.regWidget = RcuRegistersWidget(self.regFrame.width() - 10, self.regFrame.height() - 10, self.regFrame)
#        self.rdoInfo = RcuRdoInfoWidget()
