#!/usr/bin/python

import sys
import copy
from PyQt4 import QtCore, QtGui, uic
from DcsInterface import *
from phos_interface import *
from phos_buttons import *

app = QtGui.QApplication(sys.argv)


# class testInterface(QtCore.QObject):

#     def __init__(self):

#         QtCore.QObject.__init__(self)
#         self.dcs_interface = DcsInterface()
#         self.dcs_interface_wrapper = DcsInterfaceThreadWrapper(self.dcs_interface)

# #        self.detector_handler = detectorHandler(self.dcs_interface)
#         self.fee_card_handler = FeeCardHandler(self.dcs_interface_wrapper)

#         feeServer = FeeServer()
        
#         feeServer.fName = "dcs0327"
#         feeServer.fModId = 0
#         feeServer.fRcuId = 0
#         feeServer.fZ = 0
#         feeServer.fX = 0

# #        self.detector_handler.addFeeServer(feeServer)
#  #       self.detector_handler.startFeeClient()

#         self.connect(self.fee_card_handler, QtCore.SIGNAL("fetchLog"), self.shout)

#     def toggle(self, cardId):
        
#         self.fee_card_handler.toggleOnOff(cardId)
        
#     def shout(self):
        
#         print "Shout!"


# test = testInterface()

# test.toggle(1)

# app.exec_()





class MainWindow(QtGui.QMainWindow):
    
    def __init__(self, parent = None):

        super(MainWindow, self).__init__(parent)

        QtCore.QObject.__init__(self)
        self.dcs_interface = DcsInterface()
        self.dcs_interface_wrapper = DcsInterfaceThreadWrapper(self.dcs_interface)
        
        self.fee_button = FeePushButton(self, 1)
        self.rcu_button = RcuUpdateStatusPushButton(self, 1)

        tmpQrect = copy.deepcopy(self.rcu_button.geometry())


        tmpQrect.setX(self.rcu_button.x() + self.rcu_button.width())
        tmpQrect.setWidth(self.rcu_button.width())
        self.fee_button.setGeometry(tmpQrect)

        self.fee_button.setText("FEE On/Off")

        self.rcu_button.setText("RCU Update")
        
        self.fee_card_handler = FeeCardHandler(self.dcs_interface_wrapper)
        self.rcu_handler = RcuHandler(self.dcs_interface_wrapper)


        self.connect(self.fee_button, QtCore.SIGNAL("toggleFee"), self.toggleOnOff)
        self.connect(self.fee_card_handler, QtCore.SIGNAL("cardToggled"), self.printstuff)
        self.connect(self.fee_card_handler, QtCore.SIGNAL("fetchLog"), self.fetchLog)

        self.connect(self.rcu_button, QtCore.SIGNAL("updateStatus"), self.updateStatus)
        self.connect(self.rcu_handler, QtCore.SIGNAL("statusUpdated"), self.printstuff)
        self.connect(self.rcu_handler, QtCore.SIGNAL("fetchLog"), self.fetchLog)

    def fetchLog(self):

        print "Fetch Log!" 

    def toggleOnOff(self, feeId):
        
        self.fee_card_handler.toggleOnOff(feeId)

    def updateStatus(self, rcuId):
        
        self.rcu_handler.updateStatus(rcuId)
        
    def printstuff(self, *args):
        
        print 'Operation finished!'

#        for val in args:
#        print args[0]
#        print args[1]

#         print "feeId: " + str(args[0])
#         print "state: " + str(args[1])


window = MainWindow()
window.show()
app.exec_()

        

    


