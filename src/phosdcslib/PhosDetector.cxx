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

#include "PhosDetector.h"
#include "PhosModule.h"
#include "PhosFeeClient.h"
#include "ScriptCompiler.h"
#include "PhosDcsBase.h"
#include "Rcu.h"
#include "PhosDcsLogging.h"


PhosDetector::PhosDetector() : PhosDcsBase(), 
			       fFeeClientPtr(0),
			       fReadoutConfig() 
{
  fFeeClientPtr = new PhosFeeClient();
  for(int i=0; i<PHOS_MODS; i++)
    {
      phosModulePtr[i]=new PhosModule(fFeeClientPtr, i);
    }
}


PhosDetector::~PhosDetector()
{

}


PhosDetector::PhosDetector(PhosDetector const&): PhosDcsBase(), 
						 fFeeClientPtr(0), 
						 fReadoutConfig()  
{

}


void 
PhosDetector::ApplyApdSettings(const int modID, const int rcuId, const int branch, const int card) const
{
  phosModulePtr[modID]->ApplyApdSettings(rcuId, branch, card);
}


void 
PhosDetector::DisArmTrigger(const int modId, const int  rcuId) const
{
  phosModulePtr[modId]->DisArmTrigger(rcuId);
  stringstream log;
  log << "PhosDetector::DisArmTrigger: Disarming trigger for " << phosModulePtr[modId]->GetFeeServerName(rcuId);
  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
}

                                 
const int
PhosDetector::ArmTrigger() const
{
  int iRet = 1;
  ScriptCompiler::MakeTriggerConfigScript("s_triggerconfig.txt", fReadoutConfig.GetTriggerMode(),  fReadoutConfig.GetAltroConfig());

  for(int i=0; i<PHOS_MODS; i++)
    {
      int t = phosModulePtr[i]->ArmTrigger("s_triggerconfig.txt");
      if( t<0 )
	{
	  iRet = -1;
	}
    }
  return iRet;
}


const int
PhosDetector::ArmTrigger(const int moduleId) const
{
  ScriptCompiler::MakeTriggerConfigScript("s_triggerconfig.txt",fReadoutConfig.GetTriggerMode(), fReadoutConfig.GetAltroConfig());
  phosModulePtr[moduleId]->ArmTrigger("s_triggerconfig.txt");
}


void 
PhosDetector::SetReadoutConfig(const ModNumber_t modID,  const ReadoutConfig_t rdoConfig) 
{
  phosModulePtr[modID.GetIntValue()]->SetReadoutConfig(rdoConfig);
  fReadoutConfig = rdoConfig; 
}

void
PhosDetector::SetReadoutSettings(const ModNumber_t modId, const ReadoutSettings_t rdoSettings)
{
  phosModulePtr[modId.GetIntValue()]->SetReadoutSettings(rdoSettings);
}

void
PhosDetector::SetReadoutRegion(const ModNumber_t modId, const ReadoutRegion_t rdoRegion) 
{
  fReadoutRegion = rdoRegion;
  phosModulePtr[modId.GetIntValue()]->SetReadoutRegion(rdoRegion);
}

int
PhosDetector::ApplyReadoutRegisters(const ModNumber_t modID, const ReadoutRegisters_t readoutRegisters)
{
  int res = phosModulePtr[modID.GetIntValue()]->ApplyReadoutRegisters(readoutRegisters);
  fReadoutRegisters = readoutRegisters;
  return res;
}

int
PhosDetector::ApplyReadoutRegisters(const ModNumber_t modID) const
{
  int res = phosModulePtr[modID.GetIntValue()]->ApplyReadoutRegisters();
  return res;
}

int
PhosDetector::ApplyReadoutRegion(const ModNumber_t modID) const
{
  int res = phosModulePtr[modID.GetIntValue()]->ApplyReadoutRegion(fReadoutRegion);
  return res;
}

int
PhosDetector::StartFeeClient(const ModNumber_t modID) const
{
  //  phosModulePtr[modID.GetIntValue()]->StartFeeClient();
  return 10; //TODO: fix this value (whatever it should be...)
}

int
PhosDetector::StopFeeClient() const
{
  return fFeeClientPtr->stopFeeClient();
}

void
PhosDetector::SetPhosBit(const int moduleId) const
{
  char tmpFileName[1024];
  //  sprintf(tmpFileName, "%s/s_setphosbit.txt", fPhosDcsScriptDir);
  sprintf(tmpFileName, "s_setphosbit.txt");

  phosModulePtr[moduleId]->ExecuteScript(tmpFileName);
}


Rcu*
PhosDetector::GetRcuPtr(const int module, const int rcu) const
{
  return phosModulePtr[module]->GetRcuPtr(rcu);
}


PhosFeeClient*
PhosDetector::GetFeeClientPointer() const
{
  return  fFeeClientPtr;
}


PhosModule*
PhosDetector::GetModulePtr(const int i) const
{
  return phosModulePtr[i]; 
}


void
PhosDetector::LoadApdValues()
{
  for(int i = 0; i<PHOS_MODS; i++)
    {
      phosModulePtr[i]->LoadApdValues();
    }
}


void
PhosDetector::SetAllApds(const int Value)
{
  for(int i = 0; i<PHOS_MODS; i++)
    {
      phosModulePtr[i]->SetAllApds(Value);
    }
}

int  
PhosDetector::Reset(const ModNumber_t modId)
{
  phosModulePtr[modId.GetIntValue()]->Reset();
  int res = 0;
  return res;
}
