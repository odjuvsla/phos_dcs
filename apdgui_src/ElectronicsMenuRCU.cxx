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

#include "ElectronicsMenuRCU.h"
#include "PhosMenuButton.h" 
#include "PhosNumberEntry.h"
#include <TGFrame.h>
#include <TGLabel.h>
#include <iostream>
#include "PhosDataTypes.h"
//#include "TGGroupFrame.h"

using namespace std;

ClassImp(ElectronicsMenuRCU)


ElectronicsMenuRCU::ElectronicsMenuRCU()
{

}

ElectronicsMenuRCU::~ElectronicsMenuRCU()
{

}


ElectronicsMenuRCU::ElectronicsMenuRCU(const  TGGroupFrame *frame, 
				       const int X, const int Y, 
				       const int W, const int H)

{
  fRcuMenuPtr = new TGGroupFrame(frame, "RCU");
  fRcuMenuPtr->MoveResize(  X,  Y,  W, H);
  fArmTriggerButtPtr = new PhosMenuButton(fRcuMenuPtr, "Arm Trigger");
  fArmTriggerButtPtr->MoveResize(20, 45, 150, 20);
  fEnableTriggerButtPtr = new PhosMenuButton(fRcuMenuPtr, "External");
  fEnableTriggerButtPtr->MoveResize(20, 70, 70, 20);
  fEnableTrigger_ttcrx_ButtPtr = new PhosMenuButton(fRcuMenuPtr, "TTCrx");
  fEnableTrigger_ttcrx_ButtPtr->MoveResize(100, 70, 70, 20);
  fDisarmTriggerButtPtr = new PhosMenuButton(fRcuMenuPtr, "Disarm Trigger");
  fDisarmTriggerButtPtr->MoveResize(20, 95, 150, 20);
  fRcuMenuPtr->MapSubwindows();
}


