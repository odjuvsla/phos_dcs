from PyQt4 import QtCore, QtGui
from PhosPushButton import *

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
	print 'Setting colors for ' + str(self.feeId)
        self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 0, 0))
        self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 0, 255))
        if state == FEE_STATE_ON:
	    self.setStyleSheet('QPushButton { background : rgb(0, 255, 0) }' )
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 255, 0))
        if state == FEE_STATE_OFF:
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 255, 255))
	    self.setStyleSheet('QPushButton { background : blue }' )
        if state == FEE_STATE_WARNING: 
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 255, 0))
	    self.setStyleSheet('QPushButton { background : yellow }' )
        if state == FEE_STATE_ERROR: 
            self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 0, 0))
	    self.setStyleSheet('QPushButton { background : red }' )
        self.update()

