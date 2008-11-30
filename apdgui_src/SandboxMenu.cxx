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

#include <TGFrame.h> 
#include "SandboxMenu.h"
#include "PhosMenuButton.h"
#include "TGNumberEntry.h"
#include "PhosNumberEntry.h"
#include <iostream>

using namespace std;


ClassImp(SandboxMenu)


SandboxMenu::SandboxMenu() 
{
  // never called
}
              

SandboxMenu::~SandboxMenu()
{

}


SandboxMenu:: SandboxMenu(const TGMainFrame *framePtr, const int X, const int Y, const int W, const int H)
{
  sandboxMenuPtr = new TGGroupFrame(framePtr,"Sandbox");
  sandboxMenuPtr->MoveResize(X, Y , W, H); 
  setFeeAllButtPtr  = new PhosMenuButton(sandboxMenuPtr, "Set all APD for fee to"); 
  setFeeAllButtPtr->MoveResize(20, 20, 150, 20);
  apdValFeeInputPtr = new TGNumberEntry(sandboxMenuPtr, 512, 5, -1, (TGNumberFormat::EStyle) 5);
  apdValFeeInputPtr->MoveResize(180, 20, 80, 20);
  apdValFeeInputPtr->SetLimits(TGNumberFormat::kNELLimitMinMax, 0, 1023);
  setRcuAllButtPtr = new PhosMenuButton(sandboxMenuPtr,  "Set all APD for RCU to");
  setRcuAllButtPtr->MoveResize(20, 45, 150, 20);
  apdValRcuInputPtr= new TGNumberEntry(sandboxMenuPtr, 512, 5, -1, (TGNumberFormat::EStyle) 5);
  apdValRcuInputPtr->MoveResize(180, 45, 80, 20);
  apdValRcuInputPtr->SetLimits(TGNumberFormat::kNELLimitMinMax, 0, 1023);
  setModuleAllButtPtr = new PhosMenuButton(sandboxMenuPtr, "Set all APD for Module to"); 
  setModuleAllButtPtr->MoveResize(20, 70, 150, 20);
  apdValModuleInputPtr  = new TGNumberEntry(sandboxMenuPtr, 512, 5, -1, (TGNumberFormat::EStyle) 5);
  apdValModuleInputPtr->MoveResize(180, 70, 80, 20);
  apdValModuleInputPtr->SetLimits(TGNumberFormat::kNELLimitMinMax, 0, 1023);
  sandboxMenuPtr->MapSubwindows();  

 
  setFeeAllButtPtr->Connect("HandleButton(Event_t*)", "SandboxMenu", this, "EmitSetAllApdFeeSignal(Int_t)" );
  setRcuAllButtPtr->Connect("HandleButton(Event_t*)", "SandboxMenu", this, "EmitSetAllApdRcuSignal(Int_t)" );
  setModuleAllButtPtr->Connect("HandleButton(Event_t*)", "SandboxMenu", this, "EmitSetAllApdModuleSignal(Int_t)");
 

}



void 
SandboxMenu::EmitSetAllApdFeeSignal(Int_t value) //*SIGNAL*
{
  cout << "SandboxMenu::EmitSetAllApdFeeSignal" << endl;
  Int_t tmpVal =  apdValFeeInputPtr->GetIntNumber();
  Emit("EmitSetAllApdFeeSignal(Int_t)", tmpVal);
}


void
SandboxMenu::EmitSetAllApdRcuSignal(Int_t value) //*SIGNAL*
{
  cout << "SandboxMenu::EmitSetAllApdRcuSignal" << endl;
  Int_t tmpVal =  apdValRcuInputPtr->GetIntNumber();
  Emit("EmitSetAllApdRcuSignal(Int_t)", tmpVal);
}


void
SandboxMenu:: EmitSetAllApdModuleSignal(Int_t value) //*SIGNAL*
{
  cout << "SandboxMenu::EmitSetAllApdModuleSignal" << endl; 
  Int_t tmpVal =  apdValModuleInputPtr->GetIntNumber();
  Emit("EmitSetAllApdModuleSignal(Int_t)", tmpVal);
}

