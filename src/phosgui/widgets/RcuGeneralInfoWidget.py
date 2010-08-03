# -*- coding: utf-8 -*-
from PyQt4 import QtCore, QtGui
from RcuHandler import *

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
    
    def getValues(self, rcuHandler, rcuId, moduleId):
	print "getValues"
#	version = rcuHandler.GetRcuFwVersion(0,0)
	
