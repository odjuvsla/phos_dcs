from PhosModulePushButton import *

class ModuleDisableTriggerButton(PhosModulePushButton):
    
    def __init__(self, parent, moduleId):
        
        super(ModuleDisableTriggerButton, self).__init__(parent, moduleId)

        self.setText("Disable Trigger")
        
        self.connect(self, QtCore.SIGNAL("clicked()"), self.disableTriggerModule)

    def disableTriggerModule(self):
        
        self.emit(QtCore.SIGNAL("disableTriggerModule"), "disableTriggerModule", self.moduleId)
