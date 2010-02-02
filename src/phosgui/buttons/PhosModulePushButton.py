from PhosPushButton import *

class PhosModulePushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId):
        
        super(PhosPushButton, self).__init__(parent)

        self.moduleId = moduleId
