from PyQt4 import QtCore, QtGui

class APDSettingSelectorWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
 #       self.loadAPDSettings()
        self.initLabels()
        self.initSpinBox()
        self.initTextBrowser()
        self.initButtons()

#    def loadAPDSettings(self):
        
    def initLabels(self):
        
        self.apdLabel = QtGui.QLabel("APD Setting:", self)
        self.apdLabel.setGeometry(10, 10, 120, 20)
        
    def initSpinBox(self):
    
        self.apdSpinbox = QtGui.QSpinBox(self)
        self.apdSpinbox.setGeometry(self.apdLabel.x() + 120, self.apdLabel.y(), 60, 20)
        self.apdSpinbox.setMinimum(0)
        self.apdSpinbox.setMaximum(1023)
        self.apdSpinbox.setValue(0)
        
        self.connect(self.apdSpinbox, QtCore.SIGNAL("valueChanged(int)"), self.fetchConfig)
                                                     
    def initTextBrowser(self):
        
        self.apdTextEdit = QtGui.QTextBrowser(self)
        self.apdTextEdit.setGeometry(self.apdLabel.x(), self.apdLabel.y() + 30, self.width()-20, self.height() - self.apdLabel.y() - 50)

        self.apdTextEdit.setFixedSize(self.width()-10, self.height() - self.apdLabel.y() - 80)

    def setConfig(self, id, latest, description):
        
        self.apdSpinbox.setMaximum(latest)
        self.apdSpinbox.setValue(id)
        self.apdTextEdit.setText(description)
        self.configId = id

    def fetchConfig(self, id):
                
        self.emit(QtCore.SIGNAL("getConfig"), id)
    
    
    def initButtons(self):
             
        self.apdButtonLayoutWidget = QtGui.QWidget(self)
        self.apdButtonLayoutWidget.setGeometry(self.apdTextEdit.x(), self.apdTextEdit.y() + self.apdTextEdit.height() + 10, self.width()-20, self.height() - self.apdTextEdit.y() - self.apdTextEdit.height())

        self.apdButtonLayout = QtGui.QHBoxLayout(self.apdButtonLayoutWidget)

        self.loadApdButton = QtGui.QPushButton(self.apdButtonLayoutWidget)
        self.loadApdButton.setText("L&oad")
        
        self.applyApdButton = QtGui.QPushButton(self.apdButtonLayoutWidget)
        self.applyApdButton.setText("&Apply to Module")

        self.apdButtonLayout.addWidget(self.loadApdButton)
        self.apdButtonLayout.addWidget(self.applyApdButton)

        self.apdButtonLayoutWidget.setLayout(self.apdButtonLayout)

        self.connect(self.loadApdButton, QtCore.SIGNAL("clicked()"), self.loadApdSettings)
        
    def loadApdSettings(self):
        
        self.emit(QtCore.SIGNAL("loadApdSettings"), self.configId)
