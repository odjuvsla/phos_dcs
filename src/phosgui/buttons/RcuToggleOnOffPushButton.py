from PhosPushButton import *

class RcuToggleOnOffPushButton(PhosPushButton):

    def __init__(self, parent, moduleId, rcuId, on):

        super(RcuToggleOnOffPushButton, self).__init__(parent)

        self.on = on

        if on == True:
            self.setText("On")

        if on == False:
            self.setText("Off")

        self.setFixedWidth(52)
        self.setFixedHeight(25)
            
        self.rcuId = self.idConverter.RcuAbsoluteID(moduleId, rcuId)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)

    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("rcuToggleOnOff"), "rcuToggleOnOff", self.rcuId, self.on)
