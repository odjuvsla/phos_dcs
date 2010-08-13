from PyQt4 import QtCore, QtGui
#import pysvn

class FixedPedestalsSelectorWidget(QtGui.QWidget):
    
    def __init__(self, width, height, parent=None):
        super(QtGui.QWidget, self).__init__(parent)

        self.setGeometry(10, 15, width, height)
 #       self.loadAPDSettings()
#        self.initLabels()
        self.initCheckBoxSelectors()
        self.initSpinBox()
        self.initTextBrowser()
        self.initButtons()

#    def loadAPDSettings(self):
        
    # def initLabels(self):
        
#         self.fpLabel = QtGui.QLabel("Fixed Pedestals:", self)
#         self.fpLabel.setGeometry(10, 10, 120, 20)
        
    def initSpinBox(self):
    
        self.fpSpinbox = QtGui.QSpinBox(self)
        self.fpSpinbox.setGeometry(self.fpLabel.x() + 120, self.fpLabel.y(), 60, 20)
        self.fpSpinbox.setMinimum(0)
        self.fpSpinbox.setMaximum(1023)
        self.fpSpinbox.setValue(0)
        
        self.connect(self.fpSpinbox, QtCore.SIGNAL("valueChanged(int)"), self.getCommitMessage)

    def initCheckBoxSelectors(self):

        self.fpCheckBox = QtGui.QCheckBox(self)
        self.fpCheckBox.setText("Use fixed pedestals")
        self.fpCheckBox.setGeometry(10, 10, 120, 20)

    def initSpinBox(self):

        self.fpSbLabel = QtGui.QLabel("Revision #:", self)
        self.fpSbLabel.setGeometry(self.fpCheckBox.x() + self.fpCheckBox.width() + 10, self.fpCheckBox.y(), 60, 20)

        self.fpSpinbox = QtGui.QSpinBox(self)
        self.fpSpinbox.setGeometry(self.fpSbLabel.x() + self.fpSbLabel.width() + 20, self.fpCheckBox.y(), 60, 20)
        self.fpSpinbox.setMinimum(0)
        self.fpSpinbox.setMaximum(1023)
        self.fpSpinbox.setValue(0)
        
        self.connect(self.fpSpinbox, QtCore.SIGNAL("valueChanged(int)"), self.getCommitMessage)
                                                     
    def initTextBrowser(self):
        
        self.fpTextEdit = QtGui.QTextBrowser(self)
        self.fpTextEdit.setGeometry(self.fpCheckBox.x(), self.fpCheckBox.y() + 30, self.width()-20, self.height() - self.fpCheckBox.y() - 50)

        self.fpTextEdit.setFixedSize(self.width()-10, self.height() - self.fpCheckBox.y() - 60)

    def setCommitMessage(self, id, latest, description):
        
        self.fpSpinbox.setMaximum(latest)
        self.fpSpinbox.setValue(id)
        self.fpTextEdit.setText(description)
        self.configId = id

    def getCommitMessage(self, id):

        print ""
#        self.emit(QtCore.SIGNAL("getCommitMessage"), id)
    
    
    def initButtons(self):
             
        self.fpButtonLayoutWidget = QtGui.QWidget(self)
#        self.fpButtonLayoutWidget.setGeometry(self.fpTextEdit.x(), self.fpTextEdit.y() + self.fpTextEdit.height() + 10, self.width()-20, self.height() - self.fpTextEdit.y() - self.fpTextEdit.height())
        self.fpButtonLayoutWidget.setGeometry(self.fpTextEdit.x(), self.fpTextEdit.y() + self.fpTextEdit.height() + 10, self.width(), self.height() - self.fpTextEdit.y() - self.fpTextEdit.height())

        self.fpButtonLayout = QtGui.QHBoxLayout(self.fpButtonLayoutWidget)
        
        self.loadFpButton = QtGui.QPushButton(self.fpButtonLayoutWidget)
        self.loadFpButton.setFixedHeight(20)
        self.loadFpButton.setText("L&oad Values")
        self.loadFpButton.setEnabled(False)

        self.checkinFpButton = QtGui.QPushButton(self.fpButtonLayoutWidget)
        self.checkinFpButton.setFixedHeight(20)
        self.checkinFpButton.setText("Checkin &New File")
        self.checkinFpButton.setEnabled(False)


    def isAutoSubtracted(self):

        return self.fpCheckBox.isChecked() == False

    def setAutoSubtracted(self, status):

        self.fpCheckBox.setChecked(status)

    def isFixedSubtracted(self):

        return self.fpCheckBox.isChecked() == True

    def setFixedSubtracted(self, status):

        self.fpCheckBox.setChecked(status)
