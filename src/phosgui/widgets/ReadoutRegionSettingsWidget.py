from PyQt4 import QtCore, QtGui
from PhosConst import *

class ReadoutRegionSettingsWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        
        self.setFixedSize(width, height)

        self.initLabels()

        self.initSpinBoxes()
        
        self.initCheckBoxes()
#        self.initDetailedSelectionButton()

    def initLabels(self):
        
        self.regionLabel = QtGui.QLabel("Read out region (HG/LG):", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)

        self.hgFromLabel = QtGui.QLabel("From:", self)
        self.hgFromLabel.setGeometry(45, 40, 30, 20)

        self.hgToLabel = QtGui.QLabel("To:", self)
        self.hgToLabel.setGeometry(self.hgFromLabel.x() + self.hgFromLabel.width() + 35, self.hgFromLabel.y(), 30, 20)

        self.lgFromLabel = QtGui.QLabel("From:", self)
        self.lgFromLabel.setGeometry(self.hgToLabel.x() + self.hgToLabel.width() + 40, self.hgFromLabel.y(), 30, 20)

        self.lgToLabel = QtGui.QLabel("To:", self)
        self.lgToLabel.setGeometry(self.hgToLabel.x() + self.hgToLabel.width() + 100, self.hgFromLabel.y(), 30, 20)

        self.xLabel = QtGui.QLabel("X:", self)
        self.xLabel.setGeometry(15, 65, 10, 20)

        self.zLabel = QtGui.QLabel("Z:", self)
        self.zLabel.setGeometry(self.xLabel.x(), self.xLabel.y() + self.xLabel.height() + 5, self.xLabel.width(), self.xLabel.height())
        
        self.regionLabel = QtGui.QLabel("Read out region:", self)
        self.regionLabel.setGeometry(10, 10, 130, 20)
        

    def initSpinBoxes(self):

        # For high gain
        self.hgxSpinboxFirst = QtGui.QSpinBox(self)
        self.hgxSpinboxFirst.setGeometry(self.hgFromLabel.x(), 65, 40, 20)
        self.hgxSpinboxFirst.setMinimum(0)
        self.hgxSpinboxFirst.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.hgxSpinboxLast = QtGui.QSpinBox(self)
        self.hgxSpinboxLast.setGeometry(self.hgToLabel.x(), self.hgxSpinboxFirst.y(), self.hgxSpinboxFirst.width(), self.hgxSpinboxFirst.height())
        self.hgxSpinboxLast.setValue(N_XCOLUMNS_MOD - 1)
        self.hgxSpinboxLast.setMinimum(0)
        self.hgxSpinboxLast.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.hgzSpinboxFirst = QtGui.QSpinBox(self)
        self.hgzSpinboxFirst.setGeometry(self.hgxSpinboxFirst.x(), self.hgxSpinboxFirst.y() + self.hgxSpinboxFirst.height() + 5, self.hgxSpinboxFirst.width(), self.hgxSpinboxFirst.height())
        self.hgzSpinboxFirst.setMinimum(0)
        self.hgzSpinboxFirst.setMaximum(N_ZROWS_MOD - 1)
        
        self.hgzSpinboxLast = QtGui.QSpinBox(self)
        self.hgzSpinboxLast.setGeometry(self.hgxSpinboxLast.x(), self.hgzSpinboxFirst.y(), self.hgxSpinboxFirst.width(), self.hgxSpinboxFirst.height())
        self.hgzSpinboxLast.setValue(N_ZROWS_MOD - 1)
        self.hgzSpinboxLast.setMinimum(0)
        self.hgzSpinboxLast.setMaximum(N_ZROWS_MOD - 1)


        #For low gain
        
        self.lgxSpinboxFirst = QtGui.QSpinBox(self)
        self.lgxSpinboxFirst.setGeometry(self.lgFromLabel.x(), 65, 40, 20)
        self.lgxSpinboxFirst.setMinimum(0)
        self.lgxSpinboxFirst.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.lgxSpinboxLast = QtGui.QSpinBox(self)
        self.lgxSpinboxLast.setGeometry(self.lgToLabel.x(), self.lgxSpinboxFirst.y(), self.lgxSpinboxFirst.width(), self.lgxSpinboxFirst.height())
        self.lgxSpinboxLast.setValue(N_XCOLUMNS_MOD - 1)
        self.lgxSpinboxLast.setMinimum(0)
        self.lgxSpinboxLast.setMaximum(N_XCOLUMNS_MOD - 1)
        
        self.lgzSpinboxFirst = QtGui.QSpinBox(self)
        self.lgzSpinboxFirst.setGeometry(self.lgxSpinboxFirst.x(), self.lgxSpinboxFirst.y() + self.lgxSpinboxFirst.height() +5, self.lgxSpinboxFirst.width(), self.lgxSpinboxFirst.height())
        self.lgzSpinboxFirst.setMinimum(0)
        self.lgzSpinboxFirst.setMaximum(N_ZROWS_MOD - 1)
        
        self.lgzSpinboxLast = QtGui.QSpinBox(self)
        self.lgzSpinboxLast.setGeometry(self.lgxSpinboxLast.x(), self.lgzSpinboxFirst.y(), self.lgxSpinboxFirst.width(), self.lgxSpinboxFirst.height())
        self.lgzSpinboxLast.setValue(N_ZROWS_MOD - 1)
        self.lgzSpinboxLast.setMinimum(0)
        self.lgzSpinboxLast.setMaximum(N_ZROWS_MOD - 1)

    def initCheckBoxes(self):

        self.truRoCheckBox = QtGui.QCheckBox(self)
        self.truRoCheckBox.setText("Enable TRU Readout")
        self.truRoCheckBox.setGeometry(self.xLabel.x(), self.zLabel.y() + self.zLabel.height() + 8, 200, 20)


    def getReadOutRegion(self):
        
        hgxFirst = self.hgxSpinboxFirst.value()
        hgxLast = self.hgxSpinboxLast.value()
        hgzFirst = self.hgzSpinboxFirst.value()
        hgzLast = self.hgzSpinboxLast.value()                

        lgxFirst = self.lgxSpinboxFirst.value()
        lgxLast = self.lgxSpinboxLast.value()
        lgzFirst = self.lgzSpinboxFirst.value()
        lgzLast = self.lgzSpinboxLast.value()                
        
        return hgxFirst, hgxLast, hgzFirst, hgzLast ,lgxFirst, lgxLast, lgzFirst, lgzLast

    def setHgFirstX(self, x):

        self.hgxSpinboxFirst.setValue(x)

    def setHgLastX(self, x):

        self.hgxSpinboxLast.setValue(x)

    def setHgFirstZ(self, z):

        self.hgzSpinboxFirst.setValue(z)

    def setHgLastZ(self, z):

        self.hgzSpinboxLast.setValue(z)

    def setLgFirstX(self, x):

        self.lgxSpinboxFirst.setValue(x)

    def setLgLastX(self, x):

        self.lgxSpinboxLast.setValue(x)

    def setLgFirstZ(self, z):

        self.lgzSpinboxFirst.setValue(z)

    def setLgLastZ(self, z):

        self.lgzSpinboxLast.setValue(z)

    def setTruEnabled(self, status):

        self.truRoCheckBox.setChecked(status)

    def isTruReadoutEnabled(self):

        return self.truRoCheckBox.isChecked()

    def initDetailedSelectionButton(self):

        print 'test'
