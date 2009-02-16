#!/usr/bin/env python

import sys
import copy

from PyQt4 import QtCore, QtGui
from PhosConst import *
from phos_buttons import *

app = QtGui.QApplication(sys.argv)

class phosGui(QtGui.QMainWindow):
    """The main gui"""

    def __init__(self, parent=None):
        super(QtGui.QMainWindow, self).__init__(parent)
        
        self.resize(480, 640)
        self.tabControls = QtGui.QTabWidget(self)
        
        self.setCentralWidget(self.tabControls)
        
        self.testWidget = QtGui.QWidget()
        self.testLayout = QtGui.QVBoxLayout()
        self.testButton1 = FeePushButton(self.testWidget, 1)
        self.testButton2 = FeePushButton(self.testWidget, 2)
        self.testWidget.setLayout(self.testLayout)
        self.testLayout.addWidget(self.testButton1)
        self.testLayout.addWidget(self.testButton2)

        self.tabControls.addTab(self.testWidget, "test widget")

window = phosGui()
window.show()
app.exec_()
