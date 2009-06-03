/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
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

#include "DcsInterface.h"
#include "PhosDetector.h"
#include "PhosModule.h"
#include "DatabaseDummy.h"
#include "Rcu.h"
#include "FeeCard.h"
#include "PhosDataTypes.h"
#include <vector>
#include "PhosDcsLogging.h"

//DcsInterface::DcsInterface() : PhosDcsBase()
DcsInterface::DcsInterface()
{
  fPhosDetectorPtr = new PhosDetector();

//  fDatabasePtr = new DatabaseDummy();

}



DcsInterface::~DcsInterface()
{

}

int DcsInterface::Init(vector<FeeServer> feeServers)
{
  
  vector<FeeServer>::iterator server;
  
  int ret = 0;
  PhosModule* tmpPhosModulePtr = 0;
  stringstream log;

  server = feeServers.begin();
  while(server != feeServers.end())
    {
      tmpPhosModulePtr = fPhosDetectorPtr->GetModulePtr((*server).fModId);
      log.str("");
      log << "DcsInterface::Init: Adding FeeServer with name: " << (*server).fName <<  
	". For Module #: " << (*server).fModId << " and RCU ID: " << (*server).fRcuId << 
	". Coord: x = " << (*server).fX << ", z = " << (*server).fZ;
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
      tmpPhosModulePtr->CreateRcu((*server).fName.c_str(), (*server).fModId, (*server).fRcuId, (*server).fZ, (*server).fX);
      server++;
    }
  
  ret = fPhosDetectorPtr->StartFeeClient();
  log.str("");
  log << "DcsInterface::Init: StartFeeClient() returned: " << ret;
  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERY_VERBOSE);

  if(ret > 0) 
    {
      PhosDcsLogging::Instance()->Logging("FEE Client successfully started.", LOG_LEVEL_INFO);
      server = feeServers.begin();
      while(server != feeServers.end())
	{
	  log.str("");
	  log << (*server).fName << "Module #: " << (*server).fModId 
	      << " and RCU ID: " << (*server).fRcuId << ". Coord: x = " 
	      << (*server).fX << ", z = " << (*server).fZ;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);
	  DisArmTrigger((*server).fModId, (*server).fRcuId);
	  server++;
	}
    }
  else if(ret == 0)
    {
      log.str("");
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
      server = feeServers.begin();
      while(server != feeServers.end())
	{
	  log.str("");
	  log << (*server).fName << "Module #: " << (*server).fModId 
	      << " and RCU ID: " << (*server).fRcuId << ". Coord: x = " 
	      << (*server).fX << ", z = " << (*server).fZ;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
	  server++;
	}
      PhosDcsLogging::Instance()->Logging("No services available", LOG_LEVEL_INFO);
      fPhosDetectorPtr->StopFeeClient();
    }
  else if(ret < -1)
    {
      log.str("");
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
      server = feeServers.begin();
      while(server != feeServers.end())
	{
	  log.str("");
	  log << (*server).fName << "Module #: " << (*server).fModId 
	      << " and RCU ID: " << (*server).fRcuId << ". Coord: x = " 
	      << (*server).fX << ", z = " << (*server).fZ;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
	  server++;
	}
      PhosDcsLogging::Instance()->Logging("FEE Client already running", LOG_LEVEL_INFO);
    }
  else
    {
      log.str("");
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
      server = feeServers.begin();
      while(server != feeServers.end())
	{
	  log.str("");
	  log << (*server).fName << "Module #: " << (*server).fModId 
	      << " and RCU ID: " << (*server).fRcuId << ". Coord: x = " 
	      << (*server).fX << ", z = " << (*server).fZ;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
	  server++;
	}
      PhosDcsLogging::Instance()->Logging("Strange, FEE Client is returning to small number of services", LOG_LEVEL_INFO);
      fPhosDetectorPtr->StopFeeClient();
    }
  fDatabasePtr = new DatabaseDummy();

  return ret;

}

int DcsInterface::DeInit()
{
  return fPhosDetectorPtr->StopFeeClient();
}

void 
DcsInterface::ApplyApdSettings(const int modID, const int rcuId, const int branch, const int card) const 
{
  fPhosDetectorPtr->ApplyApdSettings(modID, rcuId, branch, card);
}

