from PhosModulePushButton import *

class ModuleTurnOffButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOffButton, self).__init__(parent, moduleId)
        self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(255, 0, 0))
        self.setText("RESET")
       
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOffModule)

    def turnOffModule(self):
        
        self.emit(QtCore.SIGNAL("shutdownModule"), "shutdownModule", self.moduleId)
