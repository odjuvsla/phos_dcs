

import sys

from PyQt4 import QtCore, QtGui

class FeePushButton(QtGui.QPushButton):
    
#    def __init__(self, parent, feeId):
    def __init__(self, parent, feeId):

        super(FeePushButton,self).__init__(parent)


        self.feeId = feeId
    
        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

        self.viewFeeAction = QtGui.QAction("View FEE", self)

        self.addAction(self.viewFeeAction)

        self.connect(self.viewFeeAction, QtCore.SIGNAL("triggered()"), self.viewFee)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)
        

    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("toggleFee"), self.feeId)

    def viewFee(self):

        self.emit(QtCore.SIGNAL("viewFee"), self.feeId)

    def setColour(self, colour):
        
        self.setPaletteBackGroundColor(colour)
        
class TruPushButton(QtGui.QPushButton):

    def __init__(self, parent, truId):
        
        super(TruPushButton, self).__init__(parent)

class RcuViewPushButton(QtGui.QPushButton):
    
    def __init__(self, parent, rcuId):
        
        super(RcuViewPushButton, self).__init__(parent)

        self.rcuId = rcuId
        self.connect(self, QtCore.SIGNAL("clicked()"), self.viewRcu)

    def viewRcu(self):

        self.emit(QtCore.SIGNAL("showRcu"), self.rcuId)

class RcuUpdateStatusPushButton(QtGui.QPushButton):
    
    def __init__(self, parent, rcuId):

        super(RcuUpdateStatusPushButton, self).__init__(parent)
        
        self.rcuId = rcuId
        self.connect(self, QtCore.SIGNAL("clicked()"), self.updateStatus)

    def updateStatus(self):
        
        self.emit(QtCore.SIGNAL("updateStatus"), self.rcuId)

class RcuToggleOnOffPushButton(QtGui.QPushButton):

    def __init__(self, parent, rcuId):

        super(RcuToggleOnOffPushButton, self).__init__(parent)

        self.rcuId = rcuId
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)

    def toggleOnOff(self):
        
        self.emit(QtCore.SIGNAL("toggleOnOff"), rcuId)

