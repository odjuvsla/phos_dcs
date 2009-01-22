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
#include "BinaryCompiler.h"
#include "PhosFeeClient.h"
#include <vector>
#include <string>
#include "unistd.h"
#include "BCRegisterMap.h"
#include "RcuRegisterMap.h"
#include "PhosDcsLogging.h"

using namespace BCRegisterMap;

using std::cout;
using std::endl;

using std::vector;

PhosFeeClient::PhosFeeClient(): FeeSampleClient(), PhosDcsBase(), scriptCompilerPtr(0), fPrintDebug(false)
{
  scriptCompilerPtr = new ScriptCompiler();
  binaryCompilerPtr = new BinaryCompiler();
  sprintf(fScriptFilename, "s_tmp.txt");
  //  sprintf(fScriptFilename, "/home/phs/testbench/s_tmp.txt");

}




PhosFeeClient::~PhosFeeClient()
{
  delete scriptCompilerPtr;
  delete binaryCompilerPtr;
}


void 
PhosFeeClient::SetScripFileName(const char *filename)
{
  //  cout << "PhosFeeClient::SetScripFileName. filename was set too"  <<  filename << endl;
  sprintf(fScriptFilename, "%s", filename);
}



PhosFeeClient::PhosFeeClient(PhosFeeClient const&):  FeeSampleClient(), PhosDcsBase(),scriptCompilerPtr(0) 
{

}


const int
PhosFeeClient::WriteReadRegisters(const int regType, const char *feeServerName, const unsigned long *regs, 
				  const unsigned long *values, const bool *verify, 
				  const int N, const int branch, const int card) 
{
  int iRet =0;
  stringstream log;
  if( (regType == REGTYPE_BC) || (regType ==  REGTYPE_ALTRO) || (regType == REGTYPE_TRU))
    {

      vector<unsigned long> binaryData;
      vector<unsigned long> resultData;
     
      int resultIndex = binaryCompilerPtr->MakeWriteReadRegisterBinary(regType, binaryData, regs, values, verify, N, branch, card, true);
      int size = ExecuteBinary(feeServerName, binaryData, resultData); 

      ExecuteInstruction(feeServerName);
      int res = GetExecutionResult(feeServerName, 2);

      if(*verify)
	{
	  res = VerifyValues(resultData, values, verify, N);
	  log.str("");
	  log << "PhosFeeClient::WriteReadRegister: Result from value verification: " << res << endl;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);
	}
      iRet = res;
    }
  else if( (regType == REGTYPE_RCU) || (regType == REGTYPE_RCU_ACL) || (regType == REGTYPE_TOR) || (regType == REGTYPE_BUSY))
    {
      unsigned long tmpMin = MinValue(regs, N);

      vector<unsigned long> binaryData;

      unsigned int tmpRegType = REGTYPE_RCU_MEM;

      binaryCompilerPtr->MakeWriteReadRegisterBinary(tmpRegType, binaryData, regs, values, verify, N, branch, card, false);
      
      vector<unsigned long> tmpResultValues;
      
      ExecuteBinary(feeServerName, binaryData, tmpResultValues);

      if(*verify)
	{
	  
 	}
    }
  return iRet;
}

 
int 
PhosFeeClient::ReadRegisters(const int regType, const char *feeServerName, const unsigned long *regs, unsigned long *rbValues, const int N, const int branch, const int card)
{  
  int iRet =0;
  unsigned int tmpBufferSize = N*MAX_WORD_SIZE;
  char resultBuffer[tmpBufferSize]; 

  unsigned long tmpMin = MinValue(regs, N);

  vector<unsigned long> tmpBinData; 
  vector<unsigned long> tmpBinResultBuffer;

  for(int i=0; i< tmpBufferSize ; i++)
  {
    resultBuffer[i] = 0;
  }
  const int htsize = binaryCompilerPtr->MakeReadRegisterBinary(regType, tmpBinData, regs, N, branch, card);
      
  int size = ExecuteBinary(feeServerName, tmpBinData, tmpBinResultBuffer);

  for(int i = 0; i < size/4; i++)
    {
      rbValues[i] = tmpBinResultBuffer[i];
      //cout << "PhosFeeClient::ReadRegisters: Result = 0x" << hex << rbValues[i] << dec<< endl;
    }
      
  if( (regType == REGTYPE_BC) || (regType ==  REGTYPE_ALTRO) || (regType == REGTYPE_TRU) )
    {

      ExecuteInstruction(feeServerName);
      int res = 0;//GetExecutionResult(feeServerName, N*2);
      vector<unsigned long> tmpBinReadData;
      vector<unsigned long> tmpBinReadResultBuffer;

      const int htsize_res = binaryCompilerPtr->MakeReadResultMemoryBinary(tmpBinReadData, N*2);
      
      //      size = ExecuteBinary(feeServerName, tmpBinReadData, tmpBinReadResultBuffer, 1); //TODO: check if I need to pass 1...
      size = ExecuteBinary(feeServerName, tmpBinReadData, tmpBinReadResultBuffer);
      
      int j = 0;
      for(int i = 0; i < tmpBinReadResultBuffer.size(); i++)
	{
	  i++;
	  rbValues[j] = tmpBinReadResultBuffer[i];
	  j++;
	  
	}  
    }
  else if( (regType == REGTYPE_RCU) || (regType == REGTYPE_RCU_ACL) || (regType == REGTYPE_TOR) || (regType == REGTYPE_BUSY)  )
    {
      
    }

  return iRet;
}


