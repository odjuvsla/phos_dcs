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

#include "ElectronicsMenu.h"
#include "PhosMenuButton.h" 
#include "PhosNumberEntry.h"
#include <TGFrame.h>
#include <TGLabel.h>
#include <iostream>
#include "PhosDataTypes.h"
//#include "TGGroupFrame.h"
#include "ElectronicsMenuApply.h"
#include "ElectronicsMenuRCU.h"
#include "ElectronicsMenuReadout.h"

using namespace std;

ClassImp(ElectronicsMenu)


ElectronicsMenu::ElectronicsMenu()
{

}

ElectronicsMenu::~ElectronicsMenu()
{

}


ElectronicsMenu::ElectronicsMenu(const TGMainFrame *mainFrame, 
				 const ReadoutConfig_t rdoconf, 
				 const int X, const int Y, 
				 const int W, const int H) : fElectronicsMenuPtr(0),
							     fReadoutConfigPtr(0)
{
  fElectronicsMenuPtr=new TGGroupFrame(mainFrame ,"Electronics Configuration"); 
  fElectronicsMenuPtr->MoveResize(X, Y,  W, H); 
  fApply = new ElectronicsMenuApply(fElectronicsMenuPtr, 20,  20,  190, 110 );
  fRCU = new ElectronicsMenuRCU(fElectronicsMenuPtr,  20,  130,  190, 130);
  fReadout = new ElectronicsMenuReadout(fElectronicsMenuPtr, rdoconf, 20,  270,  190, 170);
  fElectronicsMenuPtr->MapSubwindows();
}



void
ElectronicsMenu::DrawReadoutConfigMenu(TGGroupFrame *frame, const ReadoutConfig_t rdoconf)
{
  cout << "ElectronicsMenu::DrawReadoutConfigMenu  &rdoconf = "<<   &rdoconf  << endl;


  if( &rdoconf == 0)
    {
      cout << "ElectronicsMenu::DrawReadoutConfigMenu: ERROR" << endl;
    }
  else
    {
      fReadout = new ElectronicsMenuReadout(frame,rdoconf,20, 270, 190, 170);
    }
}

