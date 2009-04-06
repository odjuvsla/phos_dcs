
from PyQt4 import QtCore, QtGui
from PhosConst import *
from phos_dialogs import *
from phos_widgets import *
from phos_interface import *
from phos_utilities import *

class PhosGui(QtGui.QMainWindow):
    """The main gui"""

    def __init__(self, parent=None):
        super(QtGui.QMainWindow, self).__init__(parent)
        
        self.resize(1120, 880)
        self.initTabs()
        self.initMenuBar()
        self.initDialogs()

        self.setCentralWidget(self.tabControls)

        self.initConnections()

        self.rcuDialog = RcuDialog()

    def initTabs(self):
        
        self.tabControls = QtGui.QTabWidget(self)
        
        self.moduleTabs = [None]*PHOS_MODS

        for i in range(PHOS_MODS):
            
            self.moduleTabs[i] = ModuleTabWidget(i)
            self.tabControls.addTab(self.moduleTabs[i], "Module " + str(i))
#            self.moduleTabs[i].setEnabled(0)

    def initMenuBar(self):
        
        self.connectMenu = self.menuBar().addMenu("&Connect")
        self.settingsMenu = self.menuBar().addMenu("&Settings")
        
        self.connectAction = QtGui.QAction("Connect &Now", self)
        self.connectSettingsAction = QtGui.QAction("Connection &Settings...", self)
        self.connectMenu.addAction(self.connectAction)
        self.connectMenu.addAction(self.connectSettingsAction)

    def initDialogs(self):
        
        self.feeServerNames = [None]*PHOS_MODS
        self.connectSettingsDialog = ConnectSettingsDialog(self.feeServerNames)

    def initConnections(self):

        self.connect(self.connectSettingsAction, QtCore.SIGNAL("triggered()"), self.showConnectDialog)
        self.connect(self.connectAction, QtCore.SIGNAL("triggered()"), self.connectToFeeServers)

        self.dcsInterface = DcsInterfaceThreadWrapper(DcsInterface())
        
        self.feeCardHandler = FeeCardHandler(self.dcsInterface)
        self.truCardHandler = TruCardHandler(self.dcsInterface)
        self.rcuHandler = RcuHandler(self.dcsInterface)
        self.moduleHandler = ModuleHandler(self.dcsInterface)
        self.detectorHandler = DetectorHandler(self.dcsInterface)
        self.logHandler = LogHandler(self.dcsInterface)

        self.connect(self.feeCardHandler, QtCore.SIGNAL("fetchLog"), self.fetchLog)
        self.connect(self.truCardHandler, QtCore.SIGNAL("fetchLog"), self.fetchLog)
        self.connect(self.rcuHandler, QtCore.SIGNAL("fetchLog"), self.logHandler.getLogString)
        self.connect(self.moduleHandler, QtCore.SIGNAL("fetchLog"), self.fetchLog)
        self.connect(self.detectorHandler, QtCore.SIGNAL("fetchLog"), self.fetchLog)
        self.connect(self.logHandler, QtCore.SIGNAL("gotLog"), self.updateLogViewer)

        self.connect(self, QtCore.SIGNAL("viewFee"), self.showFeeDialog)
        self.connect(self, QtCore.SIGNAL("viewdTru"), self.showTruDialog)
        self.connect(self, QtCore.SIGNAL("viewRcu"), self.showRcuDialog)
        
        self.connect(self, QtCore.SIGNAL("toggleFee"), self.feeCardHandler.toggleOnOff)
        self.connect(self, QtCore.SIGNAL("toggleTru"), self.truCardHandler.toggleOnOff)
        self.connect(self, QtCore.SIGNAL("rcuUpdateStatus"), self.rcuHandler.updateStatus)
        self.connect(self, QtCore.SIGNAL("rcuToggleOnOff"), self.rcuHandler.toggleOnOff)
        
        self.connect(self, QtCore.SIGNAL("turnOnModule"), self.moduleHandler.turnOn)
        self.connect(self, QtCore.SIGNAL("shutdownModule"), self.moduleHandler.shutdown)

        self.connect(self, QtCore.SIGNAL("showModuleProperties"), self.showModulePropertiesDialog)
        self.connect(self, QtCore.SIGNAL("configureElectronicsModule"), self.showElectronicsConfigDialog)

        self.connect(self, QtCore.SIGNAL("enableTriggerModule"), self.moduleHandler.enableTrigger)
        self.connect(self, QtCore.SIGNAL("disableTriggerModule"), self.moduleHandler.disableTrigger)

        self.connect(self, QtCore.SIGNAL("FeeServerStarted"), self.enableConnectedFeeServers)        

        self.connect(self.detectorHandler, QtCore.SIGNAL("FeeServerStarted"), self.enableConnectedFeeServers)

        for i in range(PHOS_MODS):

            self.connect(self.moduleTabs[i], QtCore.SIGNAL("toggleFee"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("viewFee"), self.extractSignal)
            
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("toggleTru"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("viewTru"), self.extractSignal)

            self.connect(self.moduleTabs[i], QtCore.SIGNAL("rcuUpdateStatus"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("rcuToggleOnOff"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("viewRcu"), self.extractSignal)


            self.connect(self.moduleTabs[i], QtCore.SIGNAL("turnOnModule"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("shutdownModule"), self.extractSignal)
            
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("showModuleProperties"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("configureElectronicsModule"), self.extractSignal)

            self.connect(self.moduleTabs[i], QtCore.SIGNAL("enableTriggerModule"), self.extractSignal)
            self.connect(self.moduleTabs[i], QtCore.SIGNAL("disableTriggerModule"), self.extractSignal)

            self.connect(self, QtCore.SIGNAL("cardToggled" + str(i)), self.moduleTabs[i].updateFeeCard)
            self.connect(self, QtCore.SIGNAL("feeStateUpdated" + str(i)), self.moduleTabs[i].updateFeeCard)
            self.connect(self, QtCore.SIGNAL("statusUpdated" + str(i)), self.moduleTabs[i].updateRcu)


        self.connect(self.feeCardHandler, QtCore.SIGNAL("cardToggled"), self.translateFeeSignal)
        self.connect(self.rcuHandler, QtCore.SIGNAL("cardToggled"), self.translateFeeSignal)
        self.connect(self.rcuHandler, QtCore.SIGNAL("feeStateUpdated"), self.translateFeeSignal)

        self.connect(self.rcuHandler, QtCore.SIGNAL("statusUpdated"), self.translateRcuSignal)

    def translateFeeSignal(self, *args):
        
        feeId = args[1]
        res = args[2]
        module = feeId/(RCUS_PER_MODULE*CARDS_PER_RCU)
        self.emit(QtCore.SIGNAL(args[0] + str(module)), feeId, res)
        print args[0]

    def translateRcuSignal(self, *args):

        rcuId = args[1]
        res = args[2]
        module = rcuId/(RCUS_PER_MODULE)
        self.emit(QtCore.SIGNAL(args[0] + str(module)), rcuId, res)
        print args[0]

    def extractSignal(self, *args):
        
        params = []
        for i in range(1, len(args)):
            params.append(args[i])
        self.emit(QtCore.SIGNAL(args[0]), *params)

#     def rcuUpdateStatus(self, signal, rcuId):
        
#         self.emit(QtCore.SIGNAL("rcuUpdateStatus"), rcuId)

#     def rcuUpdateStatus(self, signal, rcuId):
        
#         self.emit(QtCore.SIGNAL("rcuUpdateStatus"), rcuId)

#     def rcuUpdateStatus(self, signal, rcuId):
        
#         self.emit(QtCore.SIGNAL("rcuUpdateStatus"), rcuId)

    def showFeeDialog(self, feeId):
        
        print 'Dialog not yet made...'

    def showTruDialog(self, feeId):

        print 'Dialog not yet made...'

    def showRcuDialog(self, feeId):
        
        self.rcuDialog.show()

    def showModulePropertiesDialog(self, moduleId):
        
        print 'Dialog not yet made...'

    def showElectronicsConfigDialog(self, moduleId):
        
        print 'Dialog not yet made...'
        
    def showConnectDialog(self):
        
        self.connectSettingsDialog.exec_()
       

    def connectToFeeServers(self):
        
        feeServerNames, feeServerEnabled = self.connectSettingsDialog.getFeeServers()
        self.detectorHandler.connectToFeeServers(feeServerNames, feeServerEnabled)
        
    def enableConnectedFeeServers(self, res):

        feeServerNames, feeServerEnabled = self.connectSettingsDialog.getFeeServers()
        for i in range(PHOS_MODS):
            for j in range(RCUS_PER_MODULE):
                if feeServerEnabled[i*(RCUS_PER_MODULE+1) + j] == True:
                    if res > 0:
                        self.moduleTabs[i].enableRcu(True, j)
                        self.moduleTabs[i].setEnabled(True)
                    else:
                        self.moduleTabs[i].enableRcu(False, j)
                        self.moduleTabs[i].SetEnabled(False)
                else:
                    self.moduleTabs[i].enableRcu(False, j)
                    
        # Need to enable TORs also ...

    def fetchLog(self, signal, moduleId):
        self.logHandler.getLogString(moduleId)
        
    def updateLogViewer(self, tmpSignal, logString):
        
        for i in range(PHOS_MODS):
            
            self.moduleTabs[i].addLogString(logString)

    
