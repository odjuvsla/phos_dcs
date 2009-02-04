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
#include "RcuManager.h"
#include "DcsInterface.h"
#include <TGFrame.h>
#include <TGLabel.h>
#include "RcuButton.h"
#include "FeeCardOnOffButton.h"
#include "FeeCardButton.h"
#include "ApdInput.h"  
#include "Rcu.h"
#include "PhosDataTypes.h"


ClassImp(RcuManager)


RcuManager::RcuManager()
{

}




RcuManager::RcuManager(TGMainFrame *framePtr): fFramePtr(0), 
					       fDcsInterfacePtr(0),
					       fCurrentModule(0),
					       fCurrentRcu(99),
					       fCurrentBranch(99),
					       fCurrentCard(99),
					       fIsSelectedRcu(kFALSE),
					       fIsSelectedFee(kFALSE),
					       fRdoConfigPtr(0) 
{
  fDcsInterfacePtr =   new DcsInterface();
  fCongigInfoPtr =     new ConfigInfo_t();
  fCurrentModule =     new ModNumber_t(MODULE_2);  

  fDcsInterfacePtr->SetPhosBit(MODULE_2);
  fDcsInterfacePtr->LoadApdConfig(fCongigInfoPtr);
  fDcsInterfacePtr->LoadApdValues(fCurrentModule->GetIntValue());
  
  //  fRdoConfigPtr;
  fRdoConfigPtr  = new ReadoutConfig_t();

  fDcsInterfacePtr->LoadReadoutConfiguration(fRdoConfigPtr); 

  fFramePtr = framePtr; 
  DrawModules(20, 20, 230, 300, 15);

  fApdInputPtr = new ApdInput(fFramePtr);

  for(int i= 0; i< RCUS_PER_MODULE; i++)
    {
      if(rcuButtonPtr[i] == 0)
	{
	  //	  cout << "RcuManager::RcuManager: ERROR  rcuButtonPtr[ "<< i << "] == 0" <<endl;
	} 
      else
	{
	  //	  cout << "RcuManager::RcuManager: INFO  rcuButtonPtr[ "<< i << "] != 0" <<endl;
	  rcuButtonPtr[i]->SetRcuId(i);  
	  rcuButtonPtr[i]->Connect("EmitSelectRcuSignal(Int_t)", "RcuManager", this, "HandleSelectRcuSlot(Int_t)");
	}
    } 
  

  DrawFeeGrid(20, 320, 230, 270, 15); 


  //  void HandleRequestConfigInfoSlot(ConfigInfo_t* t);
  
  for(int i=0; i< CARDS_PER_RCU; i++)
    {
      feeButtPtr[i]->Connect("EmitFeeCardClickedSignal(Int_t, Int_t)", "RcuManager", this, " HandleSelectFeeSlot(Int_t, Int_t)");
      onOffButtPtr[i]->Connect("EmitOnOffSignal(Int_t, Int_t, Int_t)",  "RcuManager", this, " HandleOnOffFeeSlot(Int_t, Int_t, Int_t)");
    }

  EmitConfigInfo(fCongigInfoPtr);

}



RcuManager::~RcuManager()
{
 delete  fDcsInterfacePtr;
 delete  fCongigInfoPtr;
 delete  fCurrentModule;
 delete  fApdInputPtr;
 delete  fRdoConfigPtr;
}



void 
RcuManager::EmitConfigInfo(ConfigInfo_t *t)  //*SIGNAL*
{
  if(t != 0)
    {
      //     cout << "RcuManager::EmitConfigInfo(ConfigInfo_t *t)" << endl;
      Emit("EmitConfigInfo(ConfigInfo_t*)",(Long_t)t);
    }
  else
    {
      Emit("EmitConfigInfo(ConfigInfo_t*)",(Long_t)fCongigInfoPtr);
    }
}

 
void 
RcuManager::EmitMessage(const char *text)  //*SIGNAL*
{
  Emit("EmitMessage(const char*)", text);
}


RcuButton* 
RcuManager::GetRcuButtonPtr(int i)
{
  if(i < RCUS_PER_MODULE)
    {
      return  rcuButtonPtr[i];
    }         
  else
    {
      return 0;
    }
}