void 
DcsInterface::ApplyTruSettings(int modID, int RcuID, unsigned long *regAddr, unsigned long *regVal, bool *verify, int nTruRegs)
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->rcuPtr[RcuID]->ApplyTruSettings(regAddr, regVal, verify, nTruRegs,  Mesbuf);
}


int 
DcsInterface::ArmTrigger(const int modID) const
{
  return fPhosDetectorPtr->ArmTrigger(modID);
}


unsigned int 
DcsInterface::CheckFeeState(const int mod,  const int rcu , const int branch , const int cardId)
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  return tmpRcuPtr->CheckFeeState(branch, cardId);
}


void 
DcsInterface::DisArmTrigger(const int modID, const int RcuID) const
{
  fPhosDetectorPtr->DisArmTrigger(modID, RcuID);
}


void 
DcsInterface::EnableTrigger(int modID)
{
  fPhosDetectorPtr->phosModulePtr[modID]->EnableTrigger();
}


void 
DcsInterface::EnableTrigger_ttcrx(int modID)
{
  fPhosDetectorPtr->phosModulePtr[modID]->EnableTrigger_ttcrx();
}


unsigned long*
DcsInterface::GetApdValues(const int mod, const int rcu, const int branch, const int cardId)
{
  FeeCard *tmpFeeCard  = GetFeeCard(mod,  rcu, branch, cardId);
  return tmpFeeCard->GetApdValues();
}


void
DcsInterface::GetConfigComment(char *text, const int id)
{
  fDatabasePtr->GetConfigComment(text, id);
}


FeeCard* 
DcsInterface::GetFeeCard(const int mod, const int rcu, const int branch, const int cardId) const
{
  int tmpFeeIndex = branch*CARDS_PER_BRANCH + cardId -1;

  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  FeeCard *tmpFeeCard = tmpRcuPtr->GetFeeCardPtr(tmpFeeIndex);
}


int
DcsInterface::GetLatestConfigId()
{
  return fDatabasePtr->GetLatestConfigId();
}


Rcu* 
DcsInterface::GetRcuPtr(int modID, int rcuID) const
{
  return fPhosDetectorPtr->GetRcuPtr(modID, rcuID);
}


void      
DcsInterface::LoadApdConfig(ConfigInfo_t *info) //Raed apd values from datbase and put them in sandbox directory
{
  fDatabasePtr->LoadApdConfig(info);
}


void      
DcsInterface::LoadApdConfig(ConfigInfo_t *info, int id) //Raed apd values from datbase and put them in sandbox directory
{
  fDatabasePtr->LoadApdConfig(info, id);
}

void 
DcsInterface::LoadApdValues(int modID)  //Load apd values into Feecard objects
{
  fPhosDetectorPtr->phosModulePtr[modID]->LoadApdValues();
}
 

void            
DcsInterface::LoadReadoutConfiguration(ReadoutConfig_t *rdoconfigPtr, ModNumber_t modNumber) const
{
  fDatabasePtr->LoadReadoutConfiguration(rdoconfigPtr, modNumber);
  rdoconfigPtr->PrintInfo("DcsInterface::LoadReadoutConfiguration ");
} 


void       
DcsInterface::SaveReadoutConfiguration(const ReadoutConfig_t rdoconfig, const ModNumber_t modNumber) const
{
  fDatabasePtr->SaveRadoutConfiguration(rdoconfig, modNumber);
}

void            
DcsInterface::LoadTruSettings(TRUSettings_t *trusettings) const
{
  fDatabasePtr->LoadTruSettings(trusettings);
}

int 
DcsInterface::SaveApdConfig(char *description)
{
  fDatabasePtr->SaveApdConfig(description); 
}


void            
DcsInterface::SaveTRUSettings(const TRUSettings_t trusettings)
{
  trusettings.PrintInfo("DcsInterface::SaveTRUSettings"); 
  fDatabasePtr->SaveTruSettings(trusettings);
}


void 
DcsInterface::SetAllApds(const int modID, const int apdValue)
{
  fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds(apdValue);
}


void 
DcsInterface::SetAllApds(const int modID, const int rcuId, const int apdValue)
{
  Rcu *tmpRcu =fPhosDetectorPtr->phosModulePtr[modID]->GetRcuPtr(rcuId);
  tmpRcu->SetAllApds(apdValue);
  //  fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds(apdValue);
}


