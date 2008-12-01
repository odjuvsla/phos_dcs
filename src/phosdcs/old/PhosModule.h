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

#include "CommonDefs.h"
#include "Mapper.h"
#include "Rcu.h"
#include "PhosFeeClient.h"

class PhosModule
{
 public:
  PhosModule();
  ~PhosModule();
  PhosModule(PhosFeeClient *fClientPtr);

  // --- System
  int* ArmTrigger(char triggerScriptFileName[50]);
  void EnableTrigger();
  void DisArmTrigger();

  // --- Operation to RCU/FEE
  void ApplyApdSettings(char messageBuffer[RCUS_PER_MODULE][CARDS_PER_RCU][MAX_MESSAGE_LENGTH]);
  void ApplyConfiguration();//apply current settings to electronics
  void LoadApdValues();
  void SetAllApds(int value);
  int**  feeState[RCUS_PER_MODULE];
  void CreateRcu(char *serverName, int mId, int rcuId, int zCoord, int xCoord);
  void ResetRcus();
  void TurnOnAllFee();
  void TurnOffAllFee();
  void InitRcu();
  bool CheckFeeOnOff();
  void CheckFeeStatus();
  Rcu* GetRcuPtr(int Id);

  // --- Basic Information
  void SetId(int id){ moduleId = id; } ;
  void SetReadoutRegion(int stZ, int eZ, int stX, int eX, char messageBuf[100]);

 private:
  // --- System
  PhosFeeClient *feeClientPtr;
  Mapper *mapperPtr; 

  // --- Reserved for RCU/FEE
  Rcu *rcuPtr[RCUS_PER_MODULE];
  int aclMaps[RCUS_PER_MODULE][256];//256x16 active channel list for each RCU
  unsigned long int afls[RCUS_PER_MODULE]; //Active Frontend Card List (afl) for each RCU

  // --- Basic Information
  int moduleId; //Geometrical position of the Module (The middle corresponds to ID = 2)
  int startZ;
  int endZ;
  int startX;
  int endX;
};

#endif
