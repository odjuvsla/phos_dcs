from PHOSHandler import *
from threading import *
import time

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
#            print 'toggling card'
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
#            print 'state is ' + str(state)
            # Emitting signal for fetching log information
	    time.sleep(0.15)
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", moduleId)

            # Emitting the card toggled signal together with the returned state of the card
            self.emit(QtCore.SIGNAL("cardToggled"), "cardToggled", self.feeId, state)

            # If the card is 1, 2, 13 or 14 we check the state of the complementary
            if feeId == 1:
                feeId = 14
                self.feeId = self.idConverter.FeeAbsoluteID(moduleId, rcuId, branchId, feeId)
                state = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, branchId, feeId)
            elif feeId == 2:
                feeId = 13
                self.feeId = self.idConverter.FeeAbsoluteID(moduleId, rcuId, branchId, feeId)
                state = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, branchId, feeId)
            elif feeId == 14:
                feeId = 1
                self.feeId = self.idConverter.FeeAbsoluteID(moduleId, rcuId, branchId, feeId)
                state = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, branchId, feeId)
            elif feeId == 13:
                feeId = 2
                self.feeId = self.idConverter.FeeAbsoluteID(moduleId, rcuId, branchId, feeId)
                state = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, branchId, feeId)

            self.feeId = self.idConverter.FeeAbsoluteID(moduleId, rcuId, branchId, feeId)
            state = dcs_interface.UpdateSingleFeeStatus(moduleId, rcuId, branchId, feeId)
 
#            print "state: " + str(state)
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
