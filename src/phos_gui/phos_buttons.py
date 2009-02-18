

import sys

from PyQt4 import QtCore, QtGui
from phos_utilities import *

class PhosPushButton(QtGui.QPushButton):

    def __init__(self, parent=None):
        
        super(QtGui.QPushButton, self).__init__(parent)
        
        self.idConverter = PhosIdConverter()

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

        self.emit(QtCore.SIGNAL("toggleFee"), self.feeId)
        print "Toggle FEE"

    def viewFee(self):

        self.emit(QtCore.SIGNAL("viewFee"), self.feeId)

    def setColour(self, colour):
        
        self.setPaletteBackGroundColor(colour)
        
class TruPushButton(PhosPushButton):

    def __init__(self, parent, truId):
        
        super(PhosPushButton, self).__init__(parent) 
        
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

        self.emit(QtCore.SIGNAL("toggleTru"), self.truId)
        print "Toggle TRU"

    def viewTru(self):

        self.emit(QtCore.SIGNAL("viewTru"), self.truId)
        
class RcuViewPushButton(PhosPushButton):
    
    def __init__(self, parent, rcuId):
        
        super(RcuViewPushButton, self).__init__(parent)

        self.setText("RCU View")

        self.rcuId = rcuId

        self.setFixedWidth(110)
        self.setFixedHeight(25)

        self.connect(self, QtCore.SIGNAL("clicked()"), self.viewRcu)

    def viewRcu(self):

        self.emit(QtCore.SIGNAL("showRcu"), self.rcuId)

class RcuUpdateStatusPushButton(PhosPushButton):
    
    def __init__(self, parent, rcuId):

        super(RcuUpdateStatusPushButton, self).__init__(parent)
        
        self.setText("Update Status")

        self.rcuId = rcuId
        self.connect(self, QtCore.SIGNAL("clicked()"), self.updateStatus)

    def updateStatus(self):
        
        self.emit(QtCore.SIGNAL("updateStatus"), self.rcuId)

class RcuToggleOnOffPushButton(PhosPushButton):

    def __init__(self, parent, rcuId):

        super(RcuToggleOnOffPushButton, self).__init__(parent)

        self.setText("Toggle On/Off")

        self.rcuId = rcuId
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)

    def toggleOnOff(self):
        
        self.emit(QtCore.SIGNAL("toggleOnOff"), self.rcuId)

