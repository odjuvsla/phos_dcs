import sys
import time
import copy

from PyQt4 import QtCore, QtGui
from DcsInterface import *
from PhosConst import *
from phos_utilities import *
from threading import *


class PHOSHandler(QtCore.QObject):
    """Base class for the handlers"""

    def __init__(self):
        super(PHOSHandler, self).__init__()

        self.idConverter = PhosIdConverter()

#    def emit_signal(self, signal, *args):
    def emit_signal(self, *args):
        """Function for forwarding the signals from the thread"""      
        print 'emitting ' + args[0]
        self.emit(QtCore.SIGNAL(args[0]), *args)
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
#        PHOSHandler.__init__(self)
        super(FeeCardHandler, self).__init__()
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

        applyApdThread = self.__ApplyApdThread(feeId, self.dcs_interface_wrapper)
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

            moduleId, rcuId, branchId, feeId = self.idConverter.GetFeeLogicalIDs(self.feeId)
            print 'toggling card'
            currentstate = 0
            tmpStates = [0]*CARDS_PER_RCU
            state = 0
            
            # Here we do the toggling
            #state = dcs_interface.ToggleOnOffFee(moduleId, rcuId, branchId, feeId, currentstate, tmpStates)
            
            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)

            # Emitting the card toggled signal together with the returned state of the card
            self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", self.feeId, state)

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

            moduleId, rcuId, branchId, feeId = self.idConverter.GetFeeLogicalIDs(self.feeId)

            currentstate = 0
            tmpStates = [0]*CARDS_PER_RCU
            
            # Here we do the applying
            #dcs_interface.ApplyApdSettings(moduleId, rcuId, branchId, feeId)

            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)

            # Emitting the applied signal
            self.emit(QtCore.SIGNAL("apdSettingApplied"), "apdSettingApplied", self.feeId)

            # Release the DcsInterface object
            self.dcs_interface_wrapper.releaseDcsInterface()
            #---------------------------------------------
    ##################################################################### End of __ApplyApdThread class

######################################################################################### End of FeeCardHandler class

############################################
# Class taking care of the TRU card commands
############################################
class TruCardHandler(PHOSHandler):
    """Class taking care of the TRU card commands"""

    def __init__(self, dcs_interface_wrapper):
        """init takes DcsInterfaceThreadWrapper object as argument"""
#        PHOSHandler.__init__(self)
        super(TruCardHandler, self).__init__()
        self.dcs_interface_wrapper = dcs_interface_wrapper

    #-----------------------------------------------------
        
    def toggleOnOff(self, truId):
        """Function for toggling cards"""
        # Start a thread for the toggling
        self.truId = truId
        onOffThread = self.__ToggleOnOffThread(self.truId, self.dcs_interface_wrapper)
        self.connect(onOffThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(onOffThread, QtCore.SIGNAL("truToggled"), self.emit_signal)
        onOffThread.start()
    #-----------------------------------------------------

    class __ToggleOnOffThread(Thread, PHOSHandler):
        """Member threading class"""
        
        def __init__(self, truId, dcs_interface_wrapper):
            """init takes DcsInterfaceThreadWrapper and TRU ID (absolute number) as arguments"""

            self.truId = truId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            Thread.__init__(self)
            PHOSHandler.__init__(self)
        #------------------------------------------------

        def run(self):
            """Run the thread"""

            # Get the DcsInterface object
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()

            moduleId, rcuId, truId = self.idConverter.GetTruLogicalIDs(self.truId)

            state = 0
         
            # Here we do the toggling
            #state = dcs_interface.ToggleOnOffTru(moduleId, rcuId, truId)

            # Emitting signal for fetching log information
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)

            # Emitting the card toggled signal together with the returned state of the card
            self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", self.truId, state)

            # Release the DcsInterface object
            self.dcs_interface_wrapper.releaseDcsInterface()
            #---------------------------------------------
    ##################################################################### End of __ToggleOnOffThread class

######################################################################################### End of TruCardHandler class


class RcuHandler(PHOSHandler):
    """Class taking care of the FEE card command"""    

    def __init__(self, dcs_interface):
        """init takes DcsInterfaceThreadWrapper object as argument"""
#        PHOSHandler.__init__(self)
        super(RcuHandler, self).__init__()        
        self.dcs_interface_wrapper = dcs_interface
        self.feeHandler = FeeCardHandler(self.dcs_interface_wrapper)
    #-------------------------------------------------

    def toggleOnOff(self, rcuId):
        """Function for toggling on/off all FEE cards and TRU cards on the RCU"""
