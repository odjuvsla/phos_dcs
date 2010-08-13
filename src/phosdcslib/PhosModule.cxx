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

#include "PhosModule.h"
#include "ScriptCompiler.h"
#include "Mapper.h"
#include "PhosFeeClient.h"
#include "Rcu.h"
#include "PhosDcsLogging.h"
#include "PhosRegisters.h"
#include "phos_dcs_config.h"

using namespace std;


PhosModule::PhosModule ( PhosFeeClient *fClientPtr,  ModNumber_t mid ) : PhosDcsBase(),
    fFeeClientPtr ( 0 ),
    fMapperPtr ( 0 ),
    fModuleId ( mid ),
    fReadoutConfig()
{
  fMapperPtr = new Mapper();
  fMapperPtr->ExcludeChannelsFromFile("excludedchannels.txt", mid);
  fFeeClientPtr = fClientPtr;

  for ( int i=0; i<RCUS_PER_MODULE; i++ )
    {
      fRcuPtr[i] = 0;
    }
}


PhosModule::~PhosModule()
{
  for ( int i=0; i<RCUS_PER_MODULE; i++ )
    {
      delete fRcuPtr[i];
    }
}

const char*
PhosModule::GetFeeServerName ( const int rcuId ) const
  {
    if ( fRcuPtr[rcuId] ) return fRcuPtr[rcuId]->GetFeeServerName();
    return 0;
  }


void
PhosModule::ExecuteScript ( const char *scriptName ) const
  {
    for ( int i=0; i<RCUS_PER_MODULE; i++ )
      {
        if ( fRcuPtr[i] != 0 )
          {
            fRcuPtr[i]->ExecuteScript ( scriptName );
          }
        else
          {
            stringstream log;
            log << "RCU pointer is NULL";
            PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
          }
      }
  }


void
PhosModule::SetAllApds ( const int value ) const
  {
    stringstream log;
    log << "PhosModule::SetAllApds: Setting all APDs for MODULE";
    PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );

    for ( int i = 0; i< RCUS_PER_MODULE; i++ )
      {
        if ( fRcuPtr[i] ) fRcuPtr[i]->SetAllApds ( value );
      }
  }


void
PhosModule::LoadApdValues() const
  {
    for ( int i = 0; i< RCUS_PER_MODULE; i++ )
      {
        if ( fRcuPtr[i] != 0 )
          {
            fRcuPtr[i]->LoadApdValues();
          }
        else
          {
            stringstream log;
            log << "PhosModule::LoadApdValues: Attempt to load apd values when fRcuPtr[" << i<<"] is zero";
            PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
          }
      }
  }


Rcu *
PhosModule::GetRcuPtr ( const int id ) const
  {
    if ( id < RCUS_PER_MODULE && fRcuPtr[id] != 0 )
      {
        return fRcuPtr[id];
      }
    else
      {
        return 0;
      }
  }


//void


const int
PhosModule::ArmTrigger ( const char *triggerScriptFileName )
{
  //  cout << endl << endl;
  fReadoutConfig.PrintInfo ( "PhosModule::ArmTrigger" );
  //  cout << endl << endl;

  int iRet = 0;
  
  fMapperPtr->GenerateACL ( fReadoutConfig.GetReadoutRegion(), fAclMapsA, fAfls, fModuleId.GetIntValue(), BRANCH_A);
  fMapperPtr->GenerateACL ( fReadoutConfig.GetReadoutRegion(), fAclMapsB, fAfls, fModuleId.GetIntValue(), BRANCH_B );
  int nTrials =0;
  int status[RCUS_PER_MODULE];
  int initialized = true;

  for ( int i=0;  i<RCUS_PER_MODULE; i++ )
    {
      if ( fReadoutConfig.GetAltroConfig().GetApplyPattern() == true )
        {
          if ( fRcuPtr[i] ) fRcuPtr[i]->ApplyPattern ( fReadoutConfig.GetAltroConfig().GetPattern() );
          //	  printf("\n%s", mbuff);

        }
    }


  for ( int i=0; i<RCUS_PER_MODULE; i++ )
    {
      status[i] = -1;
      if ( fRcuPtr[i] != 0 )
        {
          fRcuPtr[i]->SetReadoutRegion ( fAfls[i], fAclMapsA[i], fAclMapsB[i] );
          fRcuPtr[i]->ArmTrigger ( triggerScriptFileName );

          while ( ( nTrials <= MAX_TRIALS ) && ( status[i] != REG_OK ) )
            {
              status[i] = fRcuPtr[i]->ApplyReadoutRegion();
              nTrials ++;
            }
          nTrials =0;
        }
    }

  initialized = true;

  for ( int i =0; i<RCUS_PER_MODULE; i++ )
    {
      if ( status[i] < 0 )
        {
          initialized = false;
        }
    }

  if ( initialized == false )
    {
      iRet = - 1;
      stringstream log;
      log << "PhosModule::ArmTrigger: The active channel readout list was not set correctly"<< endl;
      log << "for at least one of the RCUs after 5 attemts, please check that the"<< endl;
      log << "feeserver is running and try to restart the GUI"<< endl;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
    }

  if ( initialized == true )
    {
      iRet = 1;
      stringstream log;
      log << "PhosModule::ArmTrigger: The readout configuration was applied correctly to all RCUs"<< endl;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );
    }

  return iRet;
}

