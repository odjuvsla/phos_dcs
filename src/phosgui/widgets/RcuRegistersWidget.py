from PyQt4 import QtCore, QtGui

class RcuRegistersWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
        self.layoutWidget = parent
        self.widgetLayout = QtGui.QVBoxLayout(parent)
        self.initWidgets()
        
    def initWidgets(self):
        
        self.altroIfLabel = QtGui.QLabel("ALTROIF:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroIfLabel)

        self.altroIfTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroIfTextBox)

        self.trgConfLabel = QtGui.QLabel("TRGCONF:", self.layoutWidget)
        self.widgetLayout.addWidget(self.trgConfLabel)

        self.trgConfTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.trgConfTextBox)

        self.rdoModLabel = QtGui.QLabel("RDOMOD:", self.layoutWidget)
        self.widgetLayout.addWidget(self.rdoModLabel)

        self.rdoModTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.rdoModTextBox)

        self.altroCfg1Label = QtGui.QLabel("ALTROCFG1:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg1Label)

        self.altroCfg1TextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg1TextBox)

        self.altroCfg2Label = QtGui.QLabel("ALTROCFG2:", self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg2Label)

        self.altroCfg2TextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.altroCfg2TextBox)
        
        self.rcuVersionLabel = QtGui.QLabel("RCU_VERSION:", self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuVersionLabel)

        self.rcuVersionTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.rcuVersionTextBox)

        self.bpVersionLabel = QtGui.QLabel("BP_VERSION:", self.layoutWidget)
        self.widgetLayout.addWidget(self.bpVersionLabel)

        self.bpVersionTextBox = QtGui.QLineEdit(self.layoutWidget)
        self.widgetLayout.addWidget(self.bpVersionTextBox)
