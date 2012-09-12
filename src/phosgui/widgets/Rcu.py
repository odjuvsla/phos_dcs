from PyQt4 import QtCore, QtGui
from PhosIdConverter import *
from FeePushButton import *
from TruPushButton import *
from RcuUpdateStatusPushButton import *
from RcuToggleOnOffPushButton import *
from RcuViewPushButton import *
from ModuleTurnOnButton import *
from ModuleTurnOffButton import *

class Rcu(QtGui.QWidget):
    """The RCU widget"""

    def __init__(self, moduleId, rcuId, parent=None):
        
        super(QtGui.QWidget, self).__init__(parent)
	print parent
        self.idConverter = PhosIdConverter()
        
        self.moduleId = moduleId
        self.rcuId = rcuId

        self.initFrame()
        self.initFeeLineSeperators()
        self.initFeeButtons()
        self.initTruButtons()
        self.initActionButtons()
        self.initRcuLabel()
        self.initConnections()

        self.setFixedHeight(110)
#        self.enableRcu(False)

    def emit_signal(self,*args):
        self.emit(QtCore.SIGNAL(args[0]), *args)
        
    def initFrame(self):

        self.rcuFrame = QtGui.QFrame(self)

        self.rcuFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.rcuFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.rcuFrame.setFixedWidth(650)
        self.rcuFrame.setFixedHeight(110)
        
    def initFeeLineSeperators(self):

        self.firstSep = QtGui.QFrame(self)
        self.firstSep.setGeometry(40, 10, 40, 40)
        self.firstSep.setFixedWidth(1)
        self.firstSep.setFixedHeight(90)
        self.firstSep.setFrameShadow(QtGui.QFrame.Raised)
        self.firstSep.setFrameShape(QtGui.QFrame.VLine)
        
        self.secondSep = QtGui.QFrame(self)
        self.secondSep.setGeometry(230, 10, 40, 40)
        self.secondSep.setFixedWidth(1)
        self.secondSep.setFixedHeight(90)
        self.secondSep.setFrameShadow(QtGui.QFrame.Raised)
        self.secondSep.setFrameShape(QtGui.QFrame.VLine)

        self.thirdSep = QtGui.QFrame(self)
        self.thirdSep.setGeometry(420, 10, 40, 40)
        self.thirdSep.setFixedWidth(1)
        self.thirdSep.setFixedHeight(90)
        self.thirdSep.setFrameShadow(QtGui.QFrame.Raised)
        self.thirdSep.setFrameShape(QtGui.QFrame.VLine)

        self.fourthSep = QtGui.QFrame(self)
        self.fourthSep.setGeometry(490, 10, 40, 40)
        self.fourthSep.setFixedWidth(1)
        self.fourthSep.setFixedHeight(90)
        self.fourthSep.setFrameShadow(QtGui.QFrame.Raised)
        self.fourthSep.setFrameShape(QtGui.QFrame.VLine)
        
    def initFeeButtons(self):
        

        self.feeButtons = [None]*CARDS_PER_BRANCH*2
	
        for i in range(CARDS_PER_BRANCH):
            n = i + CARDS_PER_BRANCH
            
# #            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)
#             feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_B, CARDS_PER_BRANCH - i)
#             self.feeButtons[n] = FeePushButton(self, feeId)
# #            self.feeButtons[n] = FeePushButton(self, n)
#             self.feeButtons[n].geometry().setX(50 + i*(self.feeButtons[n].geometry().width()-4))
#             self.feeButtons[n].geometry().setWidth(16)
#            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)


            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_B, CARDS_PER_BRANCH - i)
            index = feeId - self.rcuId*CARDS_PER_BRANCH*2 - self.moduleId*112

            self.feeButtons[index] = FeePushButton(self, feeId)
            
#            self.feeButtons[n] = FeePushButton(self, n)
	    self.feeButtons[index].setGeometry(50 + i*(self.feeButtons[index].geometry().width()-4), 0, 16, 110)
            #self.feeButtons[index].geometry().setLeft(50 + i*(self.feeButtons[index].geometry().width()-4))
            #self.feeButtons[index].geometry().setWidth(16)

        for i in range(CARDS_PER_BRANCH):
            
#            n = i + CARDS_PER_BRANCH
            n = i
            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)
            self.feeButtons[n] = FeePushButton(self, feeId)
            
            self.feeButtons[n].setGeometry(240 + i*(self.feeButtons[i].geometry().width()-4), 0, 16, 110)
