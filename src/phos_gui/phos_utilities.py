
from PhosConst import *

class PhosIdConverter():
    """Contains converter functions between logical FEE IDs and absolute IDs, and vice versa"""

    def FeeAbsoluteID(self, moduleId, rcuId, branchId, feeId):
        """Funtion to extract the FEE absolute ID from logical IDs"""

        return moduleId*RCUS_PER_MODULE*CARDS_PER_RCU + rcuId*CARDS_PER_RCU + branchId*CARDS_PER_BRANCH + feeId
    #------------------------------------------------------
    
    def RcuAbsoluteID(self, moduleId, rcuId):
        """Funtion to extract the RCU absolute ID from logical IDs"""

        return moduleId*RCUS_PER_MODULE + rcuId
    #------------------------------------------------------

    def TruAbsoluteID(self, moduleId, rcuId, truId):
        """Funtion to extract the FEE absolute ID from logical IDs"""

        return moduleId*RCUS_PER_MODULE*TRUS_PER_RCU + rcuId*TRUS_PER_RCU + truId
    #------------------------------------------------------

    def GetFeeLogicalIDs(self, feeId):
        """Helper funtion to extract the logical FEE card ID from absolute ID"""

        moduleId = feeId/(CARDS_PER_RCU*RCUS_PER_MODULE)
        cardIdInModule = feeId%(CARDS_PER_RCU*RCUS_PER_MODULE)
            
        rcuId = cardIdInModule/CARDS_PER_RCU
        cardIdInRcu = cardIdInModule%CARDS_PER_RCU
            
        branchId = cardIdInRcu/CARDS_PER_BRANCH
        cardIdInBranch = cardIdInRcu%CARDS_PER_BRANCH

        fee = cardIdInBranch+1

        return moduleId, rcuId, branchId, fee
    #------------------------------------------------------

    def GetRcuLogicalIDs(self, rcuId):
        """Helper funtion to extract the RCU ID from absolute ID"""
        moduleId = rcuId/RCUS_PER_MODULE
        rcuIdLog = rcuId%RCUS_PER_MODULE
            
        return moduleId, rcuId
    #------------------------------------------------------

    def GetRcuLogicalCoordinatesFromFeeServerId(self, feeServerId):
        moduleId = feeServerId/(RCUS_PER_MODULE+TORS_PER_MODULE)
        rcuIdLog = feeServerId%(RCUS_PER_MODULE+TORS_PER_MODULE)
        
        x = rcuIdLog%(RCUS_PER_MODULE/2)
        z = rcuIdLog/(RCUS_PER_MODULE/2)
        return moduleId, rcuIdLog, x, z

    def GetTruLogicalIDs(self, truId):
        """Helper funtion to extract the TRU ID from absolute ID"""

        moduleId = truId/(TRUS_PER_RCU*RCUS_PER_MODULE)

        truIdInModule = truId%(TRUS_PER_RCU*RCUS_PER_MODULE)

        rcuId = truIdInModule/TRUS_PER_RCU
        
        truId = truIdInModule%TRUS_PER_RCU

        return moduleId, rcuId, truId
        
        




