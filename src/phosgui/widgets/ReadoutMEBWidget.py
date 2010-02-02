from PyQt4 import QtCore, QtGui

class ReadoutMEBWidget(QtGui.QWidget):

    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.initLabels()
        self.initComboBox()
            
    def initLabels(self):

        self.mebLabel = QtGui.QLabel("Multi Event Buffers:", self)
        self.mebLabel.setGeometry(10, 15, 120, 20)

    def initComboBox(self):

        self.mebComboBox = QtGui.QComboBox(self)
        self.mebComboBox.setGeometry(self.mebLabel.x() + self.mebLabel.width(), self.mebLabel.y(), 40, 20)

        self.mebComboBox.addItem("4")
        self.mebComboBox.addItem("8")

    def getNumberOfMEB(self):
        
        return int(self.mebComboBox.currentText())
        
    def getMEBMode(self):
        
        return self.mebComboBox.currentText() == '8'

    def setMEBMode(self, mode):

        print 'not able to load MEB mode from file yet...'
