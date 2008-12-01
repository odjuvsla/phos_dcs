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

#include <stdio.h>
#include <iostream>
#include "FeeCard.h"
#include "Rcu.h"
#include "ScriptCompiler.h"
#include "unistd.h"

using namespace dcs::fee;

//---------------------------------------------------------------------------
Rcu::Rcu()
{
  std::cout<<WHERE<<"You cannot create an RCU without parameters"<<std::endl;
}
//---------------------------------------------------------------------------
Rcu::Rcu(PhosFeeClient *feeClientPtr, const char *feeServerName, int mId, int rId, int z, int x)
{
  activeFeeList = 0;
  activeFeeRdoList = 0;
  SetFeeClientPtr(feeClientPtr); 
  SetFeeServerName(feeServerName); //set the feeServerName same as rcu name
  SetZCoord(z);
  SetXCoord(x);  
  SetRcuId(rId);
  SetModuleId(mId);
  InitFeeCards();
}
//---------------------------------------------------------------------------
Rcu::~Rcu()
{
  for(int i=0; i<32; i++)
    {
      if(feeCardPtr[i] != 0)
	{
	  delete feeCardPtr[i];
	  feeCardPtr[i]=0;
	}
    }
}
//---------------------------------------------------------------------------
int Rcu::ActivateFee(int branch, int cardIndex)
{
  std::cout<<WHERE<<" Activating branch "<<branch<<", card "<<cardIndex<<std::endl;
  int pcmversion;
  char resultBuffer[100];
  char fname[1024] = "s_activateFee.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::ActivateFee() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<WHERE<<"ExecuteScript(\""<<fname<<"\")"<<std::endl;
  ScriptCompiler::MakeActivateFeeScript(fname, activeFeeList, branch, cardIndex, TURN_ON);
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 70);
  sscanf(resultBuffer,"0x6000: %x", &pcmversion);

  std::cout<<" Rcu::ActivateFee() resultBuffer = "<<resultBuffer<<std::endl;
  std::cout<<" Rcu::ActivateFee() pcm version for fesserver "<<feeServerName<<", card: "<<cardIndex<<" at branch "<<branch
	   <<" is: 0x"<<std::hex<<pcmversion<<std::dec<<std::endl;

  int status;
  if(pcmversion == 0xffff)
      status = FEE_STATE_ERROR;
  else if(pcmversion == 0)
    status = DCS_NOT_MASTER;
  else if(pcmversion == PCMVERSION)
    status = FEE_STATE_ON;
  else if(pcmversion == OLD_PCMVERSION)
    status = FEE_STATE_WARNING;
  else
    status = UNKNOWN_PCMVERSION;
  std::cout<<WHERE<<" state = "<<status<<std::endl;
  feeCardPtr[branch*14+cardIndex]->SetState(status);
  return status;
}
//---------------------------------------------------------------------------
int Rcu:: DeActivateFee( int branch, int cardIndex)
{
  std::cout<<WHERE<<" DeActivating branch "<<branch<<", card "<<cardIndex<<std::endl;
  char resultBuffer[100];
  char fname[1024] = "s_activateFee.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::DeActivateFee() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::DeActivateFee() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  std::cout<<" Rcu::DeActivateFee() AFL = "<<std::hex<<activeFeeList<<std::dec<<std::endl;
  ScriptCompiler::MakeActivateFeeScript(fname,activeFeeList, branch, cardIndex, TURN_OFF);
  std::cout<<" Rcu::DeActivateFee() AFL = "<<std::hex<<activeFeeList<<std::dec<<std::endl;
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 70);
  feeCardPtr[branch*14+cardIndex]->SetState(FEE_STATE_OFF);
  return FEE_STATE_OFF;
}

