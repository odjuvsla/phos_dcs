from PHOSHandler import *

class DatabaseHandler(PHOSHandler):
    """Class for handling the APD settings database"""
    
    def __init__(self, dcs_interface):
        """init takes a DcsInterfaceThreadWrapper object as argument"""
        PHOSHandler.__init__(self)
        self.dcs_interface_wrapper = dcs_interface

    def getLatestConfigId(self):
        """Get the id for the last configuration"""
        
        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        id = dcs_interface.GetLatestConfigId()
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID
        self.dcs_interface_wrapper.releaseDcsInterface()
        return id

    def getConfigComment(self, id):

        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        comment = dcs_interface.GetConfigComment(id)
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID
        self.dcs_interface_wrapper.releaseDcsInterface()
        return comment

    def loadApdConfig(self, id):
        
        configinfo = ConfigInfo_t();
        configinfo.fID = id
        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        dcs_interface.LoadApdConfig(configinfo, id)
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID
        dcs_interface.releaseDcsInterface()
        
    def loadApdValues(self, moduleId):
        
        dcs_interface = self.dcs_interface_wrapper.getDcsInterface()
        dcs_interface.LoadApdValues(moduleID)
        self.emit(QtCore.SIGNAL("fetchLog"), "fetchLog", 0) # fix module ID
        dcs_interface.releaseDcsInterface()
