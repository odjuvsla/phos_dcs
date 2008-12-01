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

#include "FeeCardOnOffButton.h"
#include "PhosConst.h"
#include <TGFrame.h>

using namespace PhosConst;

ClassImp(FeeCardOnOffButton)

FeeCardOnOffButton::FeeCardOnOffButton() :  fBranch(-1),
					      fCardId(-1),
					      fState(0)
{
  
}


FeeCardOnOffButton::FeeCardOnOffButton(TGGroupFrame *gfPtr, const int branch, const int card)  : TGTextButton(gfPtr,""), 
												 fBranch(branch),
												 fCardId(card),
												 fState(0)
{

}


void
FeeCardOnOffButton::EmitOnOffSignal(Int_t branch, Int_t card, Int_t state)   //*SIGNAL*
{
  long args[3];
  args[0] = fBranch;
  args[1] = fCardId;
  args[2] = fState;
  Emit("EmitOnOffSignal(Int_t, Int_t, Int_t)",  args);
}


void
FeeCardOnOffButton::SetState(unsigned int state)
{
  fState = state;

  if(state == FEE_STATE_OFF)
    {
      SetBackgroundColor(OFF_COLOR);
    }
  else if(state == FEE_STATE_ON)
    {
      SetBackgroundColor(ON_COLOR);  
    }
  else if(state == DCS_NOT_MASTER)
    {
      SetBackgroundColor(ERROR_COLOR);  
    }
  else if(state == FEE_STATE_ERROR)
    {
      SetBackgroundColor(ERROR_COLOR);  	
    }
  else if(state ==  FEE_STATE_UNKNOWN)
    {
      SetBackgroundColor(UNKNOWN_COLOR);   
    }
  else if(state == FEE_STATE_WARNING)
    {
      SetBackgroundColor(WARNING_COLOR);
    }
  else
    {
      SetBackgroundColor(UNKNOWN_COLOR); 
    }

  DoRedraw();
}


Bool_t
FeeCardOnOffButton::HandleButton(Event_t* event)
{
  if(event->fType == kButtonPress) 
    {
      EmitOnOffSignal(fBranch, fCardId, fState);
    }
}

