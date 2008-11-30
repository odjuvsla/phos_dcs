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

#include "ScriptCompiler.h"
#include "PhosFeeClient.h"
//#include "MainGui.h"     // Removed by H.Torii
#include "CommonDefs.h"
#include <vector>
#include <string>
#include <iostream>
#include "unistd.h"

using std::vector;

PhosFeeClient::PhosFeeClient()
{
  scriptCompilerPtr = new ScriptCompiler();
}

PhosFeeClient::~PhosFeeClient()
{
  delete scriptCompilerPtr;
}

void
PhosFeeClient::ExecuteScript(const char *scriptFilename, const char *feeServerName, char *resultBuffer, int N)
{
 
  vector<unsigned int> data;
  data.resize(2000);
  char* charData=(char*)&data[0];  
  FILE *fp;
  fp=fopen(scriptFilename, "r");
  if( fp == NULL ){
    std::cout<<" PhosFeeClient::ExecuteScript().. No such a file: "<<scriptFilename<<std::endl;
    return;
  }

  int cnt=0;
  char tmp=fgetc(fp);

  while(tmp !=EOF && cnt<(2000-2)*4)
    {
      charData[cnt+4]=tmp;
      tmp=getc(fp);
      cnt++;
    }

  fclose(fp);

  if(cnt%4)
    {
    for(int i=0; i<cnt%4; i++)
      {
      charData[cnt+4+i]=0;
      cnt++;
      }
  }
  
 
 data[0]=FEESRV_RCUSH_SCRIPT;
 data[(cnt/4)+1]= CE_CMD_TAILER;
 std::string serverName    = feeServerName;
  
 size_t size               = (1+(cnt/4)+1)*4;
 unsigned short flags = 0;
 short errorCode      = 0;
 short status         = 0;
  
 writeReadData(serverName, size, data, flags, errorCode, status);

 for(int i=0; i< N-1; i++)
   {
     resultBuffer[i]=charData[i];
   }
  resultBuffer[N-1] =0;
  
}


/*
 * todo, move in some other class
 */
int
PhosFeeClient::VerifyApdValues(int apdValue[32] ,const char *feeServerName, char *fName)
{
  int apdStatus = APD_OK;;
  char *formatString = 0;
  std::vector<unsigned int> data;
  data.resize(2000);
  char* charData=(char*)&data[0];  
  int err;
  int r[32]; //return values read back from APDs  
  
  FILE *fp;
  fp=fopen(fName, "r");
  int cnt=0;
  char tmp=fgetc(fp);
  
  while(tmp !=EOF && cnt<(2000-2)*4)
    {
      charData[cnt+4]=tmp;
      tmp=getc(fp);
      cnt++;
    }

    fclose(fp);

  if(cnt%4)
    {
      for(int i=0; i<cnt%4; i++)
	{
	  charData[cnt+4+i]=0;
	  cnt++;
	}
    }
  
  data[0]=FEESRV_RCUSH_SCRIPT;
  data[(cnt/4)+1]= CE_CMD_TAILER;
  std::string serverName    = feeServerName;
  
  size_t size               = (1+(cnt/4)+1)*4;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  writeReadData(serverName, size, data, flags, errorCode, status);
      
  formatString = new char[300];
  formatString = strcat(formatString, " 0x7800: %x");
  formatString = strcat(formatString, " 0x6000: %x %x %x %x");
  formatString = strcat(formatString, " 0x6004: %x %x %x %x");
  formatString = strcat(formatString, " 0x6008: %x %x %x %x");
  formatString = strcat(formatString, " 0x600c: %x %x %x %x");
  formatString = strcat(formatString, " 0x6010: %x %x %x %x");
  formatString = strcat(formatString, " 0x6014: %x %x %x %x");
  formatString = strcat(formatString, " 0x6018: %x %x %x %x");
  formatString = strcat(formatString, " 0x601c: %x %x %x %x");

  sscanf(charData, formatString,
	 &err,
	 &r[0],  &r[1],  &r[2],  &r[3],
	 &r[4],  &r[5],  &r[6],  &r[7],
	 &r[8],  &r[9],  &r[10], &r[11],
	 &r[12], &r[13], &r[14], &r[15],
	 &r[16], &r[17], &r[18], &r[19],
	 &r[20], &r[21], &r[22], &r[23], 
	 &r[24], &r[25], &r[26], &r[27], 
	 &r[28], &r[29], &r[30], &r[31]);
      
  int okCnt = 0;
  int crazyCnt = 0;
  int deadCnt = 0;
  int zeroCnt =0;
   
  for(int i=0; i<32; i++)
    {
      
      if(apdValue[i] != r[i])
	{
	  if(r[i] == 0xdead)
	    {
	      apdStatus = APD_DEAD;
	    }
	  else if( apdValue[i] == 0x0)
	    {
	      apdStatus = APD_ZERO;
	    }
	  else
	    {
	      apdStatus = APD_CRAZY;
	    }
	}
    }
      
  delete formatString;
  formatString = 0; // just in case
  return apdStatus;
  
}


