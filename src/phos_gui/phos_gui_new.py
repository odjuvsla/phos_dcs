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
        
        self.resize(1080, 860)
        self.initTabs()
        self.setCentralWidget(self.tabControls)
    def initTabs(self):
        
        self.tabControls = QtGui.QTabWidget(self)
        
        self.moduleTabs = [None]*PHOS_MODS

        for i in range(PHOS_MODS):
            
            self.moduleTabs[i] = ModuleTabWidget(i)
            self.tabControls.addTab(self.moduleTabs[i], "Module " + str(i))

window = phosGui()
window.show()
app.exec_()