//---------------------------------------------------------------------------
int Rcu::ToggleFeeOnOff(int branch, int cardNumber)
{
  printf("\nRcu::ToggleFeeOnOff; feestates = \n");
  for(int i=0; i < 28; i++)
    {
      //printf("%d  ",*feeState[i] ); //hoge
      printf("%d  ",feeState[i] );
      if(i == 13)
	{
	  printf("\n");
	} 
    }
  int state=0;
  char resBuffer[100];
  char message[100];
  int cardIndex = cardNumber - 1;

  if(cardNumber == 14)
    {
      ToggleFeeOnOff(branch, 1);
    }
  else if(cardNumber ==13)
    {
      ToggleFeeOnOff(branch, 2);  
    }

  else
    {
      // hoge
      if((feeState[branch*14 + cardIndex] == FEE_STATE_ON) || (feeState[branch*14 + cardIndex]== FEE_STATE_WARNING) || (feeState[branch*14 + cardIndex] == FEE_STATE_ERROR))
	{
	  feeState[branch*14+cardIndex] = DeActivateFee(branch, cardIndex);
	}
      else
	{
	  feeState[branch*14+cardIndex] = ActivateFee(branch, cardIndex); 
	}

      if(cardIndex == 0)
	{
	  if((feeState[branch*14 + 13] == FEE_STATE_ON) || (feeState[branch*14 + 13] == FEE_STATE_WARNING)|| (feeState[branch*14 + 13] == FEE_STATE_ERROR))
	    {
	      feeState[branch*14 + 13] = DeActivateFee(branch, 13);
	    }
	  
	  else
	    {
	      feeState[branch*14 + 13] = ActivateFee(branch, 13);
	    }
	}
 
      if(cardIndex == 1)
	{
	  if((feeState[branch*14+12] == FEE_STATE_ON) || (feeState[branch*14+12] == FEE_STATE_WARNING) || (feeState[branch*14+12] == FEE_STATE_ERROR))
	    {
	      feeState[branch*14+12] = DeActivateFee(branch, 12);
	    }
	  else
	    {
	      feeState[branch*14+12] = ActivateFee(branch, 12);
	    }
	}	
    }
  
  return state;
}

//---------------------------------------------------------------------------
void
Rcu::TurnOnAllFee(int *status)
{
  std::cout<<" Rcu::TurnOnAllFee() Turning on all frontend cards.. "<<std::endl;

  int tmpState;
  activeFeeList = feeClientPtr->ProbeActiveFeeList(feeServerName);

  for(unsigned long int i = 0; i<14; i++){
    std::cout<<" Rcu::TurnOnAllFee() Looping for i = "<<i<<std::endl;
    if( (activeFeeList & (1<<i)) == 0 ) {     
      //*feeState[i] =  ActivateFee(BRANCH_A, i); //hoge
      feeState[i] =  ActivateFee(BRANCH_A, i);
    }
    if( (activeFeeList & (1<<(i+16))) == 0 ) {     
      //*feeState[i+16] =  ActivateFee(BRANCH_A, i+16); //hoge
      //feeState[i+16] =  ActivateFee(BRANCH_A, i+16);  // feeState is <27, feeCardPtr is <32... non sense...
      feeState[i+14] =  ActivateFee(BRANCH_B, i);
    }
  }

  /*
  unsigned long int one = 1;
  unsigned long int two = 2;
 
  for(unsigned long int i = 0; i<14; i++)
    {
      if(i == 0 || i == 1)
	{
	  if((activeFeeList & (one<<(i+(unsigned long int)12)+one)) == 0)
	    {
	      *feeState[12+i] =  ActivateFee(BRANCH_A, 12+i);
	    } 
	}
      if((activeFeeList & (one<<(i + one))) == 0)
	{     
	  *feeState[i] =  ActivateFee(BRANCH_A, i);
	}
    }
  for(unsigned long int i = 14; i<28; i++)
    {
      if(i == 14 || i == 15)
	{
	  if((activeFeeList & (one << (i+(unsigned long int)12+two+one))) == 0)
	    {
	      *feeState[12 + i] = ActivateFee(BRANCH_B, i+12-CARDS_PER_BRANCH);
	    }
	} 
      if((activeFeeList & (one << (i+two+one))) == 0)
	{
	  *feeState[i] = ActivateFee(BRANCH_B, i - CARDS_PER_BRANCH);
	}
    }

  */
}