int
PhosFeeClient::VerifyValues(vector<unsigned long> values1, const unsigned long *values2, const bool *verify, const int N) const
{
  int regStatus = REG_OK;;

  int j = 0;

  for(int i = 0; i < N; i += 2)
    {
      if(values1[i+1] != values2[j]) 
	{
	  if(values1[i] == 0xdead)
	    {
	      regStatus = REG_DEAD;
	    }
	  else if(values1[i] == 0x0)
	    {
	      regStatus = REG_ZERO;
	    }
	  else
	    {
	      regStatus = REG_CRAZY;
	    }
	}
      j++;
    }
  return regStatus;
}


void
PhosFeeClient::ScanValues(unsigned long *values, const char *resultBuffer, const int bufferSize, const unsigned long baseAddress, const int N)
{
  // cout << "bufferSize =" << bufferSize <<endl;
  // cout << "N = " << N << endl;
  //  char *formatString = new char[bufferSize];
  
  MakeFormatString(N, formatString, baseAddress); 

  int cnt = 0;
  int lines = 0;

  if(N%4 != 0)
    {
      lines = N/4 + 1;
    }
  else
    {
      lines = N/4;
    }

  char tmpFormat[lines][100];
  char tmpBuf[lines][100];
  int fTotCnt = 0;
  int rTotCnt = 0;
  unsigned long tmpVal[lines*4]; 
  //  printf("\nlines = %d\n", lines);

  for(int i=0; i< lines; i++)
    {
      cnt = 0;

      while((formatString[fTotCnt]  != '\n')  &&  (fTotCnt <  bufferSize) )
 	{
	  if(cnt <  100)
	    {
	      tmpFormat[i][cnt] = formatString[fTotCnt];
	      cnt ++;
	      fTotCnt ++;
	    }
	  else
	    {
	      fTotCnt ++;
	    }
	}

      fTotCnt ++;
      tmpFormat[i][cnt] = 0;
      cnt = 0;
 
      while( (resultBuffer[rTotCnt] != '\n')  &&  (rTotCnt <  bufferSize) )
	{
	  if( rTotCnt <  bufferSize)
	    {  
	    
	      if(cnt <  100)
		    {
		      tmpBuf[i][cnt] =resultBuffer[rTotCnt];
		      cnt ++;
		      rTotCnt ++;
		    }
	      else
		{
		  rTotCnt ++;		  
		}
	    }
	}
 
      rTotCnt ++;
      tmpBuf[i][cnt] = 0;
   }

  for(int i = 0; i < lines; i++)
    {
      sscanf(tmpBuf[i], tmpFormat[i], &tmpVal[0 + i*4], &tmpVal[1 + i*4], &tmpVal[2 + i*4], &tmpVal[3 + i*4]);
    }
  
 
  for(int i=0; i<N; i++)
    {
      values[i] = tmpVal[i];
    }

  //  delete[]  formatString;
}

void
PhosFeeClient::MakeFormatString(const int N, char *formatString, const int baseAddr) 
{
  char tmp[1000];
  int cnt = 0;

  int baseAddress = baseAddr;

  sprintf(formatString,"0x%x:",baseAddress);

  for(int i=0; i< N; i++)
    {
      if( (i%4 == 0) && (i != 0))
	{
	  baseAddress = baseAddress +4;
	  sprintf(tmp,"0x%x:", baseAddress);
	  formatString = strcat(formatString, "\n");
	  formatString = strcat(formatString, tmp);
	}
      formatString = strcat(formatString, " %x");
    }
}


