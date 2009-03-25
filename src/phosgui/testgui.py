#!/usr/bin/env python
import sys
import copy

from PyQt4 import QtCore, QtGui, uic
from phos_gui import *
import DcsInterface

app = QtGui.QApplication(sys.argv)

dcs_interface = DcsInterface.DcsInterface()



window = phosGui()
window.show()
app.exec_()

