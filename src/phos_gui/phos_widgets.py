
import sys

from PyQt4 import QtCore, QtGui
from PhosConst import *
from phos_buttons import *
from phos_utilities import *

class ModuleTabWidget(QtGui.QWidget):
    """Module tab widget"""
    
    def __init__(self, moduleId, parent=None):
        
        super(QtGui.QWidget, self).__init__(parent)

        self.moduleId = moduleId

        self.idConverter = PhosIdConverter()

        self.initRcus()
        self.initLogViewer()
        self.initModuleIndicator()
        self.initModuleButtons()

    def initRcus(self):

        self.rcuTopFrame = RcuTopFrame(self)
        self.rcuTopFrame.setGeometry(20, 0, 650, 40)
        self.rcus = [None]*RCUS_PER_MODULE
 
        for i in range(RCUS_PER_MODULE):
            
            self.rcus[i] = Rcu(self.moduleId, i, self)
            self.rcus[i].geometry().setX(20)
            self.rcus[i].geometry().setY(i*self.rcus[i].geometry().height() + self.rcuTopFrame.geometry().y() + self.rcuTopFrame.geometry().height())

    def initLogViewer(self):

        self.logViewer = LogViewer(self, self.moduleId)

    def initModuleIndicator(self):
        
        self.moduleIndicatorFrame = QtGui.QFrame(self)
        self.moduleIndicatorFrame.setGeometry(720, 0, 330, 100)
        self.moduleIndicatorFrame.setFrameShadow(QtGui.QFrame.Sunken)
        self.moduleIndicatorFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleIndicatorFrame.setFixedWidth(330)
        self.moduleIndicatorFrame.setFixedHeight(100)

        picFile = "graphics/5_mods_" + str(self.moduleId) + "_on.png"
        image = QtGui.QImage(picFile)
        self.moduleIndicator = QtGui.QLabel(self.moduleIndicatorFrame)
        self.moduleIndicator.setPixmap(QtGui.QPixmap.fromImage(image))
        self.moduleIndicator.setGeometry(5, 5, 320, 90)

    def initModuleButtons(self):
        
        self.moduleMainButtonFrame = QtGui.QFrame(self)
        self.moduleMainButtonFrame.setGeometry(720, 120, 330, 145)
        self.moduleMainButtonFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleMainButtonFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.moduleTurnOnButton = QtGui.QPushButton(self.moduleMainButtonFrame)
        self.moduleTurnOnButton.setGeometry(5, 5, 320, 60)
        self.moduleTurnOnButton.setText("Turn On Module Electronics")
        
        self.moduleShutdownButton = QtGui.QPushButton(self.moduleMainButtonFrame)
        self.moduleShutdownButton.setGeometry(5, 80, 320, 60)
        self.moduleShutdownButton.setText("Shutdown Module Electronics")
        
        self.moduleConfigurationButtonsFrame = QtGui.QFrame(self)
        self.moduleConfigurationButtonsFrame.setGeometry(720, 280, 330, 75)
        self.moduleConfigurationButtonsFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleConfigurationButtonsFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.modulePropertiesButton = QtGui.QPushButton(self.moduleConfigurationButtonsFrame)
        self.modulePropertiesButton.setGeometry(5, 5, 320, 30)
        self.modulePropertiesButton.setText("Module Properties")

        self.moduleConfigureElectronicsButton = QtGui.QPushButton(self.moduleConfigurationButtonsFrame)
        self.moduleConfigureElectronicsButton.setGeometry(5, 40, 320, 30)
        self.moduleConfigureElectronicsButton.setText("Configure Electronics")
        
        self.moduleConfigurationButtonsFrame = QtGui.QFrame(self)
        self.moduleConfigurationButtonsFrame.setGeometry(720, 370, 330, 75)
        self.moduleConfigurationButtonsFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleConfigurationButtonsFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.modulePropertiesButton = QtGui.QPushButton(self.moduleConfigurationButtonsFrame)
        self.modulePropertiesButton.setGeometry(5, 5, 320, 30)
        self.modulePropertiesButton.setText("Module Properties")

        self.moduleConfigureElectronicsButton = QtGui.QPushButton(self.moduleConfigurationButtonsFrame)
        self.moduleConfigureElectronicsButton.setGeometry(5, 40, 320, 30)
        self.moduleConfigureElectronicsButton.setText("Configure Electronics")
        
        
