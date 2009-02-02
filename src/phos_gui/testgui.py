#!/usr/bin/env python
import sys
import copy

from PyQt4 import QtCore, QtGui, uic

app = QtGui.QApplication(sys.argv)
window_class, base_class = uic.loadUiType("phos_gui.ui")

        
window = phosGui()
window.show()
app.exec_()

