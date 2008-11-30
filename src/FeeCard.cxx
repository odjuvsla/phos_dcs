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
#include "BCRegisterMap.h"
#include "FeeCard.h"
#include "ScriptCompiler.h"
#include "PhosFeeClient.h"
//#include <iostream>
using namespace BCRegisterMap;


FeeCard::FeeCard() :PhosDcsBase(), 
		    fPcmVersion(999), 
		    fIsInitialized(false), 
		    fApdBaseAddress(0x68), 
		    fDisableHamming(true), 
		    fIsDisabledHamming(true),
		    module(99),
		    rcuId(99),
		    branch(99),
		    cardNumber(99)
{
  

}
  

FeeCard::FeeCard(PhosFeeClient *fClientPtr, char *sName, const int mod, const int rId, const int br, const int cardIndex) :PhosDcsBase(), 
															   fPcmVersion(0), 
															   fIsInitialized(false), 
															   fApdBaseAddress(0x68), 
															   fDisableHamming(true), 
															   fIsDisabledHamming(true),
															   module(mod),
															   rcuId(rId),
															   branch(br),
															   cardNumber(cardIndex)
{
  Reset(apdFilename, 200);
  Reset(apdValue,  CSPS_PER_FEE); 
  feeClientPtr = fClientPtr;
  SetState(FEE_STATE_UNKNOWN);
  SetServerName(sName);
  sprintf(apdFilename,"%s/module%d_RCU%d_Branch%d_card%d.txt",fSandboxFolder, mod, rcuId, br, cardNumber);
  LoadApdValues();
  
  for(int i=0; i< CSPS_PER_FEE; i++)
    {
      apdVerify[i] = true;
    }

}

 
unsigned long*  
FeeCard::GetApdValues()
{
  //  cout << "FeeCard::GetApdValues(), module =  "<<  module << "  rcu = " << rcuId << "  branch= "<< branch << "cardNumber = "<< cardNumber    << endl;
  return apdValue;
}


void 
FeeCard::SetAllApds(int value)
{
  for(int i = 0; i < CSPS_PER_FEE; i++)
    {
      apdValue[i]= value;
    }
  SaveApdValues();
}