void
PhosModule::EnableTrigger ( RcuTRGCONF_t trgConf ) const
  {

    for ( int i=0; i<RCUS_PER_MODULE; i++ )
      {
        if ( fRcuPtr[i] != 0 )
          {
            fRcuPtr[i]->EnableTrigger ( trgConf );
          }
      }
  }

void
PhosModule::EnableTrigger_ttcrx() const
  {
    for ( int i=0; i<RCUS_PER_MODULE; i++ )
      {
        if ( fRcuPtr[i] ) fRcuPtr[i]->EnableTrigger_ttcrx();
      }
  }


void
PhosModule::DisArmTrigger ( const int rcuId ) const
  {
    if ( fRcuPtr[rcuId] ) fRcuPtr[rcuId]->DisArmTrigger();
  }


void
PhosModule::CreateRcu ( const char *serverName, const int mId, const int rcuId, const  int zCoord, const int xCoord )
{
  char resultBuffer[100];

  if ( fFeeClientPtr != 0 )
    {
      fRcuPtr[rcuId] = new Rcu ( fFeeClientPtr, serverName, mId, rcuId, zCoord, xCoord );
    }
  else
    {
      stringstream log;
      log << "PhosModule::CreateRcu: fFeeClientPtr == NULL"  <<endl;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_ERROR );
    }
}


void
PhosModule::ApplyApdSettings ( const int rcuId, const int branch, const int card ) const
  {
    if ( fRcuPtr[rcuId] ) fRcuPtr[rcuId]->ApplyApdSettings ( branch, card );

  }


void
PhosModule::SetReadoutConfig ( const ReadoutConfig_t rdoConfig )
{
  fReadoutConfig = rdoConfig;
}

void
PhosModule::SetReadoutSettings ( const ReadoutSettings_t rdoSettings )
{
  fReadoutSettings = rdoSettings;
}

void
PhosModule::SetReadoutRegion ( const ReadoutRegion_t rdoRegion )
{

  fReadoutRegion = rdoRegion;
}


int
PhosModule::ApplyReadoutRegisters ( const ReadoutRegisters_t readoutRegisters )
{
  int n = 0;
  int res = 0;
  for ( int n = 0; n < RCUS_PER_MODULE; n++ )
    {
      if ( fRcuPtr[n] != 0 )
        {
          res += fRcuPtr[n]->ApplyReadoutRegisters ( readoutRegisters );
        }
    }
}

int
PhosModule::ApplyReadoutRegisters() const
  {
    stringstream log;

    RcuALTROIF_t altroif ( fReadoutSettings.GetNSamples().GetIntValue() );
    RcuRDOMOD_t rdomod ( false, fReadoutSettings.IsSparseReadout(),  fReadoutSettings.IsSparseReadoutRcu(), false, fReadoutSettings.GetMEBMode() );
//     RcuALTROCFG1_t altrocfg1 ( fReadoutSettings.IsZeroSuppressed(), fReadoutSettings.IsAutoBaselineSubtracted(),
//                                fReadoutSettings.GetZeroSuppressionOffset(), fReadoutSettings.GetZeroSuppressionThreshold() );
//     RcuALTROCFG2_t altrocfg2 ( fReadoutSettings.GetNPreSamples().GetIntValue(), fReadoutSettings.IsAutoBaselineSubtracted(), fReadoutSettings.IsFixedBaselineSubtracted());
    RcuALTROCFG1_t altrocfg1 ( fReadoutSettings.IsZeroSuppressed(), fReadoutSettings.IsAutoBaselineSubtracted(),
                               fReadoutSettings.GetZeroSuppressionOffset(), fReadoutSettings.GetZeroSuppressionThreshold() );
    //RcuALTROCFG2_t altrocfg2 ( fReadoutSettings.GetNPreSamples().GetIntValue(), fReadoutSettings.IsAutoBaselineSubtracted(), fReadoutSettings.IsFixedBaselineSubtracted());
    int sampleFreq = 10000000;
    RcuALTROCFG2_t altrocfg2( fReadoutSettings.GetMEBMode(), fReadoutSettings.GetNPreSamples().GetIntValue(), fReadoutSettings.GetNSamples().GetIntValue(),
				 fReadoutSettings.IsSparseReadout(), sampleFreq);

    RcuL1LAT_t tmpLOneLat;
    RcuL1MSGLAT_t tmpLOneMsgLat;

    ReadoutRegisters_t readoutRegs ( altroif, rdomod, altrocfg1, altrocfg2, tmpLOneLat, tmpLOneMsgLat );

    log.str ( "" );
    readoutRegs.Print ( log, string ( "V" ) );
    PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_INFO );

    int n = 0;
    int res = 0;
    for ( int n = 0; n < RCUS_PER_MODULE; n++ )
      {
        if ( fRcuPtr[n] != 0 )
          {
            res += fRcuPtr[n]->ApplyReadoutRegisters ( readoutRegs );
          }
      }
  }

