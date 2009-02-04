import sys
import time
import copy

from PyQt4 import QtCore, QtGui
from DcsInterface import *
from threading import *


class PHOSHandler(QtCore.QObject):
    """Base class for the handlers"""

    def __init__(self):
        QtCore.QObject.__init__(self)

    def GetFeeLogicalIDs(self, feeId):
        """Helper funtion to extract the logical FEE card ID from absolute ID"""
        moduleId = feeId/(CARDS_PER_RCU*RCUS_PER_MODULE)
        cardIdInModule = feeId%(CARDS_PER_RCU*RCUS_PER_MODULE)
            
        rcuId = cardIdInModule/CARDS_PER_RCU
        cardIdInRcu = cardIdInModule%CARDS_PER_RCU
            
        branchId = cardIdInRcu/CARDS_PER_BRANCH
        cardIdInBranch = cardIdInRcu%CARDS_PER_BRANCH

        feeId = cardIdInBranch+1
    
        return moduleId, rcuId, branchId, feeId
    #------------------------------------------------------

    def GetRcuLogicalIDs(self, rcuId):
        """Helper funtion to extract the RCU ID from absolute ID"""
        moduleId = rcuId/RCUS_PER_MODULE
        rcuId = rcuId%RCUS_PER_MODULE
            
        return moduleId, rcuId
    #------------------------------------------------------

    def emit_signal(self, signal, *args):
        """Function for forwarding the signals from the thread"""        
        self.emit(QtCore.SIGNAL(signal), *args)
    #-----------------------------------------------------


class DcsInterfaceThreadWrapper():
    """PHOS Fee Client is not thread safe. Hence we need this class to protect it for threading"""

    def __init__(self, dcs_interface):
        """init function"""

        self.dcs_interface = dcs_interface
        self.lock = Lock()
    #-------------------------------------

    # Get the DcsInterface object
    def getDcsInterface(self):
        """Get the DcsInterface object"""

        # Acquire the lock and return the interface object
        self.lock.acquire()
        return self.dcs_interface
    #-------------------------------------


    def releaseDcsInterface(self):
        """Release the lock/object"""
        self.lock.release()
    #-------------------------------------

############################################################################## End of DcsInterfaceThreadWrapper class


