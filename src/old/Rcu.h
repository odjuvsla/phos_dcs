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
#include <FeeClientLibImp.hpp>
#include "FeeCard.h"
#include "PhosFeeClient.h"
#include "CommonDefs.h"

class Rcu
{
 public: 
  Rcu();
  Rcu(PhosFeeClient *feeClientPtr, const char *feeServerName, int mId, int rId, int z, int x);
  ~Rcu(); // This should be a destructor...

  // --- System
  void InitRcu();
  void ResetRcu();
  void SetReadoutRegion(unsigned long int afl, int aclMaps[256]);  
  int ApplyReadoutRegion();
  void ArmTrigger(char *triggerScriptFilename);
  void EnableTrigger();
  void DisArmTrigger();
  FeeCard* GetFeeCardPtr(int index);
  void SetFeeClientPtr(PhosFeeClient *fcPtr);
  void SetFeeServerName(const char *name);
  char* GetFeeServerName();

  // --- Operation to FEE
  int ActivateFee(int branch, int card);
  unsigned long GetActiveFeeList();
  int DeActivateFee(int branch, int card);
  int VerifyAcl(int acl[256], char *resultBuffer);
  int ToggleFeeOnOff(int branch, int card);
  void TurnOnAllFee(int *state);
  void TurnOffAllFee(int *state);
  void InitFeeCards();
  bool CheckFeeOnOff();
  unsigned long CheckFeeStatus();
  //int** GetFeeStatus(){return feeState; }; // Dangerous return type 
  int* GetFeeStatus(){return feeState; };
  int ApplyApdSettings(char messageBuffer[CARDS_PER_RCU][MAX_MESSAGE_LENGTH]);
  void LoadApdValues();
  void SetAllApds(int value);

  // --- Basic Information
  void SetZCoord(int z){ zCoord = z; };
  int  GetZCoord(){ return zCoord; };
  void SetXCoord(int x){ xCoord = x; };
  int  GetXCoord(){ return xCoord; };
  void SetModuleId(int id){ moduleId = id; };
  int  GetModuleId(){ return moduleId; };
  void SetRcuId(int id){ rcuId = id; };
  int  GetRcuId(){ return rcuId; };

 private:
  // --- System
  PhosFeeClient *feeClientPtr;
  char feeServerName[30];

  // --- Reserved for FEE
  FeeCard *feeCardPtr[MAX_CARDS_PER_RCU]; //each RCU has 28 Front end Cards
  unsigned long int activeFeeList;
  unsigned long int activeFeeRdoList;
  int activeChList[256];
  //int *feeState[CARDS_PER_RCU];  // Ooou!! This is dangerous part...
  int feeState[CARDS_PER_RCU];
 
  // --- Basic Information
  int zCoord;
  int xCoord;
  int rcuId; // number indicting which of the 4 RCUs for a module this is
  int moduleId;
};


#endif
