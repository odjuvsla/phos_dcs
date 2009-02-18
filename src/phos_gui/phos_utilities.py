
from PhosConst import *

class PhosIdConverter():
    """Contains converter functions between logical FEE IDs and absolute IDs, and vice versa"""

    def FeeAbsoluteID(self, moduleId, rcuId, branchId, feeId):
        """Funtion to extract the FEE absolute ID from logical IDs"""

        return moduleId*RCUS_PER_MODULE*CARDS_PER_RCU + rcuId*CARDS_PER_RCU + branchId*CARDS_PER_BRANCH + feeId
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

        feeId = cardIdInBranch+1

        return moduleId, rcuId, branchId, feeId
    #------------------------------------------------------

    def GetRcuLogicalIDs(self, rcuId):
        """Helper funtion to extract the RCU ID from absolute ID"""
        moduleId = rcuId/RCUS_PER_MODULE
        rcuId = rcuId%RCUS_PER_MODULE
            
        return moduleId, rcuId
    #------------------------------------------------------













