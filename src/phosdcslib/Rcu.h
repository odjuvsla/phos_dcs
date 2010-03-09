#ifndef RCU_H
#define RCU_H

/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2006                                       *
 *                                                                        *
 * Author: Per Thomas Hille perthi@fys.uio.no for the ALICE DCS Project.  *
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to perthi@fys.uio.no                                *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/
#include <FeeSampleClient.hpp>
#include "PhosFeeClient.h"
#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
#include "RcuRegisterMap.h"

class FeeCard;
class FeeCard;
class MainGui;
class ReadoutRegisters_t;
class RcuTRGCONF_t;

class Rcu : public PhosDcsBase
  {
  public:
    virtual ~Rcu();
    Rcu ( PhosFeeClient *feeClientPtr, const char *feeServerName, const int mId, const int rId, const int z, const int x );
    void ApplyPattern ( const Pattern_t pattern ) const;
    unsigned int CheckFeeState ( const int branch, const int cardNumber );
    void SetPcmVersion ( const unsigned long pcmversion, const int branch, const int card ) const ;
    void SetReadoutRegion ( const unsigned long int afl, const int aclMaps[RcuRegisterMap::Active_Channel_List_Length] );
    void SetAllApds ( const int value );
    unsigned int  ActivateFee ( const int branch, const int card );
    unsigned int  DeActivateFee ( const int branch, const int card );
    void ArmTrigger ( const char *triggerScriptFilename );
    void EnableTrigger ( RcuTRGCONF_t trgConf ) const ;
    void EnableTrigger_ttcrx() const;
    void DisArmTrigger() const ;
    const int  ApplyReadoutRegion() const ;
    int  ApplyApdSettings() const;
    int  ApplyApdSettings ( const int branch, const int card );
    void ApplyTruSettings ( const unsigned long regAddr[N_TRU_REGS], const unsigned long regVal[N_TRU_REGS], const bool verify[N_TRU_REGS],
                            const int N ) const;
    int  ApplyReadoutRegisters ( ReadoutRegisters_t readoutRegisters );
    void ExecuteScript ( const char *fileName ) const;
    int  ToggleFeeOnOff ( const int branch, const int card );
    int  ToggleTruOnOff ( const int tru );
    void InitFeeCards();
    void LoadApdValues();
    void TurnOnAllFee();
    void TurnOnAllTru();
    void TurnOffAllFee();
    void TurnOffAllTru();
    unsigned long GetActiveFeeList();
    int** GetFeeStatus();
    int   GetRcuId() const;
    char* GetFeeServerName();
    void  UpdateAFL();
    void  Reset();
    FeeCard* GetFeeCardPtr ( const int index ) const;

    int StartFeeClient();
    
    /** 
    * Write the fixed pedestal values to the ALTRO memory
    * @return 0 upon success
    */
   int WriteFixedPedestalValues();
   
  private:
    Rcu();
    Rcu ( const Rcu & );
    Rcu & operator = ( const Rcu & );
    bool IsActiveFee ( const int branch, const int card );
    void SetFeeServer ( const char *name );
    FeeCard *fFeeCardPtr[MAX_CARDS_PER_RCU]; //each RCU has 28 Front end Cards
    char fFeeServerName[100];
    int *fFeeState[CARDS_PER_RCU];
    int fTruState[TRUS_PER_RCU];

    //  int fActiveChList[256];
    int fActiveChList[RcuRegisterMap::Active_Channel_List_Length];

    unsigned long int fActiveFeeList;
    unsigned long int fActiveFeeRdoList;
    PhosFeeClient *fFeeClientPtr;
    const int fModuleId;
    const int fRcuId;
    const int fZCoord;
    const int fXCoord;


  };


#endif
