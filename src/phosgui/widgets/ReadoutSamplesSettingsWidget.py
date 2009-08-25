from PyQt4 import QtCore, QtGui
from PhosConst import *

class ReadoutSamplesSettingsWidget(QtGui.QWidget):

    def __init__(self, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        
        self.setFixedSize(width, height)

        self.initLabels()
        self.initSpinBoxes()
        
    def initLabels(self):


        self.titleLabel = QtGui.QLabel("Number of samples:", self)
        self.titleLabel.setGeometry(10, 15, 130, 20)

        self.preLabel = QtGui.QLabel("Pre-samples:", self)
        self.preLabel.setGeometry(15, 45, 80, 20)

        self.samplesLabel = QtGui.QLabel("Samples:", self)
        self.samplesLabel.setGeometry(self.preLabel.x() + self.preLabel.width() + 15, self.preLabel.y(), 50, 20)
        

    def initSpinBoxes(self):

        self.preSpinbox = QtGui.QSpinBox(self)
        self.preSpinbox.setGeometry(self.preLabel.x(), 65, 60, 20)
        self.preSpinbox.setMinimum(0)
        self.preSpinbox.setMaximum(MAX_ALTRO_PRESAMPLES)
        self.preSpinbox.setValue(11)
        
        self.samplesSpinbox = QtGui.QSpinBox(self)
        self.samplesSpinbox.setGeometry(self.samplesLabel.x(), self.preSpinbox.y(), self.preSpinbox.width(), self.preSpinbox.height())
        self.samplesSpinbox.setValue(81)
        self.samplesSpinbox.setMinimum(0)
        self.samplesSpinbox.setMaximum(MAX_ALTRO_SAMPLES)

    def getSamplesSettings(self):
        
        nSamples = self.samplesSpinbox.value()
        nPreSamples = self.preSpinbox.value()

        return nPreSamples, nSamples

    def setPreSamples(self, nPreSamples):

        self.preSpinbox.setValue(nPreSamples)

    def setSamples(self, nSamples):

        self.samplesSpinbox.setValue(nSamples)

