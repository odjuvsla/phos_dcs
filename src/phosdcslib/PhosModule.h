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

class Mapper;
class Rcu;
class PhosFeeClient;

class PhosModule : public PhosDcsBase 
{
 public:
  ~PhosModule();
  PhosModule(PhosFeeClient *fClientPtr, const ModNumber_t  id);
  void ApplyApdSettings(const int rcuId, const int branch, const int card) const;
  //  void ApplyPattern
  const int ArmTrigger(const char *triggerScriptFileName);
  void DisArmTrigger(const int rcuId) const ;
  const char* GetFeeServerName(const int rcuId) const; 
  void EnableTrigger() const;
  void EnableTrigger_ttcrx() const ;
  void ExecuteScript(const char *scriptFileName) const;
  void CreateRcu(const char *serverName, const int mId, const int rcuId, const int zCoord, const int xCoord);
  void LoadApdValues() const;
  void SetAllApds(const int value) const;
  void SetReadoutConfig(const ReadoutConfig_t rdoConfig);
  void ApplyReadoutRegisters(const ReadoutRegisters_t readoutRegisters);
  Rcu *GetRcuPtr(const int Id) const;
  int**  fFeeState[RCUS_PER_MODULE];

 private:
  PhosModule();
  PhosModule(const PhosModule & );
  PhosModule & operator = (const PhosModule &){return *this;}
  Rcu *fRcuPtr[RCUS_PER_MODULE];
  PhosFeeClient *fFeeClientPtr;
  Mapper *fMapperPtr; 
  ModNumber_t fModuleId; //Geometrical position of the Module (The middle corresponds to ID = 2)
  ReadoutConfig_t fReadoutConfig; 

  // int fAclMaps[RCUS_PER_MODULE][256];//256x16 active channel list for each RCU
  
  
  int fAclMaps[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length];

  unsigned long int fAfls[RCUS_PER_MODULE]; //Active Frontend Card List (afl) for each RCU

};

#endif