class RcuTopFrame(QtGui.QFrame):
    """Top frame for the RCUs"""

    def __init__(self, parent):
        
        super(QtGui.QFrame, self).__init__(parent)

        self.initSeparatorLines()
        
        self.initTextLabels()
        
        self.setFrameShadow(QtGui.QFrame.Raised)
        self.setFrameShape(QtGui.QFrame.StyledPanel)
        self.setFixedWidth(650)
        self.setFixedHeight(40)
        
    def initSeparatorLines(self):

        self.firstSep = QtGui.QFrame(self)
        self.firstSep.setGeometry(40, 0, 40, 40)
        self.firstSep.setFixedWidth(1)
        self.firstSep.setFixedHeight(38)
        self.firstSep.setFrameShadow(QtGui.QFrame.Raised)
        self.firstSep.setFrameShape(QtGui.QFrame.VLine)
        
        self.secondSep = QtGui.QFrame(self)
        self.secondSep.setGeometry(230, 0, 40, 40)
        self.secondSep.setFixedWidth(1)
        self.secondSep.setFixedHeight(40)
        self.secondSep.setFrameShadow(QtGui.QFrame.Raised)
        self.secondSep.setFrameShape(QtGui.QFrame.VLine)

        self.thirdSep = QtGui.QFrame(self)
        self.thirdSep.setGeometry(420, 0, 40, 40)
        self.thirdSep.setFixedWidth(1)
        self.thirdSep.setFixedHeight(40)
        self.thirdSep.setFrameShadow(QtGui.QFrame.Raised)
        self.thirdSep.setFrameShape(QtGui.QFrame.VLine)

        self.fourthSep = QtGui.QFrame(self)
        self.fourthSep.setGeometry(490, 0, 40, 40)
        self.fourthSep.setFixedWidth(1)
        self.fourthSep.setFixedHeight(40)
        self.fourthSep.setFrameShadow(QtGui.QFrame.Raised)
        self.fourthSep.setFrameShape(QtGui.QFrame.VLine)

    def initTextLabels(self):

        self.feeALabel = QtGui.QLabel("Front End Cards Branch A", self)
        self.feeALabel.setGeometry(65, 10, 160, 20)
        self.feeBLabel = QtGui.QLabel("Front End Cards Branch B", self)
        self.feeBLabel.setGeometry(255, 10, 160, 20)
        self.truLabel = QtGui.QLabel("TRU A/B", self)
        self.truLabel.setGeometry(430, 10, 60, 20)
        self.actionsLabel = QtGui.QLabel("Actions", self)
        self.actionsLabel.setGeometry(550, 10, 60, 20)


class Rcu(QtGui.QWidget):
    """The RCU widget"""

    def __init__(self, moduleId, rcuId, parent=None):
        
        super(QtGui.QWidget, self).__init__(parent)

        self.idConverter = PhosIdConverter()
        
        self.moduleId = moduleId
        self.rcuId = rcuId

        self.initFrame()
        self.initFeeLineSeperators()
        self.initFeeButtons()
        self.initTruButtons()
        self.initActionButtons()
        self.initRcuLabel()

        self.setFixedHeight(110)

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
            
            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i)
            self.feeButtons[i] = FeePushButton(self, feeId)
            self.feeButtons[i].geometry().setX(50 + i*(self.feeButtons[i].geometry().width()-4))
            self.feeButtons[i].geometry().setWidth(16)

        for i in range(CARDS_PER_BRANCH):
            
            n = i + CARDS_PER_BRANCH

            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_B, i)
            self.feeButtons[n] = FeePushButton(self, feeId)
            self.feeButtons[n].geometry().setX(240 + i*(self.feeButtons[i].geometry().width()-4))
            self.feeButtons[i].geometry().setWidth(16)

    def initTruButtons(self):
        
        self.truButtons = [None]*TRUS_PER_RCU
        for i in range(TRUS_PER_RCU):
            
            truId = self.idConverter.TruAbsoluteID(self.moduleId, self.rcuId, i)
            self.truButtons[i] = TruPushButton(self,truId)
            self.truButtons[i].geometry().setX(435 + i*25)

        
    def initActionButtons(self):
        
        self.rcuUpdateStatusButton = RcuUpdateStatusPushButton(self, self.rcuId)
        
        self.rcuUpdateStatusButton.geometry().setX(510)
        self.rcuUpdateStatusButton.geometry().setY(10)

        self.rcuToggleButton = RcuToggleOnOffPushButton(self, self.rcuId)

        self.rcuToggleButton.geometry().setX(510)
        self.rcuToggleButton.geometry().setY(40)
        
        self.rcuViewButton = RcuViewPushButton(self, self.rcuId)
        
        self.rcuViewButton.geometry().setX(510)
        self.rcuViewButton.geometry().setY(70)

    def initRcuLabel(self):
        
        self.rcuLabel = QtGui.QLabel(self)

        self.rcuLabel.setText("R C U " + str(self.rcuId))
        
        self.rcuLabel.setWordWrap(1)

        self.rcuLabel.setFixedSize(30, 90)
        
        self.rcuLabel.geometry().setX(20)
        self.rcuLabel.geometry().setY(10)

class LogViewer(QtGui.QTextBrowser):
    
    def __init__(self, parent, moduleId):
        
        super(QtGui.QTextBrowser, self).__init__(parent)

        self.geometry().setX(20)
        self.geometry().setY(500)
        self.setFixedSize(1030, 300)
       
