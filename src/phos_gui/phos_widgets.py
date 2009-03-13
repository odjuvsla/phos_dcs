
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
        self.initConnections()

    def emit_signal(self, *args):
        print "emmiting signal: " + args[0]
        print "with ID: " + str(args[1])
        self.emit(QtCore.SIGNAL(args[0]), *args)
        
    def initRcus(self):

        self.rcuTopFrame = RcuTopFrame(self)
        self.rcuTopFrame.setGeometry(20, 0, 650, 40)
        self.rcus = [None]*RCUS_PER_MODULE
 
        for i in range(RCUS_PER_MODULE):
            
            self.rcus[i] = Rcu(self.moduleId, i, self)
            self.rcus[i].geometry().setX(20)
            self.rcus[i].geometry().setY(i*self.rcus[i].geometry().height() + self.rcuTopFrame.geometry().y() + self.rcuTopFrame.geometry().height())
    #        self.rcus[i].setEnabled(0)

    def initLogViewer(self):

        self.logViewer = LogViewer(self, self.moduleId)

    def initModuleIndicator(self):
        
        self.moduleIndicatorFrame = QtGui.QFrame(self)
        self.moduleIndicatorFrame.setGeometry(760, 0, 330, 100)
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
        self.moduleMainButtonFrame.setGeometry(760, 120, 330, 140)
        self.moduleMainButtonFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleMainButtonFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.moduleTurnOnButton = ModuleTurnOnButton(self.moduleMainButtonFrame, self.moduleId)
        self.moduleTurnOnButton.setGeometry(5, 5, 320, 60)
        
        self.moduleShutdownButton = ModuleTurnOffButton(self.moduleMainButtonFrame, self.moduleId)
        self.moduleShutdownButton.setGeometry(5, 75, 320, 60)
        
        self.moduleConfigurationButtonsFrame = QtGui.QFrame(self)
        self.moduleConfigurationButtonsFrame.setGeometry(760, 275, 330, 75)
        self.moduleConfigurationButtonsFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleConfigurationButtonsFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.modulePropertiesButton = ModulePropertiesButton(self.moduleConfigurationButtonsFrame, self.moduleId)
        self.modulePropertiesButton.setGeometry(5, 5, 320, 30)

        self.moduleConfigureElectronicsButton = ModuleConfigureElectronicsButton(self.moduleConfigurationButtonsFrame, self.moduleId)
        self.moduleConfigureElectronicsButton.setGeometry(5, 40, 320, 30)
        
        self.moduleTriggerButtonsFrame = QtGui.QFrame(self)
        self.moduleTriggerButtonsFrame.setGeometry(760, 370, 330, 75)
        self.moduleTriggerButtonsFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleTriggerButtonsFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.moduleEnableTriggerButton = ModuleEnableTriggerButton(self.moduleTriggerButtonsFrame, self.moduleId)
        self.moduleEnableTriggerButton.setGeometry(5, 5, 320, 30)

        self.moduleDisableTriggerButton = ModuleDisableTriggerButton(self.moduleTriggerButtonsFrame, self.moduleId)
        self.moduleDisableTriggerButton.setGeometry(5, 40, 320, 30)

    def initConnections(self):
        
        for i in range(RCUS_PER_MODULE):
            self.connect(self.rcus[i], QtCore.SIGNAL("toggleFee"), self.emit_signal)
            self.connect(self.rcus[i], QtCore.SIGNAL("viewFee"), self.emit_signal)

