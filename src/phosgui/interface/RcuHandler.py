from PHOSHandler import *
from FeeCardHandler import *
import time

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

    def applyApdSettings(self, moduleId, logicRcuId):
        """Apply APD settings to RCU"""

        applyApdThread = self.__ApplyApdSettingsThread(moduleId, logicRcuId, self.dcs_interface_wrapper)
        self.connect(applyApdThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        self.connect(applyApdThread, QtCore.SIGNAL("apdSettingApplied"), self.emit_signal)
        applyApdThread.start()
    
    def getRcuFwVersion(self, moduleId, rcuId):
        
        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        version = dcs_interface.GetRcuFirmwareVersion(moduleId, rcuId)
        self.dcs_interface_wrapper.releaseDcsInterface()
        return version
    
    class __ToggleOnOffThread(Thread, PHOSHandler):
        """Member threading class for toggle on/off all cards on RCU"""
        
        def __init__(self, rcuId, dcs_interface_wrapper, feeHandler, on):
            """init takes a DcsInterfaceThreadWrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)
            self.rcuId = rcuId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.dcs_interface_wrapper.getDcsInterface()
            self.feeHandler = feeHandler
            self.on = on
            
        def run(self):
            """Run the thread"""
            
#             for i in range(CARDS_PER_RCU):
#                 feeId = self.rcuId*CARDS_PER_RCU + i
#                 self.feeHandler.toggleOnOff(feeId)
#             for i in range(CARDS_PER_BRANCH-2):
#                  feeId = self.rcuId*CARDS_PER_RCU + i
#                  self.feeHandler.toggleOnOff(feeId)
                
            for i in range(CARDS_PER_BRANCH):
                feeId = self.rcuId*CARDS_PER_RCU + i

                if self.on == True:
                    self.feeHandler.toggleOn(feeId)
                    time.sleep(0.1)
                else:
                    self.feeHandler.toggleOff(feeId)
                    time.sleep(0.1)
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
            self.dcs_interface_wrapper.releaseDcsInterface()
            
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

    class __ApplyApdSettingsThread(Thread, PHOSHandler):
        """Member threading class for applying APD settings to the FEE cards"""
        
        def __init__(self, moduleId, logicRcuId, dcs_interface_wrapper):
            """init takes a Dcs_Interface_Wrapper object as argument"""
            Thread.__init__(self)
            PHOSHandler.__init__(self)

            self.rcuId = logicRcuId
            self.moduleId = moduleId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            
        def run(self):
            
            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
            
            dcs_interface.UpdateAFL(self.moduleId, self.rcuId)

#            for i in range(CARDS_PER_BRANCH):
            for i in range(14):
                dcs_interface.ApplyApdSettings(self.moduleId, self.rcuId, BRANCH_A, i+1)
                feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_A, i+1)
                self.emit(QtCore.SIGNAL("apdSettingApplied"), "apdSettingApplied", feeId)
                self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)
                time.sleep(0.05)
                
            for j in range(CARDS_PER_BRANCH):
                dcs_interface.ApplyApdSettings(self.moduleId, self.rcuId, BRANCH_B, j+1)
                feeId = self.idConverter.FeeAbsoluteID(self.moduleId, self.rcuId, BRANCH_B, j+1)
                self.emit(QtCore.SIGNAL("apdSettingApplied"), "apdSettingApplied", feeId)
                self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)
                time.sleep(0.05)

            self.dcs_interface_wrapper.releaseDcsInterface()
