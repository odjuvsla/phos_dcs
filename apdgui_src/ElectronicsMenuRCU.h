#ifndef ELECTRONICSMENURCU_H
#define ELECTRONICSMENURCU_H

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
#include "TGFrame.h"
#include "TGComboBox.h"  

#include "PhosDataTypes.h"

class PhosMenuButton;


class ElectronicsMenuRCU
{
  RQ_OBJECT("ElectronicsMenuRCU") 

 public:
  ElectronicsMenuRCU();
  ElectronicsMenuRCU(const  TGGroupFrame *frame, 
		     const int X, const int Y, const int W, const int H);  

  ~ElectronicsMenuRCU();
 
  TGGroupFrame     *fRcuMenuPtr;
  PhosMenuButton   *fArmTriggerButtPtr;  
  PhosMenuButton   *fEnableTriggerButtPtr;
  PhosMenuButton   *fEnableTrigger_ttcrx_ButtPtr;
  PhosMenuButton   *fDisarmTriggerButtPtr; 

  ClassDef(ElectronicsMenuRCU, 1)

};

#endif
