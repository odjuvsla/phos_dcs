from PyQt4 import QtCore, QtGui
from ReadoutRegionSettingsWidget import *
from ReadoutSamplesSettingsWidget import *
from ReadoutZeroSuppressionWidget import *
from ReadoutMEBWidget import *
from APDSettingsSelectorWidget import *
from PhosDataTypes import *

class ConfigureElectronicsDialog(QtGui.QDialog):
    """Dialog for setting up the electronics configuration"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(700, 560)

        self.initButtons()
        self.initConnections()

        self.configFile = "test.config"

    def start(self, moduleHandler, databaseHandler, moduleId):

        self.moduleHandler = moduleHandler
        self.databaseHandler = databaseHandler
        self.moduleId = moduleId

        self.initFrames()
        self.loadFromFile()
        self.exec_()
        
    def initButtons(self):

        self.buttonLayoutWidget = QtGui.QWidget(self)
        self.buttonLayoutWidget.setGeometry(QtCore.QRect(self.width() - 330, self.height() - 50, 330, 60))

        self.buttonLayout = QtGui.QHBoxLayout(self.buttonLayoutWidget)

        self.saveButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.saveButton.setText("&Save")
        
        self.configureButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.configureButton.setText("C&onfigure")

        self.cancelButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.cancelButton.setText("&Cancel")

        self.buttonLayout.addWidget(self.saveButton)
        self.buttonLayout.addWidget(self.configureButton)
        self.buttonLayout.addWidget(self.cancelButton)

        self.buttonLayoutWidget.setLayout(self.buttonLayout)

    def initConnections(self):

        self.connect(self.saveButton, QtCore.SIGNAL("clicked()"), self.saveToFile)
        self.connect(self.configureButton, QtCore.SIGNAL("clicked()"), self.doConfigure)
        self.connect(self.cancelButton, QtCore.SIGNAL("clicked()"), self.cancelConfiguration)

    def saveToFile(self):
        
        CONFIGFILE = open(self.configFile, "w") 
        configLines = []

        xfirst, xlast, zfirst, zlast = self.regionWidget.getReadOutRegion()

        preSamples, samples = self.samplesWidget.getSamplesSettings()

        zeroSuppression = self.zsWidget.isZeroSuppressionOn()
        zsThreshold = self.zsWidget.getZSThreshold()
        zsOffset = self.zsWidget.getOffset()
        sparseReadout = self.zsWidget.isSparseReadout()
        
        
        configLines.append("XFIRST " + str(xfirst) + "\n")
        configLines.append("XLAST " + str(xlast) + "\n")
        configLines.append("ZFIRST " + str(zfirst) + "\n")
        configLines.append("ZLAST " + str(zlast) + "\n")

        configLines.append("PRESAMPLES " + str(preSamples) + "\n")
        configLines.append("SAMPLES " + str(samples) + "\n")
        configLines.append("ZEROSUPPRESSION " + str(zeroSuppression) + "\n")
        configLines.append("THRESHOLD " + str(zsThreshold) + "\n")
        configLines.append("OFFSET " + str(zsOffset) + "\n")
        configLines.append("SPARSEREADOUT " + str(sparseReadout) + "\n")
        configLines.append("MEBMODE " + str(self.mebWidget.getMEBMode()) + "\n")
        configLines.append("APDCONFIG " + str(self.getApdConfig()) + "\n")
       

        CONFIGFILE.writelines(configLines)
        CONFIGFILE.close()

    def loadFromFile(self):

        CONFIGFILE = open(self.configFile, "r")
        
        
        for line in CONFIGFILE.readlines():

            valueName = line.split(" ")[0]
            if valueName == "XFIRST":
                self.regionWidget.setFirstX(int(line.split(" ")[1]))
            if valueName == "XLAST":
                self.regionWidget.setLastX(int(line.split(" ")[1]))
            if valueName == "ZFIRST":
                self.regionWidget.setFirstZ(int(line.split(" ")[1]))
            if valueName == "ZLAST":
                self.regionWidget.setLastZ(int(line.split(" ")[1]))
            if valueName == "PRESAMPLES":
                self.samplesWidget.setPreSamples(int(line.split(" ")[1]))
            if valueName == "SAMPLES":
                self.samplesWidget.setSamples(int(line.split(" ")[1]))
            if valueName == "ZEROSUPPRESSION":
                if line.split(" ")[1].strip() == "True":
                    self.zsWidget.setZeroSuppression(True)
                if line.split(" ")[1].strip() == "False":
                    self.zsWidget.setZeroSuppression(False)
            if valueName == "SPARSEREADOUT":
                if line.split(" ")[1].strip() == "True":
                    self.zsWidget.setSparseReadout(True)
                if line.split(" ")[1].strip() == "False":
                    self.zsWidget.setSparseReadout(False)
            if valueName == "THRESHOLD":
                self.zsWidget.setZSThreshold(int(line.split(" ")[1]))
            if valueName == "OFFSET":
                self.zsWidget.setOffset(int(line.split(" ")[1]))
            if valueName == "MEBMODE":
                if line.split(" ")[1].strip() == "True":
                    self.mebWidget.setMEBMode(True)
                if line.split(" ")[1].strip() == "False":
                    self.mebWidget.setMEBMode(False)
            if valueName == "APDCONFIG":
                self.setApdConfig(int(line.split(" ")[1]))

        CONFIGFILE.close()


    def doConfigure(self):

        rdoRegion, rdoSettings = self.getReadoutConfig()

        self.moduleHandler.configureElectronics(self.moduleId, rdoRegion, rdoSettings)
        
        self.cancelConfiguration()

    def getReadoutConfig(self):

        preSamples, samples = self.samplesWidget.getSamplesSettings()

        zeroSuppression = self.zsWidget.isZeroSuppressionOn()
        zsThreshold = self.zsWidget.getZSThreshold()
        zsOffset = self.zsWidget.getOffset()
        sparseReadout = self.zsWidget.isSparseReadout()

        

        if zeroSuppression == True:
            autoBs = True
        else:
            autoBs = False


        MEBMode = self.mebWidget.getMEBMode()
        print "MEBMODE: " + str(MEBMode)
    #triggerMode = self.getTriggerMode()

        xfirst, xlast, zfirst, zlast = self.regionWidget.getReadOutRegion()
        enableFakeAltroReadout = True

        rdoRegion = ReadoutRegion_t(StartZ_t(zfirst), EndZ_t(zlast), StartX_t(xfirst), EndX_t(xlast), enableFakeAltroReadout)

        rdoSettings = ReadoutSettings_t(NPreSamples_t(preSamples), NSamples_t(samples), zeroSuppression, zsThreshold, zsOffset, 
                                        sparseReadout, autoBs, MEBMode)

        return rdoRegion, rdoSettings

    def getAltroConfig(self):
        
        preSamples, samples = self.samplesWidget.getSamplesSettings()
        
        readoutMode = self.mebWidget.getNumberOfMEB()/5

    def cancelConfiguration(self):

        self.close()
        
    def initFrames(self):
        
        self.readoutFrame = QtGui.QFrame(self)
        self.readoutFrame.setGeometry(10, 10, self.width()/2 - 15, self.height() - 60)
        self.readoutFrame.setFixedSize(self.width()/2 - 40, self.height() - 60)
        self.readoutFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.readoutFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.apdFrame = QtGui.QFrame(self)
        self.apdFrame.setGeometry(self.width()/2 - 15, 10, self.width()/2 - 10, self.height()/2 - 40)
        self.apdFrame.setFixedSize(self.width()/2 + 5, self.height()/2 - 35)
        self.apdFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.apdFrame.setFrameShadow(QtGui.QFrame.Raised)

        self.truFrame = QtGui.QFrame(self)
        self.truFrame.setGeometry(self.width()/2 - 15, self.height()/2 - 15, self.width()/2 - 10, self.height()/2 - 30)
        self.truFrame.setFixedSize(self.width()/2 + 5, self.height()/2 - 35)
        self.truFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.truFrame.setFrameShadow(QtGui.QFrame.Raised)
        
        self.readoutLabel = QtGui.QLabel("READ OUT SETTINGS", self.readoutFrame)
        self.readoutLabel.setGeometry(self.readoutFrame.width()/2 - self.readoutLabel.width()/2 - 15, 10, 130, 20)

        self.initReadoutWidgets()
        self.initApdWidgets()

    def initReadoutWidgets(self):

        self.readoutSep = QtGui.QFrame(self.readoutFrame)
        self.readoutSep.setGeometry(0, 35, self.readoutFrame.width(), self.readoutFrame.width())
        self.readoutSep.setFixedWidth(self.readoutFrame.width())
        self.readoutSep.setFixedHeight(1)
        self.readoutSep.setFrameShadow(QtGui.QFrame.Raised)
        self.readoutSep.setFrameShape(QtGui.QFrame.HLine)

        self.regionWidget = ReadoutRegionSettingsWidget(self.readoutFrame.width() - 30, 130, self)
        self.regionWidget.setGeometry(10, 45, self.readoutFrame.width() - 30, 130)

        self.regionSep = QtGui.QFrame(self.readoutFrame)
        self.regionSep.setGeometry(0, self.readoutSep.y() + self.regionWidget.height(), self.readoutFrame.width(), self.readoutFrame.width())
        self.regionSep.setFixedWidth(self.readoutFrame.width())
        self.regionSep.setFixedHeight(1)
        self.regionSep.setFrameShadow(QtGui.QFrame.Raised)
        self.regionSep.setFrameShape(QtGui.QFrame.HLine)

        self.samplesWidget = ReadoutSamplesSettingsWidget(self.readoutFrame.width() - 30, 100, self)
        self.samplesWidget.setGeometry(10, self.regionSep.y() + 5, self.readoutFrame.width() - 30, 100)

        self.samplesSep = QtGui.QFrame(self.readoutFrame)
        self.samplesSep.setGeometry(0, self.regionSep.y() + self.samplesWidget.height(), self.readoutFrame.width(), self.readoutFrame.width())
        self.samplesSep.setFixedWidth(self.readoutFrame.width())
        self.samplesSep.setFixedHeight(1)
        self.samplesSep.setFrameShadow(QtGui.QFrame.Raised)
        self.samplesSep.setFrameShape(QtGui.QFrame.HLine)

        self.zsWidget = ReadoutZeroSuppressionWidget(self.readoutFrame.width() - 30, 150, self)
        self.zsWidget.setGeometry(10, self.samplesSep.y() + 5, self.readoutFrame.width() - 30, 150)

        self.zsSep = QtGui.QFrame(self.readoutFrame)
        self.zsSep.setGeometry(0, self.samplesSep.y() + self.zsWidget.height(), self.readoutFrame.width(), self.readoutFrame.width())
        self.zsSep.setFixedWidth(self.readoutFrame.width())
        self.zsSep.setFixedHeight(1)
        self.zsSep.setFrameShadow(QtGui.QFrame.Raised)
        self.zsSep.setFrameShape(QtGui.QFrame.HLine)

        self.mebWidget = ReadoutMEBWidget(self.readoutFrame.width() - 30, 150, self)
        self.mebWidget.setGeometry(10, self.zsSep.y() + 5, self.readoutFrame.width() - 30, 150)

    def initApdWidgets(self):

        self.apdWidget = APDSettingSelectorWidget(self.apdFrame.width() - 30, 200, self.apdFrame)
        latest = self.databaseHandler.getLatestConfigId()
        id = latest
        self.configId = id

        comment = self.databaseHandler.getConfigComment(id)

        self.apdWidget.setConfig(id, latest, comment)

        self.connect(self.apdWidget, QtCore.SIGNAL("getConfig"), self.setApdConfig)
        self.connect(self.apdWidget, QtCore.SIGNAL("loadApdSettings"), self.loadApdSettings)

    def setApdConfig(self, id):
        
        comment = self.databaseHandler.getConfigComment(id)
        latest = self.databaseHandler.getLatestConfigId()
        self.apdWidget.setConfig(id, latest, comment)
        self.configId = id

    def getApdConfig(self):

        return self.configId

    def loadApdSettings(self, id):
        
        self.databaseHandler.loadApdValues(self.moduleId)
