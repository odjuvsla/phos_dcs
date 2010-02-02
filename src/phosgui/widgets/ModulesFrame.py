from PyQt4 import QtCore, QtGui

class ModulesFrame(QtGui.QFrame):
    """Frame containg the PHOS modules"""

    def __init__(self, parent=None):

        super(QtGui.QFrame, self).__init__(parent)
        
        self.setFrameShadow(QtGui.QFrame.Raised)
        self.setFrameShape(QtGui.QFrame.StyledPanel)
        self.setFixedWidth(650)
        self.setFixedHeight(40)

