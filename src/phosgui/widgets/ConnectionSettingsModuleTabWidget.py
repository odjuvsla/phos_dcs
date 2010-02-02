from PyQt4 import QtCore, QtGui
from PhosConst import *

class ConnectionSettingsModuleTabWidget(QtGui.QWidget):
    """Module tab for the connection settings dialog"""

    def __init__(self, moduleId, width, height, parent = None):
        super(QtGui.QWidget, self).__init__(parent)

        self.moduleId = moduleId
       
        self.setGeometry(10, 10, width - 25, height - 90)
        self.setFixedSize(width - 25, height - 90)
        
        self.initFrame()
        self.initConnections()
        
    def initFrame(self):
        
        self.mainFrame = QtGui.QFrame(self)
        self.mainFrame.setGeometry(10, 10, self.width() - 40, self.height() - 60)
        self.mainFrame.setFixedSize(self.width() - 40, self.height() - 60)
        self.mainFrame.setFrameShape(QtGui.QFrame.StyledPanel);
        self.mainFrame.setFrameShadow(QtGui.QFrame.Raised);

        self.initFeeNameLineEdits()
        self.initCheckBoxes()
        self.initLabels()

    def initFeeNameLineEdits(self):

        self.feeNameLayoutWidget = QtGui.QWidget(self.mainFrame)
        
#        self.feeNameLayoutWidget.setGeometry(QtCore.QRect(10, 40, self.tabWidth - 90, self.tabHeight - 120))
        self.feeNameLayoutWidget.setGeometry(QtCore.QRect(10, 40, 230, 310))
        self.feeServerNameLayout = QtGui.QVBoxLayout(self.feeNameLayoutWidget)
 
        self.feeServerRcuLineEdit = [None]*RCUS_PER_MODULE

        for i in range(RCUS_PER_MODULE):
            
            self.feeServerRcuLineEdit[i] = QtGui.QLineEdit(self.feeNameLayoutWidget)
            self.feeServerRcuLineEdit[i].setFixedSize(230, 30)
#            self.feeServerRcuLineEdit[i].setEnabled(0)
            self.feeServerNameLayout.addWidget(self.feeServerRcuLineEdit[i])
        
        self.feeNameLayoutWidget.setLayout(self.feeServerNameLayout)
        
    def initCheckBoxes(self):

        self.enabledLayoutWidget = QtGui.QWidget(self.mainFrame)
        self.enabledLayoutWidget.setGeometry(QtCore.QRect(250, 40, 120, 310))

        self.enabledLayout = QtGui.QVBoxLayout(self.enabledLayoutWidget)

        self.enabledRcuBoxes = [None]*RCUS_PER_MODULE

        for i in range(RCUS_PER_MODULE):
            
            self.enabledRcuBoxes[i] = QtGui.QCheckBox(self.enabledLayoutWidget)
            self.enabledRcuBoxes[i].setText("RCU " + str(i))
            self.enabledLayout.addWidget(self.enabledRcuBoxes[i])

        self.enabledLayoutWidget.setLayout(self.enabledLayout)
        
    def initLabels(self):
        
        self.feeNameLabel = QtGui.QLabel("FeeServer Names:", self.mainFrame)
        self.feeNameLabel.setGeometry(10, 15, 130, 20)
        
        self.enabledLabel = QtGui.QLabel("Enabled:", self.mainFrame)
        self.enabledLabel.setGeometry(250, 15, 60, 20)

    def initConnections(self):

        for i in range(RCUS_PER_MODULE):
            self.connect(self.enabledRcuBoxes[i], QtCore.SIGNAL("stateChanged"), self.feeServerRcuLineEdit[i].setEnabled)
