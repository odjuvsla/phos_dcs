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

using namespace BCRegisterMap;

using std::cout;
using std::endl;

using std::vector;


PhosFeeClient::PhosFeeClient(): FeeSampleClient(), PhosDcsBase(), scriptCompilerPtr(0)
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
  unsigned int tmpBufferSize = N*MAX_WORD_SIZE;
  //cout << "tmpBufferSize: " << tmpBufferSize << " MAX_WORD_SIZE: " << MAX_WORD_SIZE << " sizeof(unsigned long): " << sizeof(long) << endl;
  char resultBuffer[tmpBufferSize]; 
  unsigned long *tmpScannedValues = new unsigned long[N];

  unsigned long tmpBinData[N*2 + 16]; //the binary data may double in size and 16 extra words may be added.
  unsigned long tmpBinResultBuffer[N*2 + 16];
  
  for(int i=0; i< tmpBufferSize ; i++)
  {
    resultBuffer[i] = 0;
  }

  if( (regType == REGTYPE_BC) || (regType ==  REGTYPE_ALTRO) || (regType == REGTYPE_TRU))
    {

      int tmpN = N*2 + 10;
      
      vector<unsigned long> binaryData;
     
      vector<unsigned long> tmpResultValues;
           
      const int htsize = binaryCompilerPtr->MakeWriteReadRegisterBinary(regType, binaryData, regs, values, verify, N, branch, card, true);
      int size = ExecuteBinary(feeServerName, binaryData, tmpResultValues, tmpN, htsize); 

      ExecuteInstruction(feeServerName);
      int res = GetExecutionResult(feeServerName, 2);
      
      //ReadExecutionResult(feeServerName, tmpResultValues, N);
      
// 	  for(int i = 0; i < size/4; i++)
// 	    {
// 	      tmpScannedValues[i] = tmpBinResultBuffer[i];
// 	      cout << "PhosFeeClient::ReadRegisters: Result_MEM = 0x" << hex << tmpScannedValues[i] << dec<< endl;
// 	      i++;
// 	    }  
      //ScanValues(tmpScannedValues, resultBuffer, tmpBufferSize, RcuRegisterMap::Result_MEM, N);
      //iRet = VerifyValues(tmpScannedValues, values, verify, N);
      iRet = res;
    }
  else if( (regType == REGTYPE_RCU) || (regType == REGTYPE_RCU_ACL) || (regType == REGTYPE_TOR) || (regType == REGTYPE_BUSY))
    {
      unsigned long tmpMin = MinValue(regs, N);
      
      if( regType == REGTYPE_RCU_ACL)
	{
	  vector<unsigned long> binaryData;
	  int tmpN = RcuRegisterMap::Active_Channel_List_Length;
	  //binaryData.resize(2);
	  unsigned int tmpRegType = REGTYPE_RCU_MEM;
	  unsigned long* baseAdd = new unsigned long;
	  *baseAdd = RcuRegisterMap::Active_Channel_List;
	  const int htsize = binaryCompilerPtr->MakeWriteReadRegisterBinary(tmpRegType, binaryData, baseAdd, values, verify, tmpN, branch, card, false);

	  vector<unsigned long> tmpResultValues;
	  //	  tmpResultValues.resize(2);

	  ExecuteBinary(feeServerName, binaryData, tmpResultValues, N, htsize);
	  //	      ExecuteACLBinary(feeServerName, values, tmpResultValues, N);
	  //	  iRet = VerifyValues(tmpResultValues, values, verify, N);
	  //  delete [] binaryData;	      
	}
      else
	{
	  scriptCompilerPtr->MakeWriteReadRegisterScript(regType, fScriptFilename, regs, values, verify, N, branch, card, true);
	  ExecuteScript(fScriptFilename, feeServerName, resultBuffer, tmpBufferSize); 
	    
	  ScanValues(tmpScannedValues, resultBuffer, tmpBufferSize, tmpMin, N);
	  iRet = VerifyValues(tmpScannedValues, values, verify, N);
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

  vector<unsigned long> tmpBinData; //the binary data may double in size and 16 extra words can be added.
  vector<unsigned long> tmpBinResultBuffer;

  for(int i=0; i< tmpBufferSize ; i++)
  {
    resultBuffer[i] = 0;
  }
  if(CheckFile(fScriptFilename, "w") == 0)
    {
      //      scriptCompilerPtr->MakeReadRegisterScript(regType, fScriptFilename, regs, N, branch, card);
      //ExecuteScript(fScriptFilename, feeServerName, resultBuffer, tmpBufferSize); 
      const int htsize = binaryCompilerPtr->MakeReadRegisterBinary(regType, tmpBinData, regs, N, branch, card);
      
      //cout << "PhosFeeClient::ReadRegisters: Executing binary, size:" << N + htsize << endl;
      int size = ExecuteBinary(feeServerName, tmpBinData, tmpBinResultBuffer, N, htsize);
      //cout << "PhosFeeClient::ReadRegisters: Executing binary...Done! Size = " << size << endl;
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
	  //cout << "PhosFeeClient::ReadRegisters: Executing binary_MEM" << endl;
	  size = ExecuteBinary(feeServerName, tmpBinReadData, tmpBinReadResultBuffer, 1, htsize_res);
	  //cout << "PhosFeeClient::ReadRegisters: Executing binary_MEM...Done! Size = " << size << endl;
	  //	  for(int i = 0; i < size/4; i++)
	  int j = 0;
	  for(int i = 0; i < tmpBinReadResultBuffer.size(); i++)
	  //for(int i = 0; i < 1; i++)
	    {
	      i++;
	      rbValues[j] = tmpBinReadResultBuffer[i];
	      j++;
	      //cout << "PhosFeeClient::ReadRegisters: Result_MEM = 0x" << hex << rbValues[i] << dec<< endl;
	    }  

	  //ScanValues(rbValues, resultBuffer, tmpBufferSize, RcuRegisterMap::Result_MEM, N);
	}
      else if( (regType == REGTYPE_RCU) || (regType == REGTYPE_RCU_ACL) || (regType == REGTYPE_TOR) || (regType == REGTYPE_BUSY)  )
	{
	  //ScanValues(rbValues, resultBuffer, tmpBufferSize, tmpMin, N);
	}
   }
  return iRet;
}