############################################
# Class taking care of the FEE card commands
############################################
class FeeCardHandler(PHOSHandler):
    """Class taking care of the FEE card commands"""

    def __init__(self, dcs_interface_wrapper):
        """init takes DcsInterfaceThreadWrapper object as argument"""
        PHOSHandler.__init__(self)
        self.dcs_interface_wrapper = dcs_interface_wrapper
    #-----------------------------------------------------
        
    def toggleOnOff(self, feeId):
        """Function for toggling cards"""
        # Start a thread for the toggling
        self.feeId = feeId
        onOffThread = self.__ToggleOnOffThread(self.feeId, self.dcs_interface_wrapper)
        self.connect(onOffThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(onOffThread, QtCore.SIGNAL("cardToggled"), self.emit_signal)
        onOffThread.start()
    #-----------------------------------------------------

    def applyApdSettings(self, feeId):
        """Apply APD settings for this card"""

        self.feeId = feeId
        applyApdThread = self.__ApplyApdThread(self.feeId, self.dcs_interface_wrapper)
        self.connect(applyApdThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(applyApdThread, QtCore.SIGNAL("settingApplied"), self.emit_signal)
        applyApdThread.start()

    class __ToggleOnOffThread(Thread, PHOSHandler):
        """Member threading class"""
        
        def __init__(self, feeId, dcs_interface_wrapper):
            """init takes DcsInterfaceThreadWrapper and FEE ID (absolute number) as arguments"""

            self.feeId = feeId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            Thread.__init__(self)
            PHOSHandler.__init__(self)
        #------------------------------------------------

        def run(self):
            """Run the thread"""

            # Get the DcsInterface object
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()

            moduleId, rcuId, branchId, feeId = self.GetFeeLogicalIDs(self.feeId)

            currentstate = 0
            tmpStates = [0]*CARDS_PER_RCU
            state = 0
            
            # Here we do the toggling
            #state = dcs_interface.ToggleOnOffFee(moduleId, rcuId, branchId, feeId, currentstate, tmpStates)

            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog")

            # Emitting the card toggled signal together with the returned state of the card
            self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", feeId, state)

            # Release the DcsInterface object
            self.dcs_interface_wrapper.releaseDcsInterface()
            #---------------------------------------------
    ##################################################################### End of __ToggleOnOffThread class

    class __ApplyApdThread(Thread, PHOSHandler):
        """Member threading class for applying APD settings"""
        
        def __init__(self, feeId, dcs_interface_wrapper):
            """init takes DcsInterfaceThreadWrapper and FEE ID (absolute number) as arguments"""

            self.feeId = feeId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            Thread.__init__(self)
            PHOSHandler.__init__(self)
        #------------------------------------------------

        def run(self):
            """Run the thread"""

            # Get the DcsInterface object
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()

            moduleId, rcuId, branchId, feeId = self.GetFeeLogicalIDs(self.feeId)

            currentstate = 0
            tmpStates = [0]*CARDS_PER_RCU
            
            # Here we do the applying
            #dcs_interface.ApplyApdSettings(moduleId, rcuId, branchId, feeId)

            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog")

            # Emitting the applied signal
            self.emit(QtCore.SIGNAL("apdSettingApplied"), "apdSettingApplied", feeId)

            # Release the DcsInterface object
            self.dcs_interface_wrapper.releaseDcsInterface()
            #---------------------------------------------
    ##################################################################### End of __ApplyApdThread class

######################################################################################### End of FeeCardHandler class


class RcuHandler(PHOSHandler):
    """Class taking care of the FEE card command"""    

    def __init__(self, dcs_interface):
        """init takes DcsInterfaceThreadWrapper object as argument"""
        PHOSHandler.__init__(self)
        
        self.dcs_interface_wrapper = dcs_interface
    #-------------------------------------------------

    def toggleOnOff(self, rcuId):
        """Function for toggling on/off all FEE cards and TRU cards on the RCU"""
        
        # Start a thread for the toggling        
        onOffThread = self.__ToggleOnOffThread(rcuId, self.dcs_interface_wrapper)
        self.connect(onOffThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(onOffThread, QtCore.SIGNAL("cardsToggled"), self.emit_signal)
        onOffThread.start()
        updateStatus(rcuId)
    #-------------------------------------------------

    def updateStatus(self, rcuId):
        """Update the status of all cards"""
        updateStatusThread = self.__UpdateStatusThread(rcuId, self.dcs_interface_wrapper)
        self.connect(updateStatusThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(updateStatusThread, QtCore.SIGNAL("statusUpdated"), self.emit_signal)
        updateStatusThread.start()
    #------------------------------------------------
    
    class __ToggleOnOffThread(Thread, PHOSHandler):
        """Member threading class for toggle on/off all cards on RCU"""
        
        def __init__(self, rcuId, dcs_interface_wrapper):
            """init takes a DcsInterfaceThreadWrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)
            self.rcuId = rcuId
            self.dcs_interface_wrapper = dcs_interface

        def run(self):
            """Run the thread"""
            
            # Get the DcsInterface object
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
            
            moduleId, rcuId = self.GetRcuLogicalIDs(feeId)
            
            # Here we toggle
            dcs_interface.TurnOnAllFee(moduleId, rcuId)
            
            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog")
            
            # Emitting the cards toggled signal 
            self.emit(QtCore.SIGNAL("cardsToggled"), "cardsToggled")
            
            # Release the DcsInterface object
            self.dcs_interface_wrapper.releaseDcsInterface()
    #################################################################### End of __ToggleOnOffThread class

    class __UpdateStatusThread(Thread, PHOSHandler):
        """Member threading class for getting the up to date status of the FEE cards"""
        
        def __init__(self, rcuId, dcs_interface_wrapper):
            """init takes a Dcs_Interface_Wrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)

            self.rcuId = rcuId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            
        def run(self):
            
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
            
            moduleId, rcuId = self.GetRcuLogicalIDs(self.rcuId)
            status = 0
#            status = vectorint(1)
            
#            dcs_interface.UpdateFeeStatus(moduleId, rcuId, status)

            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog")
            
            self.emit(QtCore.SIGNAL("statusUpdated"), "statusUpdated", status)

            self.dcs_interface_wrapper.releaseDcsInterface()

class ModuleHandler():
    
    def __init__(self, dcs_interface):

        print 'starting module handler'
        
    def turnOnOff(moduleId):
        
        print 'turning on/off ' + str(moduleId)
        
class DetectorHandler():

    def __init__(self, dcs_interface):

        print 'starting detector handler'
        
        self.dcs_interface = dcs_interface
        
        self.fee_servers = vectorfee(PHOS_MODS*RCUS_PER_MODULE)
        self.fee_servers.clear()
    
    def turnOnOff(self):
        
        print 'turning on/off PHOS' 

    def addFeeServer(self, feeServer):

        self.fee_servers.push_back(feeServer)
        print 'adding fee server'

    def startFeeClient(self):
        
#        self.dcs_interface.Init(fee_servers)
        print 'starting fee client'

    def stopFeeClient(self):

        self.dcs_interface.DeInit()
        self.fee_servers.clear()
        print 'stopping fee client'

