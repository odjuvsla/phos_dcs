from PyQt4 import QtCore, QtGui
        
class RcuTopFrame(QtGui.QFrame):
    """Top frame for the RCUs"""

    def __init__(self, parent):
        
        super(QtGui.QFrame, self).__init__(parent)

        self.initSeparatorLines()
        
        self.initTextLabels()
        
        self.setFrameShadow(QtGui.QFrame.Raised)
        self.setFrameShape(QtGui.QFrame.StyledPanel)
        self.setFixedWidth(650)
        self.setFixedHeight(40)

    def initSeparatorLines(self):

        self.firstSep = QtGui.QFrame(self)
        self.firstSep.setGeometry(40, 0, 40, 40)
        self.firstSep.setFixedWidth(1)
        self.firstSep.setFixedHeight(38)
        self.firstSep.setFrameShadow(QtGui.QFrame.Raised)
        self.firstSep.setFrameShape(QtGui.QFrame.VLine)
        
        self.secondSep = QtGui.QFrame(self)
        self.secondSep.setGeometry(230, 0, 40, 40)
        self.secondSep.setFixedWidth(1)
        self.secondSep.setFixedHeight(40)
        self.secondSep.setFrameShadow(QtGui.QFrame.Raised)
        self.secondSep.setFrameShape(QtGui.QFrame.VLine)

        self.thirdSep = QtGui.QFrame(self)
        self.thirdSep.setGeometry(420, 0, 40, 40)
        self.thirdSep.setFixedWidth(1)
        self.thirdSep.setFixedHeight(40)
        self.thirdSep.setFrameShadow(QtGui.QFrame.Raised)
        self.thirdSep.setFrameShape(QtGui.QFrame.VLine)

        self.fourthSep = QtGui.QFrame(self)
        self.fourthSep.setGeometry(490, 0, 40, 40)
        self.fourthSep.setFixedWidth(1)
        self.fourthSep.setFixedHeight(40)
        self.fourthSep.setFrameShadow(QtGui.QFrame.Raised)
        self.fourthSep.setFrameShape(QtGui.QFrame.VLine)

    def initTextLabels(self):

        self.feeALabel = QtGui.QLabel("Front End Cards Branch B", self)
        self.feeALabel.setGeometry(65, 10, 160, 20)
        self.feeBLabel = QtGui.QLabel("Front End Cards Branch A", self)
        self.feeBLabel.setGeometry(255, 10, 160, 20)
        self.truLabel = QtGui.QLabel("TRU A/B", self)
        self.truLabel.setGeometry(430, 10, 60, 20)
        self.actionsLabel = QtGui.QLabel("Actions", self)
        self.actionsLabel.setGeometry(550, 10, 60, 20)
