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

using namespace std;


PhosModule::PhosModule(PhosFeeClient *fClientPtr,  ModNumber_t mid) : PhosDcsBase(), 
								  fFeeClientPtr(0), 
								  fMapperPtr(0),
								  fModuleId(mid),
								  fReadoutConfig()
{
  fMapperPtr = new Mapper();
  fFeeClientPtr = fClientPtr;

  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      fRcuPtr[i] = 0;
    }
}


PhosModule::~PhosModule()
{
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      delete fRcuPtr[i];
    } 
}


const char*
PhosModule::GetFeeServerName(const int rcuId) const
{
  return fRcuPtr[rcuId]->GetFeeServerName(); 
}


void
PhosModule::ExecuteScript(const char *scriptName) const 
{
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if(fRcuPtr[i] != 0)
	{
	  fRcuPtr[i]->ExecuteScript(scriptName);
	} 
      else {
	printf("\nWarning, RCU Ptr is ZERO\n");
      }
  }
}


void
PhosModule::SetAllApds(const int value) const
{
  printf("\nSetting all APDs for MODULE\n");
  
  for(int i = 0; i< RCUS_PER_MODULE; i++)
    {
      fRcuPtr[i]->SetAllApds(value);
    }
}


void
PhosModule::LoadApdValues() const
{
  for(int i = 0; i< RCUS_PER_MODULE; i++)
    {
      if( fRcuPtr[i] != 0)
	{
	  fRcuPtr[i]->LoadApdValues();
	}
      else
	{
	  cout << "PhosModule::LoadApdValues, ERROR attempt to load padvalues when fRcuPtr[" << i<<"] is zero"<<endl;
	}
    }
}


Rcu *
PhosModule::GetRcuPtr(const int id) const
{
  if(id < RCUS_PER_MODULE && fRcuPtr[id] != 0)
    {
      printf("");
      return fRcuPtr[id];
    }
  else 
    {
      printf("\nError, coud not return RCU pointer\n");
      return 0;
    }
}


//void


const int
PhosModule::ArmTrigger(const char *triggerScriptFileName)
{
  //  cout << endl << endl;
  fReadoutConfig.PrintInfo("PhosModule::ArmTrigger");
  //  cout << endl << endl;

  int iRet = 0;
  fMapperPtr->GenerateACL(fReadoutConfig.GetReadoutRegion(), fAclMaps, fAfls);
  int nTrials =0;
  int status[RCUS_PER_MODULE];
  int initialized = true;
  char messageBuff[300];

  for(int i=0;  i<RCUS_PER_MODULE; i++  )
    {
      if( fReadoutConfig.GetAltroConfig().GetApplyPattern() == true )
	{
	  char mbuff[256];

	  fRcuPtr[i]->ApplyPattern(fReadoutConfig.GetAltroConfig().GetPattern(), mbuff);
	  printf("\n%s", mbuff);
	    
	}
    }


  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      status[i] = -1;
      fRcuPtr[i]->SetReadoutRegion(fAfls[i], fAclMaps[i]); 
      fRcuPtr[i]->ArmTrigger(triggerScriptFileName, messageBuff); 

      while((nTrials <= MAX_TRIALS) && (status[i] != REG_OK))
 	{
	  status[i] = fRcuPtr[i]->ApplyReadoutRegion();     
	  nTrials ++;
	}
      nTrials =0;
   }

  initialized = true;
  
  for(int i =0; i<RCUS_PER_MODULE; i++)
    {
      if(status[i] < 0)
	{
	  initialized = false;
	} 
    }
  
  if(initialized == false)
    {
      iRet = - 1;
      cout << "WARNING, the active channel readout list was not set correctly"<< endl;
      cout << "for at least one of the RCUs after 5 attemts, please check that the"<< endl;
      cout << "feeserver is running and try to restart the GUI"<< endl;
    }
  
  if(initialized == true)
    {
      iRet = 1;
      cout << "The readout configuration was apllied correctly to all RCUs"<< endl;
    }

  return iRet;
}


void   
PhosModule::EnableTrigger() const
{
   for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      fRcuPtr[i]->EnableTrigger();
    } 
}


void   
PhosModule::EnableTrigger_ttcrx() const
{
   for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      fRcuPtr[i]->EnableTrigger_ttcrx();
    } 
}


void
PhosModule::DisArmTrigger(const int rcuId) const
{
  fRcuPtr[rcuId]->DisArmTrigger();
}


void
PhosModule::CreateRcu(const char *serverName, const int mId, const int rcuId, const  int zCoord, const int xCoord)
{
  char resultBuffer[100];

  if(fFeeClientPtr != 0) 
    {
      fRcuPtr[rcuId] = new Rcu(fFeeClientPtr, serverName, mId, rcuId, zCoord, xCoord);
     }  
  else
    {
      cout << "PhosModule:XXX:CreateRcu, ERROR !!!!, fFeeClientPtr == NULL !!!!!!!!"  <<endl;
    }    
} 


void 
PhosModule::ApplyApdSettings(const int rcuId, const int branch, const int card, char *messageBuffer) const
{
  fRcuPtr[rcuId]->ApplyApdSettings(branch, card, messageBuffer);
}


void
PhosModule::SetReadoutConfig(const ReadoutConfig_t rdoConfig, char *messageBuf)
{
  fReadoutConfig = rdoConfig;
}
