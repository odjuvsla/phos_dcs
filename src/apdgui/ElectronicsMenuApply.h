#ifndef ELECTRONICSMENUAPPLY_H
#define ELECTRONICSMENUAPPLY_H

//#define ELECTRONICSMENUAPPLY_H

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
//#include "PhosMenuButton.h"
//#include "TGFrame.h"

class TGGroupFrame;
class PhosMenuButton;

class ElectronicsMenuApply
{
  RQ_OBJECT("ElectronicsMenuApply") 

 public:
  ~ElectronicsMenuApply();
  ElectronicsMenuApply();

  ElectronicsMenuApply(const  TGGroupFrame *frame,
		       const int X, const int Y, const int W, const int H);

  TGGroupFrame     *fApplyApdMenuPtr;
  PhosMenuButton   *fApplyFeeButtPtr;
  PhosMenuButton   *fApplyRcuButtPtr;
  PhosMenuButton   *fApplyModuleButtPtr;

  ClassDef(ElectronicsMenuApply, 1)
};


#endif
