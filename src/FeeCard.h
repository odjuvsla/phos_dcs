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

#include "PhosDcsBase.h"


class PhosFeeClient;

class FeeCard : public PhosDcsBase
{
 public:
  FeeCard(PhosFeeClient *feecClientPtr, char *fName, const int mod, const int rcuId, const int br, const int card);
  void InitMapping();
  int ApplyApdSettings(char *messageBuffer);
  void DisableHamming();
  void SetState(int state);
  int* GetState();
  void LoadApdValues();
  void SaveApdValues();
  void SetApdValues(const unsigned long int values[CSPS_PER_FEE]);
  void SetAllApds(int value); //sets all APDs to the value given by "value"
  void SetPcmversion(unsigned long pcmversion);
  void SetServerName(char *sName);
  void SetRcuId(int id);
  unsigned long*  GetApdValues();
  int GetRcu();
  int GetBranch();
  int GetCardNumber();
  int GetRcuId();

 private:
  FeeCard();
  int fApdBaseAddress;
  unsigned long  fPcmVersion;
  bool fDisableHamming;    // whether or not to disable hamming coding of the APD values
  bool fIsDisabledHamming; // wether or not hamming coding of the APD values is enabled  
  bool fIsInitialized;
  PhosFeeClient *feeClientPtr;
  char apdFilename[200];
  unsigned long apdValue[CSPS_PER_FEE];
  bool apdVerify[CSPS_PER_FEE];
  int currentState;
  char *feeServerName;
  const int rcuId;
  const int module;
  const int branch;
  const int cardNumber;
  unsigned long  crystAdress[CSPS_PER_FEE];
};

#endif