int
PhosFeeClient::VerifyValues(const unsigned long *values1, const unsigned long *values2, const bool *verify, const int N) const
{
  int regStatus = REG_OK;;

  for(int i=0; i<N; i++)
    {
      if(verify[i] == true)
	{  
	  printf("PhosFeeClient::VerifyValues: value1[%d] = %d,, value2[%d] = %d\n", i, values1[i], i, values2[i]);
	  if(values1[i] != values2[i])
	    {
	      
	      if(values1[i] == 0xdead)
		{
		  //	  printf("PhosFeeClient::VerifyValues: value1[%d] = %d,, value2[%d] = %d\n", i, values1[i], i, values2[i]);
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
	}
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
PhosFeeClient::ExecuteBinary(const char* feeServerName, const vector<unsigned long> & binData, vector<unsigned long> &  resultBuffer, const int N, const int headerTrailersize)
{

  vector<unsigned int> data;
  data.resize(binData.size());
  std::string serverName    = feeServerName;
	 
  size_t size          = binData.size()*4;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  // cout << "PhosFeeClient::ExecuteBinary: size: " << size << endl;


  for(int i = 0; i < binData.size(); i++)
    {
      data[i] = binData[i];
      //      if(i < 100)
	//cout << "PhosFeeClient::ExecuteBinary: setting data = 0x" << hex << data[i] << dec << endl;
    }

  cout << "PhosFeeClient::ExecuteBinary: size = " << size << endl;

  writeReadData(serverName, size, data, flags, errorCode, status);
  cout << "writeReadData: " << status << endl;
  
  resultBuffer.clear();
  for(int i=0; i< size/4; i++)
    {
      //cout << "PhosFeeClient::ExecuteBinary: result = 0x" << hex << data[i] << dec << endl;
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
  cout << "Executing instruction..." << endl;
  writeReadData(serverName, size, data, flags, errorCode, status);  
  
}

const unsigned int
PhosFeeClient::CheckFeeState(const char *feeServerName, const int branch, const int cardNumber,  char *message, unsigned long int *pcmv)
{
  unsigned long pcmversion = 0;
  unsigned long address = BCVERSION;

  ReadRegisters(REGTYPE_BC, feeServerName, &address, &pcmversion, 1, branch, cardNumber);

  cout << "PhosFeeClient::CheckFeeState, feeservername ="<< feeServerName  << endl;
  cout << "PhosFeeClient::CheckFeeState, address = "  <<  address <<endl;
  cout << "PhosFeeClient::CheckFeeState, card = " << cardNumber << "branch = " << branch <<"   pcmversion = " << pcmversion  << endl;
  
  if(pcmv != 0)
    {
      *pcmv = pcmversion; 
    }

  if(pcmversion == 0xffff)
    {
      sprintf(message, "checking.. branch %d,  card %d pcmversion = %d, FEE_STATE_ERROR",  branch, cardNumber, pcmversion); 
      return FEE_STATE_ERROR;
    }
  else if(pcmversion == PCMVERSION)
    {
      sprintf(message, "checking.. branch %d,  card %d pcmversion = %d, FEE_STATE_ON",  branch, cardNumber, pcmversion);   
      return FEE_STATE_ON;
    }
  else if(pcmversion == 0)
    {
      sprintf(message, "checking.. branch %d,  card %d pcmversion = %d, FEE_STATE_ERROR",  branch, cardNumber, pcmversion);    
      return FEE_STATE_ERROR;   
    }
  else if(pcmversion == OLD_PCMVERSION)
    {
      sprintf(message, "checking.. branch %d,  card %d pcmversion = %d, FEE_STATE_WARNING, old pcmversion",  branch, cardNumber, pcmversion);     
     return FEE_STATE_WARNING;
    }
  else
    {
      sprintf(message, "checking.. branch %d,  card %d pcmversion = %d, FEE_STATE_ERROR, unknown",  branch, cardNumber, pcmversion);  
      return FEE_STATE_ERROR;
    }
}

unsigned int
PhosFeeClient::ActivateFee(unsigned long afl, const char* feeServerName, const unsigned long branch, 
			   const unsigned long cardIndex, const int onOff) 
{
  
  unsigned long  activeFeeList = afl;
  //  unsigned long  activeFeeList = 0;
  unsigned long int  tmpFeeList;
  int shift;
  int cardNumber = cardIndex +1;

  size_t size          = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;


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
     printf("\nERROR in activating card, branch has invalid value:%d\n", branch);
    }
  tmpFeeList = 1<<(cardNumber+shift);

  if(onOff == TURN_OFF)
   {
     if(activeFeeList & tmpFeeList)
       {
	 activeFeeList = (activeFeeList ^ tmpFeeList);  
       }
    
     printf("\nPhosFeeClien::acticefrontendlist = 0x%x\n", activeFeeList);
   }

  else if(onOff == TURN_ON)
    {
      activeFeeList = (activeFeeList | tmpFeeList);
    }

  cout << "PhosFeeClient::ActiveFeeList: " << hex << activeFeeList << dec << endl;

  vector<unsigned int> data;
  std::string serverName = feeServerName;

  WriteAFL(activeFeeList, feeServerName);

  SendWaitCommand(4000, feeServerName);

  data.clear();
  data.push_back(RcuRegisterMap::RCU_READ_RESULT|1);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);    

  writeReadData(serverName, size, data, flags, errorCode, status);  


  return data[0];

}

bool
PhosFeeClient::ActivateFeeByBranch(unsigned long afl, const char* feeServerName, const unsigned int branch, const int onOff) 
{
  
  unsigned long  activeFeeList = afl;
  //  unsigned long  activeFeeList = 0;
  unsigned long int  tmpFeeList;
  int shift;

  size_t size               = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;


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
     printf("\nERROR in activating card, branch has invalid value:%d\n", branch);
    }
  tmpFeeList = 0x7ffe<<shift;

  if(onOff == 0)
   {
     if(activeFeeList & tmpFeeList)
       {
	 activeFeeList = (activeFeeList ^ tmpFeeList);  
       }
   }
  
  else if(onOff == 1)
    {
      activeFeeList = (activeFeeList | tmpFeeList);
    }

  status = WriteAFL(activeFeeList, feeServerName);

  if(status != 0)
    return false;

  return true;

}

bool
PhosFeeClient::ActivateAllFee(unsigned long afl, const char* feeServerName, const int onOff) 
{
  
  unsigned long  activeFeeList = afl;
  //  unsigned long  activeFeeList = 0;
  unsigned long int  tmpFeeList;

  size_t size               = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  tmpFeeList = 0x7ffe7ffe;

  cout << "PhosFeeClient::ActiveFeeList: " << hex << activeFeeList << dec << endl;

  if(onOff == 0)
   {
     activeFeeList = 0x0;
   }
    
  else if(onOff == 1)
    {
      while(activeFeeList != 0x7ffe7ffe || activeFeeList != 0x7fff7fff)
	{
	  
	  activeFeeList = (activeFeeList | tmpFeeList);
	}
      
    }

  status = WriteAFL(activeFeeList, feeServerName);

  if(status != 0)
    return false;

  return true;

}

bool
PhosFeeClient::ActivateAllTru(unsigned long afl, const char* feeServerName, const int onOff) 
{
  
  unsigned long  activeFeeList = afl;
  //  unsigned long  activeFeeList = 0;
  unsigned long int  tmpFeeList;

  size_t size               = 0;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;


  tmpFeeList = 0x10001;

  cout << "PhosFeeClient::ActiveFeeList: " << hex << activeFeeList << dec << endl;

  if(onOff == 0)
   {
     activeFeeList = activeFeeList ^ 0x10001;
     //     printf("\nPhosFeeClient::Activefrontendlist = 0x%x\n", activeFeeList);
   }
  
  
  else if(onOff == 1)
    {
      activeFeeList = (activeFeeList | tmpFeeList);
    }

  cout << "PhosFeeClient::ActiveFeeList: " << hex << activeFeeList << dec << endl;

  status = WriteAFL(activeFeeList, feeServerName);

  if(status != 0)
    return false;


  return true;
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
  
//   SendWaitCommand(4000, feeServerName);

//   Reset(feeServerName, RcuRegisterMap::FEC_RESET);
  
//   SendWaitCommand(4000, feeServerName);

//   Reset(feeServerName, RcuRegisterMap::FEC_RESET);

//   SendWaitCommand(4000, feeServerName);

//   Reset(feeServerName, RcuRegisterMap::RCU_RESET);

//   SendWaitCommand(4000, feeServerName);



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

//   size = 5*4;
//   data[0] = RcuRegisterMap::RCU_EXEC_INSTRUCTION|1;
//   data[1] = RcuRegisterMap::RCU_WAIT_COMMAND| nCycles;
//   data[2] = RcuRegisterMap::END;
//   data[3] = RcuRegisterMap::ENDMEM;
//   data[4] = RcuRegisterMap::CE_CMD_TRAILER;  
//   writeReadData(serverName, size, data, flags, errorCode, status);  

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

//   size = 3*4;
//   data[0] = RcuRegisterMap::RCU_WRITE_MEMBLOCK|1;
//   data[1] = RcuRegisterMap::GLB_RESET | type;
//   data[2] = RcuRegisterMap::CE_CMD_TRAILER;  
//   writeReadData(serverName, size, data, flags, errorCode, status);  

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

//   size = 5*4;
//   data[0] = RcuRegisterMap::RCU_READ_MEMBLOCK|(N*2);
//   data[1] = RcuRegisterMap::Result_MEM;
//   data[2] = RcuRegisterMap::END;
//   data[3] = RcuRegisterMap::ENDMEM;
//   data[4] = RcuRegisterMap::CE_CMD_TRAILER;  
//   writeReadData(serverName, size, data, flags, errorCode, status);  
  
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

//   size = 5*4;
//   Data[0] = RcuRegisterMap::RCU_READ_MEMBLOCK|(N*2);
//   data[1] = RcuRegisterMap::Result_MEM;
//   data[2] = RcuRegisterMap::END;
//   data[3] = RcuRegisterMap::ENDMEM;
//   data[4] = RcuRegisterMap::CE_CMD_TRAILER;  
//   writeReadData(serverName, size, data, flags, errorCode, status);  
//  cout << "PhosFeeClient::GetExecutionResult: N = " << N << endl;
  data.clear();
  data.push_back(RcuRegisterMap::RCU_READ_MEMBLOCK|(N*2));
  data.push_back(RcuRegisterMap::Result_MEM);
  //  data.push_back(RcuRegisterMap::END);
  //  data.push_back(RcuRegisterMap::ENDMEM);
  data.push_back(RcuRegisterMap::CE_CMD_TRAILER);
  
  size = data.size()*4;

  //cout << "PhosFeeClient::GetExecutionResult: size before = " << size/4 << endl;

  writeReadData(serverName, size, data, flags, errorCode, status);  

  //cout << "PhosFeeClient::GetExecutionResult: size after = " << size/4 << endl;

  for(int i = 0; i < size/8; i++)
    {
      cout << "PhosFeeClient::GetExecutionResult: data[" << i << "] = " << hex << data[i] << dec << endl;
      if((data[i]&(0x100000)) != 0) 
	{
	  cout << "Error bit set for " << i << " data = " << data[i] << endl;
	  return -1; //Error bit set
	}
    }
  cout << "PhosFeeClient::GetExecutionResult: result = success"  << endl;
  return 1;
}