//---------------------------------------------------------------------------
void
Rcu::TurnOffAllFee(int *status)
{
  std::cout<<" Rcu::TurnOffAllFee() Turning OFF all FEE "<<std::endl;
  activeFeeList = feeClientPtr->ProbeActiveFeeList(feeServerName);

  for(unsigned long int i = 0; i<14; i++){
    std::cout<<" Rcu::TurnOffAllFee() activeFeeList = "<<std::hex<<activeFeeList<<std::dec<<std::endl;
    std::cout<<" Rcu::TurnOffAllFee() Looping for i = "<<i<<std::endl;
    if( (activeFeeList & (1<<i)) != 0 ) {
      //*feeState[i] =  DeActivateFee(BRANCH_A, i); //hoge
      feeState[i] =  DeActivateFee(BRANCH_A, i);
    }
    if( (activeFeeList & (1<<(i+16))) != 0 ) {
      //*feeState[i+16] =  DeActivateFee(BRANCH_A, i+16);//hoge
      //feeState[i+16] =  DeActivateFee(BRANCH_A, i+16);
      feeState[i+14] =  DeActivateFee(BRANCH_B, i);
    }
  }

  for(int i =0; i<CARDS_PER_RCU; i++)
    {
      //*feeState[i] = FEE_STATE_OFF; //hoge
      feeState[i] = FEE_STATE_OFF;
    }

  /* 
  unsigned long int one = 1;
  unsigned long int two = 2;
  for(unsigned long int i = 0; i<14; i++)
    {
      if(i == 0 || i == 1)
	{  
	  
	  if((activeFeeList & (one<<(i+(unsigned long int)12)+one)) != 0)
	    {
	      *feeState[12+i] = DeActivateFee(BRANCH_A, i+12);
	    }
	}

      if((activeFeeList & (one<<(i + one))) != 0)
	{ 
	  *feeState[i] = DeActivateFee(BRANCH_A, i);
	}
    }
  
  for(unsigned long i=14; i<28; i++)
    {
      if(i == 14 || i == 15)
	{  
	  if((activeFeeList & (one << (i+(unsigned long int)12+two+one))) != 0)
	    {	  
	      *feeState[i+12] =  DeActivateFee(BRANCH_B, 12+i);
	    }
	} 
      if((activeFeeList & (one << (i+two+one))) != 0)
	{
	  *feeState[i] = DeActivateFee(BRANCH_B, i - CARDS_PER_BRANCH);
	} 
    }

  for(int i =0; i<CARDS_PER_RCU; i++)
    {
      *feeState[i] = FEE_STATE_OFF;
    }

  */
}

//---------------------------------------------------------------------------
void
Rcu::SetReadoutRegion(unsigned long int afl, int acl[256])
{
  int i = 256;
  while( i-- )
    activeChList[i] = acl[i];
  activeFeeRdoList = afl;
}

//---------------------------------------------------------------------------
int
Rcu::ApplyReadoutRegion()
{
  int nRetrys=0;
  char resultBuffer[1585];
  activeFeeRdoList = 0;
  char fname[1024];
  sprintf(fname, "s_rdoconf_%s.txt", feeServerName);
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::ApplyReadoutRegion() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::ApplyReadoutRegion() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  ScriptCompiler::MakeReadouRegionScript(fname, activeFeeRdoList, activeChList); 
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 1585);

  int status = VerifyAcl(activeChList, resultBuffer);
  
  if(status > 0)
    {
      std::cout<<" Rcu::ApplyReadoutRegion() The activre channel list was set correctly for "
	       <<feeServerName<<" status = "<<status<<std::endl;
    }
  else if(status < 0)
    {
      std::cout<<" Rcu::ApplyReadoutRegion() WARNING:Active channel list was not set correctly for "
	       <<feeServerName<<" status = "<<status<<std::endl;
   }
  return status;
}

//---------------------------------------------------------------------------
void
Rcu::ArmTrigger(char *fileName)
{
  std::cout<<" Rcu::ArmTrigger() Arming trigger for server: "<<feeServerName<<std::endl;
  char resultBuffer[50];
  feeClientPtr->ExecuteScript(fileName, feeServerName, resultBuffer, 50);
}

//---------------------------------------------------------------------------
void
Rcu::EnableTrigger()
{
  char resultBuffer[50];
  char fname[1024] = "s_enabletrigger.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::EnableTrigger() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::EnableTrigger() ExecuteScript(\""<<fname<<"\")"<<std::endl;

  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 50);
  std::cout<<" Rcu::EnableTrigger() Enable trigger for server: "<<feeServerName<<" ...... Done ! "<<std::endl;
}