#             self.connect(self.rcus[i], QtCore.SIGNAL("toggleFee"), self.emit_signal)
#             self.connect(self.rcus[i], QtCore.SIGNAL("viewFee"), self.emit_signal)

            self.connect(self.rcus[i], QtCore.SIGNAL("toggleTru"), self.emit_signal)
            self.connect(self.rcus[i], QtCore.SIGNAL("viewTru"), self.emit_signal)

            self.connect(self.rcus[i], QtCore.SIGNAL("rcuUpdateStatus"), self.emit_signal)
            self.connect(self.rcus[i], QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
            self.connect(self.rcus[i], QtCore.SIGNAL("viewRcu"), self.emit_signal)
        
        self.connect(self.moduleTurnOnButton, QtCore.SIGNAL("turnOnModule"), self.emit_signal)
        self.connect(self.moduleShutdownButton, QtCore.SIGNAL("shutdownModule"), self.emit_signal)
        
        self.connect(self.modulePropertiesButton, QtCore.SIGNAL("showModuleProperties"), self.emit_signal)
        self.connect(self.moduleConfigureElectronicsButton, QtCore.SIGNAL("configureElectronicsModule"), self.emit_signal)
        
        self.connect(self.moduleEnableTriggerButton, QtCore.SIGNAL("enableTriggerModule"), self.emit_signal)
        self.connect(self.moduleDisableTriggerButton, QtCore.SIGNAL("disableTriggerModule"), self.emit_signal)

    def addLogString(self, logString):
                
#        self.logViewer.append(logString)
        self.logViewer.setText(self.logViewer.toPlainText() + logString)

    def updateFeeCard(self, feeId, state):
        
        print 'update card ' + str(feeId) + ' with state ' + str(state)
        module, rcu, branch, fee = self.idConverter.GetFeeLogicalIDs(feeId)

        self.rcus[rcu].updateFeeCard(branch, fee, state)
        self.update()

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
        self.initConnections()

        self.setFixedHeight(110)

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
            
            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)
            self.feeButtons[i] = FeePushButton(self, feeId)
            self.feeButtons[i].geometry().setX(50 + i*(self.feeButtons[i].geometry().width()-4))
            self.feeButtons[i].geometry().setWidth(16)

        for i in range(CARDS_PER_BRANCH):
            
            n = i + CARDS_PER_BRANCH

            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_B, i+1)
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
        
        self.rcuUpdateStatusButton = RcuUpdateStatusPushButton(self, self.moduleId, self.rcuId)
        
        self.rcuUpdateStatusButton.geometry().setX(510)
        self.rcuUpdateStatusButton.geometry().setY(10)

        self.rcuToggleButton = RcuToggleOnOffPushButton(self, self.moduleId, self.rcuId)

        self.rcuToggleButton.geometry().setX(510)
        self.rcuToggleButton.geometry().setY(40)
        
        self.rcuViewButton = RcuViewPushButton(self, self.moduleId, self.rcuId)
        
        self.rcuViewButton.geometry().setX(510)
        self.rcuViewButton.geometry().setY(70)

    def initRcuLabel(self):
        
        self.rcuLabel = QtGui.QLabel(self)

        self.rcuLabel.setText("R C U " + str(self.rcuId))
        
        self.rcuLabel.setWordWrap(1)

        self.rcuLabel.setFixedSize(30, 90)
        
        self.rcuLabel.geometry().setX(20)
        self.rcuLabel.geometry().setY(10)

    def initConnections(self):
        
        for i in range(CARDS_PER_RCU):
            self.connect(self.feeButtons[i], QtCore.SIGNAL("toggleFee"), self.emit_signal)
            self.connect(self.feeButtons[i], QtCore.SIGNAL("viewFee"), self.emit_signal)
        for i in range(TRUS_PER_RCU):
            self.connect(self.truButtons[i], QtCore.SIGNAL("toggleTru"), self.emit_signal)
            self.connect(self.truButtons[i], QtCore.SIGNAL("viewTru"), self.emit_signal)

        self.connect(self.rcuUpdateStatusButton, QtCore.SIGNAL("rcuUpdateStatus"), self.emit_signal)
        self.connect(self.rcuToggleButton, QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
        self.connect(self.rcuViewButton, QtCore.SIGNAL("viewRcu"), self.emit_signal)

    def updateFeeCard(self, branchId, feeId, state):
        
#        feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, branchId, feeId)
        feeId = feeId - 1 + branchId*CARDS_PER_BRANCH
        
        self.feeButtons[feeId].setState(state)
   
class LogViewer(QtGui.QTextBrowser):
    
    def __init__(self, parent, moduleId):
        
        super(QtGui.QTextBrowser, self).__init__(parent)

        self.geometry().setX(20)
        self.geometry().setY(500)
        self.setFixedSize(1070, 300)

class ConnectionSettingsModuleTabWidget(QtGui.QWidget):
    """Module tab for the connection settings dialog"""

    def __init__(self, moduleId, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)

        self.moduleId = moduleId
       
        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)
        
        self.initFrame()
        self.initConnections()
        
    def initFrame(self):
        
        self.mainFrame = QtGui.QFrame(self)
        self.mainFrame.setGeometry(10, 10, self.width() - 40, self.height() - 60)
        self.mainFrame.setFixedSize(self.width() - 40, self.height() - 60)
        self.mainFrame.setFrameShape(QtGui.QFrame.StyledPanel);
        self.mainFrame.setFrameShadow(QtGui.QFrame.Raised);

        self.initFeeNameLineEdits()
        self.initCheckBoxes()
        self.initLabels()

    def initFeeNameLineEdits(self):

        self.feeNameLayoutWidget = QtGui.QWidget(self.mainFrame)
        
