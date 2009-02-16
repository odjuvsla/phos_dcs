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
 

//   tmpPhosModulePtr->CreateRcu("tpc-fee_0_17_3", MODULE_2, RCU_0, Z_0, X_0);
//   tmpPhosModulePtr->CreateRcu("tpc-fee_0_17_3", MODULE_2, RCU_1, Z_1, X_0);
//   tmpPhosModulePtr->CreateRcu("tpc-fee_0_17_3", MODULE_2, RCU_2, Z_0, X_1);
//   tmpPhosModulePtr->CreateRcu("alphsdcs0280", MODULE_2, RCU_3, Z_1, X_1);
 
//  tmpPhosModulePtr->CreateRcu("dcs0327", MODULE_2, RCU_0, Z_0, X_0);
//  tmpPhosModulePtr->CreateRcu("dcs0327", MODULE_2, RCU_1, Z_1, X_0);
//  tmpPhosModulePtr->CreateRcu("dcs0327", MODULE_2, RCU_2, Z_0, X_1);
//  tmpPhosModulePtr->CreateRcu("dcs0327", MODULE_2, RCU_3, Z_1, X_1);

//   tmpPhosModulePtr->CreateRcu("alphsdcs0282", MODULE_2, RCU_0, Z_0, X_0);
//   tmpPhosModulePtr->CreateRcu("alphsdcs0279", MODULE_2, RCU_1, Z_1, X_0);
//   tmpPhosModulePtr->CreateRcu("alphsdcs0281", MODULE_2, RCU_2, Z_0, X_1);
//   tmpPhosModulePtr->CreateRcu("alphsdcs0280", MODULE_2, RCU_3, Z_1, X_1);
  
//  fPhosDetectorPtr->StartFeeClient();
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

  server = feeServers.begin();
  while(server != feeServers.end())
    {
      tmpPhosModulePtr = fPhosDetectorPtr->GetModulePtr((*server).fModId);

      tmpPhosModulePtr->CreateRcu((*server).fName.c_str(), (*server).fModId, (*server).fRcuId, (*server).fZ, (*server).fX);
      server++;
    }
  
  ret = fPhosDetectorPtr->StartFeeClient();
  if(ret > 0) 
    {
      server = feeServers.begin();
      while(server != feeServers.end())
	{
	  DisArmTrigger((*server).fModId, (*server).fRcuId);
	  server++;
	}
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
  char messageBuffer[256];
  fPhosDetectorPtr->ApplyApdSettings(modID, rcuId, branch, card, messageBuffer);
}

void 
DcsInterface::ApplyTruSettings(int modID, int RcuID, char *Mesbuf, unsigned long *regAddr, unsigned long *regVal, bool *verify, int nTruRegs)
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
  char message[128];
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  return tmpRcuPtr->CheckFeeState(branch, cardId, message);
}


void 
DcsInterface::DisArmTrigger(const int modID, const int RcuID) const
{
  char messageBuffer[128];
  fPhosDetectorPtr->DisArmTrigger(modID, RcuID, messageBuffer);
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
DcsInterface::LoadReadoutConfiguration(ReadoutConfig_t *rdoconfigPtr) const
{
  fDatabasePtr->LoadReadoutConfiguration(rdoconfigPtr);
  rdoconfigPtr->PrintInfo("DcsInterface::LoadReadoutConfiguration ");
} 


void       
DcsInterface::SaveReadoutConfiguration(const ReadoutConfig_t rdoconfig) const
{
  fDatabasePtr->SaveRadoutConfiguration(rdoconfig);
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
DcsInterface::SetReadoutConfig(const ModNumber_t modID,  const ReadoutConfig_t rdoConfig) const
{
  char messageBuf[256];
  //  rdoConfig.PrintInfo("DcsInterface::SetReadoutConfig"); 
  fPhosDetectorPtr->SetReadoutConfig(modID,  rdoConfig,  messageBuf);
}


unsigned int 
DcsInterface::ToggleOnOffFee(const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate, unsigned int tmpStates[CARDS_PER_RCU])
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(mod, rcu); 
  int state = tmpRcuPtr->ToggleFeeOnOff(branch, cardId);
  int **tmp = tmpRcuPtr->GetFeeStatus();

  for(int i=0; i < CARDS_PER_RCU; i++)
    {
      tmpStates[i] = *tmp[i];
    }
  return state;
}


void 
DcsInterface::TurnOnAllFee(const int modID, const int rcuId) const
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr(modID, rcuId); 
  tmpRcuPtr->TurnOnAllFee();
  char* tmp = 0;
  TurnOnAllTru(modID, rcuId, tmp); //bad
}


void 
DcsInterface::TurnOnAllTru(const int modID, const int rcuId, char *message) const
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
  char* tmp = 0;
  TurnOffAllTru(modID, rcuId, tmp); //bad
  //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOffAllFee();
}

void 
DcsInterface::TurnOffAllTru(const int modID, const int rcuId, char *message) const
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

  status.clear();
  for(int i = 0; i < CARDS_PER_BRANCH; i++)
    {
      //      status.push_back(CheckFeeState(mod, rcu, BRANCH_A, i+1));
      status.push_back(i);
    }
  for(int i = 0; i < CARDS_PER_BRANCH; i++)
    {
      //      status.push_back(CheckFeeState(mod, rcu, BRANCH_B, i+1));
      status.push_back(i);
    }
  return status;
}

string
DcsInterface::GetLogViewerString()
{
  return PhosDcsLogging::Instance()->GetLogViewerString();
}


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







