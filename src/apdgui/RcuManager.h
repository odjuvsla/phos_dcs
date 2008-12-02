#ifndef RCUMANAGER_H
#define RCUMANAGER_H


/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
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

#include "RQ_OBJECT.h"
#include "PhosConst.h"
#include "PhosDataTypes.h"

using namespace PhosConst;

class TGLabel;
class TGMainFrame;
class TGGroupFrame;
class DcsInterface;
class RcuButton;
class FeeCardOnOffButton;
class FeeCardButton;
class ApdInput;
class ConfigInfo_t;
class ReadoutConfig_t;

//#include "PhosDataTypes.h"

class  RcuManager
{
  RQ_OBJECT("RcuManager") 

 public:
  RcuManager(TGMainFrame *framPtr);
  virtual ~RcuManager();
  void EmitMessage(const char *message);
  void EmitConfigInfo(ConfigInfo_t *t =0);
  RcuButton *GetRcuButtonPtr(int i); 
  
  const ReadoutConfig_t GetReadoutConfiguration() const {return *fRdoConfigPtr;};
  const TRUSettings_t GetTRUSettings() const;

  void  HandleSaveTruConfigSlot(const TRUSettings_t*) const;
  void  HandleApplyTruConfigSlot(const TRUSettings_t*) const;

  void HandleApplyFeeSlot();
  void HandleApplyModuleSlot();
  void HandleApplyRcuSlot();
  void HandleArmTriggerSlot(); 
  void HandleDisarmTriggerSlot();
  void HandleEnableTriggerSlot();
  void HandleEnableTrigger_ttcrx_Slot(); 
  void HandleOnOffFeeSlot(Int_t branch, Int_t card, Int_t state);
 
  void HandleReadoutConfigChangedSlot(const ReadoutConfig_t *rdoConfigPtr);
  
  
  void HandleRequestConfigInfoSlot(ConfigInfo_t* t);
  void HandleRequestConfigLoadSlot(ConfigInfo_t* t);
  void HandleRequestConfigSaveSlot(ConfigInfo_t *t);
  void HandleSaveConfigSlot();
  void HandleSelectFeeSlot(Int_t branch, Int_t card, Bool_t save = kTRUE);
  void HandleSelectRcuSlot(Int_t id);
  void HandleSetAllApdFeeSlot(Int_t val);
  void HandleSetAllApdRcuSlot(Int_t val);
  void HandleSetAllApdModuleSlot(Int_t val);
  void HandleTurnOffAllFeeSlot(); 
  void HandleTurnOnAllFeeSlot();
  void HandleTurnOffAllTruSlot(); 
  void HandleTurnOnAllTruSlot();
  
  

 private:
  RcuManager(); 
  void DrawFeeGrid(int X, int Y, int W, int H, int B);
  void DrawModules(int X, int Y, int W, int H, int B);
 
  ConfigInfo_t *fCongigInfoPtr;


  TGMainFrame        *fFramePtr; 
  TGGroupFrame       *rcuGroupPtr;  
  TGGroupFrame       *feeGroupFramePtr;  
  TGLabel            *branchA;
  TGLabel            *branchB; 
  DcsInterface       *fDcsInterfacePtr;
  RcuButton          *rcuButtonPtr[RCUS_PER_MODULE];  /**<pointers to the RCUs of the PHOS module */
  FeeCardButton      *feeButtPtr[CARDS_PER_RCU];
  FeeCardOnOffButton *onOffButtPtr[CARDS_PER_RCU];
  const  ModNumber_t *fCurrentModule;
  int fCurrentRcu;
  int fCurrentBranch;
  int fCurrentCard;
  bool fIsSelectedRcu;
  bool fIsSelectedFee;
  ApdInput *fApdInputPtr;
  int fApdValues[CSPS_PER_FEE];
  ReadoutConfig_t *fRdoConfigPtr;

  ClassDef(RcuManager, 1)
};

#endif
