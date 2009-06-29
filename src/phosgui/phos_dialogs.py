import copy
from PyQt4 import QtCore, QtGui
from PhosConst import *
from PhosDataTypes import *
from phos_widgets import *


class ConnectSettingsDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, feeServerNames, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(450, 530)
        
        self.feeServerNames = feeServerNames

        self.initTabs()
        self.initButtons()
        self.initConnections()

        self.feeServerFile = "../GuiConfigurationFiles/feeServerNames.cfg"

        self.feeServerNames = [" "]*(PHOS_MODS*RCUS_PER_MODULE+1)
        self.feeServerEnabled = [False]*(PHOS_MODS*RCUS_PER_MODULE+1)
        self.getFeeServers()
        self.loadFromFile()
        
    def initTabs(self):
        
        self.tabs = QtGui.QTabWidget(self)
        self.tabs.setGeometry(10, 10, 0, 0)
        self.tabs.setFixedSize(self.width() - 25, self.height() - 90)
        self.settingsTabs = [None]*(PHOS_MODS+1)

        for i in range(PHOS_MODS):
            
            self.settingsTabs[i] = ConnectionSettingsModuleTabWidget(i, self.width(), self.height(), self)
            self.tabs.addTab(self.settingsTabs[i], "Module " + str(i))
            
        self.settingsTabs[PHOS_MODS] = ConnectionSettingsBusyboxTabWidget(self.width(), self.height(), self)
        self.tabs.addTab(self.settingsTabs[PHOS_MODS], "Busybox")

    def initButtons(self):

        self.buttonLayoutWidget = QtGui.QWidget(self)
        self.buttonLayoutWidget.setGeometry(QtCore.QRect(110, 460, 330, 60))

        self.buttonLayout = QtGui.QHBoxLayout(self.buttonLayoutWidget)

        self.saveButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.saveButton.setText("&Save")
        
        self.okButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.okButton.setText("&Ok")

        self.cancelButton = QtGui.QPushButton(self.buttonLayoutWidget)
        self.cancelButton.setText("&Cancel")

        self.buttonLayout.addWidget(self.saveButton)
        self.buttonLayout.addWidget(self.okButton)
        self.buttonLayout.addWidget(self.cancelButton)

        self.buttonLayoutWidget.setLayout(self.buttonLayout)

    def initConnections(self):

        self.connect(self.saveButton, QtCore.SIGNAL("clicked()"), self.saveToFile)
        self.connect(self.okButton, QtCore.SIGNAL("clicked()"), self.settingsOk)
        self.connect(self.cancelButton, QtCore.SIGNAL("clicked()"), self.cancelSettings)

    def saveToFile(self):
        
        self.getFeeServers()
        FEEFILE = open(self.feeServerFile, "w") 
        feeLines = []
        
        for i in range(PHOS_MODS):
            for j in range(RCUS_PER_MODULE):
                feeLines.append(self.feeServerNames[i*(RCUS_PER_MODULE) + j] + " " +  str(self.feeServerEnabled[i*(RCUS_PER_MODULE) + j]) + "\n")
        feeLines.append(self.feeServerNames[PHOS_MODS*(RCUS_PER_MODULE)]+ " " + str(self.feeServerEnabled[PHOS_MODS*(RCUS_PER_MODULE)]) + "\n")
        FEEFILE.writelines(feeLines)
        FEEFILE.close()

    def loadFromFile(self):

        FEEFILE = open(self.feeServerFile, "r")
        n = 0
        for line in FEEFILE.readlines():

            self.feeServerNames[n] = line.split(" ")[0]
            if line.split(" ")[1].strip() == "True":
                self.feeServerEnabled[n] = True
            else:
                self.feeServerEnabled[n] = False
            n += 1

        for i in range(PHOS_MODS):
            for j in range(RCUS_PER_MODULE):
                self.settingsTabs[i].feeServerRcuLineEdit[j].setText(self.feeServerNames[i*RCUS_PER_MODULE + j])
                self.settingsTabs[i].enabledRcuBoxes[j].setChecked(self.feeServerEnabled[i*RCUS_PER_MODULE + j])

    def settingsOk(self):
        
        self.emit(QtCore.SIGNAL("fetchFeeServer"))
        self.close()

    def cancelSettings(self):

        self.close()

    def getFeeServers(self):
        
        for i in range(PHOS_MODS):
            for j in range(RCUS_PER_MODULE):
                self.feeServerNames[i*RCUS_PER_MODULE + j] = self.settingsTabs[i].feeServerRcuLineEdit[j].text()
                self.feeServerEnabled[i*RCUS_PER_MODULE + j] = bool(self.settingsTabs[i].enabledRcuBoxes[j].checkState())
        return self.feeServerNames, self.feeServerEnabled
    
class RcuDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(640, 480)
        
        self.initGeneralInfoFrame()
        self.initRegistersFrame()
        self.initRdoInfoFrame()
        self.initCloseButton()

        self.initWidgets()
    
    def initGeneralInfoFrame(self): 
        
        self.infoFrame = QtGui.QFrame(self)
        self.infoFrame.setGeometry(10, 10, self.width()/2 - 10, self.height() - 60)
        self.infoFrame.setFixedSize(self.width()/2 - 20, self.height()/4)
        self.infoFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.infoFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    
    def initRegistersFrame(self):
                
        self.regFrame = QtGui.QFrame(self)
        self.regFrame.setGeometry(self.width()/2 + 10, 10, self.width()/2 - 10, self.height() - 10)
        self.regFrame.setFixedSize(self.width()/2 - 20, self.height() - 20)
        self.regFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.regFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    def initRdoInfoFrame(self):
        
        
        self.rdoFrame = QtGui.QFrame(self)
        self.rdoFrame.setGeometry(10, self.infoFrame.y() + self.infoFrame.height() + 10, self.width()/2 - 10, self.height() - 60)
#        self.rdoFrame.setGeometry(10, 10 + self.infoFrame.height() + 10, self.width()/2 - 10, self.height() - 60)
        self.rdoFrame.setFixedSize(self.width()/2 - 20,  self.height()/4)
        self.rdoFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.rdoFrame.setFrameShadow(QtGui.QFrame.Raised)
        
    def initCloseButton(self):
        
        print 'init close button'
        
    def initWidgets(self):
        
        self.genInfoWidget = RcuGeneralInfoWidget(self.infoFrame.width() - 10, self.infoFrame.height() - 10, self.infoFrame)
        self.regWidget = RcuRegistersWidget(self.regFrame.width() - 10, self.regFrame.height() - 10, self.regFrame)
#        self.rdoInfo = RcuRdoInfoWidget()
        
class ConfigureElectronicsDialog(QtGui.QDialog):
    """Dialog for setting up the electronics configuration"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(700, 560)

        self.initButtons()
        self.initConnections()


    def start(self, moduleHandler, databaseHandler, moduleId):

        self.moduleHandler = moduleHandler
        self.databaseHandler = databaseHandler
        self.moduleId = moduleId

        self.initFrames()

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

        print 'saveToFile'

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

    def loadApdSettings(self, id):
        
        self.databaseHandler.loadApdValues(self.moduleId)

