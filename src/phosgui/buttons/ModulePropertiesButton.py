from PhosModulePushButton import *

class ModulePropertiesButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModulePropertiesButton, self).__init__(parent, moduleId)

        self.setText("Module Properties")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.showModuleProperties)

    def showModuleProperties(self):
        
        self.emit(QtCore.SIGNAL("showModuleProperties"), "showModuleProperties", self.moduleId)
