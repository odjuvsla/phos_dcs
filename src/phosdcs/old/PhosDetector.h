#ifndef PHOSDETECTOR_H
#define PHOSDETECTOR_H

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

#include "CommonDefs.h"
#include "PhosModule.h"
#include "PhosFeeClient.h"

class PhosDetector
{
 public:
  PhosDetector();
  ~PhosDetector();
  static PhosDetector* GetInstance();

  // --- System
  PhosFeeClient *feeClientPtr;

  // --- Action to PhosModule/Rcu/Fee
  void ArmTrigger();
  void ArmTrigger(int moduleId);
  void LoadApdValues();
  void SetAllApds(int value);
  PhosModule* GetPhosModule(int imod){ return phosModulePtr[imod]; }

  // --- Basic Information
  void SetNSamples(int n);  
  void SetNPreSamples(int n);
  void SetL2TriggerDelay(int n);

 private:
  static PhosDetector* _instance;
  
  // --- To PhosModule/Rcu/Fee
  PhosModule *phosModulePtr[PHOS_MODS];

  // --- Basic Information
  int nSamples;
  int nPreSamples;
  int triggerDelay;
  int triggerType;
};

#endif


