#!/usr/bin/env python
import sys
from PyQt4 import QtCore, QtGui
from phos_main_window import *

app = QtGui.QApplication(sys.argv)

window = PhosGui()
window.show()
app.exec_()
