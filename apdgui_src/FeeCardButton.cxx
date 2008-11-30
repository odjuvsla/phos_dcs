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
#include "FeeCardButton.h"
#include "PhosConst.h"
#include <TGFrame.h>

using namespace PhosConst;

ClassImp(FeeCardButton)


FeeCardButton::FeeCardButton() : fBranch(-1),
				 fCardId(-1)
{

}


FeeCardButton::FeeCardButton(TGGroupFrame *gfPtr, const char *buttName, const int branch, const int card) : TGTextButton(gfPtr,buttName),  
													    fBranch(branch),
													    fCardId(card)
{
  SetBackgroundColor(UNKNOWN_COLOR);
  AllowStayDown(kFALSE);
}


Bool_t
FeeCardButton::HandleButton(Event_t* event)  //*SIGNAL*
{
  if(event->fType == kButtonPress) 
    {
      EmitFeeCardClickedSignal();
    }
}


void 
FeeCardButton::RedrawCard()
{
  DoRedraw();
}


void
FeeCardButton::EmitFeeCardClickedSignal(Int_t branch, Int_t card)   //*SIGNAL*
{
  long args[2];
  args[0] = fBranch;
  args[1] = fCardId; 
  Emit("EmitFeeCardClickedSignal(Int_t , Int_t )",  args);
}