//---------------------------------------------------------------------------
void
Rcu::DisArmTrigger()
{
  char resultBuffer[50];
  char message[100];
  char fname[1024] = "s_disarmtrigger.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::DisArmTrigger() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::DisArmTrigger() Disarm Trigger on feeserver:"<<feeServerName<<std::endl;
  std::cout<<" Rcu::DisArmTrigger() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 50);
  std::cout<<" Rcu::DisArmTrigger() ..... Done "<<std::endl;
}

//---------------------------------------------------------------------------
unsigned long 
Rcu::CheckFeeStatus()
{
  activeFeeList = feeClientPtr->CheckFeeStatus(feeState,  feeServerName);
  printf("\nRcu::CheckFeeStaus, activeFeeList = 0x%x\n", activeFeeList);
  int nn = CARDS_PER_RCU;
  while( nn-- ){
    feeCardPtr[nn]->SetState(feeState[nn]);
  }
  return activeFeeList;
}
//---------------------------------------------------------------------------
bool Rcu::CheckFeeOnOff()
{
  return 0; //off
  //return 1; // on
}

//---------------------------------------------------------------------------
unsigned long 
Rcu::GetActiveFeeList()
{
  return activeFeeList;
}
//---------------------------------------------------------------------------
void
Rcu::InitRcu()
{
  char resultBuffer[50];
  char fname[1024] = "s_initrcu.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::InitRcu() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::InitRcu() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 50);
  std::cout<<" Rcu::InitRcu() Initializing: "<<feeServerName<<" ...... Done ! "<<std::endl;
}

//---------------------------------------------------------------------------
void
Rcu::ResetRcu()
{
  char resultBuffer[50];
  char fname[1024] = "s_resetrcu.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" Rcu::ResetRcu() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" Rcu::ResetRcu() ExecuteScript(\""<<fname<<"\")"<<std::endl;
  feeClientPtr->ExecuteScript(fname, feeServerName, resultBuffer, 50);
  char message[100];    
  sprintf(message, "Resetting server: %s  ...... Done ! ", feeServerName);
  //MainGui::DisplayMessage(message);    // Removed by H.Torii
  std::cout<<message<<std::endl;
}
//---------------------------------------------------------------------------
FeeCard * 
Rcu::GetFeeCardPtr(int index)
{
  return feeCardPtr[index];
}

//---------------------------------------------------------------------------
void
Rcu::InitFeeCards()
{
  for(int i = 0; i < CARDS_PER_BRANCH; i++) // for(int i = 0; i <= CARDS_PER_BRANCH; i++) modified by H.Torii
    {
      feeCardPtr[i] = new FeeCard(feeClientPtr, feeServerName, moduleId, rcuId, BRANCH_A, i);
      feeCardPtr[i]->SetRcuZ(zCoord);
      feeCardPtr[i]->SetRcuX(xCoord);		 
      feeState[i] = feeCardPtr[i]->GetState();
    } 

  for(int i = 0; i < CARDS_PER_BRANCH; i++) // for(int i = 0; i <= CARDS_PER_BRANCH; i++) modified by H.Torii
    {
      feeCardPtr[i+CARDS_PER_BRANCH] = new FeeCard(feeClientPtr, feeServerName, moduleId, rcuId, BRANCH_B, i);
      feeCardPtr[i+CARDS_PER_BRANCH]->SetRcuZ(zCoord);
      feeCardPtr[i+CARDS_PER_BRANCH]->SetRcuX(xCoord);
      feeState[i+CARDS_PER_BRANCH] = feeCardPtr[i+CARDS_PER_BRANCH]->GetState(); 
    } 
}

//---------------------------------------------------------------------------
void
Rcu::LoadApdValues()
{
   for(int i=0; i<CARDS_PER_RCU; i++)
    {
      feeCardPtr[i]->LoadApdValues();
    }
}

//---------------------------------------------------------------------------
int
Rcu::ApplyApdSettings(char messageBuffer[CARDS_PER_RCU][MAX_MESSAGE_LENGTH])
{
  
  for(int i=0; i<CARDS_PER_RCU;i++)
    {
      feeCardPtr[i]->ApplyApdSettings(messageBuffer[i]);
    }
}

//---------------------------------------------------------------------------
char* 
Rcu::GetFeeServerName()
{
  return feeServerName; 
}


