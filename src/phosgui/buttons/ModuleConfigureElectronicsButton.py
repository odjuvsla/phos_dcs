from PhosModulePushButton import *

class ModuleConfigureElectronicsButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleConfigureElectronicsButton, self).__init__(parent, moduleId)

        self.setText("Configure Electronics")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.configureElectronicsModule)

    def configureElectronicsModule(self):
        
        self.emit(QtCore.SIGNAL("configureElectronicsModule"), "configureElectronicsModule", self.moduleId)
