from PhosModulePushButton import *

class ModuleTurnOnButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOnButton, self).__init__(parent, moduleId)
        self.palette().setColor(QtGui.QPalette.Button, QtGui.QColor(0, 255, 0))
        self.setText("GO READY")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOnModule)

    def turnOnModule(self):
        
        self.emit(QtCore.SIGNAL("turnOnModule"), "turnOnModule", self.moduleId)
