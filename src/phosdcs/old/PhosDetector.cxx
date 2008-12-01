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
#include <stdio.h>
#include <iostream>
#include "CommonDefs.h"

PhosDetector* PhosDetector::_instance = NULL;

//---------------------------------------------------------------------------
PhosDetector::PhosDetector()
{
  feeClientPtr = new PhosFeeClient();
  int i = PHOS_MODS;
  while( i-- )
    {
      phosModulePtr[i]=new PhosModule(feeClientPtr);
      phosModulePtr[i]->SetId(i);
    }
}
//---------------------------------------------------------------------------
PhosDetector::~PhosDetector()
{
  int i = PHOS_MODS;
  while( i-- )
    {
      if( phosModulePtr[i] )
	delete phosModulePtr[i];
    }
}
//---------------------------------------------------------------------------
PhosDetector* PhosDetector::GetInstance(){
  if(! _instance )
    _instance = new PhosDetector();
  return _instance;
}
//---------------------------------------------------------------------------
void
PhosDetector::ArmTrigger()
{
  char fname[1024] = "s_triggerconfig.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosDetector::ArmTrigger() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosDetector::ArmTrigger() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  ScriptCompiler::MakeTriggerConfigScript(fname, triggerType, triggerDelay, nPreSamples,  nSamples);
  for(int i=0; i<PHOS_MODS; i++)
    {
      if( phosModulePtr[i] )
	phosModulePtr[i]->ArmTrigger(fname);
    }
}

//---------------------------------------------------------------------------
void
PhosDetector::ArmTrigger(int moduleId)
{
  char fname[1024] = "s_triggerconfig.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosDetector::ArmTrigger() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosDetector::ArmTrigger() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  ScriptCompiler::MakeTriggerConfigScript(fname, triggerType, triggerDelay, nPreSamples, nSamples);
  phosModulePtr[moduleId]->ArmTrigger(fname);
}
//---------------------------------------------------------------------------
void
PhosDetector::LoadApdValues()
{
  for(int i = 0; i<PHOS_MODS; i++)
    {
      phosModulePtr[i]->LoadApdValues();
    }
}
//---------------------------------------------------------------------------
void
PhosDetector::SetAllApds(int Value)
{
  for(int i = 0; i<PHOS_MODS; i++)
    {
      phosModulePtr[i]->SetAllApds(Value);
    }
  ///set all APD values for the Detector to value
}


//---------------------------------------------------------------------------
void
PhosDetector::SetNSamples(int n)
{
  if( n < 0)
    {
      nSamples = 0;
    }

  else if(n > 1008)
    {
      nSamples = 1008;
    }
  else
    {
      nSamples=n;
    }
} 

//---------------------------------------------------------------------------
void
PhosDetector::SetNPreSamples(int n)
{
  if(n < 0)
    {
      nPreSamples = 0;
    }
  else if(n > 15)
    {
      nPreSamples = 15;
    }
  else
    {
      nPreSamples =n;
    }
}

//---------------------------------------------------------------------------
void 
PhosDetector::SetL2TriggerDelay(int n)
{
  if(n > MAX_TRIGGER_DELAY)
    {
      triggerDelay = MAX_TRIGGER_DELAY;
      printf("\nWarning: attempt to set triggerdelay to 0x%x:", n);
      printf("\nMax valu is 0x%x: \n", MAX_TRIGGER_DELAY);
      printf("\nTrigger delay was set to: 0x%x  RCU clock cycles\n",MAX_TRIGGER_DELAY);
    }
  else if(n < 4*(nSamples + nPreSamples))
    {
      printf("\nWarning: Trigger delay is set very low");
      printf("\nThe trigger delay should be at least 4 times samples + presamples");
      printf("\nTrigger delay wa set to: 0x%x  RCU clock cycles\n");
      n = triggerDelay;
    }
 
  else
    {
      triggerDelay = n;
    }

}
//---------------------------------------------------------------------------
