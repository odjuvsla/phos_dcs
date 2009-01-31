#!/usr/bin/env python
import sys
import copy

from PyQt4 import QtCore, QtGui, uic

app = QtGui.QApplication(sys.argv)
window_class, base_class = uic.loadUiType("phos_gui.ui")

class testGui(QtGui.QMainWindow, window_class):

    def __init__(self, *args):
        QtGui.QMainWindow.__init__(self, *args)
        self.setupUi(self)
        
    def initFee(self):

        tmpQrect = copy.deepcopy(self.fee_1_a.geometry())

        self.pushButton_fee_a = range(14)
        self.pushButton_fee_a[0] = self.fee_1_a
        
        for i in range(1,14):

            self.pushButton_fee_a[i] = QtGui.QPushButton(self.frame_rcu0)
            tmpQrect.setX(tmpQrect.x()+11)
            tmpQrect.setWidth(16)
            self.pushButton_fee_a[i].setGeometry(tmpQrect)

            
window = testGui()
window.initFee()
window.show()
app.exec_()

