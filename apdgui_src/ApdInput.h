#ifndef APDINPUT_H
#define APDINPUT_H

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

#include <TGFrame.h>
#include "PhosConst.h"

using namespace PhosConst;

class MainGui;
class TGMainFrame; 
class TGNumberEntry;
class TGLabel;

class ApdInput : public TGGroupFrame
{
 public:
  ApdInput(TGMainFrame *fPtr);
  virtual ~ApdInput();
  void GetApdValues(unsigned long *apdvalues);
  void SetApdValues(int values[CSPS_PER_FEE]);
  void ResetApdValues();
  void DrawInput();
  void DrawLabels(const int rcu, const  int branch, const int card);

 private:
  ApdInput();
  TGMainFrame *fFramePtr; //pointer to frame to draw entries
  TGLabel  *fRowLabelPtr[16];
  TGLabel  *fColumnLabelPtr[2];
  TGNumberEntry *fApdEntryPtr[CSPS_PER_FEE];
 };

#endif