void
PhosFeeClient::ExecuteScript(const char *scriptFilename, const char *feeServerName, char *resultBuffer, const int N)
{
  //cout << "PhosFeeClient::ExecuteScript,scriptFilenam = " << scriptFilename << endl;

  vector<unsigned int> data;
  data.resize(200000);
  //  data.resize(20000);

  char* charData=(char*)&data[0];  
  
    if(CheckFile(scriptFilename, "r") == 0)
      {
	FILE *fp;
	fp=fopen(scriptFilename, "r");
	int cnt=0;
	char tmp=fgetc(fp);

	while(tmp !=EOF && cnt<(200000-2)*4)
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
	cout << "cnt: " << cnt << " size: " << size << endl;
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
}

int
PhosFeeClient::ExecuteBinary(const char* feeServerName, const vector<unsigned long> & binData, vector<unsigned long> &  resultBuffer)
{

  vector<unsigned int> data;
  data.resize(binData.size());
  std::string serverName    = feeServerName;
	 
  size_t size          = binData.size()*4;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  for(int i = 0; i < binData.size(); i++)
    {
      data[i] = binData[i];
    }

  writeReadData(serverName, size, data, flags, errorCode, status);
    
  resultBuffer.clear();
  for(int i=0; i< size/4; i++)
    {
      resultBuffer.push_back(data[i]);
    }
  
  return size;
}

void
PhosFeeClient::ExecuteInstruction(const char* feeServerName)
{
  vector<unsigned int> data;
  //data.resize(4);
  std::string serverName    = feeServerName;
	 
  size_t size          = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;
  
  data.clear();
  data.push_back(RcuRegisterMap::RCU_WRITE_MEMBLOCK|1);
  data.push_back(RcuRegisterMap::EXEC);
  data.push_back(RcuRegisterMap::Instruction_MEM);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);

  size = data.size()*4;
  PhosDcsLogging::Instance()->Logging("Executing instruction...", LOG_LEVEL_VERBOSE);
  writeReadData(serverName, size, data, flags, errorCode, status);  
  
}

const unsigned int
PhosFeeClient::CheckFeeState(const char *feeServerName, const int branch, const int cardNumber,  char *message, unsigned long int *pcmv)
{
  unsigned long pcmversion = 0;
  unsigned long address = BCVERSION;

  ReadRegisters(REGTYPE_BC, feeServerName, &address, &pcmversion, 1, branch, cardNumber);

  stringstream log;
  log << "PhosFeeClient::CheckFeeState: feeservername ="<< feeServerName;
  log << "PhosFeeClient::CheckFeeState: address = "  <<  address;
  log << "PhosFeeClient::CheckFeeState: card = " << cardNumber << "branch = " << branch <<"   pcmversion = " << pcmversion;
  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);
  
  if(pcmv != 0)
    {
      *pcmv = pcmversion; 
    }

  if(pcmversion == 0xffff || pcmversion == 0)
    {
      log.str("");
      log << "PhosFeeClient::CheckFeeState: Checking.. branch " << branch << ", card " << cardNumber << ", pcmversion = " << pcmversion << ", FEE_STATE_ERROR";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
      
      return FEE_STATE_ERROR;
    }
  else if(pcmversion == PCMVERSION)
    {
      log.str("");
      log << "PhosFeeClient::CheckFeeState: Checking.. branch " << branch << ", card " << cardNumber << ", pcmversion = " << pcmversion << ", FEE_STATE_ON";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);
      
      return FEE_STATE_ON;
    }
  else if(pcmversion == OLD_PCMVERSION)
    {
      log.str("");
      log << "PhosFeeClient::CheckFeeState: Checking.. branch " << branch << ", card " << cardNumber << ", pcmversion = " << pcmversion << ", FEE_STATE_WARNING";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_WARNING);
      
     return FEE_STATE_WARNING;
    }
  else
    {
      log.str("");
      log << "PhosFeeClient::CheckFeeState: Checking.. branch " << branch << ", card " << cardNumber << ", pcmversion = " << pcmversion << ", FEE_STATE_ERROR";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);

      return FEE_STATE_ERROR;
    }
}

