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
DcsInterface::DcsInterface() : PhosDcsBase()
{
  fPhosDetectorPtr = new PhosDetector();

//  fDatabasePtr = new DatabaseDummy();

}



DcsInterface::~DcsInterface()
{

}

int DcsInterface::Init ( vector<FeeServer> feeServers )
{

  vector<FeeServer>::iterator server;

  int ret = 0;
  PhosModule* tmpPhosModulePtr = 0;
  stringstream log;

  server = feeServers.begin();
  while ( server != feeServers.end() )
    {
      tmpPhosModulePtr = fPhosDetectorPtr->GetModulePtr ( ( *server ).fModId );
      log.str ( "" );
      log << "DcsInterface::Init: Adding FeeServer with name: " << ( *server ).fName <<
      ". For Module #: " << ( *server ).fModId << " and RCU ID: " << ( *server ).fRcuId <<
      ". Coord: x = " << ( *server ).fX << ", z = " << ( *server ).fZ;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
      tmpPhosModulePtr->CreateRcu ( ( *server ).fName.c_str(), ( *server ).fModId, ( *server ).fRcuId, ( *server ).fZ, ( *server ).fX );
      ret += tmpPhosModulePtr->StartFeeClient ( ( *server ).fRcuId );
      server++;
    }

  log.str ( "" );
  log << "DcsInterface::Init: StartFeeClient() returned: " << ret;
  PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_VERY_VERBOSE );

  if ( ret > 0 )
    {
      PhosDcsLogging::Instance()->Logging ( "FEE Client successfully started.", LOG_LEVEL_INFO );
      server = feeServers.begin();
      while ( server != feeServers.end() )
        {
          log.str ( "" );
          log << ( *server ).fName << "Module #: " << ( *server ).fModId
          << " and RCU ID: " << ( *server ).fRcuId << ". Coord: x = "
          << ( *server ).fX << ", z = " << ( *server ).fZ;
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_VERBOSE );
          //	  DisArmTrigger((*server).fModId, (*server).fRcuId);
          server++;
        }
    }
  else if ( ret == 0 )
    {
      log.str ( "" );
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
      server = feeServers.begin();
      while ( server != feeServers.end() )
        {
          log.str ( "" );
          log << ( *server ).fName << "Module #: " << ( *server ).fModId
          << " and RCU ID: " << ( *server ).fRcuId << ". Coord: x = "
          << ( *server ).fX << ", z = " << ( *server ).fZ;
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
          server++;
        }
      PhosDcsLogging::Instance()->Logging ( "No services available", LOG_LEVEL_INFO );
      fPhosDetectorPtr->StopFeeClient();
    }
  else if ( ret < -1 )
    {
      log.str ( "" );
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
      server = feeServers.begin();
      while ( server != feeServers.end() )
        {
          log.str ( "" );
          log << ( *server ).fName << "Module #: " << ( *server ).fModId
          << " and RCU ID: " << ( *server ).fRcuId << ". Coord: x = "
          << ( *server ).fX << ", z = " << ( *server ).fZ;
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
          server++;
        }
      PhosDcsLogging::Instance()->Logging ( "FEE Client already running", LOG_LEVEL_INFO );
    }
  else
    {
      log.str ( "" );
      log << "Could not start FEE Client for FEE servers: ";
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
      server = feeServers.begin();
      while ( server != feeServers.end() )
        {
          log.str ( "" );
          log << ( *server ).fName << "Module #: " << ( *server ).fModId
          << " and RCU ID: " << ( *server ).fRcuId << ". Coord: x = "
          << ( *server ).fX << ", z = " << ( *server ).fZ;
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
          server++;
        }
      PhosDcsLogging::Instance()->Logging ( "Strange, FEE Client is returning to small number of services", LOG_LEVEL_INFO );
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
DcsInterface::ApplyApdSettings ( const int modID, const int rcuId, const int branch, const int card ) const
  {
    fPhosDetectorPtr->ApplyApdSettings ( modID, rcuId, branch, card );
  }

void
DcsInterface::ApplyTruSettings ( int modID, int RcuID, unsigned long *regAddr, unsigned long *regVal, bool *verify, int nTruRegs )
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->rcuPtr[RcuID]->ApplyTruSettings(regAddr, regVal, verify, nTruRegs,  Mesbuf);
}


int
DcsInterface::ArmTrigger ( const int modID ) const
  {
    return fPhosDetectorPtr->ArmTrigger ( modID );
  }


