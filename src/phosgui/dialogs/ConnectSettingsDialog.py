from PyQt4 import QtCore, QtGui
from PhosConst import *
from ConnectionSettingsModuleTabWidget import *
from ConnectionSettingsBusyboxTabWidget import *

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
 
