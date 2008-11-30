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

#include "ElectronicsMenuReadout.h"
#include "ElectronicsMenuGetUserData.h"

#include <iostream>
#include "TGFrame.h"

#include "PhosNumberEntry.h"
#include "PhosMenuButton.h"
#include "TGComboBox.h" 
#include "TGLabel.h"  

using namespace std;




ElectronicsMenuReadout::ElectronicsMenuReadout()
{

}


ElectronicsMenuReadout::ElectronicsMenuReadout(const TGGroupFrame *frame, 
					       const ReadoutConfig_t rdoconf, 
					       const int X, const int Y, 
					       const int W, const int H) : fReadoutConfigPtr(0),
									   fApplyPattern(true)
									   //		   fPatternPtr(0)
{
  fReadoutConfigMenuPtr = new TGGroupFrame(frame,"Readout Configuration"); 
  fReadoutConfigMenuPtr->MoveResize(X, Y, W, H); 

  fSaveButtPtr = new PhosMenuButton(fReadoutConfigMenuPtr, "Save");
  fSaveButtPtr->MoveResize(130, 20, 50,20 );

  fSaveButtPtr = new PhosMenuButton(fReadoutConfigMenuPtr, "Save");
  fSaveButtPtr->MoveResize(130, 20, 50,20 );
  TGLabel  *startLabelPtr = new TGLabel(fReadoutConfigMenuPtr, "From");
  startLabelPtr-> MoveResize( 30, 20, 50, 20);
  TGLabel  *endLabelPtr = new TGLabel(fReadoutConfigMenuPtr, "To");
  endLabelPtr->MoveResize(80, 20, 50, 20);

  fStartZInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr, rdoconf.GetReadoutRegion().GetStartZ().GetIntValue(), 
					5, -1, (TGNumberFormat::EStyle) 5);
  fStartZInputPtr->MoveResize( 30, 40, 40, 18);
  fStartZInputPtr->SetLimits(0, 55);
  fEndZInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr,  rdoconf.GetReadoutRegion().GetEndZ().GetIntValue(), 
				      5, -1, (TGNumberFormat::EStyle) 5);
  fEndZInputPtr->MoveResize( 80,  40, 40, 18); 
  fEndZInputPtr->SetLimits(0, 55);
  fStartXInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr,  rdoconf.GetReadoutRegion().GetStartX().GetIntValue(),
					5, -1, (TGNumberFormat::EStyle) 5);
  fStartXInputPtr->MoveResize(30, 60, 40, 18);
  fStartXInputPtr->SetLimits(0, 63);
  fEndXInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr,  rdoconf.GetReadoutRegion().GetEndX().GetIntValue(),
				      5, -1, (TGNumberFormat::EStyle) 5);
  fEndXInputPtr->MoveResize(  80, 60, 40, 18); 
  fEndXInputPtr->SetLimits(0, 63);

  TGLabel  *zLabelPtr = new TGLabel(fReadoutConfigMenuPtr, "Z");
  zLabelPtr-> MoveResize(     10,   40, 20, 20);
  TGLabel  *xLabelPtr = new TGLabel(fReadoutConfigMenuPtr, "X");
  xLabelPtr->MoveResize(     10,  60, 20, 20);

  fNSamplesInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr, rdoconf.GetAltroConfig().GetNSamples().GetIntValue(), 
					  5, -1, (TGNumberFormat::EStyle) 5);
  fNSamplesInputPtr->MoveResize(120, 80, 50, 18);
  fNSamplesInputPtr->SetLimits(0, 1008);
  fNPreSamplesInputPtr = new PhosNumberEntry(fReadoutConfigMenuPtr,  rdoconf.GetAltroConfig().GetNPreSamples().GetIntValue(),
					     5, -1, (TGNumberFormat::EStyle) 5);
  fNPreSamplesInputPtr->MoveResize(120, 100, 50, 18);
  fNPreSamplesInputPtr->SetLimits(0, 15);

  TGLabel  *nSamplesLabelPtr =  new TGLabel(fReadoutConfigMenuPtr, "Samples");
  nSamplesLabelPtr->MoveResize(20, 80, 70, 20);
  TGLabel *nPreSamplesLabelPtr= new TGLabel(fReadoutConfigMenuPtr, "Pre-Samples");
  nPreSamplesLabelPtr->MoveResize(20, 100, 70, 20);

  fReadoutModeInpuPtr  = new TGComboBox(fReadoutConfigMenuPtr,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
  fReadoutModeInpuPtr->AddEntry("Normal(0) ",0);
  fReadoutModeInpuPtr->AddEntry("Pattern(1)",1);
  fReadoutModeInpuPtr->Resize(102,22);
  fReadoutModeInpuPtr->Select(0);
  TGLabel *rdoConfLabelPtr = new  TGLabel(fReadoutConfigMenuPtr, "mode");
  rdoConfLabelPtr->MoveResize(10, 130, 30, 20);

  fReadoutConfigMenuPtr->AddFrame(fReadoutModeInpuPtr, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  fReadoutModeInpuPtr->MoveResize(45,130, 140 ,20);
  fReadoutConfigMenuPtr->MapSubwindows();  


  fReadoutConfigPtr = new ReadoutConfig_t(); 
  ConnectSignalAndSlots();
  EmitReadoutConfigChangedSignal( fReadoutConfigPtr); 

}



ElectronicsMenuReadout::~ElectronicsMenuReadout()
{

}


void 
ElectronicsMenuReadout::ConnectSignalAndSlots()
{
  fStartZInputPtr->Connect("ValueChanged(Long_t)",      "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)");
  fEndZInputPtr->Connect("ValueChanged(Long_t)",        "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)");  
  fStartXInputPtr->Connect("ValueChanged(Long_t)",      "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)");
  fEndXInputPtr->Connect("ValueChanged(Long_t)",        "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)");    
  fNSamplesInputPtr->Connect("ValueChanged(Long_t)",    "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)");  
  fNPreSamplesInputPtr->Connect("ValueChanged(Long_t)", "ElectronicsMenuReadout", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)"); 
  fReadoutModeInpuPtr->Connect("Selected(Int_t)",       "ElectronicsMenuReadout", this, "HandleReadoutModeChanged(Int_t)");
 
  fUserData.Connect("EmitPatternChangedSignal(const Pattern_t*)", "ElectronicsMenuReadout", this, "HandlePatternChanged(const Pattern_t*)" );
  fUserData.Connect("HandleOKApply()",     "ElectronicsMenuReadout",  this,  "HandleApply()");
  fUserData.Connect("HandleOKDontApply()", "ElectronicsMenuReadout",  this,  "HandleDontApply()");

}
 

void 
ElectronicsMenuReadout::HandleApply()
{
  fReadoutConfigPtr->SetApplyPattern(true); 
  EmitReadoutConfigChangedSignal( fReadoutConfigPtr);  
}


void 
ElectronicsMenuReadout::HandleDontApply()
{
  fReadoutConfigPtr->SetApplyPattern(false);
  EmitReadoutConfigChangedSignal( fReadoutConfigPtr);  
}


void 
ElectronicsMenuReadout::HandlePatternChanged(const Pattern_t *pattern)
{
  if(pattern !=0)
    {
      fReadoutConfigPtr->SetPattern(*pattern);

    }

  EmitReadoutConfigChangedSignal(fReadoutConfigPtr);  
  
}



void 
ElectronicsMenuReadout::EmitReadoutConfigChangedSignal(const ReadoutConfig_t *rdoConfig)  //*SIGNAL*
{
  StartZ_t  tmpStartZ; 
  EndZ_t    tmpEndZ;
  StartX_t  tmpStartX; 
  EndX_t    tmpEndX;
  tmpStartZ.SetIntValue(fStartZInputPtr->GetIntNumber());  
  tmpEndZ.SetIntValue(fEndZInputPtr->GetIntNumber());  
  tmpStartX.SetIntValue(fStartXInputPtr->GetIntNumber());  
  tmpEndX.SetIntValue(fEndXInputPtr->GetIntNumber()); 
  ReadoutRegion_t  *tmpReadoutRegionPtr = new ReadoutRegion_t(tmpStartZ, tmpEndZ, tmpStartX, tmpEndX);
  fReadoutConfigPtr->SetReadoutRegion(*tmpReadoutRegionPtr);
  NSamples_t tmpNSamples = fNSamplesInputPtr->GetIntNumber();  
  NPreSamples_t tmpNPreSamples = fNPreSamplesInputPtr->GetIntNumber(); 
  const int tmp = fReadoutModeInpuPtr->GetSelected();  
  ReadoutMode_t tmpRdomode;
  Pattern_t tmpPattern = fReadoutConfigPtr->GetAltroConfig().GetPattern();
  bool tmpApply =  fReadoutConfigPtr->GetAltroConfig().GetApplyPattern();

  tmpRdomode = fReadoutConfigPtr->GetAltroConfig().GetReadoutMode(); 
  AltroConfig_t *tmpAltroConfigPtr = new  AltroConfig_t(tmpNSamples, tmpNPreSamples, tmpRdomode);
  tmpAltroConfigPtr->SetPattern(tmpPattern);
  tmpAltroConfigPtr->SetApplyPattern(tmpApply);
  fReadoutConfigPtr->SetAltroConfig(*tmpAltroConfigPtr);
  Emit("EmitReadoutConfigChangedSignal(ReadoutConfig_t*)", (Long_t)fReadoutConfigPtr);
 
  delete tmpReadoutRegionPtr;
  delete tmpAltroConfigPtr;
}


void 
ElectronicsMenuReadout::HandleReadoutModeChanged(Int_t t)
{
  ReadoutMode_t tmpRdomode; 
  
  if(t == 0)
    {
      tmpRdomode.SetIntValue(0);
    }
  if(t == 1)
    {
      tmpRdomode.SetIntValue(0xa);
      fReadoutConfigPtr->SetReadoutMode(tmpRdomode);
      fUserData.GetPatternFromUser(); 
    }
  EmitReadoutConfigChangedSignal(fReadoutConfigPtr); 
};