unsigned int
DcsInterface::CheckFeeState ( const int mod,  const int rcu , const int branch , const int cardId )
{
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( mod, rcu );
  if ( tmpRcuPtr ) return tmpRcuPtr->CheckFeeState ( branch, cardId );
  stringstream log;
  log.str ( "" );
  log << "DcsInterface::CheckFeeState: Checking FEE state for module: " << mod << " for RCU: " << rcu << " for card: " << cardId
  << " fails due to missing RCU " << endl;
  PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );

  return FEE_STATE_OFF;
}


void
DcsInterface::DisArmTrigger ( const int modID, const int RcuID ) const
  {
    if ( fPhosDetectorPtr ) fPhosDetectorPtr->DisArmTrigger ( modID, RcuID );
  }


void
DcsInterface::EnableTrigger ( int modID, string triggerType )
{
  ApplyReadoutRegisters ( ModNumber_t ( modID ) );
  RcuTRGCONF_t tmpTrgConf;

  if ( triggerType == "ttc" )
    {
      tmpTrgConf.EnableTTCrxTrigger();
    }
  else if ( triggerType == "soft" )
    {
      tmpTrgConf.EnableSoftwareTrigger();
    }
  else if ( triggerType == "aux" )
    {
      tmpTrgConf.EnableAuxTrigger();
    }
  else
    {
      tmpTrgConf.DisableAllTriggers();
    }

  if ( fPhosDetectorPtr ) fPhosDetectorPtr->phosModulePtr[modID]->EnableTrigger ( tmpTrgConf );
}
void
DcsInterface::DisableTrigger ( int modID )
{
  EnableTrigger ( modID, string ( "disable" ) );
  Reset ( ModNumber_t ( modID ) );
}

void
DcsInterface::EnableTrigger_ttcrx ( int modID )
{
  if ( fPhosDetectorPtr ) fPhosDetectorPtr->phosModulePtr[modID]->EnableTrigger_ttcrx();
}


unsigned long*
DcsInterface::GetApdValues ( const int mod, const int rcu, const int branch, const int cardId )
{
  FeeCard *tmpFeeCard  = GetFeeCard ( mod,  rcu, branch, cardId );
  if ( tmpFeeCard ) return tmpFeeCard->GetApdValues();
  return 0;
}


void
DcsInterface::GetConfigComment ( char *text, const int id )
{
  if ( fDatabasePtr ) fDatabasePtr->GetConfigComment ( text, id );
}

string
DcsInterface::GetConfigComment ( const int id )
{
  if ( fDatabasePtr ) return fDatabasePtr->GetConfigComment ( id );
  return string ( "No database initialised" );
}


FeeCard*
DcsInterface::GetFeeCard ( const int mod, const int rcu, const int branch, const int cardId ) const
  {
    int tmpFeeIndex = branch*CARDS_PER_BRANCH + cardId -1;

    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( mod, rcu );
    if ( tmpRcuPtr )
      {
        FeeCard *tmpFeeCard = tmpRcuPtr->GetFeeCardPtr ( tmpFeeIndex );
        return tmpFeeCard;
      }
    return 0;

  }


int
DcsInterface::GetLatestConfigId()
{
  if ( fDatabasePtr ) return fDatabasePtr->GetLatestConfigId();
  return -1;
}


Rcu*
DcsInterface::GetRcuPtr ( int modID, int rcuID ) const
  {
    if ( fPhosDetectorPtr ) return fPhosDetectorPtr->GetRcuPtr ( modID, rcuID );
    return 0;
  }


// void
// DcsInterface::LoadApdConfig(ConfigInfo_t *info) //Raed apd values from datbase and put them in sandbox directory
// {
//   fDatabasePtr->LoadApdConfig(info);
// }


void
DcsInterface::LoadApdConfig ( ConfigInfo_t &info, int id ) //Raed apd values from datbase and put them in sandbox directory
{

  if ( fDatabasePtr )
    {
      char tmpDscr[2000];
      fDatabasePtr->SaveApdConfig ( tmpDscr );
      //fDatabasePtr->LoadApdConfig(info.fInfo, id);
      fDatabasePtr->LoadApdConfig ( info, id );
    }

}

void
DcsInterface::LoadApdValues ( int modID )  //Load apd values into Feecard objects
{
  if ( fPhosDetectorPtr )
    {
      fPhosDetectorPtr->phosModulePtr[modID]->LoadApdValues();
    }
}


