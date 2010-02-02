from PHOSHandler import *

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