void  
RcuManager::HandleSaveTruConfigSlot(const TRUSettings_t *t) const
{
  //  cout << "RcuManager:::HandleSaveTruConfigSlot"  << endl;
  fDcsInterfacePtr->SaveTRUSettings(*t); 
}

void  
RcuManager::HandleApplyTruConfigSlot(const TRUSettings_t *t) const
{
  cout << "RcuManager::HandleApplyTruConfigSlot not implemented"  << endl;
  //  fDcsInterfacePtr->ApplyTRUSettings(*t) ; 
}



void 
RcuManager::HandleApplyFeeSlot()
{
  char message[1024];
  
  if((fIsSelectedRcu == kTRUE)  && ( fIsSelectedFee == kTRUE))
    {
      fDcsInterfacePtr->ApplyApdSettings(fCurrentModule->GetIntValue(),  fCurrentRcu, fCurrentBranch, fCurrentCard, message);
    }
  else
    {
      sprintf(message,"No card selected, cannot apply APD bias settings");
      cout << "ElectronicsMenu::HandleApplyFee: ERROR. no card is selected, caannot apply APD bias settings"<<  endl;
    }

  EmitMessage(message);

  cout << "RcuManager::HandleApplyFeeSlot()" << endl;
}


void 
RcuManager::HandleApplyModuleSlot()
{
  char message[1024];  

  for(int rcu = 0; rcu < RCUS_PER_MODULE; rcu ++)
    {
      sprintf(message, "checking rcu %d", rcu);
      HandleSelectRcuSlot(rcu);

      for(int branch =0; branch < BRANCHES_PER_RCU; branch ++)
	{
	  for(int card= 0; card < CARDS_PER_BRANCH; card ++)
	    {
	      cout << endl << endl;
	      int cardNumber = card +1;
	      fDcsInterfacePtr->ApplyApdSettings(fCurrentModule->GetIntValue(),  fCurrentRcu, branch, cardNumber, message);
	      cout<< "RcuManager::HandleApplyRcuSlot(), card =" << card << "  cardNumber = "<< cardNumber <<endl; 
	      cout << endl << endl;
	      EmitMessage(message);

	    }
	}
    }
}


void 
RcuManager::HandleApplyRcuSlot()
{
  char message[1024];

  if(fIsSelectedRcu == kTRUE)
    {
      for(int branch =0; branch < BRANCHES_PER_RCU; branch ++)
	{
	  for(int card= 0; card < CARDS_PER_BRANCH; card ++)
	    {
	      int cardNumber = card +1;
	      fDcsInterfacePtr->ApplyApdSettings(fCurrentModule->GetIntValue(),  fCurrentRcu, branch, cardNumber, message);
	      EmitMessage(message);
	    }
	}
    }
  else
    {
      cout << "RcuMnager::HandleApplyFee: ERROR. no RCU is selected, caannot apply APD bias settings"<<  endl;
      sprintf(message, "%s",  "RcuManager: ERROR. no RCU is selected, caannot apply APD bias settings");
   }
  EmitMessage(message); 
}


void 
RcuManager::HandleArmTriggerSlot()
{
  cout << "RcuManager::HandleArmTriggerSlot()"  << endl;
  char messageBuf[256];
  fDcsInterfacePtr->SetReadoutConfig(*fCurrentModule,  *fRdoConfigPtr, messageBuf);  
  EmitMessage(messageBuf);
  int t =fDcsInterfacePtr->ArmTrigger(fCurrentModule->GetIntValue());

  if( t<0 )
    {
      sprintf(messageBuf, "ERROR: The readout configuration was not apllied correctly");
      EmitMessage(messageBuf);
      sprintf(messageBuf, "too at least one of the RCUs");
      EmitMessage(messageBuf);
   }
  else
    {
      sprintf(messageBuf,  "INFO: The readout configuration was applied");
      EmitMessage(messageBuf);
      sprintf(messageBuf, "correctly to all readout partitions (RCUs)");
      EmitMessage(messageBuf); 
    }
  

  /*
  for(int rcu = 0; rcu < RCUS_PER_MODULE; rcu++)
    {
      fDcsInterfacePtr->ArmTrigger(fCurrentModule, rcu, messageBuf);
    }
  */
}