int
PhosFeeClient::CheckPcmVersion(const char *feeServerName, int *pcmversion,  int branch, int cardIndex)
{
  int cardNumber = cardIndex +1;
  char feeServerNameCopy[20];
  sprintf(feeServerNameCopy, "%s", feeServerName);
  char resultBuffer[22];

  char fname[1024] = "s_readpcmversion.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosFeeClient::CheckPcmVersion() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosFeeClient::CheckPcmVersion() ExecuteScript(\""<<fname<<"\")"<<std::endl;

  scriptCompilerPtr->MakeReadPcmVersionScript(fname, branch, cardNumber);
  ExecuteScript(fname, feeServerNameCopy, resultBuffer, 20);
  sscanf(resultBuffer,"0x6000: %x", pcmversion);
  std::cout<<" PhosFeeClient() pcm version for fesserver "<<feeServerName<<", card: "<<cardNumber<<" at branch "<<branch
	   <<" is: 0x"<<std::hex<<*pcmversion<<std::dec<<std::endl;
  if(*pcmversion == 0xffff)
    {
      return FEE_STATE_ERROR;
    }
  else if(*pcmversion == 0)
    {
      return FEE_STATE_ERROR;   
    }
  else if(*pcmversion == PCMVERSION)
    {
      return FEE_STATE_ON;
    }
  else if(*pcmversion == OLD_PCMVERSION)
    {
     return FEE_STATE_WARNING;
    }

  else
    {
      return FEE_STATE_ERROR;
    }
}


unsigned long int
PhosFeeClient::ProbeActiveFeeList(char *feeServerName)
{
  std::cout<<" PhosFeeClient::ProbeActiveFeeList() ... "<<std::endl;
  char resultBuffer[30];
  unsigned long int feeList;

  char fname[1024] = "s_readfeelist.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosFeeClient::ProbeActiveFeeList() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosFeeClient::ProbeActiveFeeList() ExecuteScript(\""<<fname<<"\")"<<std::endl;

  ExecuteScript(fname, feeServerName, resultBuffer, 30);
  std::cout<<" PhosFeeClient::ProbeActiveFeeList() resultbuffer is "<<resultBuffer<<std::endl;
  sscanf(resultBuffer, "0x8000: %x", &feeList);
  std::cout<<" PhosFeeClient::ProbeActiveFeeList() finnished, feelist = 0x"<<std::hex<<feeList<<std::dec<<std::endl;
  return feeList;
}

unsigned long int 
PhosFeeClient::CheckFeeStatus(int *status, const char *feeServerName)
{
  char feeServerNameCopy[20];
  sprintf(feeServerNameCopy, "%s", feeServerName);
  int *dummy = new int;
  char resultBuffer[30];
  unsigned long feeList=0;
  long mask;
  int feestatus=0;

  char fname[1024] = "s_readfeelist.txt";
  char* dir = getenv("PHOSFEECLIENT_DATAPATH");
  if( dir == NULL ){
    std::cerr<<" PhosFeeClient::CheckFeeStatus() Warning!!!. PHOSFEECLIENT_DATAPATH environment is not define."<<std::endl;
  } else {
    char tmpname[1024];
    sprintf(tmpname,"%s/%s",dir,fname); sprintf(fname,"%s",tmpname);
  }
  std::cout<<" PhosFeeClient::CheckFeeStatus() ExecuteScript(\""<<fname<<"\")"<<std::endl;

  ExecuteScript(fname, feeServerName, resultBuffer, 30);
  sscanf(resultBuffer, "0x8000: %x", &feeList);

  for(long i=0; i<CARDS_PER_BRANCH-2; i++)
    {
      if(feeList & (1<<(i+1)))
	{  	
	  status[i] = CheckPcmVersion(feeServerName, dummy, BRANCH_A, i);
	  if((i == 0) || (i == 1))
	  {
	    int tmpIndex = CARDS_PER_BRANCH -i -1;
	    int tmpCard = CARDS_PER_BRANCH -i -1;
	    //	    printf("\ni =%d,  tmpIndex1 = %d\n", i, tmpIndex);
	    status[tmpIndex] = CheckPcmVersion(feeServerName, dummy, BRANCH_A, tmpIndex);
	  }
	}
  }

  for(long i = CARDS_PER_BRANCH; i < CARDS_PER_RCU -2; i++)
    {
      if(feeList & (1<<(i+1+2)))
	{
	  status[i] = CheckPcmVersion(feeServerName, dummy, BRANCH_B, i-CARDS_PER_BRANCH);
	  
	  if((i == CARDS_PER_BRANCH) || (i == CARDS_PER_BRANCH +1))
	    {
	      int tmpIndex2 = CARDS_PER_RCU +CARDS_PER_BRANCH -i-1;
	      int tmpCard2 = CARDS_PER_RCU -i -1;  
	      //	      printf("\ni = %d,  tmpIndex2 = %d\n", i,  tmpIndex2);
	      status[tmpIndex2] = CheckPcmVersion(feeServerName, dummy, BRANCH_B, tmpCard2); 
	    }
	}
    }  

  return feeList;
}
