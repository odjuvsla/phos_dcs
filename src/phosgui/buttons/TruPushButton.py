from PhosPushButton import *


class TruPushButton(PhosPushButton):

    def __init__(self, parent, truId):
        
        super(TruPushButton, self).__init__(parent) 
        
        self.truId = truId
        
        if truId%2 == 0:
            self.setText("A")
        else:
            self.setText("B")
        
        self.setFixedWidth(16)
        self.setFixedHeight(110)

        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

        self.viewTruAction = QtGui.QAction("View TRU", self)

        self.addAction(self.viewTruAction)

        self.connect(self.viewTruAction, QtCore.SIGNAL("triggered()"), self.viewTru)
        self.connect(self, QtCore.SIGNAL("clicked()"), self.toggleOnOff)
 
    def toggleOnOff(self):

        self.emit(QtCore.SIGNAL("toggleTru"), "toggleTru", self.truId)

    def viewTru(self):

        self.emit(QtCore.SIGNAL("viewTru"), "viewTru", self.truId)
