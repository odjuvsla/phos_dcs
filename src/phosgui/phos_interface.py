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
#        print 'emitting ' + args[0]
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
        
    def toggleOn(self, feeId):
        """Function for toggling cards"""
        # Start a thread for the toggling
        self.feeId = feeId
        onOffThread = self.__ToggleOnOffThread(self.feeId, self.dcs_interface_wrapper, True, True)
        self.connect(onOffThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(onOffThread, QtCore.SIGNAL("cardToggled"), self.emit_signal)
        onOffThread.start()
    #-----------------------------------------------------
        
    def toggleOff(self, feeId):
        """Function for toggling cards"""
        # Start a thread for the toggling
        self.feeId = feeId
        onOffThread = self.__ToggleOnOffThread(self.feeId, self.dcs_interface_wrapper, True, False)
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
        
        def __init__(self, feeId, dcs_interface_wrapper, override = False, on = False):
            """init takes DcsInterfaceThreadWrapper and FEE ID (absolute number) as arguments"""
            
            self.feeId = feeId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.override = override
            self.on = on
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
#            tmpStates = [0]*CARDS_PER_RCU
            state = 0
            dcs_interface.UpdateAFL(moduleId, rcuId)
            # Here we do the toggling
            if self.override and self.on == True:
                state = dcs_interface.TurnOnFee(moduleId, rcuId, branchId, feeId, currentstate)
                #state = 1
            elif self.override and self.on == False:
                state = dcs_interface.TurnOffFee(moduleId, rcuId, branchId, feeId, currentstate)
                #state = 1
#           state = dcs_interface.ToggleOnOffFee(moduleId, rcuId, branchId, feeId, currentstate, tmpStates)
            else:
                state = dcs_interface.ToggleOnOffFee(moduleId, rcuId, branchId, feeId, currentstate)
                #state = 1
            print 'state is ' + str(state)
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

    def toggleOnOff(self, rcuId, on):
        """Function for toggling on/off all FEE cards and TRU cards on the RCU"""
#        self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", 1, FEE_STATE_ON)         
        
        # Start a thread for the toggling        
        onOffThread = self.__ToggleOnOffThread(rcuId, self.dcs_interface_wrapper, self.feeHandler, on)
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
        self.connect(updateStatusThread, QtCore.SIGNAL("feeStateUpdated"), self.emit_signal)
        updateStatusThread.start()
        
    #------------------------------------------------
    
    class __ToggleOnOffThread(Thread, PHOSHandler):
        """Member threading class for toggle on/off all cards on RCU"""
        
        def __init__(self, rcuId, dcs_interface_wrapper, feeHandler, on):
            """init takes a DcsInterfaceThreadWrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)
            self.rcuId = rcuId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.feeHandler = feeHandler
            self.on = on
            
        def run(self):
            """Run the thread"""
            
#            for i in range(CARDS_PER_RCU):
#                feeId = self.rcuId*CARDS_PER_RCU + i
#                self.feeHandler.toggleOnOff(feeId)
#             for i in range(CARDS_PER_BRANCH-2):
#                 feeId = self.rcuId*CARDS_PER_RCU + i
#                 self.feeHandler.toggleOnOff(feeId)
                
            for j in range(CARDS_PER_BRANCH):
                feeId = self.rcuId*CARDS_PER_RCU + CARDS_PER_BRANCH + j
                if self.on == True:
                    self.feeHandler.toggleOn(feeId)
                    time.sleep(0.1)
                else:
                    self.feeHandler.toggleOff(feeId)
                    time.sleep(0.1)
            # Emitting the cards toggled signal 
            self.emit(QtCore.SIGNAL("cardsToggled"), "cardsToggled")
#            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0)
            
    #################################################################### End of __ToggleOnOffThread class

    class __UpdateStatusThread(Thread, PHOSHandler):
        """Member threading class for getting the up to date status of the FEE cards"""
        
        def __init__(self, rcuId, dcs_interface_wrapper):
            """init takes a Dcs_Interface_Wrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)

            self.rcuId = rcuId
            self.moduleId = rcuId/RCUS_PER_MODULE
            self.dcs_interface_wrapper = dcs_interface_wrapper
            
        def run(self):
            
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
            
            moduleId, rcuId = self.idConverter.GetRcuLogicalIDs(self.rcuId)

            dcs_interface.UpdateAFL(moduleId, rcuId)

            for i in range(CARDS_PER_BRANCH):
                
                status = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, BRANCH_A, i+1)
                feeId = self.idConverter.FeeAbsoluteID(self.moduleId, rcuId, BRANCH_A, i+1)
                self.emit(QtCore.SIGNAL("feeStateUpdated"), "feeStateUpdated", feeId, status)
                self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)
                time.sleep(0.05)
                
            for j in range(CARDS_PER_BRANCH):
                
                status = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, BRANCH_B, j+1)
                feeId = self.idConverter.FeeAbsoluteID(self.moduleId, rcuId, BRANCH_B, j+1)
                self.emit(QtCore.SIGNAL("feeStateUpdated"), "feeStateUpdated", feeId, status)
                self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)
                time.sleep(0.05)
                
            self.dcs_interface_wrapper.releaseDcsInterface()