#        self.feeNameLayoutWidget.setGeometry(QtCore.QRect(10, 40, self.tabWidth - 90, self.tabHeight - 120))
        self.feeNameLayoutWidget.setGeometry(QtCore.QRect(10, 40, 230, 310))
        self.feeServerNameLayout = QtGui.QVBoxLayout(self.feeNameLayoutWidget)
 
        self.feeServerRcuLineEdit = [None]*RCUS_PER_MODULE

        for i in range(RCUS_PER_MODULE):
            
            self.feeServerRcuLineEdit[i] = QtGui.QLineEdit(self.feeNameLayoutWidget)
            self.feeServerRcuLineEdit[i].setFixedSize(230, 30)
#            self.feeServerRcuLineEdit[i].setEnabled(0)
            self.feeServerNameLayout.addWidget(self.feeServerRcuLineEdit[i])
        
        self.feeServerTorLineEdit = QtGui.QLineEdit(self.feeNameLayoutWidget)
        self.feeServerTorLineEdit.setFixedSize(230, 30)
#        self.feeServerTorLineEdit.setEnabled(0)
        self.feeServerNameLayout.addWidget(self.feeServerTorLineEdit)

        self.feeNameLayoutWidget.setLayout(self.feeServerNameLayout)
        
    def initCheckBoxes(self):

        self.enabledLayoutWidget = QtGui.QWidget(self.mainFrame)
        self.enabledLayoutWidget.setGeometry(QtCore.QRect(250, 40, 120, 310))

        self.enabledLayout = QtGui.QVBoxLayout(self.enabledLayoutWidget)

        self.enabledRcuBoxes = [None]*RCUS_PER_MODULE

        for i in range(RCUS_PER_MODULE):
            
            self.enabledRcuBoxes[i] = QtGui.QCheckBox(self.enabledLayoutWidget)
            self.enabledRcuBoxes[i].setText("RCU " + str(i))
            self.enabledLayout.addWidget(self.enabledRcuBoxes[i])

        self.enabledTorBox = QtGui.QCheckBox(self.enabledLayoutWidget)
        self.enabledTorBox.setText("TOR")
        self.enabledLayout.addWidget(self.enabledTorBox)

        self.enabledLayoutWidget.setLayout(self.enabledLayout)
        
    def initLabels(self):
        
        self.feeNameLabel = QtGui.QLabel("FeeServer Names:", self.mainFrame)
        self.feeNameLabel.setGeometry(10, 15, 130, 20)
        
        self.enabledLabel = QtGui.QLabel("Enabled:", self.mainFrame)
        self.enabledLabel.setGeometry(250, 15, 60, 20)

    def initConnections(self):

        for i in range(RCUS_PER_MODULE):
            self.connect(self.enabledRcuBoxes[i], QtCore.SIGNAL("stateChanged"), self.feeServerRcuLineEdit[i].setEnabled)

    


class ConnectionSettingsBusyboxTabWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
       
        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)

    
        
