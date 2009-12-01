from PyQt4 import QtCore, QtGui
from PhosIdConverter import *
from RcuTopFrame import *
from PhosConst import *
from Rcu import *
from ModulePropertiesButton import *
from ModuleConfigureElectronicsButton import *
from ModuleEnableTriggerButton import *
from ModuleDisableTriggerButton import *

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
        self.moduleTurnOnButton.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 255, 0))
        
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
        self.moduleIndicator.update()
        
    def updateFeeCard(self, feeId, state):
        
        print 'update card ' + str(feeId) + ' with state ' + str(state)
        module, rcu, branch, fee = self.idConverter.GetFeeLogicalIDs(feeId)
        self.rcus[rcu].updateFeeCard(branch, fee, state)
  #       if fee == 13:
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
