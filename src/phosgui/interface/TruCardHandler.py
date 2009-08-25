from PHOSHandler import *

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
