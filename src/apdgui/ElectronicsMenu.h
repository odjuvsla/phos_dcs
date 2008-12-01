#ifndef ELECTRONICSMENU_H
#define ELECTRONICSMENU_H

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
//#include <TGFrame.h> 
#include "TGComboBox.h"  


class TGGroupFrame;
class TGLabel; 
class TGMainFrame;  
class PhosNumberEntry;
class PhosMenuButton;
class PhosNumberEntry;
class ElectronicsMenuApply;
class ElectronicsMenuRCU;
class ElectronicsMenuReadout;

#include "PhosDataTypes.h"

class ElectronicsMenu
{
  RQ_OBJECT("ElectronicsMenu") 

 public:
  ~ElectronicsMenu();
  ElectronicsMenu(const TGMainFrame *mainFrame, const ReadoutConfig_t rdoconf, 
		  const int X, const int Y, const int W, const int H);  

  void DrawReadoutConfigMenu( TGGroupFrame *frame, const ReadoutConfig_t rdoconf);
  // private:
  ElectronicsMenu();

  TGGroupFrame     *fElectronicsMenuPtr; 
  ReadoutConfig_t  *fReadoutConfigPtr;  

  ElectronicsMenuApply *fApply;
  ElectronicsMenuRCU   *fRCU;
  ElectronicsMenuReadout   *fReadout;

  ClassDef(ElectronicsMenu, 1)
};

#endif
