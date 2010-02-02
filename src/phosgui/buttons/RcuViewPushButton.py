from PhosPushButton import *

class RcuViewPushButton(PhosPushButton):
    
    def __init__(self, parent, moduleId, rcuId):
        
        super(RcuViewPushButton, self).__init__(parent)

        self.setText("RCU View")
        
        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)

        self.setFixedWidth(110)
        self.setFixedHeight(25)

        self.connect(self, QtCore.SIGNAL("clicked()"), self.viewRcu)

    def viewRcu(self):

        self.emit(QtCore.SIGNAL("viewRcu"), "viewRcu", self.rcuId)
