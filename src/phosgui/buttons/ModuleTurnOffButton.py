from PhosModulePushButton import *

class ModuleTurnOffButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleTurnOffButton, self).__init__(parent, moduleId)

        self.setText("Shutdown Module Electronics")
       
        self.connect(self, QtCore.SIGNAL("clicked()"), self.turnOffModule)

    def turnOffModule(self):
        
        self.emit(QtCore.SIGNAL("shutdownModule"), "shutdownModule", self.moduleId)
