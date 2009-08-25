from PyQt4 import QtCore, QtGui

class Module(QtGui.QWidget):
    """The module widget"""

    def __init__(self, moduleId, parent=None):

        super(QtGui.QWidget, self).__init__(parent)

        self.moduleId = moduleId

        self.initFrame()
        self.initTextLabels()
  #      self.initStatusIndicators()
        
        self.geometry().setHeight(110)
        
    def initFrame(self):

        self.moduleFrame = QtGui.QFrame(self)

        self.moduleFrame.setFrameShadow(QtGui.QFrame.Raised)
        self.moduleFrame.setFrameShape(QtGui.QFrame.StyledPanel)
        self.moduleFrame.setFixedWidth(650)
        self.moduleFrame.setFixedHeight(110)

    def initTextLabels(self):

        self.moduleLabel = QtGui.QLabel(self)

        self.moduleLabel.setText("Module #" + str(self.moduleId))

        self.moduleLabel.setGeometry(20, 10, 90, 30)


#    def initStatusIndicators(self):

        
 #       self.moduleIndicator = ModuleIndicator(self)

        
