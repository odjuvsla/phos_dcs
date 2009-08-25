from PyQt4 import QtCore, QtGui
from PhosConst import *

class ReadoutRegionSettingsWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        
        self.setFixedSize(width, height)

        self.initLabels()

        self.initSpinBoxes()
#        self.initDetailedSelectionButton()

    def initLabels(self):
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)

        self.fromLabel = QtGui.QLabel("From:", self)
        self.fromLabel.setGeometry(45, 40, 30, 20)

        self.toLabel = QtGui.QLabel("To:", self)
        self.toLabel.setGeometry(self.fromLabel.x() + self.fromLabel.width() + 35, self.fromLabel.y(), 30, 20)

        self.xLabel = QtGui.QLabel("X:", self)
        self.xLabel.setGeometry(15, 65, 10, 20)

        self.zLabel = QtGui.QLabel("Z:", self)
        self.zLabel.setGeometry(self.xLabel.x(), self.xLabel.y() + self.xLabel.height() + 5, self.xLabel.width(), self.xLabel.height())
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)
        

    def initSpinBoxes(self):

        self.xSpinboxFirst = QtGui.QSpinBox(self)
        self.xSpinboxFirst.setGeometry(self.fromLabel.x(), 65, 40, 20)
        self.xSpinboxFirst.setMinimum(0)
        self.xSpinboxFirst.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.xSpinboxLast = QtGui.QSpinBox(self)
        self.xSpinboxLast.setGeometry(self.toLabel.x(), self.xSpinboxFirst.y(), self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.xSpinboxLast.setValue(N_XCOLUMNS_MOD - 1)
        self.xSpinboxLast.setMinimum(0)
        self.xSpinboxLast.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.zSpinboxFirst = QtGui.QSpinBox(self)
        self.zSpinboxFirst.setGeometry(self.xSpinboxFirst.x(), self.xSpinboxFirst.y() + self.xSpinboxFirst.height() + 5, self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.xSpinboxFirst.setMinimum(0)
        self.xSpinboxFirst.setMaximum(N_ZROWS_MOD - 1)
        
        self.zSpinboxLast = QtGui.QSpinBox(self)
        self.zSpinboxLast.setGeometry(self.xSpinboxLast.x(), self.zSpinboxFirst.y(), self.xSpinboxFirst.width(), self.xSpinboxFirst.height())
        self.zSpinboxLast.setValue(N_ZROWS_MOD - 1)
        self.zSpinboxLast.setMinimum(0)
        self.zSpinboxLast.setMaximum(N_ZROWS_MOD - 1)

    def getReadOutRegion(self):
        
        xFirst = self.xSpinboxFirst.value()
        xLast = self.xSpinboxLast.value()
        zFirst = self.zSpinboxFirst.value()
        zLast = self.zSpinboxLast.value()                
        
        return xFirst, xLast, zFirst, zLast

    def setFirstX(self, x):

        self.xSpinboxFirst.setValue(x)

    def setLastX(self, x):

        self.xSpinboxLast.setValue(x)

    def setFirstZ(self, z):

        self.zSpinboxFirst.setValue(z)

    def setLastZ(self, z):

        self.zSpinboxLast.setValue(z)

    def initDetailedSelectionButton(self):

        print 'test'