void
DcsInterface::LoadReadoutConfiguration ( ReadoutConfig_t *rdoconfigPtr, ModNumber_t modNumber ) const
  {
    if ( fDatabasePtr ) fDatabasePtr->LoadReadoutConfiguration ( rdoconfigPtr, modNumber );
    rdoconfigPtr->PrintInfo ( "DcsInterface::LoadReadoutConfiguration " );
  }


void
DcsInterface::SaveReadoutConfiguration ( const ReadoutConfig_t rdoconfig, const ModNumber_t modNumber ) const
  {
    if ( fDatabasePtr ) fDatabasePtr->SaveReadoutConfiguration ( rdoconfig, modNumber );
  }

void
DcsInterface::LoadTruSettings ( TRUSettings_t *trusettings ) const
  {
    if ( fDatabasePtr ) fDatabasePtr->LoadTruSettings ( trusettings );
  }

int
DcsInterface::SaveApdConfig ( char *description )
{
  if ( fDatabasePtr ) fDatabasePtr->SaveApdConfig ( description );
}


void
DcsInterface::SaveTRUSettings ( const TRUSettings_t trusettings )
{
  trusettings.PrintInfo ( "DcsInterface::SaveTRUSettings" );
  if ( fDatabasePtr ) fDatabasePtr->SaveTruSettings ( trusettings );
}


void
DcsInterface::SetAllApds ( const int modID, const int apdValue )
{
  if ( fPhosDetectorPtr ) fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds ( apdValue );
}


void
DcsInterface::SetAllApds ( const int modID, const int rcuId, const int apdValue )
{
  if ( fPhosDetectorPtr )
    {
      Rcu *tmpRcu = fPhosDetectorPtr->phosModulePtr[modID]->GetRcuPtr ( rcuId );
      if ( tmpRcu )
        {
          tmpRcu->SetAllApds ( apdValue );
        }
      else
        {
          stringstream log;
          log.str ( "" );
          log << "DcsInterface::SetAllApds: Setting all APDs for RCU: " << rcuId << " on module: " << modID << "to: " << apdValue
          << " fails due missing RCU connection" << endl;
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
        }
    }
  else
    {
      stringstream log;
      log.str ( "" );
      log << "DcsInterface::SetAllApds: Setting all APDs for RCU: " << rcuId << " on module: " << modID << "to: " << apdValue
      << " fails due missing module connection" << endl;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
    }
  //  fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds(apdValue);
}


void
DcsInterface::SetAllApds ( const int modID, const int rcuId, const int branch, const int card, const int apdValue )
{
  //  fPhosDetectorPtr->phosModulePtr[modID]->SetAllApds(apdValue);
  FeeCard *tmpFeeCard;
  Rcu *tmpRcu =fPhosDetectorPtr->phosModulePtr[modID]->GetRcuPtr ( rcuId );
  tmpFeeCard = tmpRcu->GetFeeCardPtr ( branch*CARDS_PER_BRANCH + card-1 );
  tmpFeeCard->SetAllApds ( apdValue );
}


void
DcsInterface::SetApdValues ( const int mod, const int rcu, const int branch, const int cardId, const unsigned long *values )
{
  //cout <<"DcsInterface::SetApdValues; mod  =" << mod <<"  rcu = "<< rcu <<"  branch = "<< branch << "card = " <<  cardId <<endl;
  FeeCard *tmpFeeCard  = GetFeeCard ( mod,  rcu, branch, cardId );
  tmpFeeCard->SetApdValues ( values );
}


void
DcsInterface::SetPhosBit ( const int modId ) const
  {
    fPhosDetectorPtr->SetPhosBit ( modId );
  }


void
DcsInterface::SetReadoutConfig ( const ModNumber_t modID,  const ReadoutConfig_t rdoConfig )
{
  //  rdoConfig.PrintInfo("DcsInterface::SetReadoutConfig");
  fPhosDetectorPtr->SetReadoutConfig ( modID,  rdoConfig );
}

void
DcsInterface::SetReadoutSettings ( const ModNumber_t modId, const ReadoutSettings_t rdoSettings )
{
  fPhosDetectorPtr->SetReadoutSettings ( modId, rdoSettings );
  fReadoutSettings = rdoSettings;
}

void
DcsInterface::SetReadoutRegion ( const ModNumber_t modId, const ReadoutRegion_t rdoRegion ) const
  {
    fPhosDetectorPtr->SetReadoutRegion ( modId, rdoRegion );
  }

