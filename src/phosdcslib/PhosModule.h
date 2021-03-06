#ifndef PHOSMODULE_H
#define PHOSMODULE_H

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


#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
#include "RcuRegisterMap.h"
#include "PhosRegisters.h"


class Mapper;
class Rcu;
class PhosFeeClient;
class ReadoutRegisters_t;

class PhosModule : public PhosDcsBase
  {
  public:
    ~PhosModule();
    PhosModule ( PhosFeeClient *fClientPtr, const ModNumber_t  id );
    void ApplyApdSettings ( const int rcuId, const int branch, const int card ) const;
    //  void ApplyPattern
    const int ArmTrigger ( const char *triggerScriptFileName );
    void DisArmTrigger ( const int rcuId ) const ;
    const char* GetFeeServerName ( const int rcuId ) const;
    void EnableTrigger ( RcuTRGCONF_t trgConf ) const;
    void EnableTrigger_ttcrx() const ;
    void ExecuteScript ( const char *scriptFileName ) const;
    void CreateRcu ( const char *serverName, const int mId, const int rcuId, const int zCoord, const int xCoord );
    void LoadApdValues() const;
    void SetAllApds ( const int value ) const;
    void SetReadoutConfig ( const ReadoutConfig_t rdoConfig );
    void SetReadoutSettings ( const ReadoutSettings_t rdoSettings );
    void SetReadoutRegion ( const ReadoutRegion_t rdoRegion );
    int  ApplyReadoutRegisters ( const ReadoutRegisters_t readoutRegisters );
    int  ApplyReadoutRegisters() const;
    int  ApplyReadoutRegion ( const ReadoutRegion_t readoutRegion );
    void Reset();
    Rcu *GetRcuPtr ( const int Id ) const;
    int**  fFeeState[RCUS_PER_MODULE];

    int StartFeeClient ( int rcuId );
    /**
    * Write the fixed pedestal values for this module
    * @return 0 upon success
    */
    int WriteFixedPedestals(bool fromFile = true);

  private:
    PhosModule();
    PhosModule ( const PhosModule & );
    PhosModule & operator = ( const PhosModule & )
    {
      return *this;
    }
    Rcu *fRcuPtr[RCUS_PER_MODULE];
    PhosFeeClient *fFeeClientPtr;
    Mapper *fMapperPtr;
    ModNumber_t fModuleId; //Geometrical position of the Module (The middle corresponds to ID = 2)
    ReadoutConfig_t fReadoutConfig;
    ReadoutSettings_t fReadoutSettings;
    ReadoutRegion_t fReadoutRegion;

    // int fAclMaps[RCUS_PER_MODULE][256];//256x16 active channel list for each RCU

    int fAclMaps[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length];

    int fAclMapsA[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length]; //active channel list for branch A
    int fAclMapsB[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length]; //active channel list for branch B

    unsigned long int fAfls[RCUS_PER_MODULE]; //Active Frontend Card List (afl) for each RCU

  };

#endif