void 
RcuManager::HandleDisarmTriggerSlot()
{
  //  cout << "RcuManager::HandleDisamrTrigge_ttcrx_rSlot()"  << endl;
  char tmpMessage[256];

  for(int rcu= 0; rcu < RCUS_PER_MODULE; rcu++)
    {
      fDcsInterfacePtr->DisArmTrigger(fCurrentModule->GetIntValue(), rcu, tmpMessage);
      EmitMessage(tmpMessage);
    }
}


void 
RcuManager::HandleEnableTriggerSlot()
{
  EmitConfigInfo(fCongigInfoPtr); 
  char tmpMessage[256];
  //  cout << "RcuManager::HandleEnableTriggerSlot()"  << endl;
  sprintf(tmpMessage, "Enabling NIM trigger  for module %d  ....", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage);
  fDcsInterfacePtr->EnableTrigger(fCurrentModule->GetIntValue());
  sprintf(tmpMessage, "... Done");
}


void 
RcuManager::HandleEnableTrigger_ttcrx_Slot()
{
  EmitConfigInfo(fCongigInfoPtr); 
  char tmpMessage[256];
  sprintf(tmpMessage, "Enabling trigger over TTCRX for module %d  ....", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage);
  fDcsInterfacePtr->EnableTrigger_ttcrx(fCurrentModule->GetIntValue());
  sprintf(tmpMessage, "... Done");
  //  cout << "RcuManager::HandleEnableTrigge_ttcrx_rSlot()"  << endl;
}


void 
RcuManager::HandleOnOffFeeSlot(Int_t branch, Int_t card, Int_t state)
{
  char tmpMessage[1000];

  if(fIsSelectedRcu == kTRUE)
    {
      cout << "RcuManager::HandleOnOffFeeSlot(Int_t branch, Int_t card) : branch =" << branch <<"   card =" << card << "  state =  " << state  <<endl;
      unsigned int tmpStates[CARDS_PER_RCU];
      fDcsInterfacePtr->ToggleOnOffFee(fCurrentModule->GetIntValue(),  fCurrentRcu,  branch, card, state, tmpStates);      

      for(int i=0; i< CARDS_PER_RCU; i++)
	{
	  onOffButtPtr[i]->SetState(tmpStates[i]);
	}
    }
  else
    {
      cout << "RcuManager::HandleOnOffFeeSlot(Int_t branch, Int_t card) : Please slect an RCU first  " << endl;
    }
}




void 
RcuManager::HandleReadoutConfigChangedSlot(const ReadoutConfig_t *rdoConfigPtr)
{
  char tmpBuffer[256];

  //  cout << endl << endl;
  //  rdoConfigPtr->PrintInfo("RcuManager::HandleReadoutConfigChangedSlot");
  //  cout << endl << endl;


  if(fRdoConfigPtr !=0)
    {
      *fRdoConfigPtr  = *rdoConfigPtr;
      fRdoConfigPtr->PrintInfo( "RcuManager::HandleReadoutConfigChangedSlot "); 
    }
  else
    {
      cout <<  "RcuManager::HandleReadoutConfigChangedSlot creating new readoutconfig"  <<  endl;
      fRdoConfigPtr  = new ReadoutConfig_t(*rdoConfigPtr);
    }
  fDcsInterfacePtr->SetReadoutConfig(*fCurrentModule, *fRdoConfigPtr, tmpBuffer);

}



void 
RcuManager::HandleSaveConfigSlot()
{
  cout << "RcuManager::HandleSaveConfigSlot()"  << endl;
  fDcsInterfacePtr->SaveReadoutConfiguration(*fRdoConfigPtr); 
}