int
DcsInterface::ApplyReadoutRegisters ( const ModNumber_t modID, const ReadoutRegisters_t readoutRegisters ) const
  {

    return fPhosDetectorPtr->ApplyReadoutRegisters ( modID, readoutRegisters );
  }

int
DcsInterface::ApplyReadoutRegisters ( const ModNumber_t modID ) const
  {

    return fPhosDetectorPtr->ApplyReadoutRegisters ( modID );
  }

int
DcsInterface::ApplyReadoutRegion ( const ModNumber_t modID ) const
  {
    return fPhosDetectorPtr->ApplyReadoutRegion ( modID );
  }

unsigned int
DcsInterface::TurnOnFee ( const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpState )
{
  if ( fPhosDetectorPtr->GetRcuPtr ( mod, rcu ) ) return fPhosDetectorPtr->GetRcuPtr ( mod, rcu )->ActivateFee ( branch, cardSlot );
}

unsigned int
DcsInterface::TurnOffFee ( const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpState )
{
  if ( fPhosDetectorPtr->GetRcuPtr ( mod, rcu ) ) return fPhosDetectorPtr->GetRcuPtr ( mod, rcu )->DeActivateFee ( branch, cardSlot );
}

unsigned int
//DcsInterface::ToggleOnOffFee(const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate, unsigned int tmpStates[CARDS_PER_RCU])
DcsInterface::ToggleOnOffFee ( const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate )
{
  PhosDcsLogging::Instance()->Logging("Toggling", LOG_LEVEL_VERBOSE);
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( mod, rcu );
  
  int state = tmpRcuPtr->ToggleFeeOnOff ( branch, cardId );
  int **tmp = tmpRcuPtr->GetFeeStatus();

  
  for ( int i=0; i < CARDS_PER_RCU; i++ )
    {
      //      tmpStates[i] = *tmp[i];
    }
  return state;
}

unsigned int
DcsInterface::ToggleOnOffTru ( const int mod, const int rcu, const int truId )

{
  stringstream log;

  log.str ( "" );
  log << "DcsInterface::ToggleOnOffTru: Toggling TRU: " << truId << " for RCU: " << rcu << " on module " << mod << endl;
  PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_VERBOSE );
  int state = 0;
  Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( mod, rcu );
  if ( tmpRcuPtr ) state = tmpRcuPtr->ToggleTruOnOff ( truId );

  return state;
}

void
DcsInterface::TurnOnAllFee ( const int modID, const int rcuId ) const
  {
    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( modID, rcuId );
    if ( tmpRcuPtr ) tmpRcuPtr->TurnOnAllFee();
  }


void
DcsInterface::TurnOnAllTru ( const int modID, const int rcuId ) const
  {
    //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOnAllTru(message);
    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( modID, rcuId );
    if ( tmpRcuPtr ) tmpRcuPtr->TurnOnAllTru();
  }


void
DcsInterface::TurnOffAllFee ( const int modID, const  int rcuId ) const
  {
    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( modID, rcuId );
    if ( tmpRcuPtr ) tmpRcuPtr->TurnOffAllFee();
    TurnOffAllTru ( modID, rcuId ); //bad
    //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOffAllFee();
  }

void
DcsInterface::TurnOffAllTru ( const int modID, const int rcuId ) const
  {
    //  fPhosDetectorPtr->phosModulePtr[modID]->TurnOffAllTru(message);
    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( modID, rcuId );
    if ( tmpRcuPtr ) tmpRcuPtr->TurnOffAllTru();
  }


void
DcsInterface::UpdateAFL ( const int mod, const int rcu ) const
  {
    stringstream log;
    log.str ( "" );
    log << "DcsInterface::UpdateAFL: Updating AFL for module #: " << mod << " and RCU #:  " << rcu;
    PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_VERBOSE );

    Rcu *tmpRcuPtr =  fPhosDetectorPtr->GetRcuPtr ( mod, rcu );
    if ( tmpRcuPtr ) tmpRcuPtr->UpdateAFL();
  }

vector<int>
DcsInterface::UpdateFeeStatus ( const int mod, const int rcu )
{
  vector<int> status;

  UpdateAFL ( mod, rcu );

  status.clear();
  for ( int i = 0; i < CARDS_PER_BRANCH; i++ )
    {
      status.push_back ( CheckFeeState ( mod, rcu, BRANCH_A, i+1 ) );
      //      status.push_back(i);
    }
  for ( int i = 0; i < CARDS_PER_BRANCH; i++ )
    {
      status.push_back ( CheckFeeState ( mod, rcu, BRANCH_B, i+1 ) );
      //status.push_back(i);
    }
  return status;
}