int
FeeCard::ApplyApdSettings(char *messageBuffer)
{
  if(fIsInitialized == true)

    {
      int apdStatus = 0;
      int trials= 0;
      char resultBuffer[1024];
      SaveApdValues();
      LoadApdValues();

      if((currentState == FEE_STATE_ON) || (currentState == FEE_STATE_WARNING) )
      	{

	  do
	    {
	      
	      feeClientPtr->SetScripFileName("s_apdrw.txt");
	      apdStatus = feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, crystAdress, apdValue, apdVerify, CSPS_PER_FEE, branch, cardNumber); 
	      unsigned long tmpvalue = 0x0;
	      unsigned long tmpaddress = 0x1e;
	      bool tmpverify = false;
	      cout << "FeeCard::ApplyApd: apdStatus = " << apdStatus << endl;
	      for(int i = 0; i < 32; i++)
		//cout << "FeeCard::ApplyApdSettings: value = " << hex << apdValue[i] << dec << endl;
		

	      //    apdStatus = feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);
	      feeClientPtr->SetScripFileName("s_exec_apd.txt");
	      //	      feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);

	      trials ++;
      
	      if(apdStatus == REG_OK)
		{
		  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d = SUCCESS !!\n", \
			 feeServerName, branch, cardNumber, trials, apdStatus);
		  sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..SUCCESS", feeServerName, cardNumber, branch);
		}
	      else if(apdStatus == REG_DEAD)
		{
		  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d =NO response from FEE, please check that card is ON !!\n",\
			 feeServerName, branch, cardNumber, trials, apdStatus);
		  sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 1: No response from FEE" ,feeServerName, cardNumber, branch);  
		}
      
	      else if(apdStatus == REG_ZERO)
		{
		  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d  =Cannot access RCU, check that DCS is master !!\n",\
			 feeServerName, branch, cardNumber, trials, apdStatus);
		  sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 2: Cannot acsess RCU\n",feeServerName, cardNumber, branch);	 	  
		}
      
	      else if(apdStatus == REG_CRAZY)
		{
		  printf("\nApllying APD values to  %s, branch %d, card %d, trials = %d, status = %d  = Serious mailfunction in communication with the RCU, \
          check that the 1)feeserver is running 2)check ethernet cables  3)check that you can log into the DCS cards\n!!", \
			 feeServerName, branch, cardNumber, trials, apdStatus);
		  sprintf(messageBuffer, "applying APD values for %s card%d at branch%d ..ERROR 3: Readback values are crazy", feeServerName, cardNumber, branch);	   
		}
      
	      else
		{
		  printf("three quarks for muster mark ..oops. something is very wrong, consult a psyciatrist\n", feeServerName, cardNumber, branch);
		  sprintf(messageBuffer, "three quarks for muster mark ..oops. something is very wrong, consult a psyciatrist", feeServerName, cardNumber, branch);
		}


	      if(trials == MAX_TRIALS && (apdStatus != REG_OK))
		{
		  printf("\nWARNING Giving up on  %s, branch %d, card %d, after %d attemts\n", feeServerName, branch, cardNumber, trials);
		  sprintf(messageBuffer, "Puh !!, and then DCS said, giving up on  %s, branch %d, card %d, after %d attemt ", feeServerName, branch, cardNumber, trials);
		}
	    }
	  while(apdStatus != REG_OK  && trials < MAX_TRIALS);

	  cout << "FeeCard::ApplyApd: apdStatus = " << apdStatus << endl;
	  
	  unsigned long tmpvalue = 0x0;
	  unsigned long tmpaddress = 0x1e;
	  bool tmpverify = false;
  
	  feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);
	  return apdStatus;
	}

      else
	{
	  sprintf(messageBuffer, "ERROR;  %s, branch %d, card %d,  is either not turned on or in error",  feeServerName, branch, cardNumber);
	}
    }
  else
    {
      printf("\nFeeCard::ApplyApdSetting FATAL ERROR, the card is not initialized in software APD registermap is unknown\n");
      sprintf(messageBuffer, "ERROR;  %s, branch %d, card %d,  is not intialized in software, card hasnt been on after apdgui was started",  feeServerName, branch, cardNumber); 
    }

  unsigned long tmpvalue = 0x0;
  unsigned long tmpaddress = 0x1e;
  bool tmpverify = false;
  
  feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);
  
} 


void 
FeeCard::LoadApdValues() //load default values from file
{
  FILE *fp=NULL;

  if(CheckFile(apdFilename,"r") == NO_EXIST)
    {
      printf("The file does not exist, loading default APD values = 512 for all entries, and trying to making new file......\n");
      
      if(CheckFile(apdFilename,"w") == NO_EXIST)
	{
	  cout << "ERROR from FeeCard::LoadApdValues(), couldnt make file  " << apdFilename << endl;
	}
      else
	{
	  fp = fopen(apdFilename,"w");
	  for(int i=0;i< CSPS_PER_FEE;i++)
	    {
	      apdValue[i]=DEFAULT_APD_DAC_VALUE;
	      fprintf(fp, "%d", apdValue[i]);
	    }
	  fclose(fp);
	} 
    }
  else if(CheckFile(apdFilename,"r") == EXIST ) 
    {
      fp = fopen(apdFilename,"r"); 
 
      for(int i=0; i < CSPS_PER_FEE; i++)
	{
	  fscanf(fp,"%d\n",&apdValue[i]);
	  // cout << "FeeCard::LoadApdValues: apdValue: " << apdValue[i] << endl;
	}
     fclose(fp);
    }
}



void
FeeCard::SetApdValues(const unsigned long int values[CSPS_PER_FEE])
{
  for(int i = 0; i < CSPS_PER_FEE; i++) 
    {
      apdValue[i] = values[i];
    }
  SaveApdValues();
}