void
RcuManager::HandleSelectFeeSlot(Int_t branch, Int_t card, Bool_t save)
{
  if( (fIsSelectedRcu ==kTRUE) &&  (fIsSelectedFee == kTRUE))
    {
      unsigned long tmpApdValues[CSPS_PER_FEE];
 
      if(save == kTRUE)
	{
	  fApdInputPtr->GetApdValues(tmpApdValues);
	  fDcsInterfacePtr->SetApdValues( fCurrentModule->GetIntValue(),  fCurrentRcu, fCurrentBranch, fCurrentCard, tmpApdValues);   
	}
    }

  for(int i= 0; i< CARDS_PER_RCU; i++)
    {
      feeButtPtr[i]->SetBackgroundColor(UNKNOWN_COLOR);
      feeButtPtr[i]->RedrawCard();
    }
  
  if(fIsSelectedRcu == kTRUE)
    {
      //      cout << "RcuManager::HandleSelectFeeSlot(Int_t branch, Int_t card) : Rcu ="<<  fCurrentRcu <<" branch =" << branch <<"   card =" << card <<endl;
      fCurrentBranch = branch;
      fCurrentCard = card;
      fIsSelectedFee = kTRUE;
      unsigned long *tmpApdValues = 

	fDcsInterfacePtr->GetApdValues( fCurrentModule->GetIntValue(),  fCurrentRcu, fCurrentBranch, fCurrentCard); 

      for(int i=0; i< CSPS_PER_FEE; i++)
	{
	  fApdValues[i] = tmpApdValues[i];
	  fApdInputPtr->SetApdValues(fApdValues);
	}

      feeButtPtr[fCurrentBranch*CARDS_PER_BRANCH + fCurrentCard -1]->SetBackgroundColor(SELECTED_COLOR);
      feeButtPtr[fCurrentBranch*CARDS_PER_BRANCH + fCurrentCard -1]->RedrawCard();
      fApdInputPtr->DrawLabels(fCurrentRcu, fCurrentBranch, fCurrentCard);
 
    }
  else
    {
      cout << "RcuManager::HandleSelectlot(Int_t branch, Int_t card) : Please slect an RCU first  " << endl;
    }
}


void 
RcuManager::HandleRequestConfigInfoSlot(ConfigInfo_t* t)
{
  cout <<  "RcuManager::HandleRequestConfigInfoSlot(ConfigInfo_t* t)"   << endl;
  fDcsInterfacePtr->GetConfigComment(t->fInfo, t->fID);
  fCongigInfoPtr->fID =t->fID;
  sprintf(fCongigInfoPtr->fInfo, "%s", t->fInfo);
  EmitConfigInfo(t);
}


void 
RcuManager::HandleRequestConfigLoadSlot(ConfigInfo_t* t)
{
  fCongigInfoPtr->fID = t->fID;


  fCongigInfoPtr->fIDLimit = t->fIDLimit;
  sprintf(fCongigInfoPtr->fInfo, "%s", t->fInfo);

  fDcsInterfacePtr->LoadApdConfig(fCongigInfoPtr, fCongigInfoPtr->fID);
  fDcsInterfacePtr->LoadApdValues(fCurrentModule->GetIntValue());

  if( fIsSelectedFee == true)
    {
      HandleSelectFeeSlot(fCurrentBranch, fCurrentCard, kFALSE); // dont save currrent values
    }

}


void 
RcuManager::HandleRequestConfigSaveSlot(ConfigInfo_t *t)
{
  cout << "RcuManager::HandleRequestConfigSaveSlot(ConfigInfo_t), info = " << t->fInfo <<endl;
  fDcsInterfacePtr->SaveApdConfig(t->fInfo);
}
// SaveApdConfig(char *description);


void 
RcuManager::HandleSelectRcuSlot(Int_t rcuId)
{
  fCurrentRcu = rcuId;
  fIsSelectedRcu = kTRUE; 
  fIsSelectedFee = kFALSE;
  fApdInputPtr->ResetApdValues();
  fDcsInterfacePtr->UpdateAFL(fCurrentModule->GetIntValue(), rcuId);

  for(int i= 0; i< CARDS_PER_RCU; i++)
    {
      feeButtPtr[i]->SetBackgroundColor(UNKNOWN_COLOR);
      feeButtPtr[i]->RedrawCard();
      onOffButtPtr[i]->SetState(FEE_STATE_UNKNOWN);
    }

  for(int i = 0; i<RCUS_PER_MODULE; i++ )
    {
      rcuButtonPtr[i]->SetBackgroundColor(0xAAAAAA); 
      rcuButtonPtr[i]->RedrawRcu();
    }
  
  rcuButtonPtr[fCurrentRcu]->SetBackgroundColor(1000);
  rcuButtonPtr[fCurrentRcu]->RedrawRcu();
  char tmpMessage[256];
  unsigned int tmpState = 0;

  for(int branch = 0; branch < FEE_BRANCHS; branch ++ )
    {
      for(int card = 0;  card < CARDS_PER_BRANCH;  card ++)
	{
	  tmpState = fDcsInterfacePtr->CheckFeeState(fCurrentModule->GetIntValue(),  fCurrentRcu, branch, card +1, tmpMessage); 
	  EmitMessage(tmpMessage);
	  onOffButtPtr[branch*CARDS_PER_BRANCH + card]->SetState(tmpState);
	}
    }

}