int
DcsInterface::UpdateSingleFeeStatus ( const int mod, const int rcu, const int branch, const int fee )
{
  int status = CheckFeeState ( mod, rcu, branch, fee );
  cout << "DcsInterface: state: " << status << endl;
  return status;
}

string
DcsInterface::GetLogViewerString()
{
  return PhosDcsLogging::Instance()->GetLogViewerString();
}

int
DcsInterface::Configure ( const ModNumber_t modId )
{
  stringstream log;

    log.str ( "" );

    log << "DcsInterface::Configure: IsZeroSuppressed: " << fReadoutSettings.IsZeroSuppressed() << ", AUTO BS: " << fReadoutSettings.IsAutoBaselineSubtracted();
    PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_VERBOSE );

    bool writeZeros = ((!fReadoutSettings.IsZeroSuppressed() && !fReadoutSettings.IsFixedBaselineSubtracted()) || fReadoutSettings.IsAutoBaselineSubtracted());
    
  WriteFixedPedestals(modId, 0, writeZeros);

  int res = ApplyReadoutRegisters ( modId );

  res += ApplyReadoutRegion ( modId );
  log.str("");
  log << "DcsInterface::Configure: Fixed pedestals: " << fReadoutSettings.IsFixedBaselineSubtracted() << ", write zeros: " << writeZeros;
  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);

  if ( res != 0 )
    {
      log.str ( "" );
      log << "DcsInterface::Configure: Successfully configured module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
    }
  else
    {
      log.str ( "" );
      log << "DcsInterface::Configure: Successfully configured module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
    }
  return res;
}

int DcsInterface::Reset ( const ModNumber_t modId )
{
  stringstream log;
  int res = fPhosDetectorPtr->Reset ( modId );
  if ( res != 0 )
    {
      log.str ( "" );
      log << "DcsInterface::Reset: Error in resetting module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
    }
  else
    {
      log.str ( "" );
      log << "DcsInterface::Reset: Successfully reset module #: " << modId.GetIntValue();
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
    }
  return res;
}


int DcsInterface::ApplyScriptToFeeServer ( const char *feeServerName, const char* scriptfilename )
{
  vector<FeeServer> feeserverVector;

  FeeServer server;

  server.fName = std::string ( feeServerName );
  server.fModId = 0;
  server.fRcuId = 0;
  server.fX = 0;
  server.fZ = 0;

  feeserverVector.push_back ( server );

  Init ( feeserverVector );

  char *tmpResult = new char[20000];
  fPhosDetectorPtr->GetFeeClientPointer()->ExecuteScript ( scriptfilename, feeServerName, tmpResult, 1 );

  sleep ( 10 );
  return 0;
}


int DcsInterface::WriteFixedPedestals ( const ModNumber_t modID, const int pedestalVersion, bool writeZeros )
{
   if(fPhosDetectorPtr)
   {

     fPedestalsDatabase.LoadValues(!writeZeros);
     
      return fPhosDetectorPtr->WriteFixedPedestals(modID, !writeZeros);
   }
   else
   {
      return -1;
   }
}

long unsigned int DcsInterface::GetRcuALTROIF ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::ALTROIF);
   }
   else 
   {
      return 0;
   }
}

long unsigned int DcsInterface::GetRcuTRGCONF ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::TRCFG);
   }
   else 
   {
      return 0;
   }
}

long unsigned int DcsInterface::GetRcuRDOMOD ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::RDOMOD);
   }
   else 
   {
      return 0;
   }
}

long unsigned int DcsInterface::GetRcuALTROCFG1 ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::ALTROCFG1);
   }
   else 
   {
      return 0;
   }
}

long unsigned int DcsInterface::GetRcuALTROCFG2 ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::ALTROCFG2);
   }
   else 
   {
      return 0;
   }
}

long unsigned int DcsInterface::GetRcuBPVersion ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->ReadSingleRegister(RcuRegisterMap::BP_VERSION);
   }
   else 
   {
      return 0;
   }
}

unsigned long DcsInterface::GetRcuFirmwareVersion ( const int modId, const int rcuId )
{
   Rcu *rcu = fPhosDetectorPtr->GetRcuPtr(modId, rcuId);
   if(rcu)
   {
      return rcu->GetFirmwareVersion();
   }
   else 
   {
      return 0;
   }
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







