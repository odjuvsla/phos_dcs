#ifndef ELECTRONICSMENUREADOUT_H
#define ELECTRONICSMENUREADOUT_H

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
#include "PhosDataTypes.h"
#include "TGFrame.h"

#include "ElectronicsMenuGetUserData.h"

class PhosNumberEntry;
class PhosMenuButton;
class TGComboBox;

class ElectronicsMenuReadout
{
  RQ_OBJECT("ElectronicsMenuReadout") 

 public:
  ElectronicsMenuReadout();
  ElectronicsMenuReadout(const TGGroupFrame *frame, const ReadoutConfig_t rdoconf, 
			 const int X, const int Y, const int W, const int H);  
  ~ElectronicsMenuReadout();
  void EmitReadoutConfigChangedSignal(const ReadoutConfig_t *rdoConfig = 0);
  
  void HandlePatternChanged(const Pattern_t *pattern = 0);
  void HandleApply();
  void HandleDontApply();
  void HandleReadoutModeChanged(Int_t t);

  void ConnectSignalAndSlots(); 

  TGGroupFrame     *fReadoutConfigMenuPtr;
  PhosMenuButton   *fSaveButtPtr;
  PhosNumberEntry  *fStartZInputPtr;
  PhosNumberEntry  *fEndZInputPtr;
  PhosNumberEntry  *fStartXInputPtr;
  PhosNumberEntry  *fEndXInputPtr;
  PhosNumberEntry  *fNSamplesInputPtr;
  PhosNumberEntry  *fNPreSamplesInputPtr;
  TGComboBox       *fReadoutModeInpuPtr;
  ReadoutConfig_t  *fReadoutConfigPtr; 
  ElectronicsMenuGetUserData fUserData;
 
  bool fApplyPattern;

  ClassDef(ElectronicsMenuReadout, 1)

};

#endif