void
FeeCard::SaveApdValues()
{
  FILE *fp;
  if(CheckFile (apdFilename,"w") == EXIST)
    {
      fp = fopen(apdFilename,"w");
      for(int i=0;i< CSPS_PER_FEE;i++)
	{
	  fprintf(fp,"%d\n", apdValue[i]);
	}
      fclose(fp);
    }
}


void 
FeeCard::SetState(int state)
{
  currentState = state;
}


int* 
FeeCard::GetState()
{
  return &currentState;
}


void 
FeeCard::SetServerName(char *sName)
{
  feeServerName=sName;
}


int 
FeeCard::GetBranch()
{
  return branch;
}


int 
FeeCard::GetCardNumber()
{
  return cardNumber;
}


void 
FeeCard::SetPcmversion(unsigned long  pcmversion)
{ 
  /** 
   * we need to know the pcm version befor 
   * the mapping can be initialized since different
   * version of the board controller has different mappings
  **/
  fPcmVersion = pcmversion;
 
  if(fPcmVersion <31)
    {
      fApdBaseAddress = 0x40;
    }

  else
    {
      fApdBaseAddress = 0x60;
      if( (fDisableHamming == true) &&  (fIsDisabledHamming == false) )
	{
	  DisableHamming();
	}
    }
  
  if(fIsInitialized == false)
    {
      InitMapping();
      fIsInitialized = true;
    }
  
}


void
FeeCard::DisableHamming()
{
  unsigned long tmpReg = CSR2;
  unsigned long tmpVal = 0x13F;
  bool tmpVerify = true;
  feeClientPtr->WriteReadRegisters(REGTYPE_BC, feeServerName, &tmpReg, &tmpVal, &tmpVerify, 1, branch, cardNumber);
}


void
FeeCard::InitMapping()
{
  //  scriptAdress=DCS_BASEADRESS;
 
  for(int i=0; i< CSPS_PER_FEE; i++)
    {
      crystAdress[i] = HV_DAC_settings[i];  
    }


  /*
  crystAdress[0] =  fApdBaseAddress +8;
  crystAdress[1] =  fApdBaseAddress +7;

  crystAdress[2] =  fApdBaseAddress +9;
  crystAdress[3] =  fApdBaseAddress +6;

  crystAdress[4] =  fApdBaseAddress +0xa;
  crystAdress[5] =  fApdBaseAddress +5;

  crystAdress[6] =  fApdBaseAddress +0xb;
  crystAdress[7] =  fApdBaseAddress +4;

  crystAdress[8] =  fApdBaseAddress +0xc;
  crystAdress[9] =  fApdBaseAddress +3;

  crystAdress[10] =  fApdBaseAddress +0xd;
  crystAdress[11] =  fApdBaseAddress +2;

  crystAdress[12] =  fApdBaseAddress +0xe;
  crystAdress[13] =  fApdBaseAddress +1;

  crystAdress[14] =  fApdBaseAddress +0xf;
  crystAdress[15] =  fApdBaseAddress +0;

  crystAdress[16] =  fApdBaseAddress +0x10;
  crystAdress[17] =  fApdBaseAddress +0x1f;

  crystAdress[18] =  fApdBaseAddress +0x11;
  crystAdress[19] =  fApdBaseAddress +0x1e;

  crystAdress[20] =  fApdBaseAddress +0x12;
  crystAdress[21] =  fApdBaseAddress +0x1d;

  crystAdress[22] =  fApdBaseAddress +0x13;
  crystAdress[23] =  fApdBaseAddress +0x1c;

  crystAdress[24] =  fApdBaseAddress +0x14;
  crystAdress[25] =  fApdBaseAddress +0x1b;

  crystAdress[26] =  fApdBaseAddress +0x15;
  crystAdress[27] =  fApdBaseAddress +0x1a;

  crystAdress[28] =  fApdBaseAddress +0x16;
  crystAdress[29] =  fApdBaseAddress +0x19;

  crystAdress[30] =  fApdBaseAddress +0x17;
  crystAdress[31] =  fApdBaseAddress +0x18;
  */

}//end Init()


