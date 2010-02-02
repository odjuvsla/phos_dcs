from threading import *

class DcsInterfaceThreadWrapper():
    """PHOS Fee Client is not thread safe. Hence we need this class to protect it for threading"""

    def __init__(self, dcs_interface):
        """init function"""

        self.dcs_interface = dcs_interface
#        self.lock = Lock()
    #-------------------------------------

    # Get the DcsInterface object
    def getDcsInterface(self):
        """Get the DcsInterface object"""
        
        # Acquire the lock and return the interface object
#        self.lock.acquire()
        return self.dcs_interface
    #-------------------------------------


    def releaseDcsInterface(self):
        """Release the lock/object"""
#        self.lock.release()

    #-------------------------------------
