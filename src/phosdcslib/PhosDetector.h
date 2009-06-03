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

#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
#include "PhosRegisters.h"

class PhosModule;
class Rcu;
class ScriptCompiler;
class PhosFeeClient;


class PhosDetector : public PhosDcsBase
{
 public:
  PhosDetector();
  ~PhosDetector();
  PhosModule *phosModulePtr[PHOS_MODS];
  PhosFeeClient* GetFeeClientPointer() const;
  PhosModule* GetModulePtr(const int i) const; 
  Rcu*  GetRcuPtr(const int modId, const int rcuId) const;
  void DisArmTrigger(const int modId, const int rcuId) const;
  void SetPhosBit(const int modId) const; 
  int StartFeeClient() const; 
  int StopFeeClient() const; 
  const int ArmTrigger() const;
  const int ArmTrigger(const int moduleId) const;
  void LoadApdValues();
  void SetAllApds(const int value);
  void SetReadoutConfig(const ModNumber_t modID, const ReadoutConfig_t rdoConfig);
  void SetReadoutSettings(const ModNumber_t modId, const ReadoutSettings_t rdoSettings);
  void SetReadoutRegion(const ModNumber_t modId, const ReadoutRegion_t rdoRegion) const;
  int  ApplyReadoutRegisters(const ModNumber_t modID, ReadoutRegisters_t readoutRegisters); 
  int  ApplyReadoutRegion(const ModNumber_t modID) const;
  void ApplyApdSettings(const int modID, const int rcuId, const int branch, const int card) const;
  PhosFeeClient *fFeeClientPtr;
  int             Reset(const ModNumber_t modId);

 private:
  PhosDetector(const PhosDetector & );
  PhosDetector & operator = (const PhosDetector &){return *this;}
  ReadoutConfig_t fRadoutConfig; 
  ReadoutRegisters_t fReadoutRegisters;
  ReadoutRegion_t fReadoutRegion;
};

#endif


