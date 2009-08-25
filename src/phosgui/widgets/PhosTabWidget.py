from PyQt4 import QtCore, QtGui
from ModulesFrame import *
from PhosConst import *
from Module import *

class PhosTabWidget(QtGui.QWidget):
    """PHOS tab widget"""

    def __init__(self, parent=None):

        super(QtGui.QWidget, self).__init__(parent)
        self.initModules()

    def initModules(self):

        self.modulesFrame = ModulesFrame(self)
        self.modulesFrame.setGeometry(20, 0, 650, 40)

        self.modules = [None]*PHOS_MODS

        for i in range(PHOS_MODS):

            self.modules[i] = Module(i, self)

            self.modules[i].geometry().setX(20)
            self.modules[i].geometry().setY((i*self.modules[i].geometry().height() + self.modulesFrame.geometry().y() + self.modulesFrame.geometry().height()))
