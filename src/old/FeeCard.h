#ifndef FEECARD_H
#define FEECARD_H

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

#include <stdio.h>
#include "CommonDefs.h"
#include "ScriptCompiler.h"
#include  "PhosFeeClient.h"

class FeeCard
{
 public:
  FeeCard();
  FeeCard(PhosFeeClient *feecClientPtr, char *fName, int mod, int rcuId, int br, int card);

  // --- System
  void SetState(int state){ currentState = state; };
  int GetState(){ return currentState; };   // Why is the return value a pointer????

  // --- APD Bias operation
  int ApplyApdSettings(char *messageBuffer);
  void SetAllApds(int value); //sets all APDs to the value given by "value"
  void LoadApdValues();
  void SaveApdValues();
  void SetApdValues(int values[CSPS_PER_FEE]);
  int*  GetApdValues();

  // --- Basic Information
  void SetRcuZ(int z){ rcuZ = z; };
  int GetRcuZ(){ return rcuZ; };
  void SetRcuX(int x){ rcuX = x; };
  int GetRcuX(){ return rcuX; };
  void SetModule(int mod){ module = mod; };
  int GetModule(){ return module; };
  void SetBranch(int br){ branch = br; };
  int GetBranch(){ return branch; };
  void SetCardNumber(int cardIndex){cardNumber = cardIndex + 1; };
  int GetCardNumber(){ return cardNumber;} ;
  void SetRcuId(int id){ rcuId = id; };
  int GetRcuId(){ return rcuId; };
  void SetServerName(char *sName){ feeServerName = sName; }; // Wooo, this is dangerous. H.Torii
  char *GetServerName(){ return feeServerName;};
 private:
  // --- System
  PhosFeeClient *feeClientPtr;
  int currentState;

  // --- APD Values
  char apdFilename[200];
  int apdValue[CSPS_PER_FEE];

  // --- Basic Information
  char command;
  int rcuZ;
  int rcuX;
  int rcuId;
  int module;
  int branch;
  int cardNumber;
  char *feeServerName;  // Wooo, this is dangerous... Torii
};
//}}
#endif
