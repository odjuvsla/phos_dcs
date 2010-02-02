from PyQt4 import QtCore, QtGui
from PhosIdConverter import *

class PhosPushButton(QtGui.QPushButton):

    def __init__(self, parent=None):
        
        super(QtGui.QPushButton, self).__init__(parent)
        
        self.idConverter = PhosIdConverter()