unsigned int
PhosFeeClient::ActivateFee(unsigned long afl, const char* feeServerName, const unsigned long branch, 
			   const unsigned long cardIndex, const int onOff) 
{
  
  unsigned long  activeFeeList = afl;
  unsigned long int  tmpFeeList;
  int shift;

  size_t size          = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  int res = 0;

  if(branch == 0)
    {
      shift = 0;
    } 
  else if(branch == 1)
    {
      shift = 16;
    } 
  else
    {         
      PhosDcsLogging::Instance()->Logging(string("PhosFeeClient::ActivateFee: In activating card, branch has invalid value"), LOG_LEVEL_ERROR);	
    }

  tmpFeeList = 1<<(cardIndex+shift);

  if(onOff == TURN_OFF)
   {
     if(activeFeeList & tmpFeeList)
       {
	 activeFeeList = (activeFeeList ^ tmpFeeList);  
       }
   }

  else if(onOff == TURN_ON)
    {
      activeFeeList = (activeFeeList | tmpFeeList);
    }
  
  if(fPrintDebug)
    {
      stringstream log;
      log << "PhosFeeClient::ActivateFee: Active FEE List: " << activeFeeList;
    }

  vector<unsigned int> data;
  std::string serverName = feeServerName;

  res = WriteAFL(activeFeeList, feeServerName);

  SendWaitCommand(4000, feeServerName);

  data.clear();
  data.push_back(RcuRegisterMap::RCU_READ_RESULT|1);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);    

  writeReadData(serverName, size, data, flags, errorCode, status);  

  return res;

}

bool
PhosFeeClient::WriteAFL(unsigned long activeFeeList, const char* feeServerName)
{

  vector<unsigned int> data;
  std::string serverName = feeServerName;

  size_t size          = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;
  
  data.clear();
  data.push_back(RcuRegisterMap::RCU_WRITE_MEMBLOCK|1);
  data.push_back(RcuRegisterMap::AFL);
  data.push_back(activeFeeList);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);  

  size = data.size()*4;

  int res = writeReadData(serverName, size, data, flags, errorCode, status);  
    if(res != 0)
    return false;

  return true;
}

void
PhosFeeClient::SendWaitCommand(int nCycles, const char* feeServerName)
{

  size_t size               = 5*4;

  vector<unsigned int> data;
  //  data.resize(10);
  std::string serverName = feeServerName;


  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  data.clear();
  data.push_back(RcuRegisterMap::RCU_EXEC_INSTRUCTION|1);
  data.push_back(RcuRegisterMap::RCU_WAIT_COMMAND| nCycles);
  data.push_back(RcuRegisterMap::END);
  data.push_back(RcuRegisterMap::ENDMEM);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);  

  size = data.size()*4;

  writeReadData(serverName, size, data, flags, errorCode, status);  
  
}

void
PhosFeeClient::Reset(const char* feeServerName, const int type)
{

  size_t size          = 0;

  vector<unsigned int> data;
  //data.resize(10);
  std::string serverName = feeServerName;

  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  data.clear();
  data.push_back(RcuRegisterMap::RCU_WRITE_MEMBLOCK|1);
  data.push_back(RcuRegisterMap::GLB_RESET | type);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);  
  
  size = data.size()*4;

  writeReadData(serverName, size, data, flags, errorCode, status);  
  
}


void
PhosFeeClient::ReadExecutionResult(const char* feeServerName, vector<unsigned long> & resultBuffer, int N)
{

  size_t size           = 0;

  vector<unsigned int> data;
  //data.resize(5);
  std::string serverName = feeServerName;


  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;
  
  data.clear();
  data.push_back(RcuRegisterMap::RCU_READ_MEMBLOCK|(N*2));
  data.push_back(RcuRegisterMap::Result_MEM);
  data.push_back(RcuRegisterMap::END);
  data.push_back(RcuRegisterMap::ENDMEM);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);
  
  size = data.size()*4;
  
  writeReadData(serverName, size, data, flags, errorCode, status);  

  resultBuffer.clear();
  for(int i = 0; i < size/4; i++)
    {
      resultBuffer.push_back(data[i]);
    }
  
}

int
PhosFeeClient::GetExecutionResult(const char* feeServerName, int N)
{

  size_t size          = 0;

  vector<unsigned int> data;
  //data.resize(5);
  std::string serverName = feeServerName;


  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  data.clear();
  data.push_back(RcuRegisterMap::RCU_READ_MEMBLOCK|(N*2));
  data.push_back(RcuRegisterMap::Result_MEM);

  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);
  
  size = data.size()*4;

  writeReadData(serverName, size, data, flags, errorCode, status);  

  stringstream log;

  for(int i = 0; i < size/8; i++)
    {
      log << "PhosFeeClient::GetExecutionResult: data[" << i << "] = " << hex << data[i] << dec;
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);

      if((data[i]&(0x100000)) != 0) 
	{
	  log.str("");
	  log << "PhosFeeClient::GetExecutionResult: Error bit set for " << i << " data = " << data[i];
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
	  return -1; //Error bit set
	}
    }
  PhosDcsLogging::Instance()->Logging(string("PhosFeeClient::GetExecutionResult: result = success"), LOG_LEVEL_VERBOSE);

  return 1;
}
