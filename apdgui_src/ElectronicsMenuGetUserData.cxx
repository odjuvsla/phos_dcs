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

#include "ElectronicsMenuGetUserData.h"
#include <iostream>
#include "PhosNumberEntry.h"
#include "PhosMenuButton.h"

using namespace std;

ClassImp(ElectronicsMenuGetUserData)


ElectronicsMenuGetUserData::~ElectronicsMenuGetUserData()
{

}


ElectronicsMenuGetUserData::ElectronicsMenuGetUserData():fPatternInputFramePtr(0),
							 fPatternTypeComboPtr(0),
							 fAmplitudeComboPtr(0),
							 fStepComboPtr(0),
							 fStepSizeInputPtr(0),
							 fMaxAmplitudeInputPtr(0),
							 fOKApplyPtr(0),
							 fOKDontApplyPtr(0),
							 fPatternPtr(0)
{
  fPatternPtr = new Pattern_t();
}


void 
ElectronicsMenuGetUserData::DrawPatterntypeCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H)
{
  fPatternTypeComboPtr =  new TGComboBox(t,-1, kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
  fPatternTypeComboPtr->AddEntry("Ramp", RAMP_PATTERN);
  fPatternTypeComboPtr->AddEntry("Sawtooth", SAWTOOTH_PATTERN);
  fPatternTypeComboPtr->AddEntry("Gamma2",  G2_PATTERN);
  fPatternTypeComboPtr->MoveResize(X, Y, W, H);
  t->AddFrame(fPatternTypeComboPtr, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
}


void 
ElectronicsMenuGetUserData::DrawAmplitudeCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H)
{
  fAmplitudeComboPtr = new TGComboBox(t,-1, kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground); 
  fAmplitudeComboPtr->AddEntry("30", 30);
  fAmplitudeComboPtr->AddEntry("100", 100);
  fAmplitudeComboPtr->AddEntry("200", 200);
  fAmplitudeComboPtr->AddEntry("300", 300);
  fAmplitudeComboPtr->AddEntry("400", 400); 
  fAmplitudeComboPtr->AddEntry("500", 500); 
  fAmplitudeComboPtr->AddEntry("600", 600);
  fAmplitudeComboPtr->AddEntry("700", 700);
  fAmplitudeComboPtr->AddEntry("800", 800);
  fAmplitudeComboPtr->AddEntry("900", 900); 
  fAmplitudeComboPtr->AddEntry("1023", 1023); 
  fAmplitudeComboPtr->MoveResize(X, Y, W, H);
  t->AddFrame(fAmplitudeComboPtr, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2)); 
}


void 
ElectronicsMenuGetUserData::DrawStepCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H)
{
  fStepComboPtr = new TGComboBox(fPatternInputFramePtr,-1, kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);    
  fStepComboPtr->AddEntry("1",1);
  fStepComboPtr->AddEntry("5",5);
  fStepComboPtr->AddEntry("10",10);
  fStepComboPtr->AddEntry("20",20);
  fStepComboPtr->AddEntry("20",20);
  fStepComboPtr->AddEntry("50",50);
  fStepComboPtr->AddEntry("100",100);
  fStepComboPtr->MoveResize(X, Y, W, H);
  t->AddFrame(fStepComboPtr, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
}


void 
ElectronicsMenuGetUserData::DrawButtons(TGTransientFrame *t, const int X, const int Y, const int W, const int H)
{
  int spacing = 10;
  fOKApplyPtr = new  PhosMenuButton(t, "Download this pattern and use pattern trigger");
  fOKApplyPtr->MoveResize(X, Y, W, H);
  fOKDontApplyPtr = new  PhosMenuButton(t, "Dont download pattern, but use pattern trigger");
  fOKDontApplyPtr->MoveResize(X, Y + H +spacing, W, H);
}


void 
ElectronicsMenuGetUserData::ConnectSignalAndSlots()
{
  fPatternTypeComboPtr->Connect("Selected(Int_t)", "ElectronicsMenuGetUserData", this, "HandleSelectPatternType(Int_t)");
  fAmplitudeComboPtr->Connect("Selected(Int_t)",   "ElectronicsMenuGetUserData", this, "HandleSelectAmplitude(Int_t)");
  fStepComboPtr->Connect("Selected(Int_t)",        "ElectronicsMenuGetUserData", this, "HandleSelectStepSize(Int_t)");
  fOKApplyPtr->Connect("HandleButton(Event_t*)", "ElectronicsMenuGetUserData", this, "HandleOKApply()");  
  fOKDontApplyPtr->Connect("HandleButton(Event_t*)", "ElectronicsMenuGetUserData", this, "HandleOKDontApply()");   
}


void  
ElectronicsMenuGetUserData::GetPatternFromUser()
{
  if(fPatternPtr == 0)
    {
      fPatternPtr = new Pattern_t(); 
    }

  fPatternInputFramePtr   = new TGTransientFrame();
  fPatternInputFramePtr->MoveResize(50, 350, 300, 300);
  DrawPatterntypeCombo(fPatternInputFramePtr, 50, 50, 102, 22);
  DrawAmplitudeCombo(fPatternInputFramePtr, 50, 80, 102, 22);
  DrawStepCombo(fPatternInputFramePtr, 50, 110, 102, 22);
  DrawButtons(fPatternInputFramePtr, 20, 150, 270, 22);
  ConnectSignalAndSlots();

  fPatternTypeComboPtr->Select(0); 
  fAmplitudeComboPtr->Select(600); 
  fStepComboPtr->Select(1);

  fPatternInputFramePtr->MapSubwindows();
  fPatternInputFramePtr->MapWindow();

}


void 
ElectronicsMenuGetUserData::HandleOKApply() //*SIGNAL*
{
  fPatternInputFramePtr->DestroyWindow();
  Emit("HandleOKApply()"); 
}


void 
ElectronicsMenuGetUserData::HandleOKDontApply() //*SIGNAL*
{
  fPatternInputFramePtr->DestroyWindow(); 
  delete fPatternPtr;
  fPatternPtr = 0; 
  Emit("HandleOKDontApply()");
}


void 
ElectronicsMenuGetUserData::HandleSelectPatternType(Int_t t)
{
  fPatternPtr->SetPatternType(t);
  EmitPatternChangedSignal(fPatternPtr); 
}


void 
ElectronicsMenuGetUserData::HandleSelectAmplitude(Int_t t)
{
  fPatternPtr->SetAmplitude(t);
  EmitPatternChangedSignal(fPatternPtr); 
}


void 
ElectronicsMenuGetUserData::HandleSelectStepSize(Int_t t)
{
  fPatternPtr->SetStep(t);
  EmitPatternChangedSignal(fPatternPtr); 
}


void 
ElectronicsMenuGetUserData::EmitPatternChangedSignal(const Pattern_t *pattern) //*SIGNAL*
{
  Emit("EmitPatternChangedSignal(const Pattern_t*) const", (Long_t)fPatternPtr);
}

