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

#include "MainGui.h"
#include "MainMenu.h"
#include "LogViewer.h"
#include "PhosMenuButton.h"
#include "PhosNumberEntry.h"
#include "SandboxMenu.h"
#include "ElectronicsMenu.h"
#include "ElectronicsMenuApply.h"
#include "ElectronicsMenuRCU.h"
#include "ElectronicsMenuReadout.h"

#include "RcuButton.h"
#include "LogViewer.h"
#include "TruMenu.h"
#include "RcuManager.h"
#include "PhosDataTypes.h"


ClassImp(MainGui) 


MainGui*  MainGui::fgInstancePtr = 0;

MainGui*
MainGui::Instance() 
{
  if (!fgInstancePtr) fgInstancePtr = new MainGui;
  return fgInstancePtr;
}


MainGui::MainGui() :  TGMainFrame(), 
		      PhosDcsBase(), 
		      fRcuManagerPtr(0),
		      rcuGroupPtr(0), 
		      sandboxMenuPtr(0),
		      electronicsMenuPtr(0),
		      mainMenuPtr(0),
		      logviewerPtr(0),
		      truFramePtr(0),
		      truMenuPtr(0),
		      allFeeOnButtPtr(0),
		      allFeeOffButtPtr(0),
		      allTruOnButtPtr(0),
		      allTruOffButtPtr(0)
{
  fRcuManagerPtr = new  RcuManager(this); 
  InitGraphics();
  InitSignalSlotConnections();
}


MainGui::~MainGui()
{

}



void 
MainGui::InitSignalSlotConnections()
{
  fRcuManagerPtr->Connect("EmitConfigInfo(ConfigInfo_t*)", "MainMenu", mainMenuPtr, "HandleConfigChangedSlot(ConfigInfo_t*)");
  fRcuManagerPtr->Connect("EmitMessage(const char*)", "LogViewer", logviewerPtr, "HandleMessage(const char*)" );

  electronicsMenuPtr->fApply->fApplyFeeButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleApplyFeeSlot()");
  electronicsMenuPtr->fApply->fApplyRcuButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleApplyRcuSlot()");
  electronicsMenuPtr->fApply->fApplyModuleButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleApplyModuleSlot()");

  electronicsMenuPtr->fRCU->fArmTriggerButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleArmTriggerSlot()");
  electronicsMenuPtr->fRCU->fEnableTriggerButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleEnableTriggerSlot()");
  electronicsMenuPtr->fRCU->fEnableTrigger_ttcrx_ButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleEnableTrigger_ttcrx_Slot()");
  electronicsMenuPtr->fRCU->fDisarmTriggerButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleDisarmTriggerSlot()");
  electronicsMenuPtr->fReadout->fSaveButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr, "HandleSaveConfigSlot()");
  electronicsMenuPtr->fReadout->Connect("EmitReadoutConfigChangedSignal(const ReadoutConfig_t*)", "RcuManager", fRcuManagerPtr ,"HandleReadoutConfigChangedSlot(const ReadoutConfig_t*)");

  truMenuPtr->fApplyButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", fRcuManagerPtr , "HandleApplyTruConfigSlot(const TRUSettings_t*) const" );
  
  truMenuPtr->Connect("EmitSaveSettingsSignal(const TRUSettings_t*)",  
 		      "RcuManager", fRcuManagerPtr , "HandleSaveTruConfigSlot(const TRUSettings_t*) const" );
  mainMenuPtr->Connect("EmitRequestConfigInfoSignal(ConfigInfo_t*)", "RcuManager", 
 		       fRcuManagerPtr, "HandleRequestConfigInfoSlot(ConfigInfo_t*)");
  mainMenuPtr->Connect("EmitRequestConfigLoadSignal(ConfigInfo_t*)", "RcuManager", 
 		       fRcuManagerPtr, "HandleRequestConfigLoadSlot(ConfigInfo_t*)");
  mainMenuPtr->Connect("EmitRequestConfigSaveSignal(ConfigInfo_t*)", "RcuManager", 
 		       fRcuManagerPtr, "HandleRequestConfigSaveSlot(ConfigInfo_t*)");

  allFeeOnButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", 
 			   fRcuManagerPtr, "HandleTurnOnAllFeeSlot()");
  allFeeOffButtPtr->Connect("HandleButton(Event_t*)", "RcuManager", 
 			    fRcuManagerPtr, "HandleTurnOffAllFeeSlot()"); 
  sandboxMenuPtr->Connect("EmitSetAllApdFeeSignal(Int_t)",    "RcuManager",  
 			  fRcuManagerPtr,  "HandleSetAllApdFeeSlot(Int_t)");
  sandboxMenuPtr->Connect("EmitSetAllApdRcuSignal(Int_t)",    "RcuManager",  
 			  fRcuManagerPtr,  "HandleSetAllApdRcuSlot(Int_t)");
  sandboxMenuPtr->Connect("EmitSetAllApdModuleSignal(Int_t)", "RcuManager",  
 			  fRcuManagerPtr,  "HandleSetAllApdModuleSlot(Int_t)");
  fRcuManagerPtr->EmitConfigInfo();
  electronicsMenuPtr->fReadout->EmitReadoutConfigChangedSignal();


}


void
MainGui::InitGraphics()
{
  this->MapWindow();
  this->SetWindowName("PHOS APD bias control");
  this->MoveResize(200,200,1000,720);

  mainMenuPtr = new MainMenu(this, 650, 20, 280, 290 );

  //  ReadoutConfig_t t = fRcuManagerPtr->GetReadoutConfiguration();

  electronicsMenuPtr = new ElectronicsMenu(this, fRcuManagerPtr->GetReadoutConfiguration(), 400, 20, 230, 460);
  



  sandboxMenuPtr = new SandboxMenu(this, 650, 320, 280, 160);
  logviewerPtr = new LogViewer(this, 270, 490, 700, 220);

  allFeeOnButtPtr = new PhosMenuButton(this, "Turn ON Electronics");
  allFeeOnButtPtr->MoveResize(20, 600, 130, 30);
  allFeeOffButtPtr = new PhosMenuButton(this, "Turn OFF Electronics" );
  allFeeOffButtPtr->MoveResize(20, 650, 130, 30);
  allTruOnButtPtr = new PhosMenuButton(this, "Turn ON TRUs");
  allTruOnButtPtr->MoveResize(170, 600, 90, 30);
  allTruOffButtPtr = new PhosMenuButton(this, "Turn OFF TRUs" );
  allTruOffButtPtr->MoveResize(170, 650, 90, 30);

  this->MapSubwindows(); 
  logviewerPtr->DisplayMessage("Phos APD bias controll was initialized successfully");


  truFramePtr = new TGMainFrame();
  //  truMenuPtr = new TruMenu(truFramePtr, 20, 20, 230, 460);
  truMenuPtr = new TruMenu(truFramePtr, fRcuManagerPtr->GetTRUSettings() , 20, 20, 230, 460);

  truFramePtr->MoveResize(300,300,300,500);
  truFramePtr->MapWindow();
  truFramePtr->SetWindowName("TRU control");
  truFramePtr->MapSubwindows();
 
  //  fRcuManagerPtr = new  RcuManager(this); 
}







