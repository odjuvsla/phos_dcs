
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
#        self.enableRcu(False, 0)
#        self.setEnabled(False)
        
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
#            self.rcus[i].setEnabled(0)

    def initLogViewer(self):

        self.logViewer = LogViewer(self, self.moduleId)

    def initModuleIndicator(self):
        
        self.moduleIndicatorFrame = QtGui.QFrame(self)
        self.moduleIndicatorFrame.setGeometry(760, 0, 330, 100)
        self.moduleIndicatorFrame.setFrameShadow(QtGui.QFrame.Sunken)
        self.moduleIndicatorFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleIndicatorFrame.setFixedWidth(330)
        self.moduleIndicatorFrame.setFixedHeight(100)

        picFile = "../graphics/5_mods_" + str(self.moduleId) + "_on.png"
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
        self.logViewer.verticalScrollBar().setValue(self.logViewer.verticalScrollBar().maximum())
        
    def updateFeeCard(self, feeId, state):
        
        print 'update card ' + str(feeId) + ' with state ' + str(state)
        module, rcu, branch, fee = self.idConverter.GetFeeLogicalIDs(feeId)
        self.rcus[rcu].updateFeeCard(branch, fee, state)
#         if fee == 13:

#             self.rcus[rcu].updateFeeCard(branch, 2, state)

#         if fee == 14:
#             self.rcus[rcu].updateFeeCard(branch, 1, state)

#         if fee == 1:
#             self.rcus[rcu].updateFeeCard(branch, 14, state)

#         if fee == 2:
#             self.rcus[rcu].updateFeeCard(branch, 13, state)

        self.update()
        
    def updateRcu(self, rcuId, state):

        module, rcu = self.idConverter.GetRcuLogicalIDs(rcuId)
        
        for i in range(CARDS_PER_BRANCH):
            print 'update card ' + str(i) + ' with state ' + str(state[i])
            self.rcus[rcu].updateFeeCard(BRANCH_A, i+1, state[i])
        
        for j in range(CARDS_PER_BRANCH):
            print 'update card ' + str(j) + ' with state ' + str(state[j + CARDS_PER_BRANCH])
            self.rcus[rcu].updateFeeCard(BRANCH_B, j+1, state[j+CARDS_PER_BRANCH])
            
    def enableRcu(self, enable, rcuId):
        
        self.rcus[rcuId].enableRcu(enable)
#        print "enabling rcu.."
#        self.emit(QtCore.SIGNAL("rcuUpdateStatus"), "rcuUpdateStatus", rcuId)
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

        self.feeALabel = QtGui.QLabel("Front End Cards Branch B", self)
        self.feeALabel.setGeometry(65, 10, 160, 20)
        self.feeBLabel = QtGui.QLabel("Front End Cards Branch A", self)
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
            self.feeButtons[index].geometry().setX(50 + i*(self.feeButtons[index].geometry().width()-4))
            self.feeButtons[index].geometry().setWidth(16)

        for i in range(CARDS_PER_BRANCH):
            
#            n = i + CARDS_PER_BRANCH
            n = i
            feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)
            self.feeButtons[n] = FeePushButton(self, feeId)
            self.feeButtons[n].geometry().setX(240 + i*(self.feeButtons[i].geometry().width()-4))
            self.feeButtons[n].geometry().setWidth(16)

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

        self.rcuToggleButtonOn = RcuToggleOnOffPushButton(self, self.moduleId, self.rcuId, True)
        self.rcuToggleButtonOff = RcuToggleOnOffPushButton(self, self.moduleId, self.rcuId, False)

        self.rcuToggleButtonOn.geometry().setX(510)
        self.rcuToggleButtonOn.geometry().setY(40)

        self.rcuToggleButtonOff.geometry().setX(567)
        self.rcuToggleButtonOff.geometry().setY(40)
        
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
        self.connect(self.rcuToggleButtonOn, QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
        self.connect(self.rcuToggleButtonOff, QtCore.SIGNAL("rcuToggleOnOff"), self.emit_signal)
        self.connect(self.rcuViewButton, QtCore.SIGNAL("viewRcu"), self.emit_signal)

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
        self.rcuViewButton.setEnabled(enable)


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

        self.enabledLayoutWidget.setLayout(self.enabledLayout)
        
    def initLabels(self):
        
        self.feeNameLabel = QtGui.QLabel("FeeServer Names:", self.mainFrame)
        self.feeNameLabel.setGeometry(10, 15, 130, 20)
        
        self.enabledLabel = QtGui.QLabel("Enabled:", self.mainFrame)
        self.enabledLabel.setGeometry(250, 15, 60, 20)

    def initConnections(self):

        for i in range(RCUS_PER_MODULE):
            self.connect(self.enabledRcuBoxes[i], QtCore.SIGNAL("stateChanged"), self.feeServerRcuLineEdit[i].setEnabled)

class StatusTabWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)
        self.setEnabled(False)

class ConnectionSettingsBusyboxTabWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
       
        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)

class ReadoutRegionSettingsWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        
        self.setFixedSize(width, height)

        self.initLabels()

        self.initSpinBoxes()
#        self.initDetailedSelectionButton()

    def initLabels(self):
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)

        self.fromLabel = QtGui.QLabel("From:", self)
        self.fromLabel.setGeometry(45, 40, 30, 20)

        self.toLabel = QtGui.QLabel("To:", self)
        self.toLabel.setGeometry(self.fromLabel.x() + self.fromLabel.width() + 35, self.fromLabel.y(), 30, 20)

        self.xLabel = QtGui.QLabel("X:", self)
        self.xLabel.setGeometry(15, 65, 10, 20)

        self.zLabel = QtGui.QLabel("Z:", self)
        self.zLabel.setGeometry(self.xLabel.x(), self.xLabel.y() + self.xLabel.height() + 5, self.xLabel.width(), self.xLabel.height())
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)
        

    def initSpinBoxes(self):

        self.xSpinboxFirst = QtGui.QSpinBox(self)
        self.xSpinboxFirst.setGeometry(self.fromLabel.x(), 65, 40, 20)
        self.xSpinboxFirst.setMinimum(0)
        self.xSpinboxFirst.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.xSpinboxLast = QtGui.QSpinBox(self)
        self.xSpinboxLast.setGeometry(self.toLabel.x(), self.xSpinboxFirst.y(), self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.xSpinboxLast.setValue(N_XCOLUMNS_MOD - 1)
        self.xSpinboxLast.setMinimum(0)
        self.xSpinboxLast.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.zSpinboxFirst = QtGui.QSpinBox(self)
        self.zSpinboxFirst.setGeometry(self.xSpinboxFirst.x(), self.xSpinboxFirst.y() + self.xSpinboxFirst.height() + 5, self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.xSpinboxFirst.setMinimum(0)
        self.xSpinboxFirst.setMaximum(N_ZROWS_MOD - 1)
        
        self.zSpinboxLast = QtGui.QSpinBox(self)
        self.zSpinboxLast.setGeometry(self.xSpinboxLast.x(), self.zSpinboxFirst.y(), self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.zSpinboxLast.setValue(N_ZROWS_MOD - 1)
        self.zSpinboxLast.setMinimum(0)
        self.zSpinboxLast.setMaximum(N_ZROWS_MOD - 1)

    def getReadOutRegion(self):
        
        xFirst = self.xSpinboxFirst.value()
        xLast = self.xSpinboxLast.value()
        zFirst = self.zSpinboxFirst.value()
        zLast = self.zSpinboxLast.value()                
        
        return xFirst, xLast, zFirst, zLast

    def setFirstX(self, x):

        self.xSpinboxFirst.setValue(x)

    def setLastX(self, x):

        self.xSpinboxLast.setValue(x)

    def setFirstZ(self, z):

        self.zSpinboxFirst.setValue(z)

    def setLastZ(self, z):

        self.zSpinboxLast.setValue(z)

    def initDetailedSelectionButton(self):

        print 'test'
        

class ReadoutSamplesSettingsWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        
        self.setFixedSize(width, height)

        self.initLabels()
        self.initSpinBoxes()
        
    def initLabels(self):


        self.titleLabel = QtGui.QLabel("Number of samples:", self)
        self.titleLabel.setGeometry(10, 15, 130, 20)

        self.preLabel = QtGui.QLabel("Pre-samples:", self)
        self.preLabel.setGeometry(15, 45, 80, 20)

        self.samplesLabel = QtGui.QLabel("Samples:", self)
        self.samplesLabel.setGeometry(self.preLabel.x() + self.preLabel.width() + 15, self.preLabel.y(), 50, 20)
        

    def initSpinBoxes(self):

        self.preSpinbox = QtGui.QSpinBox(self)
        self.preSpinbox.setGeometry(self.preLabel.x(), 65, 60, 20)
        self.preSpinbox.setMinimum(0)
        self.preSpinbox.setMaximum(MAX_ALTRO_PRESAMPLES)
        self.preSpinbox.setValue(11)
        
        self.samplesSpinbox = QtGui.QSpinBox(self)
        self.samplesSpinbox.setGeometry(self.samplesLabel.x(), self.preSpinbox.y(), self.preSpinbox.width(), self.preSpinbox.height())
        self.samplesSpinbox.setValue(81)
        self.samplesSpinbox.setMinimum(0)
        self.samplesSpinbox.setMaximum(MAX_ALTRO_SAMPLES)

    def getSamplesSettings(self):
        
        nSamples = self.samplesSpinbox.value()
        nPreSamples = self.preSpinbox.value()

        return nPreSamples, nSamples

    def setPreSamples(self, nPreSamples):

        self.preSpinbox.setValue(nPreSamples)

    def setSamples(self, nSamples):

        self.samplesSpinbox.setValue(nSamples)


class ReadoutZeroSuppressionWidget(QtGui.QWidget):

    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.initLabels()
        self.initSpinBoxes()
        self.initZsSparseSelectors()
        
    def initLabels(self):

        self.zsLabel = QtGui.QLabel("Zero Suppression:", self)
        self.zsLabel.setGeometry(10, 15, 130, 20)

        self.thresholdLabel = QtGui.QLabel("Threshold:", self)
        self.thresholdLabel.setGeometry(15, 45, 80, 20)

        self.offsetLabel = QtGui.QLabel("Offset:", self)
        self.offsetLabel.setGeometry(self.thresholdLabel.x() + self.thresholdLabel.width() + 15, self.thresholdLabel.y(), 50, 20)

    def initSpinBoxes(self):

        self.thresholdSpinbox = QtGui.QSpinBox(self)
        self.thresholdSpinbox.setGeometry(self.thresholdLabel.x(), 65, 60, 20)
        self.thresholdSpinbox.setMinimum(0)
        self.thresholdSpinbox.setMaximum(1023)
        self.thresholdSpinbox.setValue(1)
        
        self.offsetSpinbox = QtGui.QSpinBox(self)
        self.offsetSpinbox.setGeometry(self.offsetLabel.x(), self.thresholdSpinbox.y(), self.thresholdSpinbox.width(), self.thresholdSpinbox.height())
        self.offsetSpinbox.setValue(2)
        self.offsetSpinbox.setMinimum(0)
        self.offsetSpinbox.setMaximum(1023)

    def initZsSparseSelectors(self):

        self.zsCheckBox = QtGui.QCheckBox(self)
        self.zsCheckBox.setText("Enable Zero Suppression")
        self.zsCheckBox.setGeometry(self.thresholdSpinbox.x(), self.thresholdSpinbox.y() + self.thresholdSpinbox.height() + 8, 200, 20)

        self.sparseCheckBox = QtGui.QCheckBox(self)
        self.sparseCheckBox.setText("Enable Sparse Readout")
        self.sparseCheckBox.setGeometry(self.thresholdSpinbox.x(), self.zsCheckBox.y() + self.zsCheckBox.height() + 8, 200, 20)

    def isZeroSuppressionOn(self):
        
        return self.zsCheckBox.isChecked()

    def isSparseReadout(self):
        
        return self.sparseCheckBox.isChecked()

    def getZSThreshold(self):
        
        return self.thresholdSpinbox.value()

    def getOffset(self):
        
        return self.offsetSpinbox.value()

    def setZeroSuppression(self, status):

        self.zsCheckBox.setChecked(status)

    def setSparseReadout(self, status):

        self.sparseCheckBox.setChecked(status)

    def setZSThreshold(self, threshold):

        self.thresholdSpinbox.setValue(threshold)

    def setOffset(self, offset):

        self.offsetSpinbox.setValue(offset)
        
class ReadoutMEBWidget(QtGui.QWidget):

    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.initLabels()
        self.initComboBox()
            
    def initLabels(self):

        self.mebLabel = QtGui.QLabel("Multi Event Buffers:", self)
        self.mebLabel.setGeometry(10, 15, 120, 20)

    def initComboBox(self):

        self.mebComboBox = QtGui.QComboBox(self)
        self.mebComboBox.setGeometry(self.mebLabel.x() + self.mebLabel.width(), self.mebLabel.y(), 40, 20)

        self.mebComboBox.addItem("4")
        self.mebComboBox.addItem("8")

    def getNumberOfMEB(self):
        
        return int(self.mebComboBox.currentText())
        
    def getMEBMode(self):
        
        return self.mebComboBox.currentText() == '8'

    def setMEBMode(self, mode):

        print 'not able to load MEB mode from file yet...'
    
class APDSettingSelectorWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
 #       self.loadAPDSettings()
        self.initLabels()
        self.initSpinBox()
        self.initTextBrowser()
        self.initButtons()

#    def loadAPDSettings(self):
        
    def initLabels(self):
        
        self.apdLabel = QtGui.QLabel("APD Setting:", self)
        self.apdLabel.setGeometry(10, 10, 120, 20)
        
    def initSpinBox(self):
    
        self.apdSpinbox = QtGui.QSpinBox(self)
        self.apdSpinbox.setGeometry(self.apdLabel.x() + 120, self.apdLabel.y(), 60, 20)
        self.apdSpinbox.setMinimum(0)
        self.apdSpinbox.setMaximum(1023)
        self.apdSpinbox.setValue(0)
        
        self.connect(self.apdSpinbox, QtCore.SIGNAL("valueChanged(int)"), self.fetchConfig)
                                                     
    def initTextBrowser(self):
        
        self.apdTextEdit = QtGui.QTextBrowser(self)
        self.apdTextEdit.setGeometry(self.apdLabel.x(), self.apdLabel.y() + 30, self.width()-20, self.height() - self.apdLabel.y() - 50)

        self.apdTextEdit.setFixedSize(self.width()-10, self.height() - self.apdLabel.y() - 80)

    def setConfig(self, id, latest, description):
        
        self.apdSpinbox.setMaximum(latest)
        self.apdSpinbox.setValue(id)
        self.apdTextEdit.setText(description)
        self.configId = id

    def fetchConfig(self, id):
                
        self.emit(QtCore.SIGNAL("getConfig"), id)
    
    
    def initButtons(self):
             
        self.apdButtonLayoutWidget = QtGui.QWidget(self)
        self.apdButtonLayoutWidget.setGeometry(self.apdTextEdit.x(), self.apdTextEdit.y() + self.apdTextEdit.height() + 10, self.width()-20, self.height() - self.apdTextEdit.y() - self.apdTextEdit.height())

        self.apdButtonLayout = QtGui.QHBoxLayout(self.apdButtonLayoutWidget)

        self.loadApdButton = QtGui.QPushButton(self.apdButtonLayoutWidget)
        self.loadApdButton.setText("L&oad")
        
        self.applyApdButton = QtGui.QPushButton(self.apdButtonLayoutWidget)
        self.applyApdButton.setText("&Apply to Module")

        self.apdButtonLayout.addWidget(self.loadApdButton)
        self.apdButtonLayout.addWidget(self.applyApdButton)

        self.apdButtonLayoutWidget.setLayout(self.apdButtonLayout)

        self.connect(self.loadApdButton, QtCore.SIGNAL("clicked()"), self.loadApdSettings)
        
    def loadApdSettings(self):
        
        self.emit(QtCore.SIGNAL("loadApdSettings"), self.configId)

class RcuGeneralInfoWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
        self.layoutWidget = parent
        self.widgetLayout = QtGui.QVBoxLayout(parent)
        self.initWidgets()
        
    def initWidgets(self):
        
        self.feeServerLabel = QtGui.QLabel("FEE Server Name:", self.layoutWidget)
        self.widgetLayout.addWidget(self.feeServerLabel)

        self.feeServerTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.feeServerTextBox)

        self.rcuFwVersionLabel = QtGui.QLabel("RCU FW Version:", self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuFwVersionLabel)

        self.rcuFwVersionTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuFwVersionTextBox)
        
class RcuRegistersWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
        self.layoutWidget = parent
        self.widgetLayout = QtGui.QVBoxLayout(parent)
        self.initWidgets()
        
    def initWidgets(self):
        
        self.altroIfLabel = QtGui.QLabel("ALTROIF:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroIfLabel)

        self.altroIfTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroIfTextBox)

        self.trgConfLabel = QtGui.QLabel("TRGCONF:", self.layoutWidget)
        self.widgetLayout.addWidget(self.trgConfLabel)

        self.trgConfTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.trgConfTextBox)

        self.rdoModLabel = QtGui.QLabel("RDOMOD:", self.layoutWidget)
        self.widgetLayout.addWidget(self.rdoModLabel)

        self.rdoModTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.rdoModTextBox)

        self.altroCfg1Label = QtGui.QLabel("ALTROCFG1:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg1Label)

        self.altroCfg1TextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg1TextBox)

        self.altroCfg2Label = QtGui.QLabel("ALTROCFG2:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg2Label)

        self.altroCfg2TextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg2TextBox)
        
        self.rcuVersionLabel = QtGui.QLabel("RCU_VERSION:", self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuVersionLabel)

        self.rcuVersionTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuVersionTextBox)

        self.bpVersionLabel = QtGui.QLabel("BP_VERSION:", self.layoutWidget)
        self.widgetLayout.addWidget(self.bpVersionLabel)

        self.bpVersionTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.bpVersionTextBox)

        
