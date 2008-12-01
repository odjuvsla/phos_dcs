#ifndef FEECARDONOFFBUTTON_H
#define FEECARDONOFFBUTTON_H

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
#include "RQ_OBJECT.h"
#include <TGButton.h>

class TGGroupFrame;

class FeeCardOnOffButton : public TGTextButton
{
  RQ_OBJECT("FeeCardOnOffButton")

 public:
  FeeCardOnOffButton(TGGroupFrame *gfPtr, const int branch, const int card); 
  void SetState(unsigned int state);
  virtual Bool_t HandleButton(Event_t* event);
  void EmitOnOffSignal(Int_t branch, Int_t card, Int_t state);
  const int GetBranch() { return fBranch; };
  const int GetCard()  { return fCardId; };
 private:
  FeeCardOnOffButton();
  unsigned int fState;
  const int fBranch;
  const int fCardId;

  ClassDef(FeeCardOnOffButton, 1)

};

#endif
