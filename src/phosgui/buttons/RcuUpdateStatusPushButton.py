from PhosPushButton import *

class RcuUpdateStatusPushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId, rcuId):

        super(RcuUpdateStatusPushButton, self).__init__(parent)
        
        self.setText("Update Status")

        self.setFixedWidth(110)
        
        self.setFixedHeight(25)

        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.updateStatus)

    def updateStatus(self):
        
        self.emit(QtCore.SIGNAL("rcuUpdateStatus"), "rcuUpdateStatus", self.rcuId)
