
from PyQt4 import QtCore, QtGui
from PhosConst import *
from phos_widgets import *


class ConnectSettingsDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(450, 530)
        
        self.initTabs()
        self.initButtons()

    def initTabs(self):
        
        self.tabs = QtGui.QTabWidget(self)
        self.tabs.setGeometry(10, 10, 0, 0)
        self.tabs.setFixedSize(self.width() - 25, self.height() - 90)
        self.settingsTabs = [None]*PHOS_MODS

        for i in range(PHOS_MODS):
            
            self.settingsTabs[i] = ConnectionSettingsTabWidget(i, self.width(), self.height(), self)
            self.tabs.addTab(self.settingsTabs[i], "Module " + str(i))
        
    def initButtons(self):

        self.buttonLayout = QtGui.QHBoxLayout(self)
        self.buttonLayout.setGeometry(QtCore.QRect(100, 460, 331, 61))

#        self.saveButton = PhosConfigSaveButton(self.buttonLayout)
        self.saveButton = QtGui.QPushButton(self)
#        self.saveButton.setConfigFile("../../../configurationFiles/feeServerNames.cfg")
        self.okButton = QtGui.QPushButton(self)
        self.cancelButton = QtGui.QPushButton(self)

        self.buttonLayout.addWidget(self.saveButton)
        self.buttonLayout.addWidget(self.okButton)
        self.buttonLayout.addWidget(self.cancelButton)

class RcuDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(640, 480)
