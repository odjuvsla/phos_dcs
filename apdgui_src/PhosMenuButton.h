#ifndef PHOSMENUBUTTON_H
#define PHOSMENUBUTTON_H

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

#include <TGButton.h>
#include "RQ_OBJECT.h"

class  TGGroupFrame;
class  TGMainFrame;

class PhosMenuButton: public TGTextButton
{
  RQ_OBJECT("PhosMenuButton") 

public:
  PhosMenuButton(TGGroupFrame *gfPtr, char *name);
  PhosMenuButton(TGMainFrame *framePtr, char *name);
  virtual Bool_t HandleButton(Event_t* event);

 private:
  PhosMenuButton();
  ClassDef(PhosMenuButton, 1)
};
#endif
