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
#include "PhosDcsLogging.h"
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
  feeModuleNumber = mod;
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
FeeCard::ApplyApdSettings()
{
  stringstream log;
  if(fIsInitialized == true)
    //if(1)

    {
      int apdStatus = 0;
      int trials= 0;
      char resultBuffer[1024];
      SaveApdValues();
      LoadApdValues();
   
      //if((currentState == FEE_STATE_ON) || (currentState == FEE_STATE_WARNING) )
      if(1)
	{
	  do
	    {
	      
	      feeClientPtr->SetScripFileName("s_apdrw.txt");
	      apdStatus = feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, crystAdress, apdValue, apdVerify, CSPS_PER_FEE, branch, cardNumber); 
	      unsigned long tmpvalue = 0x0;
	      unsigned long tmpaddress = 0x1e;
	      bool tmpverify = false;
	      log.str();
	      log << "FeeCard::ApplyApdSetting: apdStatus = " << apdStatus;
	      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);
	      for(int i = 0; i < 32; i++)
		//cout << "FeeCard::ApplyApdSettings: value = " << hex << apdValue[i] << dec << endl;
		

	      //    apdStatus = feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);
	      feeClientPtr->SetScripFileName("s_exec_apd.txt");
	      //	      feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);

	      trials ++;
      
	      if(apdStatus == REG_OK)
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: Applying APD values to " << feeServerName << ", branch " << branch << ", card " << cardNumber << ", trials " << trials << ", status = " << apdStatus << " = SUCCESS";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
		}
 	      else if(apdStatus == REG_DEAD)
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: Applying APD values to " << feeServerName << ", branch " << branch << ", card " << cardNumber << ", trials " << trials << ", status = " << apdStatus << " = NO response from FEE, please check that card is ON";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_WARNING);
		}
      
	      else if(apdStatus == REG_ZERO)
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: Applying APD values to " << feeServerName << ", branch " << branch << ", card " << cardNumber << ", trials " << trials << ", status = " << apdStatus << " = Cannot access RCU, check that DCS is master";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_WARNING);
		}
      
	      else if(apdStatus == REG_CRAZY)
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: Applying APD values to " << feeServerName << ", branch " << branch << ", card " << cardNumber << ", trials " << trials << ", status = " << apdStatus << " = Serious mailfunction in communication with the RCU";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_WARNING);
		}
      
	      else
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: three quarks for muster mark ..oops. something is very wrong, consult a psyciatrist";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_WARNING);
		}


	      if(trials == MAX_TRIALS && (apdStatus != REG_OK))
		{
		  log.str("");
		  log << "FeeCard::ApplyApdSetting: Giving up on " << feeServerName << ", branch " << branch << ", card " << cardNumber << ", after " << trials << " attemts\n";
		  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
		}
	    }
	  while(apdStatus != REG_OK  && trials < MAX_TRIALS);

	  unsigned long tmpvalue = 0x0;
	  unsigned long tmpaddress = 0x1e;
	  bool tmpverify = false;
  
	  feeClientPtr->WriteReadRegisters( REGTYPE_BC , feeServerName, &tmpaddress, &tmpvalue, &tmpverify, 1, branch, cardNumber);
	  return apdStatus;
	}

      else
	{
	  log.str("");
	  log << "FeeCard::ApplyApdSetting: " << feeServerName << ", branch " << branch << ", card " << cardNumber << " is either not turned on or in error";
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
	}
    }
  else
    {
      log.str("");
      log << "FeeCard::ApplyApdSetting: the card is not initialized in software APD registermap is unknown";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
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
      PhosDcsLogging::Instance()->Logging(string("Rcu::LoadApdValues: The file does not exist, loading default APD values = 512 for all entries, and trying to making new file......\n"), LOG_LEVEL_VERBOSE);
      
      if(CheckFile(apdFilename,"w") == NO_EXIST)
	{
	  PhosDcsLogging::Instance()->Logging(string("Rcu::LoadApdValues: Could not create file for APD values"), LOG_LEVEL_ERROR);
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
      stringstream log;
      log.str("");
      log << "FeeCard::LoadApdValues: Loading APD values from file: " << apdFilename << endl;
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);

 
      for(int i=0; i < CSPS_PER_FEE; i++)
	{
	  fscanf(fp,"%d\n",&apdValue[i]);
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

  if(feeModuleNumber == 4)
    {
      cout << "Initialising module 4" << endl;
      for(int i=0; i< CSPS_PER_FEE; i++)
	{
	  crystAdress[i] = HV_DAC_settings[i];  
	}
    }
  else
    {
      cout << "Initialising module " << feeModuleNumber << endl;
      for(int i=0; i< CSPS_PER_FEE; i++)
	{
	  crystAdress[i] = HV_DAC_settings_mod_2_3[i];  
	}
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