#        self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", 1, FEE_STATE_ON)         
        
        # Start a thread for the toggling        
        onOffThread = self.__ToggleOnOffThread(rcuId, self.dcs_interface_wrapper, self.feeHandler)
        self.connect(onOffThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(onOffThread, QtCore.SIGNAL("cardsToggled"), self.emit_signal)
        self.connect(self.feeHandler, QtCore.SIGNAL("cardToggled"), self.emit_signal)
        onOffThread.start()
#        self.updateStatus(rcuId)
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
        
        def __init__(self, rcuId, dcs_interface_wrapper, feeHandler):
            """init takes a DcsInterfaceThreadWrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)
            self.rcuId = rcuId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.feeHandler = feeHandler
            
        def run(self):
            """Run the thread"""
            
            for i in range(CARDS_PER_RCU):
                feeId = self.rcuId*CARDS_PER_RCU + i
                self.feeHandler.toggleOnOff(feeId)
            # Emitting the cards toggled signal 
            self.emit(QtCore.SIGNAL("cardsToggled"), "cardsToggled")
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)
            
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
            
            moduleId, rcuId = self.idConverter.GetRcuLogicalIDs(self.rcuId)

            status = dcs_interface.UpdateFeeStatus(moduleId, rcuId)
            
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)
            
            self.emit(QtCore.SIGNAL("statusUpdated"), "statusUpdated", status)

            self.dcs_interface_wrapper.releaseDcsInterface()

class ModuleHandler(PHOSHandler):
    
    def __init__(self, dcs_interface):
        super(ModuleHandler, self).__init__()
               
    def turnOn(self, moduleId):
        
        print 'Turning on module: ' + str(moduleId)
        
    def shutdown(self, moduleId):
        
        print "Shutting down module: " + str(moduleId)

    def enableTrigger(self, moduleId):
        
        print "Enabling trigger for module: " + str(moduleId)

    def disableTrigger(self, moduleId):

        print "Disabling trigger for module: " + str(moduleId)

class DetectorHandler(PHOSHandler):

    def __init__(self, dcs_interface):
        super(DetectorHandler, self).__init__()

        self.dcs_interface = dcs_interface
        
        self.fee_servers = vectorfee(PHOS_MODS*RCUS_PER_MODULE)
        self.fee_servers.clear()

    def turnOnOff(self):
        
        print 'turning on/off PHOS' 

    def addFeeServer(self, feeServer, id):

        tmpFeeServer = FeeServer()
        
        tmpFeeServer.fName = str(feeServer)
        moduleId, rcuId, x, z = self.idConverter.GetRcuLogicalCoordinatesFromFeeServerId(id)
        tmpFeeServer.fModId = moduleId
        tmpFeeServer.fRcuId = rcuId
        tmpFeeServer.fZ = z
        tmpFeeServer.fX = x

        self.fee_servers.push_back(tmpFeeServer)
        
    def startFeeClient(self):
        
        self.dcs_interface.getDcsInterface().Init(self.fee_servers)
        self.dcs_interface.releaseDcsInterface()
        self.fee_servers.clear()

    def stopFeeClient(self):

        self.dcs_interface.DeInit()
        self.fee_servers.clear()

    def connectToFeeServers(self, feeServerNames, feeServerEnabled):
        
        for i in range(len(feeServerNames)):
            if feeServerEnabled[i] == True:
                self.addFeeServer(feeServerNames[i], i)

        self.startFeeClient()
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID
        
class LogHandler(PHOSHandler):
    """Class for handling the logging system"""

    def __init__(self, dcs_interface):
        """init takes a DcsInterfaceThreadWrapper object as argument"""
        PHOSHandler.__init__(self)
        self.dcs_interface_wrapper = dcs_interface

    def getLogString(self, moduleId):
        """ Gets log strings from the different modules"""
        
        getLogThread = self.__GetLogThread(moduleId, self.dcs_interface_wrapper)

        self.connect(getLogThread, QtCore.SIGNAL("gotLog"), self.emit_signal)

        getLogThread.start()

    class __GetLogThread(Thread, PHOSHandler):
        """Member threading class for getting the log"""
        
        def __init__(self, moduleId, dcs_interface_wrapper):
            """init takes DcsInterfaceThreadWrapper and module ID as argument"""

            self.moduleId = moduleId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            Thread.__init__(self)
            PHOSHandler.__init__(self)

        def run(self):
            """Run the thread"""
            
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()

            logString = dcs_interface.GetLogViewerString()
            self.emit(QtCore.SIGNAL("gotLog"), "gotLog", logString)

            self.dcs_interface_wrapper.releaseDcsInterface()

    

