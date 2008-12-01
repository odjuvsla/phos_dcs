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

#include "FeeCard.h"
#include "CommonDefs.h"
#include "ScriptCompiler.h"
#include "PhosFeeClient.h"
#include <iostream>

using std::cout;
using std::endl;
//---------------------------------------------------------------------------
FeeCard::FeeCard()
{
  printf("Cannot call FeeCard without parameters\n");
}

//---------------------------------------------------------------------------
FeeCard::FeeCard(PhosFeeClient *fClientPtr, char *sName, int mod, int rcuId, int br, int cardIndex)
{
  feeClientPtr = fClientPtr;
  SetState(FEE_STATE_UNKNOWN);
  //apdInputPtr = 0; // Removed by H.Torii
  SetModule(mod);
  SetRcuId(rcuId);
  SetBranch(br);
  SetCardNumber(cardIndex); //remeber to add one because feecards starts counting at 1
  SetServerName(sName);
  sprintf(apdFilename,"%s/module%d_RCU%d_Branch%d_card%d.txt",APDVAL_BASE_PATH, mod, rcuId, br, cardNumber);
  std::cout<<" FeeCard::FeeCard() apdFilename = "<<apdFilename<<std::endl;
  //LoadApdValues(); // Skip load APD values from file here.. by H.Torii
}
//---------------------------------------------------------------------------
int* 
FeeCard::GetApdValues()
{
  return apdValue;
}


//---------------------------------------------------------------------------
void 
FeeCard::SetAllApds(int value)
{
  for(int i = 0; i < CSPS_PER_FEE; i++)
    {
      apdValue[i]= value;
    }
  SaveApdValues();
}

//---------------------------------------------------------------------------
int
FeeCard::ApplyApdSettings(char *messageBuffer)
{
  int apdStatus;
  int trials= 0;
  char resultBuffer[100];
  
  SaveApdValues();
  LoadApdValues();

  char fname_set[1024] = "s_setapd.txt";
  char fname_read[1024] = "s_readapd.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" FeeCard::ApplyApdSettings() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname_set); sprintf(fname_set,"%s",tmpname);
    sprintf(tmpname,"%s/%s",dir,fname_read); sprintf(fname_read,"%s",tmpname);
  }
  std::cout<<" FeeCard::ApplyApdSettings() ExecuteScript(\""<<fname_set<<"\")"<<std::endl;
  std::cout<<" FeeCard::ApplyApdSettings() ExecuteScript(\""<<fname_read<<"\")"<<std::endl;

  ScriptCompiler::MakeApdScript(fname_set, apdValue, branch, cardNumber);
  ScriptCompiler::MakeApdVerifyScript(fname_read, branch, cardNumber); 
  
  do
    {
      feeClientPtr->ExecuteScript(fname_set, feeServerName, resultBuffer, 0);
      apdStatus = feeClientPtr->VerifyApdValues(apdValue, feeServerName, fname_read);
      trials ++;
      
      if(apdStatus == APD_OK)
	{
	  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d = SUCCESS !!", \
		 feeServerName, branch, cardNumber, trials, apdStatus);
	}
      if(apdStatus == APD_DEAD)
	{
	  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d =NO response from FEE, please check that card is ON !!",\
		 feeServerName, branch, cardNumber, trials, apdStatus);
	}
      
      if(apdStatus == APD_ZERO)
	{
	  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d  =Cannot access RCU, check that DCS is master !!",\
		 feeServerName, branch, cardNumber, trials, apdStatus);
	}
      
      if(apdStatus == APD_CRAZY)
	{
	  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d  = Serious mailfunction in communication with the RCU, \
          check that the 1)feeserver is running 2)check ethernet cables  3)check that you can log into the DCS cards!!", \
		 feeServerName, branch, cardNumber, trials, apdStatus);
	}
      
     
      if(trials == MAX_TRIALS && (apdStatus != APD_OK))
	{
	  printf("\nWARNING Giving up on  %s, branch %d, card %d, after %d attemts\n", feeServerName, branch, cardNumber, trials);
	}
    }
      
  while(apdStatus != APD_OK  && trials < MAX_TRIALS);
  
  if(apdStatus == APD_OK)
    {
      sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..SUCCESS", feeServerName, cardNumber, branch);
    }
  else if(apdStatus == APD_DEAD)
    {
      sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 1: No response from FEE" ,feeServerName, cardNumber, branch);	  
    }
  else if(apdStatus == APD_ZERO)
    {
      sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 2: Cannot acsess RCU\n",feeServerName, cardNumber, branch);	 
    }          
  else if(apdStatus == APD_CRAZY)
    {
      sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 3: Readback values are crazy", feeServerName, cardNumber, branch);	 
    }
  
   return apdStatus;
}

//---------------------------------------------------------------------------
void 
FeeCard::LoadApdValues() //load default values from file
{
  FILE *fp=NULL;
  std::cout<<" FeeCard::LoadApdValues() Open file: "<<apdFilename<<std::endl;
  fp = fopen(apdFilename,"r");  
  if(fp==NULL)
    {
      std::cout<<" FeeCard::LoadApdValues() The file does not exist. Set default APD values = 512."<<std::endl;
      for(int i=0;i< CSPS_PER_FEE;i++)
      	{
	  apdValue[i]=512;
     	}
    }
  else 
    {
      for(int i=0; i<CSPS_PER_FEE; i++)
	{
	  fscanf(fp,"%d\n",&apdValue[i]);
	}
      fclose(fp);
    }
}

//---------------------------------------------------------------------------
void
FeeCard::SetApdValues(int values[CSPS_PER_FEE])
{
  for(int i = 0; i<CSPS_PER_FEE; i++)
    {
      apdValue[i] = values[i];
    }
  SaveApdValues();
}

//---------------------------------------------------------------------------
void
FeeCard::SaveApdValues()
{
  FILE *fp;
  fp = fopen(apdFilename,"w");

  for(int i=0;i< CSPS_PER_FEE;i++)
    {
      fprintf(fp,"%d\n", apdValue[i]);
    }
  fclose(fp);
}
//---------------------------------------------------------------------------

