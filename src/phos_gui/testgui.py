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
        print self.pushButton_rcu_update_status.text()
        print self.pushButton_rcu_update_status.geometry().x()
        print self.pushButton_rcu_update_status.geometry().y()
        print self.pushButton_rcu_view.geometry().x()
        print self.pushButton_rcu_view.geometry().y()

        tmpQrect = copy.deepcopy(self.fee_1.geometry())
        tmpQrect.setX(tmpQrect.x()+12)

        #self.push_test = QtGui.QPushButton(self.tab_modules.currentWidget())
#        self.push_test = QtGui.QPushButton(self.frame_rcu0)
#        self.push_test = QtGui.QPushButton()
 #       tmpQrect = self.pushButton_rcu_update_status.geometry()

#        self.push_test.setGeometry(tmpQrect)

window = testGui()
window.show()
app.exec_()

