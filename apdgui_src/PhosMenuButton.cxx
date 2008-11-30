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

#include "PhosMenuButton.h"
#include "TGFrame.h"

ClassImp(PhosMenuButton)

PhosMenuButton::PhosMenuButton()
{
  // never called
}


PhosMenuButton::PhosMenuButton(TGGroupFrame *gfPtr, char *name)
  : TGTextButton(gfPtr, name)
{

}


PhosMenuButton::PhosMenuButton(TGMainFrame *framePtr, char *name)
 : TGTextButton(framePtr, name)
{

}


Bool_t
PhosMenuButton::HandleButton(Event_t* event)   //*SIGNAL*
{
  AllowStayDown(kFALSE);

  if(event->fType == kButtonPress) 
    {
      AllowStayDown(kFALSE);
      Emit("HandleButton(Event_t*)", event);
    }
}