void 
DcsInterface::SetAllApds(const int modID, const int rcuId, const int branch, const int card, const int apdValue)
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds(apdValue);
  FeeCard *tmpFeeCard;
  Rcu *tmpRcu =fPhosDetectorPtr->phosModulePtr[modID]->GetRcuPtr(rcuId);
  tmpFeeCard = tmpRcu->GetFeeCardPtr(branch*CARDS_PER_BRANCH + card-1);
  tmpFeeCard->SetAllApds(apdValue);
}


void 
DcsInterface::SetApdValues(const int mod, const int rcu, const int branch, const int cardId, const unsigned long *values)
{
  //cout <<"DcsInterface::SetApdValues; mod  =" << mod <<"  rcu = "<< rcu <<"  branch = "<< branch << "card = " <<  cardId <<endl;  
  FeeCard *tmpFeeCard  = GetFeeCard(mod,  rcu, branch, cardId);
  tmpFeeCard->SetApdValues(values);
}


void
DcsInterface::SetPhosBit(const int modId) const
{
  fPhosDetectorPtr->SetPhosBit(modId);
}


void 
DcsInterface::SetReadoutConfig(const ModNumber_t modID,  const ReadoutConfig_t rdoConfig)
{
  //  rdoConfig.PrintInfo("DcsInterface::SetReadoutConfig"); 
  fPhosDetectorPtr->SetReadoutConfig(modID,  rdoConfig);
}

void
DcsInterface::SetReadoutSettings(const ModNumber_t modId, const ReadoutSettings_t rdoSettings)
{
  // fPhosDetectorPtr->SetReadoutSettings(modId, rdoSettings);
  fReadoutSettings = rdoSettings;
}

void
DcsInterface::SetReadoutRegion(const ModNumber_t modId, const ReadoutRegion_t rdoRegion) const
{
 
  fPhosDetectorPtr->SetReadoutRegion(modId, rdoRegion);
}

int
DcsInterface::ApplyReadoutRegisters(const ModNumber_t modID, const ReadoutRegisters_t readoutRegisters) const
{

  return fPhosDetectorPtr->ApplyReadoutRegisters(modID, readoutRegisters);
}

int
DcsInterface::ApplyReadoutRegion(const ModNumber_t modID) const 
{
  return fPhosDetectorPtr->ApplyReadoutRegion(modID);
}

unsigned int
DcsInterface::TurnOnFee(const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpState)
{
  return fPhosDetectorPtr->GetRcuPtr(mod, rcu)->ActivateFee(branch, cardSlot);
}

unsigned int
DcsInterface::TurnOffFee(const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpState)
{
  return fPhosDetectorPtr->GetRcuPtr(mod, rcu)->DeActivateFee(branch, cardSlot);
}

unsigned int 
//DcsInterface::ToggleOnOffFee(const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate, unsigned int tmpStates[CARDS_PER_RCU])
DcsInterface::ToggleOnOffFee(const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate)
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  int state = tmpRcuPtr->ToggleFeeOnOff(branch, cardId);
  int **tmp = tmpRcuPtr->GetFeeStatus();

  for(int i=0; i < CARDS_PER_RCU; i++)
    {
      //      tmpStates[i] = *tmp[i];
    }
  return state;
}

unsigned int
DcsInterface::ToggleOnOffTru(const int mod, const int rcu, const int truId)

{  
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  int state = tmpRcuPtr->ToggleTruOnOff(truId);
  return state;
}

void 
DcsInterface::TurnOnAllFee(const int modID, const int rcuId) const
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(modID, rcuId); 
  tmpRcuPtr->TurnOnAllFee();
  char* tmp = 0;
 }


void 
DcsInterface::TurnOnAllTru(const int modID, const int rcuId) const
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOnAllTru(message);
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(modID, rcuId); 
  tmpRcuPtr->TurnOnAllTru();
}


void 
DcsInterface::TurnOffAllFee(const int modID, const  int rcuId) const
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(modID, rcuId); 
  tmpRcuPtr->TurnOffAllFee();
  TurnOffAllTru(modID, rcuId); //bad
  //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOffAllFee();
}

