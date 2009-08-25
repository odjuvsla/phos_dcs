from PyQt4 import QtCore, QtGui

class ConnectionSettingsBusyboxTabWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
       
        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)