#             status = dcs_interface.UpdateFeeStatus(moduleId, rcuId)
            
#             self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)
            
#             self.emit(QtCore.SIGNAL("statusUpdated"), "statusUpdated", self.rcuId, status)

#self.dcs_interface_wrapper.releaseDcsInterface()

class ModuleHandler(PHOSHandler):
    
    def __init__(self, dcs_interface_wrapper):
        super(ModuleHandler, self).__init__()

        self.dcs_interface_wrapper = dcs_interface_wrapper
        self.rcuHandler = RcuHandler(dcs_interface_wrapper)
        
    def turnOn(self, moduleId):
        
        print 'Turning on module: ' + str(moduleId)
        
    def shutdown(self, moduleId):
        
        print "Shutting down module: " + str(moduleId)

    def enableTrigger(self, moduleId):
        
        print "Enabling trigger for module: " + str(moduleId)

    def disableTrigger(self, moduleId):

        print "Disabling trigger for module: " + str(moduleId)

    def configureElectronics(self, moduleId, readoutConfiguration):
        # Start a thread for the toggling        

        configureElectronicsThread = self.__ConfigureElectronicsThread(self.dcs_interface_wrapper, moduleId, readoutConfiguration)
        self.connect(configureElectronicsThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        configureElectronicsThread.start()
#        self.updateStatus(rcuId)

    class __ConfigureElectronicsThread(Thread, PHOSHandler):

        def __init__(self, dcs_interface_wrapper, moduleId, readoutConfiguration):
            
            Thread.__init__(self)
            PHOSHandler.__init__(self)

            self.moduleId = moduleId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.readoutConfiguration = readoutConfiguration
 
        def run(self):

            modId = ModNumber_t(self.moduleId)
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()

            dcs_interface.SetReadoutConfig(modId, self.readoutConfiguration)
            dcs_interface.ArmTrigger(self.moduleId)
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)

            self.dcs_interface_wrapper.releaseDcsInterface()

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
        
        res = self.dcs_interface.getDcsInterface().Init(self.fee_servers)
        self.dcs_interface.releaseDcsInterface()
        self.fee_servers.clear()
        return res
    def stopFeeClient(self):

        self.dcs_interface.DeInit()
        self.fee_servers.clear()

    def connectToFeeServers(self, feeServerNames, feeServerEnabled):
        
        self.connect(self, QtCore.SIGNAL("feeServerStarted"), self.emit_signal)
       # self.connect(self, QtCore.SIGNAL("fetchLog"), self.emit_signal)

        for i in range(len(feeServerNames)):
            if feeServerEnabled[i] == True:
                self.addFeeServer(feeServerNames[i], i)

        res = self.startFeeClient()
        #res = 1
        self.emit(QtCore.SIGNAL("feeServerStarted"), "FeeServerStarted", res)
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID

    def disconnectFromFeeServers(self, feeServerNames, feeServerEnabled):
        
        self.connect(self, QtCore.SIGNAL("feeServerStopped"), self.emit_signal)
       # self.connect(self, QtCore.SIGNAL("fetchLog"), self.emit_signal)

        res = self.stopFeeClient()

        self.emit(QtCore.SIGNAL("feeServerStopped"), "FeeServerStopped", res)
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

    

