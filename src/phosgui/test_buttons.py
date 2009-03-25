
import sys
import time

from PyQt4 import QtCore, QtGui

from phos_buttons import *

app = QtGui.QApplication(sys.argv)

class MainWindow(QtGui.QMainWindow):
    
    def __init__(self, parent = None):

        super(MainWindow, self).__init__(parent)

        self.fee_button = FeePushButton(self, 1)
        
        self.connect(self.fee_button, QtCore.SIGNAL("toggleFee"), self.shout)

    def shout(self):

        print "shouting!"
        time.sleep(1)
        print "again!"

window = MainWindow()
window.show()
app.exec_()
