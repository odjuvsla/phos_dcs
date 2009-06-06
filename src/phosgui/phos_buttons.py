

import sys

from PyQt4 import QtCore, QtGui
from phos_utilities import *

class PhosPushButton(QtGui.QPushButton):

    def __init__(self, parent=None):
        
        super(QtGui.QPushButton, self).__init__(parent)
        
        self.idConverter = PhosIdConverter()

class PhosModulePushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId):
        
        super(PhosPushButton, self).__init__(parent)

        self.moduleId = moduleId


class FeePushButton(PhosPushButton):
    
#    def __init__(self, parent, feeId):
    def __init__(self, parent, feeId):

        super(FeePushButton,self).__init__(parent)

        self.feeId = feeId
        
        module, rcu, branch, fee = self.idConverter.GetFeeLogicalIDs(self.feeId)

        self.setText(hex(fee)[2:].upper())
        
        self.setFixedWidth(16)
        self.setFixedHeight(110)

        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

        self.viewFeeAction = QtGui.QAction("View FEE", self)

        self.addAction(self.viewFeeAction)

        self.connect(self.viewFeeAction, QtCore.SIGNAL("triggered()"), self.viewFee)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)
        
    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("toggleFee"), "toggleFee", self.feeId)
     
    def viewFee(self):

        self.emit(QtCore.SIGNAL("viewFee"), "viewFee", self.feeId)

    def setState(self, state):

        self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 0, 0))
        if state == FEE_STATE_ON:
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 255, 0))
        if state == FEE_STATE_OFF:
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 255, 255))
        if state == FEE_STATE_WARNING: 
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 255, 0))
        if state == FEE_STATE_ERROR: 
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 0, 0))
        print FEE_STATE_OFF
class TruPushButton(PhosPushButton):

    def __init__(self, parent, truId):
        
        super(TruPushButton, self).__init__(parent) 
        
        self.truId = truId
        
        if truId%2 == 0:
            self.setText("A")
        else:
            self.setText("B")
        
        self.setFixedWidth(16)
        self.setFixedHeight(110)

        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

        self.viewTruAction = QtGui.QAction("View TRU", self)

        self.addAction(self.viewTruAction)

        self.connect(self.viewTruAction, QtCore.SIGNAL("triggered()"), self.viewTru)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)
 
    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("toggleTru"), "toggleTru", self.truId)

    def viewTru(self):

        self.emit(QtCore.SIGNAL("viewTru"), "viewTru", self.truId)
        
class RcuViewPushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId, rcuId):
        
        super(RcuViewPushButton, self).__init__(parent)

        self.setText("RCU View")
        
        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)

        self.setFixedWidth(110)
        self.setFixedHeight(25)

        self.connect(self, QtCore.SIGNAL("clicked()"), self.viewRcu)

    def viewRcu(self):

        self.emit(QtCore.SIGNAL("viewRcu"), "viewRcu", self.rcuId)

class RcuUpdateStatusPushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId, rcuId):

        super(RcuUpdateStatusPushButton, self).__init__(parent)
        
        self.setText("Update Status")

        self.setFixedWidth(110)
        
        self.setFixedHeight(25)

        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.updateStatus)

    def updateStatus(self):
        
        self.emit(QtCore.SIGNAL("rcuUpdateStatus"), "rcuUpdateStatus", self.rcuId)

class RcuToggleOnOffPushButton(PhosPushButton):

    def __init__(self, parent, moduleId, rcuId, on):

        super(RcuToggleOnOffPushButton, self).__init__(parent)

        self.on = on

        if on == True:
            self.setText("On")

        if on == False:
            self.setText("Off")

        self.setFixedWidth(52)
        self.setFixedHeight(25)
            
        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)

    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("rcuToggleOnOff"), "rcuToggleOnOff", self.rcuId, self.on)


class ModuleTurnOnButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOnButton, self).__init__(parent, moduleId)
        
        self.setText("Turn On Module Electronics")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOnModule)

    def turnOnModule(self):
        
        self.emit(QtCore.SIGNAL("turnOnModule"), "turnOnModule", self.moduleId)

class ModuleTurnOffButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOffButton, self).__init__(parent, moduleId)

        self.setText("Shutdown Module Electronics")
       
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOffModule)

    def turnOffModule(self):
        
        self.emit(QtCore.SIGNAL("shutdownModule"), "shutdownModule", self.moduleId)


class ModulePropertiesButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModulePropertiesButton, self).__init__(parent, moduleId)

        self.setText("Module Properties")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.showModuleProperties)

    def showModuleProperties(self):
        
        self.emit(QtCore.SIGNAL("showModuleProperties"), "showModuleProperties", self.moduleId)

class ModuleConfigureElectronicsButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleConfigureElectronicsButton, self).__init__(parent, moduleId)

        self.setText("Configure Electronics")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.configureElectronicsModule)

    def configureElectronicsModule(self):
        
        self.emit(QtCore.SIGNAL("configureElectronicsModule"), "configureElectronicsModule", self.moduleId)

class ModuleEnableTriggerButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleEnableTriggerButton, self).__init__(parent, moduleId)

        self.setText("Enable Trigger")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.enableTriggerModule)

    def enableTriggerModule(self):
        
        self.emit(QtCore.SIGNAL("enableTriggerModule"), "enableTriggerModule", self.moduleId)

class ModuleDisableTriggerButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleDisableTriggerButton, self).__init__(parent, moduleId)

        self.setText("Disable Trigger")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.disableTriggerModule)

    def disableTriggerModule(self):
        
        self.emit(QtCore.SIGNAL("disableTriggerModule"), "disableTriggerModule", self.moduleId)
        

# class PhosSaveButton(QtGui.QPushButton):
    
#     def __init__(self, parent):
#         super(QtGui.QPushButton, self).__init__(parent)

#         self.setText("Save")

#     def setConfigFile(self, filepath):
        
#         self.filePath = filepath
        
#         self.connect(self, QtCore.SIGNAL("clicked()"), self.saveToFile)

#     def saveToFile(self):

#         GetSaveData()

#         args = ['test1', 'test2', 'test3']
  
#         for i in args:
#             print i


            
        
