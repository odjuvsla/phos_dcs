from PHOSHandler import *
from RcuHandler import *
from PhosDataTypes import *

class ModuleHandler(PHOSHandler):
    
    def __init__(self, dcs_interface_wrapper):
        super(ModuleHandler, self).__init__()

        self.dcs_interface_wrapper = dcs_interface_wrapper
        self.rcuHandler = RcuHandler(dcs_interface_wrapper)
        
    def turnOn(self, moduleId):
        
        self.configureElectronics(moduleId)
        self.disableTrigger(moduleId)
        self.enableTrigger(moduleId)
        
    def shutdown(self, moduleId):
        
#        print "Shutting down module: " + str(moduleId)

        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        for i in range(RCUS_PER_MODULE):
            dcs_interface.DisArmTrigger(moduleId, i)
            
        self.dcs_interface_wrapper.releaseDcsInterface()

    def enableTrigger(self, moduleId):
        
        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        dcs_interface.EnableTrigger(moduleId, "ttc")
        self.dcs_interface_wrapper.releaseDcsInterface()

    def disableTrigger(self, moduleId):

        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        dcs_interface.DisableTrigger(moduleId)
        self.dcs_interface_wrapper.releaseDcsInterface()
        
    def configureElectronics(self, moduleId, readoutRegion, readoutSettings):
        # Start a thread for the toggling        

        configureElectronicsThread = self.__ConfigureElectronicsThread(self.dcs_interface_wrapper, moduleId, readoutRegion, readoutSettings)
        self.connect(configureElectronicsThread, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        configureElectronicsThread.start()
#        self.updateStatus(rcuId)

    def applyApdSettings(self, moduleId):

        self.connect(self.rcuHandler, QtCore.SIGNAL("apdSettingApplied"), self.emit_signal)
        self.connect(self.rcuHandler, QtCore.SIGNAL("fetchLog"), self.emit_signal)
        for i in range(RCUS_PER_MODULE):
            self.rcuHandler.applyApdSettings(moduleId, i)
    
    class __ConfigureElectronicsThread(Thread, PHOSHandler):

        def __init__(self, dcs_interface_wrapper, moduleId, readoutRegion, readoutSettings):
            
            Thread.__init__(self)
            PHOSHandler.__init__(self)
            self.moduleId = moduleId
            self.dcs_interface_wrapper = dcs_interface_wrapper
            self.readoutRegion = readoutRegion
            self.readoutSettings = readoutSettings

        def run(self):

            modId = ModNumber_t(self.moduleId)

            dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
            
            dcs_interface.SetReadoutRegion(modId, self.readoutRegion)

            dcs_interface.SetReadoutSettings(modId, self.readoutSettings)
#            dcs_interface.ArmTrigger(self.moduleId)
            dcs_interface.Configure(modId)
            self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", self.moduleId)

            self.dcs_interface_wrapper.releaseDcsInterface()
