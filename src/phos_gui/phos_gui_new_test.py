#!/usr/bin/env python

import sys
import copy

from PyQt4 import QtCore, QtGui
from PhosConst import *
from phos_buttons import *
from phos_widgets import *

app = QtGui.QApplication(sys.argv)

class phosGui(QtGui.QMainWindow):
    """The main gui"""

    def __init__(self, parent=None):
        super(QtGui.QMainWindow, self).__init__(parent)
        
        self.resize(1280, 860)
        self.tabControls = QtGui.QTabWidget(self)

        self.setCentralWidget(self.tabControls)
        
        self.testWidget = QtGui.QWidget()
        self.testLayout = QtGui.QVBoxLayout()
        self.testButton1 = FeePushButton(self.testWidget, 1)
        self.testButton2 = FeePushButton(self.testWidget, 2)

        self.rcutopframe = RcuTopFrame(self.testWidget)
        self.rcutopframe.geometry().setX(20)
        self.rcu = Rcu(0, 0, self.testWidget)
        self.rcu.geometry().setX(20)
        self.rcu.geometry().setY(40)
        
#         self.testWidget.setLayout(self.testLayout)
#         self.testLayout.addWidget(self.testButton1)
#         self.testLayout.addWidget(self.testButton2)
#         self.testLayout.addWidget(self.rcutopframe)

        self.moduleTab = ModuleTabWidget(0)
#        self.tabControls.addTab(self.testWidget, "test widget")
        self.tabControls.addTab(self.moduleTab, "Module 0")

window = phosGui()
window.show()
app.exec_()
