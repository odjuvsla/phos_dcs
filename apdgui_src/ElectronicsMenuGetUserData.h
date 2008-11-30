#ifndef ELECTRONICSMENUGETUSERDATA_H
#define ELECTRONICSMENUGETUSERDATA_H


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
#include "TGComboBox.h"
#include "TBrowser.h"
//#include "PhosMenuButton.h"

class  PhosMenuButton;
class  PhosNumberEntry;

class ElectronicsMenuGetUserData
{
  RQ_OBJECT("ElectronicsMenuGetUserData") 
    
 public:
  ElectronicsMenuGetUserData();  
  ~ElectronicsMenuGetUserData(); 
  void DrawPatterntypeCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H);
  void DrawAmplitudeCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H);
  void DrawStepCombo(TGTransientFrame *t, const int X, const int Y, const int W, const int H);
  void DrawButtons(TGTransientFrame *t, const int X, const int Y, const int W, const int H);
  void ConnectSignalAndSlots();
  void GetPatternFromUser();
  void HandleSelectPatternType(Int_t t);
  void HandleSelectAmplitude(Int_t t);
  void HandleSelectStepSize(Int_t t);
  void HandleOKApply();
  void HandleOKDontApply();
  void EmitPatternChangedSignal(const Pattern_t *pattern);
  TGTransientFrame *fPatternInputFramePtr;
  TGComboBox *fPatternTypeComboPtr;
  TGComboBox *fAmplitudeComboPtr;
  TGComboBox *fStepComboPtr;
  PhosNumberEntry *fStepSizeInputPtr;
  PhosNumberEntry *fMaxAmplitudeInputPtr;
  PhosMenuButton   *fOKApplyPtr;
  PhosMenuButton   *fOKDontApplyPtr;
  Pattern_t    *fPatternPtr;
  ClassDef(ElectronicsMenuGetUserData, 1)
};

#endif
