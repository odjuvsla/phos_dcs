from PhosModulePushButton import *

class ModuleTurnOnButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOnButton, self).__init__(parent, moduleId)
        
        self.setText("Turn On Module Electronics")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOnModule)

    def turnOnModule(self):
        
        self.emit(QtCore.SIGNAL("turnOnModule"), "turnOnModule", self.moduleId)