void 
RcuManager::HandleSetAllApdFeeSlot(Int_t val)
{
  cout << "RcuManager::HandleSetAllApdFeeSlot(Int_t val), val ="  << val <<endl;
  if(fIsSelectedFee == true)
    {
      fDcsInterfacePtr->SetAllApds(fCurrentModule->GetIntValue(), fCurrentRcu, fCurrentBranch, fCurrentCard, val);
      HandleSelectFeeSlot(fCurrentBranch, fCurrentCard, kFALSE);
    }
  else
    {
      cout << "RcuManager::HandleSetAllApdFeeSlot(Int_t val): ERROR, no feecard selected"  << endl;
    }
}


void 
RcuManager::HandleSetAllApdRcuSlot(Int_t val)
{
  cout << "RcuManager::HandleSetAllApdRculot(Int_t val), val = "  << val <<endl;
  fDcsInterfacePtr->SetAllApds(fCurrentModule->GetIntValue(), fCurrentRcu, val);
  
  if(fIsSelectedFee == true)
    {
      HandleSelectFeeSlot(fCurrentBranch, fCurrentCard, kFALSE);
    }

}


void 
RcuManager::HandleSetAllApdModuleSlot(Int_t val)
{
  cout << "RcuManager::HandleSetAllApdModuleSlot(Int_t val), val =" << val  << endl;
  fDcsInterfacePtr->SetAllApds(fCurrentModule->GetIntValue(),  val);
  if(fIsSelectedFee == true)
    {
      HandleSelectFeeSlot(fCurrentBranch, fCurrentCard, kFALSE);
    }
}


void 
RcuManager::HandleTurnOffAllFeeSlot()
{
  char tmpMessage[256];
  Rcu *tmpRcuPtr;

  for(int rcuId = 0; rcuId < RCUS_PER_MODULE; rcuId ++)
    {
      tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"turning Off all FEESCs for %s, pleae wait ",tmpRcuPtr-> GetFeeServerName());
      EmitMessage(tmpMessage);
      fDcsInterfacePtr-> TurnOffAllFee(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"Done turning Off all FEESCs for %s",tmpRcuPtr-> GetFeeServerName());  
      EmitMessage(tmpMessage);
    }

  sprintf(tmpMessage,"All FFFECs for module %d was turned of", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage); 

  if(fIsSelectedRcu == true)
    {
      sprintf(tmpMessage,"Probing FEE status for currently selected Module %d, rcu %d ", fCurrentModule->GetIntValue(), fCurrentRcu);
      EmitMessage(tmpMessage);  
      HandleSelectRcuSlot(fCurrentRcu);
      sprintf(tmpMessage,"Finnsihed Probing FEE status for currently selected Module %d, rcu %d ", fCurrentModule->GetIntValue(), fCurrentRcu);
      EmitMessage(tmpMessage); 
    }
}