#            self.feeButtons[n].geometry().setX(240 + i*(self.feeButtons[i].geometry().width()-4))
#            self.feeButtons[n].geometry().setWidth(16)

    def initTruButtons(self):
        
        self.truButtons = [None]*TRUS_PER_RCU
        for i in range(TRUS_PER_RCU):
            
            truId = self.idConverter.TruAbsoluteID(self.moduleId, self.rcuId, i)
            self.truButtons[i] = TruPushButton(self,truId)
            self.truButtons[i].setGeometry(435 + i*25, 0, 16, 110)
#            self.truButtons[i].geometry().setX(435 + i*25)

        
    def initActionButtons(self):
        
        self.rcuUpdateStatusButton = RcuUpdateStatusPushButton(self, self.moduleId, self.rcuId)
        buttonWidth = self.rcuUpdateStatusButton.geometry().width()
        buttonHeight = self.rcuUpdateStatusButton.geometry().height()
        self.rcuUpdateStatusButton.setGeometry(510, 10, buttonWidth, buttonHeight)
        
       # self.rcuUpdateStatusButton.geometry().setX(510)
       # self.rcuUpdateStatusButton.geometry().setY(10)

        self.rcuToggleButtonOn = RcuToggleOnOffPushButton(self, self.moduleId, self.rcuId, True)
        self.rcuToggleButtonOff = RcuToggleOnOffPushButton(self, self.moduleId, self.rcuId, False)

	self.rcuToggleButtonOn.setGeometry(510, 40, buttonWidth/2, buttonHeight)
	self.rcuToggleButtonOff.setGeometry(567, 40, buttonWidth/2, buttonHeight)
        
        #self.rcuViewButton = RcuViewPushButton(self, self.moduleId, self.rcuId)
        
        #self.rcuViewButton.geometry().setX(510)
        #self.rcuViewButton.geometry().setY(70)

    def initRcuLabel(self):
        
        self.rcuLabel = QtGui.QLabel(self)

        self.rcuLabel.setText("R C U " + str(self.rcuId))
        
        self.rcuLabel.setWordWrap(1)

        self.rcuLabel.setFixedSize(10, 90)
        
        self.rcuLabel.setGeometry(20, 10, 10, 90)
        self.rcuLabel.setFixedSize(10, 90)

    def initConnections(self):
        
        for i in range(CARDS_PER_RCU):
            self.connect(self.feeButtons[i], QtCore.SIGNAL("toggleFee"), self.emit_signal)
            self.connect(self.feeButtons[i], QtCore.SIGNAL("viewFee"), self.emit_signal)
        for i in range(TRUS_PER_RCU):
            self.connect(self.truButtons[i], QtCore.SIGNAL("toggleTru"), self.emit_signal)
            self.connect(self.truButtons[i], QtCore.SIGNAL("viewTru"), self.emit_signal)

        self.connect(self.rcuUpdateStatusButton, QtCore.SIGNAL("rcuUpdateStatus"), self.emit_signal)
        self.connect(self.rcuToggleButtonOn, QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
        self.connect(self.rcuToggleButtonOff, QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
      #  self.connect(self.rcuViewButton, QtCore.SIGNAL("viewRcu"), self.emit_signal)

    def updateFeeCard(self, branchId, feeId, state):
        
#        feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, branchId, feeId)
        feeId = feeId - 1 + branchId*CARDS_PER_BRANCH
        
        self.feeButtons[feeId].setState(state)
        self.update()
        
    def enableRcu(self, enable):

        if enable == True:
            print "enabling rcu.."
        else:
            print "disabling rcu.."
        for i in range(CARDS_PER_BRANCH*2):
            self.feeButtons[i].setEnabled(enable)

        for i in range(TRUS_PER_RCU):
            self.truButtons[i].setEnabled(enable)

        self.rcuUpdateStatusButton.setEnabled(enable)
        self.rcuToggleButtonOn.setEnabled(enable)
        self.rcuToggleButtonOff.setEnabled(enable)
       # self.rcuViewButton.setEnabled(enable)


class LogViewer(QtGui.QTextBrowser):
    
    def __init__(self, parent, moduleId):
        
        super(QtGui.QTextBrowser, self).__init__(parent)

	self.setGeometry(20, 500, 1070, 300)
        self.setFixedSize(1070, 300)
