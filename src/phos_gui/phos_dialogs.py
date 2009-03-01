
from PyQt4 import QtCore, QtGui
from PhosConst import *


class ConnectSettingsDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(640, 480)
        
        self.initTabs()
        
    def initTabs(self):
        
        self.tabs = QtGui.QTabWidget(self)

        self.settingsTabs = [None]*PHOS_MODS

        for i in range(PHOS_MODS):
            
            self

    def initCheckBoxes(self):
        
        print "init check boxes"

    def initSetupButtons(self):

        print "init setup buttons"

class RcuDialog(QtGui.QDialog):
    """Connection dialog"""

    def __init__(self, parent=None):
        super(QtGui.QDialog, self).__init__(parent)

        self.resize(640, 480)
