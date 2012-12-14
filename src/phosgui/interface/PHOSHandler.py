from PyQt4 import QtCore, QtGui
from threading import *
from PhosIdConverter import *

class PHOSHandler(QtCore.QObject):
    """Base class for the handlers"""

    def __init__(self):
        super(PHOSHandler, self).__init__()

        self.idConverter = PhosIdConverter()

#    def emit_signal(self, signal, *args):
    def emit_signal(self, *args):
        """Function for forwarding the signals from the thread"""      
	if len(args) > 0:
        	print 'Emitting ' + args[0]
        	self.emit(QtCore.SIGNAL(args[0]), *args)
    #-----------------------------------------------------


# class DcsInterfaceThreadWrapper():
#     """PHOS Fee Client is not thread safe. Hence we need this class to protect it for threading"""

#     def __init__(self, dcs_interface):
#         """init function"""

#         self.dcs_interface = dcs_interface
#         self.lock = Lock()
#     #-------------------------------------

#     # Get the DcsInterface object
#     def getDcsInterface(self):
#         """Get the DcsInterface object"""

#         # Acquire the lock and return the interface object
#         self.lock.acquire()
#         return self.dcs_interface
#     #-------------------------------------


#     def releaseDcsInterface(self):
#         """Release the lock/object"""
#         self.lock.release()
#     #-------------------------------------