void 
RcuManager::HandleTurnOnAllFeeSlot()
{
  char tmpMessage[256];
  Rcu *tmpRcuPtr;

  for(int rcuId = 0; rcuId < RCUS_PER_MODULE; rcuId ++)
    {
      tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), rcuId);   
      sprintf(tmpMessage,"turning ON all FEESCs for %s, pleae wait ",tmpRcuPtr-> GetFeeServerName()); 
      EmitMessage(tmpMessage);
      fDcsInterfacePtr->TurnOnAllFee(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"Done turning ON all FEESCs for %s",tmpRcuPtr-> GetFeeServerName());   
      EmitMessage(tmpMessage); 
    }
  
  sprintf(tmpMessage,"All FFFECs for module %d was turned of", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage); 

  if(fIsSelectedRcu == true)
    {
      sprintf(tmpMessage,"Probing FEE status for currently selected Module %d, rcu %d ", fCurrentModule->GetIntValue(), fCurrentRcu);
      EmitMessage(tmpMessage);  
      HandleSelectRcuSlot(fCurrentRcu);
      sprintf(tmpMessage,"Finnsihed Probing FEE status for currently selected Module %d, rcu %d ", fCurrentModule->GetIntValue(), fCurrentRcu);
      EmitMessage(tmpMessage);   
    } 
}

void 
RcuManager::HandleTurnOffAllTruSlot()
{
  char tmpMessage[256];
  Rcu *tmpRcuPtr;

  for(int rcuId = 0; rcuId < RCUS_PER_MODULE; rcuId ++)
    {
      tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"Turning off all TRUs for %s",tmpRcuPtr-> GetFeeServerName());  
      EmitMessage(tmpMessage);
      fDcsInterfacePtr-> TurnOffAllTru(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"Done turning off all TRUs for %s",tmpRcuPtr-> GetFeeServerName());  
      EmitMessage(tmpMessage);
    }

  sprintf(tmpMessage,"All TRUs for module %d was turned of", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage); 
}


void 
RcuManager::HandleTurnOnAllTruSlot()
{
  char tmpMessage[256];
  Rcu *tmpRcuPtr;

  for(int rcuId = 0; rcuId < RCUS_PER_MODULE; rcuId ++)
    {
      tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), rcuId);   
      sprintf(tmpMessage,"Turning on all TRUs for %s, pleae wait ",tmpRcuPtr-> GetFeeServerName()); 
      EmitMessage(tmpMessage);
      fDcsInterfacePtr->TurnOnAllTru(fCurrentModule->GetIntValue(), rcuId);
      sprintf(tmpMessage,"Done turning on all TRUs for %s",tmpRcuPtr-> GetFeeServerName());   
      EmitMessage(tmpMessage); 
    }
  
  sprintf(tmpMessage,"All TRUs for module %d was turned on", fCurrentModule->GetIntValue());
  EmitMessage(tmpMessage); 
}


void
RcuManager::DrawFeeGrid(int X, int Y, int W, int H, int B)
{
  feeGroupFramePtr = new TGGroupFrame(fFramePtr,"Front End Cards");
  feeGroupFramePtr->MoveResize(X, Y, W, H); 
  int s=0;
  int x=B;
  int y = B;
  int w = (W-2*B-15*s)/15;
  int h = (H-2*B)/2;   //height
  char name[5];    //label
  int mNr;         //module nr
  int fNr=0;
  char tmpName[100];

  int tmpBranch;

  for(int i = 0; i < CARDS_PER_BRANCH; i++)http://start.fedoraproject.org/
    {
      tmpBranch = BRANCH_A;

      sprintf(tmpName, "%d", i+1);
      feeButtPtr[i] = new FeeCardButton(feeGroupFramePtr, tmpName, tmpBranch, i+1);
      onOffButtPtr[i] = new FeeCardOnOffButton(feeGroupFramePtr,tmpBranch, i+1); 
      feeButtPtr[i]->MoveResize(x+i*(w+s), y+30, w, h-35);    
      onOffButtPtr[i]->MoveResize(x+i*(w+s), y, w, 30); 
   } 

  for(int i = 0; i < CARDS_PER_BRANCH; i++)
    {
      tmpBranch = BRANCH_B;

      sprintf(tmpName, "%d", i+1);
      feeButtPtr[i+CARDS_PER_BRANCH] = new FeeCardButton(feeGroupFramePtr, tmpName, tmpBranch, i+1); 
      onOffButtPtr[i+CARDS_PER_BRANCH] = new FeeCardOnOffButton(feeGroupFramePtr, tmpBranch, i+1);   
      feeButtPtr[i+CARDS_PER_BRANCH]->MoveResize(x+i*(w+s), y+h+30, w, h-35);    
      onOffButtPtr[i+CARDS_PER_BRANCH]->MoveResize(x+i*(w+s), y+h, w, 30); 
    }

  branchA = new TGLabel(feeGroupFramePtr  , "A");
  branchB = new TGLabel(feeGroupFramePtr  , "B");
  branchA->MoveResize(10, 100,  10, 10);
  branchB->MoveResize(10, 250, 10, 10);
  fFramePtr->MapSubwindows();  
  feeGroupFramePtr->MapSubwindows();  
}


