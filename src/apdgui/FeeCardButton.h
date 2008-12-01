#ifndef FEECARDBUTTON_H
#define FEECARDBUTTON_H

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

class FeeCardButton : public TGTextButton
{
  RQ_OBJECT("FeeCardButton")
 
 public:
  FeeCardButton(TGGroupFrame *gfPtr, const char *buttName, const int branch, const int card);
  virtual bool HandleButton(Event_t* event);
  void EmitFeeCardClickedSignal(Int_t branch = 999, Int_t card = 999);
  void RedrawCard();
  const int GeBranch(){return fBranch; };
  const int GetCard() {return fCardId; };

 private:
  FeeCardButton();
  const Int_t fBranch;
  const Int_t fCardId;

  ClassDef(FeeCardButton, 1)
};

#endif
