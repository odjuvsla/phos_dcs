#ifndef SANDBOXMENU_H
#define SANDBOXMENU_H

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

class PhosMenuButton;
class PhosNumberEntry;
class TGNumberEntry;
class TGMainFrame;
class TGGroupFrame;

#include "RQ_OBJECT.h"

class SandboxMenu
{
  RQ_OBJECT("SandboxMenu") 

 public:
  ~SandboxMenu();
  SandboxMenu(const TGMainFrame *framePtr, const int X, const int Y, const int W, const int H); 

  void EmitSetAllApdFeeSignal(Int_t value);
  void EmitSetAllApdRcuSignal(Int_t value); 
  void EmitSetAllApdModuleSignal(Int_t value);
  
 private:
  SandboxMenu();
  TGGroupFrame    *sandboxMenuPtr;

  PhosMenuButton  *setFeeAllButtPtr;
  PhosMenuButton  *setRcuAllButtPtr;
  PhosMenuButton  *setModuleAllButtPtr;

  TGNumberEntry   *apdValFeeInputPtr;
  TGNumberEntry   *apdValRcuInputPtr;
  TGNumberEntry   *apdValModuleInputPtr;

  ClassDef(SandboxMenu, 1)
};


#endif
