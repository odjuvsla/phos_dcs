from PhosModulePushButton import *

class ModuleEnableTriggerButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleEnableTriggerButton, self).__init__(parent, moduleId)

        self.setText("Enable Trigger")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.enableTriggerModule)

    def enableTriggerModule(self):
        
        self.emit(QtCore.SIGNAL("enableTriggerModule"), "enableTriggerModule", self.moduleId)