int
PhosModule::ApplyReadoutRegion ( const ReadoutRegion_t readoutRegion )
{
  stringstream log;
  int n = 0;
  int res = 0;
  int nTrials = 0;
  SetReadoutRegion ( readoutRegion );
  fMapperPtr->InitAltroMapping ( 0, fModuleId );
  fMapperPtr->GenerateACL ( fReadoutRegion, fAclMapsA, fAfls, fModuleId.GetIntValue(), BRANCH_A );
  
  
  fMapperPtr->GenerateACL ( fReadoutRegion, fAclMapsB, fAfls, fModuleId.GetIntValue(), BRANCH_B );

  int status[RCUS_PER_MODULE];

  for ( int i=0; i<RCUS_PER_MODULE; i++ )
    {
      status[i] = -1;
      if ( fRcuPtr[i] != 0 )
        {
          fRcuPtr[i]->SetReadoutRegion ( fAfls[i], fAclMapsA[i], fAclMapsB[i] );

          while ( ( nTrials <= MAX_TRIALS ) && ( status[i] != REG_OK ) )
            {
              status[i] = fRcuPtr[i]->ApplyReadoutRegion();
              nTrials ++;
            }
          nTrials =0;
        }
      else
        {
          log.str ( "" );
          log << "PhosModule::ApplyReadoutRegion: Module #: " << fModuleId.GetIntValue() << " RCU #: " << i << " is not connected";
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
          status[i] = 0;
        }
    }
}

void
PhosModule::Reset()
{
  stringstream log;

  for ( int i=0; i<RCUS_PER_MODULE; i++ )
    {
      if ( fRcuPtr[i] != 0 )
        {
          fRcuPtr[i]->Reset();
        }
      else
        {
          log.str ( "" );
          log << "PhosModule::Reset: Module #: " << fModuleId.GetIntValue() << " RCU #: " << i << " is not connected";
          PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
        }
    }
}

int
PhosModule::StartFeeClient ( int rcuID )
{
  stringstream log;
  if ( fRcuPtr[rcuID] != 0 )
    {
      fRcuPtr[rcuID]->StartFeeClient();
    }
  else
    {
      log.str ( "" );
      log << "PhosModule::StartFeeServer: Module #: " << fModuleId.GetIntValue() << " RCU #: " << rcuID << " is not connected";
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_WARNING );
    }
}

int PhosModule::WriteFixedPedestals(bool fromFile)
{
   int res = -1;
   for(int rcuID = 0; rcuID < RCUS_PER_MODULE; rcuID++)
   {
      if(fRcuPtr[rcuID])
      {
  stringstream log;
  log << "PhosModule::WriteFixedPedestals: Module #: " << fModuleId.GetIntValue() << ", RCU: " << rcuID << ", from file: " << fromFile;
   PhosDcsLogging::Instance()->Logging (log.str(), LOG_LEVEL_INFO );

	 res = fRcuPtr[rcuID]->WriteFixedPedestalValues(fromFile);
	 if(res)
	 {
	   return res;
	 }
      }
   }
   if(res)
   {
      stringstream log;
      log << "PhosModule::WriteFixedPedestals: Module #: " << fModuleId.GetIntValue() << ", no RCUs connected";
      PhosDcsLogging::Instance()->Logging (log.str(), LOG_LEVEL_WARNING );
   }
 
   return res;
}
