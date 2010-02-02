from PyQt4 import QtCore, QtGui

class ReadoutZeroSuppressionWidget(QtGui.QWidget):

    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.initLabels()
        self.initSpinBoxes()
        self.initZsSparseSelectors()
        
    def initLabels(self):

        self.zsLabel = QtGui.QLabel("Zero Suppression:", self)
        self.zsLabel.setGeometry(10, 15, 130, 20)

        self.thresholdLabel = QtGui.QLabel("Threshold:", self)
        self.thresholdLabel.setGeometry(15, 45, 80, 20)

        self.offsetLabel = QtGui.QLabel("Offset:", self)
        self.offsetLabel.setGeometry(self.thresholdLabel.x() + self.thresholdLabel.width() + 15, self.thresholdLabel.y(), 50, 20)

    def initSpinBoxes(self):

        self.thresholdSpinbox = QtGui.QSpinBox(self)
        self.thresholdSpinbox.setGeometry(self.thresholdLabel.x(), 65, 60, 20)
        self.thresholdSpinbox.setMinimum(0)
        self.thresholdSpinbox.setMaximum(1023)
        self.thresholdSpinbox.setValue(1)
        
        self.offsetSpinbox = QtGui.QSpinBox(self)
        self.offsetSpinbox.setGeometry(self.offsetLabel.x(), self.thresholdSpinbox.y(), self.thresholdSpinbox.width(), self.thresholdSpinbox.height())
        self.offsetSpinbox.setValue(2)
        self.offsetSpinbox.setMinimum(0)
        self.offsetSpinbox.setMaximum(1023)

    def initZsSparseSelectors(self):

        self.zsCheckBox = QtGui.QCheckBox(self)
        self.zsCheckBox.setText("Enable Zero Suppression")
        self.zsCheckBox.setGeometry(self.thresholdSpinbox.x(), self.thresholdSpinbox.y() + self.thresholdSpinbox.height() + 8, 200, 20)

        self.sparseCheckBox = QtGui.QCheckBox(self)
        self.sparseCheckBox.setText("Enable Sparse Readout")
        self.sparseCheckBox.setGeometry(self.thresholdSpinbox.x(), self.zsCheckBox.y() + self.zsCheckBox.height() + 8, 200, 20)

    def isZeroSuppressionOn(self):
        
        return self.zsCheckBox.isChecked()

    def isSparseReadout(self):
        
        return self.sparseCheckBox.isChecked()

    def getZSThreshold(self):
        
        return self.thresholdSpinbox.value()

    def getOffset(self):
        
        return self.offsetSpinbox.value()

    def setZeroSuppression(self, status):

        self.zsCheckBox.setChecked(status)

    def setSparseReadout(self, status):

        self.sparseCheckBox.setChecked(status)

    def setZSThreshold(self, threshold):

        self.thresholdSpinbox.setValue(threshold)

    def setOffset(self, offset):

        self.offsetSpinbox.setValue(offset)