void 
DcsInterface::TurnOffAllTru(const int modID, const int rcuId) const
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOffAllTru(message);
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(modID, rcuId); 
  tmpRcuPtr->TurnOffAllTru();
}


void
DcsInterface::UpdateAFL(const int mod, const int rcu) const
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  tmpRcuPtr->UpdateAFL();
}

vector<int>
DcsInterface::UpdateFeeStatus(const int mod, const int rcu)
{
  vector<int> status;

  UpdateAFL(mod, rcu);

  status.clear();
  for(int i = 0; i < CARDS_PER_BRANCH; i++)
    {
      status.push_back(CheckFeeState(mod, rcu, BRANCH_A, i+1));
      //      status.push_back(i);
    }
  for(int i = 0; i < CARDS_PER_BRANCH; i++)
    {
      status.push_back(CheckFeeState(mod, rcu, BRANCH_B, i+1));
      //status.push_back(i);
    }
  return status;
}

int
DcsInterface::UpdateSingleFeeStatus(const int mod, const int rcu, const int branch, const int fee)
{
  int status = CheckFeeState(mod, rcu, branch, fee);

  return status;
}

string
DcsInterface::GetLogViewerString()
{
  return PhosDcsLogging::Instance()->GetLogViewerString();
}

int 
DcsInterface::Configure(const ModNumber_t modId)
{
  stringstream log;
  
  RcuALTROIF_t altroif(fReadoutSettings.GetNSamples().GetIntValue());
  RcuRDOMOD_t rdomod(false, fReadoutSettings.IsSparseReadout(), false, fReadoutSettings.GetMEBMode());
  RcuALTROCFG1_t altrocfg1(fReadoutSettings.IsZeroSuppressed(), fReadoutSettings.IsAutoBaselineSubtracted(),
			 fReadoutSettings.GetZeroSuppressionOffset(), fReadoutSettings.GetZeroSuppressionThreshold());
  RcuALTROCFG2_t altrocfg2(fReadoutSettings.GetNPreSamples().GetIntValue());

  ReadoutRegisters_t readoutRegs(altroif, rdomod, altrocfg1, altrocfg2);

  log.str("");
  readoutRegs.Print(log);
  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
  
  int res = ApplyReadoutRegisters(modId.GetIntValue(), readoutRegs);
  
  res += ApplyReadoutRegion(modId);

  if(res != 0) 
    {
      log.str("");
      log << "DcsInterface::Configure: Error in configuring module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
    }
  else
    {
      log.str("");
      log << "DcsInterface::Configure: Successfully configured module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
    }
  return res;
}

int DcsInterface::Reset(const ModNumber_t modId)
{
  stringstream log;
  int res = fPhosDetectorPtr->Reset(modId);
  if(res != 0) 
    {
      log.str("");
      log << "DcsInterface::Reset: Error in resetting module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
    }
  else
    {
      log.str("");
      log << "DcsInterface::Reset: Successfully reset module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
    }
  return res;
}

// int 
// DcsInterface::ApplyReadoutConfiguration(const ModNumber_t modID,  const ReadoutConfig_t rdoConfig)
// {
//   PhosDetector* tmpPhosModulePtr = fPhosDetectorPtr->GetModulePtr((*server).fModId);
//   return tmpPhosModulePtr->ApplyReadoutConfiguration(const ReadoutConfig_t rdoConfig);
// }


// unsigned int    
// TurnOnTru(const int mod,  const int rcu , const int truId)
// {
//   int tmpStates[CARDS_PER_RCU];

//   return TurnOnOffTru(mod, rcu , truId);
// }

// unsigned int    
// TurnOffTru(const int mod,  const int rcu , const int truId)
// {
//   int tmpStates[CARDS_PER_RCU];

// }
// unsigned int 
// DcsInterface::TurnOnFee(const int mod,  const int rcu , const int branch , 
// 			const int cardId,  unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage)
//   //DcsInterface::TurnOnFee(FeePos_t feePos,  unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage)
// {
 
// }


// unsigned int 
// DcsInterface::TurnOffFee(const int mod,  const int rcu , const int branch , 
// 			 const int cardId, unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage)
//   //DcsInterface::TurnOffFee(FeePos_t feePos, unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage)
// {
//   //  FeeCard *tmpFeeCard  = GetFeeCard(mod,  rcu, branch, cardId);
  
// }