void
RcuManager::DrawModules(int X, int Y, int W, int H, int B)
{
  bool isok = true;

  rcuGroupPtr = new TGGroupFrame(fFramePtr,"Phos Module as seen from the back");
  rcuGroupPtr->MoveResize(X, Y, W, H);

  int s=10;                //spacing between modules;
  int x= B;                //distance from lef
  int y= B;                //distance from top
  int w= (W-2*B-8*s)/2+30;   //width of each rcubutton
  int h= (H-2*B)/2;   //height of each rcubutton
  
  int i=2;
  int j=0;
  char tmpName[100];
  Rcu *tmpRcuPtr;

  tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), RCU_0);

  if( tmpRcuPtr  != 0)
    {
      rcuButtonPtr[RCU_0] = new RcuButton(rcuGroupPtr, tmpRcuPtr->GetFeeServerName()); 
    }
  else
    {
      isok = false;
      cout <<  "RcuManager::DrawModules, ERROR, rcuButtonPtr[" <<  RCU_0   << "] =" << 0  << endl;
    }
      



  tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), RCU_1);
  
  if( tmpRcuPtr  != 0)
    {
      rcuButtonPtr[RCU_1] = new RcuButton(rcuGroupPtr, tmpRcuPtr->GetFeeServerName()); 
    }
  else
    {
      isok = false;
      cout <<  "RcuManager::DrawModules, ERROR, rcuButtonPtr[" <<  RCU_1   << "] ="<< 0  << endl;
    }
  
 






  tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), RCU_2);
  
  if( tmpRcuPtr  != 0)
    {
      rcuButtonPtr[RCU_2] = new RcuButton(rcuGroupPtr, tmpRcuPtr->GetFeeServerName()); 
    }
  else
    {
      isok = false;
      cout <<  "RcuManager::DrawModules, ERROR, rcuButtonPtr[" <<  RCU_2   << "] ="<< 0  << endl;
    } 
  



  tmpRcuPtr = fDcsInterfacePtr->GetRcuPtr(fCurrentModule->GetIntValue(), RCU_3);
					  
  if( tmpRcuPtr  != 0)
    {
      rcuButtonPtr[RCU_3] = new RcuButton(rcuGroupPtr, tmpRcuPtr->GetFeeServerName()); 
    }
  else
    {
      isok = false; 
      cout <<  "RcuManager::DrawModules, ERROR, rcuButtonPtr[" <<  RCU_3   << "] ="<< 0  << endl;
    }  


  if(isok == true)
    {
      //     rcuButtonPtr[RCU_3] = new RcuButton(rcuGroupPtr, tmpRcuPtr->GetFeeServerName()); 
      rcuButtonPtr[RCU_0]->MoveResize(x+2*j*(w+s),     y,   w, h);
      rcuButtonPtr[RCU_1]->MoveResize(x+2*j*(w+s)+w,   y,   w, h);
      rcuButtonPtr[RCU_2]->MoveResize(x+2*j*(w+s),     y+h, w, h);
      rcuButtonPtr[RCU_3]->MoveResize(x+2*j*(w+s)+w,   y+h, w, h);
      rcuGroupPtr->MapSubwindows(); 
    }

  else
    {
      cout << "RcuManager::DrawModules, ERROR, could not drwa guio beacues one or more RCUs points to zero "<< endl;
    }

}

 
const TRUSettings_t 
RcuManager::GetTRUSettings() const
{
  TRUSettings_t *t = new   TRUSettings_t(); 

  fDcsInterfacePtr->LoadTruSettings(t);
  
  TRUSettings_t t2 = *t;
  delete t;

  return t2;
}
