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

        self.truSamplesLabel = QtGui.QLabel("TRU Samples:", self)
        self.truSamplesLabel.setGeometry(self.samplesLabel.x() + self.samplesLabel.width() + 20, self.titleLabel.y(), 80, 20)

        self.truSamplesMinLabel = QtGui.QLabel("Min:", self)
        self.truSamplesMinLabel.setGeometry(self.truSamplesLabel.x(), self.truSamplesLabel.y() + 22, 25, 20)

        self.truSamplesMaxLabel = QtGui.QLabel("Max:", self)
        self.truSamplesMaxLabel.setGeometry(self.truSamplesLabel.x(), self.samplesLabel.y() + 22, 25, 20)
        

    def initSpinBoxes(self):

        self.preSpinbox = QtGui.QSpinBox(self)
        self.preSpinbox.setGeometry(self.preLabel.x(), 65, 60, 20)
        self.preSpinbox.setMinimum(0)
        self.preSpinbox.setMaximum(MAX_ALTRO_PRESAMPLES)
        self.preSpinbox.setValue(11)
        
        self.samplesSpinbox = QtGui.QSpinBox(self)
        self.samplesSpinbox.setGeometry(self.samplesLabel.x(), self.preSpinbox.y(), self.preSpinbox.width()-10, self.preSpinbox.height())
        self.samplesSpinbox.setValue(81)
        self.samplesSpinbox.setMinimum(0)
        self.samplesSpinbox.setMaximum(MAX_ALTRO_SAMPLES-1)

        self.truSamplesSpinboxMin = QtGui.QSpinBox(self)
        self.truSamplesSpinboxMin.setGeometry(self.truSamplesLabel.x() + 40, self.truSamplesLabel.y() + 22, self.preSpinbox.width(), self.preSpinbox.height())
        self.truSamplesSpinboxMin.setValue(0)
        self.truSamplesSpinboxMin.setMinimum(0)
        self.truSamplesSpinboxMin.setMaximum(127)

        self.truSamplesSpinboxMax = QtGui.QSpinBox(self)
        self.truSamplesSpinboxMax.setGeometry(self.truSamplesSpinboxMin.x(), self.preSpinbox.y(), self.preSpinbox.width(), self.preSpinbox.height())
        self.truSamplesSpinboxMax.setValue(127)
        self.truSamplesSpinboxMax.setMinimum(0)
        self.truSamplesSpinboxMax.setMaximum(127)

    def getSamplesSettings(self):
        
        nSamples = self.samplesSpinbox.value()
        nPreSamples = self.preSpinbox.value()
        truSamplesMin = self.truSamplesSpinboxMin.value()
        truSamplesMax = self.truSamplesSpinboxMax.value()
        
        return nPreSamples, nSamples, truSamplesMin, truSamplesMax 

    def setPreSamples(self, nPreSamples):

        self.preSpinbox.setValue(nPreSamples)

    def setSamples(self, nSamples):

        self.samplesSpinbox.setValue(nSamples)

    def setTruSamples(self, nSamplesMin, nSamplesMax):

        self.truSamplesSpinboxMin.setValue(nSamplesMin)
        self.truSamplesSpinboxMax.setValue(nSamplesMax)

    def setTruSamplesMin(self, nsamples):

        self.truSamplesSpinboxMin.setValue(nsamples)

    def setTruSamplesMax(self, nsamples):

        self.truSamplesSpinboxMax.setValue(nsamples)
