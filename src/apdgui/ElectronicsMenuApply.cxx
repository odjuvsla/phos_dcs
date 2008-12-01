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

#include "ElectronicsMenuApply.h"
#include "PhosDataTypes.h"
#include "TGFrame.h"
#include "PhosMenuButton.h" 

using namespace std;


ClassImp(ElectronicsMenuApply)


ElectronicsMenuApply::ElectronicsMenuApply(const  TGGroupFrame *frame, const int X, const int Y, const int W, const int H)
{
  fApplyApdMenuPtr = new TGGroupFrame(frame, "Apply APD settings");
  fApplyApdMenuPtr->MoveResize(   X,  Y,  W, H);
  fApplyFeeButtPtr  = new PhosMenuButton(fApplyApdMenuPtr, "Apply to FEE");
  fApplyFeeButtPtr->MoveResize(   20,  20,  150, 20);
  fApplyRcuButtPtr  = new PhosMenuButton(fApplyApdMenuPtr, "Apply to RCU");
  fApplyRcuButtPtr->MoveResize(   20,  45,  150, 20);
  fApplyModuleButtPtr  = new PhosMenuButton(fApplyApdMenuPtr, "Apply to Module");
  fApplyModuleButtPtr->MoveResize(20,  70, 150, 20);
  fApplyApdMenuPtr->MapSubwindows(); 
}


ElectronicsMenuApply::ElectronicsMenuApply()
{

}

ElectronicsMenuApply::~ElectronicsMenuApply()
{

}