//---------------------------------------------------------------------------
void
Rcu::SetAllApds(int apdVal)
{
  for(int i=0; i< 28; i++)
    {
      if(feeCardPtr[i] != 0)
	{
	  feeCardPtr[i]->SetAllApds(apdVal);
	}
      else
	{
	  printf("\nApdInputPtr is ZERO\n");
	}
    }
}

//---------------------------------------------------------------------------
void
Rcu::SetFeeClientPtr(PhosFeeClient *fcPtr)
{
  feeClientPtr=fcPtr;
}

//---------------------------------------------------------------------------
void
Rcu::SetFeeServerName(const char *name)
{
  feeServerName[sprintf(feeServerName,"%s",name)] = 0;
  std::cout<<" Rcu::SetFeeServerName() ServerName was set to: "<<feeServerName<<std::endl; 
  feeClientPtr->registerFeeServerName(feeServerName); 
}
//---------------------------------------------------------------------------
int
Rcu::VerifyAcl(int acl[256], char *resultBuffer)
{
  int status = 1;
  unsigned int r[256];
  char formatString[2000] =
"0x6400: %x %x %x %x
0x6404: %x %x %x %x
0x6408: %x %x %x %x
0x640c: %x %x %x %x
0x6410: %x %x %x %x
0x6414: %x %x %x %x
0x6418: %x %x %x %x
0x641c: %x %x %x %x
0x6420: %x %x %x %x
0x6424: %x %x %x %x
0x6428: %x %x %x %x
0x642c: %x %x %x %x
0x6430: %x %x %x %x
0x6434: %x %x %x %x
0x6438: %x %x %x %x
0x643c: %x %x %x %x
0x6440: %x %x %x %x
0x6444: %x %x %x %x
0x6448: %x %x %x %x
0x644c: %x %x %x %x
0x6450: %x %x %x %x
0x6454: %x %x %x %x
0x6458: %x %x %x %x
0x645c: %x %x %x %x
0x6460: %x %x %x %x
0x6464: %x %x %x %x
0x6468: %x %x %x %x
0x646c: %x %x %x %x
0x6470: %x %x %x %x
0x6474: %x %x %x %x
0x6478: %x %x %x %x
0x647c: %x %x %x %x
0x6480: %x %x %x %x
0x6484: %x %x %x %x
0x6488: %x %x %x %x
0x648c: %x %x %x %x
0x6490: %x %x %x %x
0x6494: %x %x %x %x
0x6498: %x %x %x %x
0x649c: %x %x %x %x
0x64a0: %x %x %x %x
0x64a4: %x %x %x %x
0x64a8: %x %x %x %x
0x64ac: %x %x %x %x
0x64b0: %x %x %x %x
0x64b4: %x %x %x %x
0x64b8: %x %x %x %x
0x64bc: %x %x %x %x
0x64c0: %x %x %x %x
0x64c4: %x %x %x %x
0x64c8: %x %x %x %x
0x64cc: %x %x %x %x
0x64d0: %x %x %x %x
0x64d4: %x %x %x %x
0x64d8: %x %x %x %x
0x64dc: %x %x %x %x
0x64e0: %x %x %x %x
0x64e4: %x %x %x %x
0x64e8: %x %x %x %x
0x64ec: %x %x %x %x
0x64f0: %x %x %x %x
0x64f4: %x %x %x %x
0x64f8: %x %x %x %x
0x64fc: %x %x %x %x";

    /*
  strcat(formatString, "0x6400: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6404: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6408: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x640c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6410: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6414: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6418: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x641c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6420: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6424: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6428: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x642c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6430: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6434: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6438: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x643c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6440: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6444: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6448: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x644c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6450: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6454: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6458: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x645c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6460: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6464: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6468: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x646c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6470: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6474: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6478: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x647c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6480: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6484: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6488: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x648c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6490: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6494: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x6498: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x649c: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64a0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64a4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64a8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64ac: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64b0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64b4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64b8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64bc: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64c0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64c4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64c8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64cc: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64d0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64d4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64d8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64dc: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64e0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64e4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64e8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64ec: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64f0: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64f4: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64f8: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "0x64fc: %x %x %x %x\n");
  strcat(formatString+strlen(formatString), "\0");

    */
    
  //std::cout<<" Rcu::Verify() DEBUG--------------------------- "<<std::endl;
  //std::cout<<formatString<<std::endl;
  //std::cout<<" Rcu::Verify() DEBUG--------------------------- "<<std::endl;
  
  int nMatch=sscanf(resultBuffer, formatString,
		    &r[0],  &r[1],  &r[2],  &r[3],
		    &r[4],  &r[5],  &r[6],  &r[7],
		    &r[8],  &r[9],  &r[10], &r[11],
		    &r[12], &r[13], &r[14], &r[15],
		    &r[16], &r[17], &r[18], &r[19],
		    &r[20], &r[21], &r[22], &r[23], 
		    &r[24], &r[25], &r[26], &r[27], 
		    &r[28], &r[29], &r[30], &r[31],
		    &r[32], &r[33], &r[34], &r[35],
		    &r[36], &r[37], &r[38], &r[39],
		    &r[40], &r[41], &r[42], &r[43],
		    &r[44], &r[45], &r[46], &r[47],
		    &r[48], &r[49], &r[50], &r[51],
		    &r[52], &r[53], &r[54], &r[55], 
		    &r[56], &r[57], &r[58], &r[59], 
		    &r[60], &r[61], &r[62], &r[63],
		    &r[64], &r[65], &r[66], &r[67],
		    &r[68], &r[69], &r[70], &r[71],
		    &r[72], &r[73], &r[74], &r[75],
		    &r[76], &r[77], &r[78], &r[79],
		    &r[80], &r[81], &r[82], &r[83],
		    &r[84], &r[85], &r[86], &r[87], 
		    &r[88], &r[89], &r[90], &r[91], 
		    &r[92], &r[93], &r[94], &r[95],
		    &r[96], &r[97], &r[98], &r[99],
		    &r[100], &r[101], &r[102], &r[103],
		    &r[104], &r[105], &r[106], &r[107],
		    &r[108], &r[109], &r[110], &r[111],
		    &r[112], &r[113], &r[114], &r[115],
		    &r[116], &r[117], &r[118], &r[119], 
		    &r[120], &r[121], &r[122], &r[123], 
		    &r[124], &r[125], &r[126], &r[127],
		    &r[128], &r[129], &r[130], &r[131],
		    &r[132], &r[133], &r[134], &r[135],
		    &r[136], &r[137], &r[138], &r[139],
		    &r[140], &r[141], &r[142], &r[143],
		    &r[144], &r[145], &r[146], &r[147],  
		    &r[148], &r[149], &r[150], &r[151], 
		    &r[152], &r[153], &r[154], &r[155], 
		    &r[156], &r[157], &r[158], &r[159],
		    &r[160], &r[161], &r[162], &r[163],
		    &r[164], &r[165], &r[166], &r[167],
		    &r[168], &r[169], &r[170], &r[171],
		    &r[172], &r[173], &r[174], &r[175],
		    &r[176], &r[177], &r[178], &r[179],
		    &r[180], &r[181], &r[182], &r[183], 
		    &r[184], &r[185], &r[186], &r[187], 
		    &r[188], &r[189], &r[190], &r[191],
		    &r[192], &r[193], &r[194], &r[195],
		    &r[196], &r[197], &r[198], &r[199],
		    &r[200], &r[201], &r[202], &r[203],
		    &r[204], &r[205], &r[206], &r[207],
		    &r[208], &r[209], &r[210], &r[211],
		    &r[212], &r[213], &r[214], &r[215], 
		    &r[216], &r[217], &r[218], &r[219], 
		    &r[220], &r[221], &r[222], &r[223],
		    &r[224], &r[225], &r[226], &r[227],
		    &r[228], &r[229], &r[230], &r[231],
		    &r[232], &r[233], &r[234], &r[235],
		    &r[236], &r[237], &r[238], &r[239],
		    &r[240], &r[241], &r[242], &r[243],
		    &r[244], &r[245], &r[246], &r[247], 
		    &r[248], &r[249], &r[250], &r[251], 
		    &r[252], &r[253], &r[254], &r[255]);

  for(int i=0; i <256; i++)
    {
      if(acl[i] != r[i])    
	{
	  std::cout<<" Rcu::VerifyAcl() WARNING: Active channel list is not set properly : acl["<<i<<"] = 0x"
		   <<std::hex<<acl[i]<<std::dec
		   <<",  r["<<i<<"] = 0x"<<std::hex<<r[i]<<std::dec<<std::endl;
	  status = -1;
	}
    }
  return status;
}
//---------------------------------------------------------------------------
