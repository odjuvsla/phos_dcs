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


#define GEOM_ADRESS_0  0
#define GEOM_ADRESS_1  1
#define GEOM_ADRESS_2  2
#define GEOM_ADRESS_3  3
#define GEOM_ADRESS_4  4

#include "PhosModule.h"
#include "Rcu.h"
#include "ScriptCompiler.h"
#include "Mapper.h"
#include <stdio.h>
#include <iostream>
#include "CommonDefs.h"

//---------------------------------------------------------------------------
PhosModule::PhosModule()
{
  int i = RCUS_PER_MODULE;
  while(i--)
    rcuPtr[i] = NULL;
}
//---------------------------------------------------------------------------
PhosModule::PhosModule(PhosFeeClient *fClientPtr)
{
  int i = RCUS_PER_MODULE;
  while(i--)
    rcuPtr[i] = NULL;
  mapperPtr = new Mapper();
  feeClientPtr = fClientPtr;
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      rcuPtr[i] = 0;
    }
}

//---------------------------------------------------------------------------
PhosModule::~PhosModule()
{
  int i = RCUS_PER_MODULE;
  while( i-- ){
    if( rcuPtr[i] )
      delete rcuPtr[i];
  } 
}

//---------------------------------------------------------------------------
void
PhosModule::TurnOnAllFee()
{
  int *dummy;  //!!!!!!!!Change  
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if(rcuPtr[i] )
	  rcuPtr[i]->TurnOnAllFee(dummy);
      else 
	std::cout<<" PhosModule::TurnOnAllFee() Warning, RCU Ptr rcuPtr["<<i<<"]is ZERO"<<std::endl;
    }
}
//---------------------------------------------------------------------------
void
PhosModule::TurnOffAllFee()
{
  int *dummy;  //!!!!!!!!Change  
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->TurnOffAllFee(dummy);
    }
}
//---------------------------------------------------------------------------
void
PhosModule::SetAllApds(int value)
{
  printf("\nSetting all APDs for MODULE\n");
  for(int i = 0; i< RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->SetAllApds(value);
    }
}
//---------------------------------------------------------------------------
void
PhosModule::LoadApdValues()
{
  std::cout<<" PhosModule:LoadApdValues() .... "<<std::endl;
  for(int i = 0; i< RCUS_PER_MODULE; i++) {
    if( rcuPtr[i] )
      rcuPtr[i]->LoadApdValues();
  }
}

//---------------------------------------------------------------------------
Rcu *
PhosModule::GetRcuPtr(int id)
{
  std::cout<<" PhosModule::GetRcuPtr(ID = "<<id<<")"<<std::endl;
  if(id < RCUS_PER_MODULE && rcuPtr[id] != 0)
    {
      return rcuPtr[id];
    }
  else 
    {
      std::cout<<" PhosModule::GetRcuPtr() Error!!! Could not return RCU pointer "<<id<<std::endl;
      return 0;
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int*
PhosModule::ArmTrigger(char triggerScriptFileName[50])
{
  std::cout<<" PhosModule::ArmTrigger, startZ ="<<startZ<<", endZ ="<<endZ
	   <<" startX ="<<startX<<" endX = "<<endX<<std::endl;
  mapperPtr->GenerateACL(startZ, endZ, startX, endX, moduleId, aclMaps, afls);
  int nTrials =0;
  int status[RCUS_PER_MODULE];
  int initialized = TRUE;

  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      status[i] = -1;
      if( rcuPtr[i] ){
	rcuPtr[i]->SetReadoutRegion(afls[i], aclMaps[i]); 
	rcuPtr[i]->ArmTrigger(triggerScriptFileName);
	while((nTrials <= MAX_TRIALS) && (status[i] < 0))
	  {
	    status[i] = rcuPtr[i]->ApplyReadoutRegion();     
	    nTrials ++;
	  }
	if( status[i] < 0 ){
	  initialized = FALSE;
	  std::cout<<" PhosModule::ArmTrigger() Warning, the active channel readout list was not set correctly "<<std::endl;
	}
	nTrials =0;
      }
   }
  if(initialized == FALSE)
    {
      std::cout<<" PhosModule::ArmTrigger() Warning, the active channel readout list was not set correctly "<<std::endl;
      std::cout<<" PhosModule::ArmTrigger() for at least one of the RCUs after 5 attempts, please check that the"<<std::endl;
      std::cout<<" PhosModule::ArmTrigger() feeserver is running and try to restart the GUI"<<std::endl;
    }
  if(initialized == TRUE)
    {
      std::cout<<"The readout configuration was apllied correctly to all RCUs"<<std::endl;
    }
}

//---------------------------------------------------------------------------
void   
PhosModule::EnableTrigger()
{
   for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->EnableTrigger();
    } 
}

//---------------------------------------------------------------------------
void
PhosModule::DisArmTrigger()
{
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->DisArmTrigger();
    }
}
//---------------------------------------------------------------------------
void
PhosModule::InitRcu()
{
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->InitRcu();
    }
}
//---------------------------------------------------------------------------
void
PhosModule::CheckFeeStatus()
{
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	rcuPtr[i]->CheckFeeStatus();
    }
}
//---------------------------------------------------------------------------
bool PhosModule::CheckFeeOnOff()
{
  bool status = true;
  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	status = status && rcuPtr[i]->CheckFeeOnOff();
    }
  return status;
}
//---------------------------------------------------------------------------
void
PhosModule::CreateRcu(char *serverName, int mId, int rcuId, int zCoord, int xCoord)
{
  char resultBuffer[100];
  rcuPtr[rcuId] = new Rcu(feeClientPtr, serverName, mId, rcuId, zCoord, xCoord);
  char fname[1024] = "s_setphosbit.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosModule::CreateRcu() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosModule::CreateRcu() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  feeClientPtr->ExecuteScript(fname, serverName, resultBuffer, 50);
} 

//---------------------------------------------------------------------------
void
PhosModule::ApplyApdSettings(char messageBuffer[RCUS_PER_MODULE][CARDS_PER_RCU][MAX_MESSAGE_LENGTH])
{
  for(int i=0; i< RCUS_PER_MODULE; i++)
    {
      if( rcuPtr[i] )
	  rcuPtr[i]->ApplyApdSettings(messageBuffer[i]);
    }
}

//---------------------------------------------------------------------------
void
PhosModule::ApplyConfiguration()
{
  mapperPtr->GenerateACL(startZ, endZ, startX, endX, moduleId, aclMaps, afls);
}

//---------------------------------------------------------------------------
void
PhosModule::ResetRcus()
{
  DisArmTrigger();
}

//---------------------------------------------------------------------------
void
PhosModule::SetReadoutRegion(int stZ, int eZ, int stX, int eX, char messageBuf[100])
{
  if( stZ >= PHOS_COLS || eZ > PHOS_COLS || stZ <0 || eZ < 0 || stX >= PHOS_ROWS || eX >= PHOS_ROWS || stX<0 || eX < 0)
    {
      sprintf(messageBuf, "ERROR, readout region is out of range");
    }
  else if(stZ > eZ || stX > eX)
    {
      sprintf(messageBuf, "ERROR, start coordinate must be less that end coordinate ");
    }
  else
    {
      startZ = stZ;
      endZ   = eZ;
      startX = stX;
      endX   = eX;
      sprintf(messageBuf, "Applying readout region");
   }
}

//---------------------------------------------------------------------------
