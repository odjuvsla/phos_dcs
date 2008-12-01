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

#include "BinaryCompiler.h"
#include "RcuRegisterMap.h"
#include "ScriptCompiler.h"

BinaryCompiler::BinaryCompiler() : PhosDcsBase()
{

}

BinaryCompiler::~BinaryCompiler()
{

}

int
BinaryCompiler::MakeWriteReadRegisterBinary(const unsigned int regType, vector<unsigned long> & binData, const unsigned long *reg, 
					    const unsigned long *value,  const bool *verify, const int N, 
					    const int branch ,  const int card , 
					    const bool writeZeroes )
{

  int ret = 0;
  if(regType == REGTYPE_RCU_MEM)
    {
      ret = MakeWriteReadRcuMemoryBlockBinary(binData, reg[0], value, N);
    }
  if(regType == REGTYPE_ALTRO)
    {
    }
  if(regType == REGTYPE_BC)
    {
      ret = MakeWriteReadFeeRegisterBinary(regType, binData, reg, value, verify, N, branch, card, 1, writeZeroes);
    }
  if(regType == REGTYPE_TRU)
    {
    }
  return ret;
}


int
BinaryCompiler::MakeReadRegisterBinary(const int regType, vector<unsigned long> & binData, 
				       const unsigned long *reg, const int N, 
				       const unsigned long branch , const unsigned long card , 
				       const unsigned long chip , const unsigned long channel )
{
  int ret = 0;

  if( (regType == REGTYPE_BC) || (regType ==  REGTYPE_ALTRO) || (regType == REGTYPE_TRU))
    {
      ret = MakeReadFeeRegisterBinary(regType, binData , reg, N, branch, card);
    }
  else if( (regType == REGTYPE_RCU) || (regType == REGTYPE_RCU_ACL) || (regType == REGTYPE_TOR) || (regType == REGTYPE_BUSY))
    {
      ret =  MakeReadRcuRegisterBinary(regType, binData, reg[0] , N);
    }
  return ret;
}

int
BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary(vector<unsigned long> & binData, const unsigned long baseReg, const unsigned long* value, 
						  const int N)
{
  binData.push_back(RcuRegisterMap::RCU_WRITE_MEMBLOCK|(N));
  //cout << "BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary: binData[0] =  0x";
  //  cout << hex << binData[0] << dec << endl;

  binData.push_back(baseReg);
  //cout << "BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary: binData[1] =  0x";
  //cout << hex << binData[1] << dec << endl;

  //  for(int i = 0; i < N-1; i++) 
  for(int i = 0; i < N; i++) 
    {
      binData.push_back(value[i]);

    }
  for(int i = 0; i < binData.size()-2; i++) 
    {
      //  cout << "BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary: binData[" << i + 2 <<"] =  0x";
      //  cout << hex << binData[i+2] << dec << endl;
    }

  //  binData[N-1] = RcuRegisterMap::CE_CMD_TRAILER;
  binData.push_back(RcuRegisterMap::CE_CMD_TRAILER);
  //cout << "BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary: binData[" << binData.size() - 1<< "] =  0x";
  //  cout << hex << binData[binData.size()-1] << dec << endl;
  
  return 0; 
}


int
BinaryCompiler::MakeWriteReadFeeRegisterBinary(const unsigned int registerType, vector<unsigned long> & binData, 
					       const unsigned long *reg, const unsigned long *value, const bool *verify, 
					       const int N, const int branch , const int card , 
					       const int chip , const int channel , const bool writeZeroes )
{
  

  if( (registerType == REGTYPE_BC) || (registerType ==  REGTYPE_ALTRO) || (registerType == REGTYPE_TRU) )
    {
      
      int tmpN = N;
      binData.push_back((RcuRegisterMap::RCU_WRITE_MEMBLOCK | (tmpN*2+2)));
      //      cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[0] =  0x";
      //cout << hex << binData[0] << dec << endl;
      
      binData.push_back(RcuRegisterMap::Instruction_MEM);
      //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[1] =  0x";
      //cout << hex << binData[1] << dec << endl;
      
      
      int j = 0;
      for(int i=0; i<tmpN; i++)
	{
	  
	  binData.push_back(ScriptCompiler::MakeMS20Instruction(registerType, false, reg[j], branch, card));
	  //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[" << binData.size() - 1 <<"] =  0x";
	  //cout << hex << binData.back() << dec << endl;
	  binData.push_back(ScriptCompiler::MakeLS20Instruction(false, value[j]));
	  //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[" << binData.size() - 1 <<"] =  0x";
	  //cout << hex << binData.back() << dec << endl;
	  j++;
	}  
      binData.push_back(RcuRegisterMap::END);
      //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[" << tmpN + 2<<"] =  0x";
      //cout << hex << binData[tmpN+2] << dec << endl;
      binData.push_back(RcuRegisterMap::ENDMEM);
      //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[" << tmpN + 3<<"] =  0x";
      //cout << hex << binData[tmpN+3] << dec << endl;
      binData.push_back(RcuRegisterMap::CE_CMD_TRAILER);
      //cout << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: binData[" << tmpN + 4<<"] =  0x";
      //cout << hex << binData[tmpN+4] << dec << endl;
    }

  return 0; 

}

int
BinaryCompiler::MakeReadRcuRegisterBinary(const int registerType, vector<unsigned long> & binData, 
					  const unsigned long baseAddress,  const int N) 
{
  binData.push_back(RcuRegisterMap::RCU_READ_MEMBLOCK|N);

  binData.push_back(baseAddress);

  binData.push_back(RcuRegisterMap::CE_CMD_TRAILER);

  //cout << "BinaryCompiler::MakeReadRcuRegisterBinary: data = 0x" << hex << binData[0] << dec << endl;
  //cout << "BinaryCompiler::MakeReadRcuRegisterBinary: data = 0x" << hex << binData[1] << dec << endl;
  //cout << "BinaryCompiler::MakeReadRcuRegisterBinary: data = 0x" << hex << binData[2] << dec << endl;

  return 0; 
}

int
BinaryCompiler::MakeReadFeeRegisterBinary(const int registerType, vector<unsigned long> & binData, const unsigned long *reg, 
					  const int N, const unsigned long branch , const unsigned long card ,
					  const unsigned long chip , const unsigned long channel )
{

  binData.push_back(RcuRegisterMap::RCU_WRITE_MEMBLOCK|(N+2));
  binData.push_back(RcuRegisterMap::Instruction_MEM);

  for(int i=0; i<N;i++)
    {
      binData.push_back(ScriptCompiler::MakeMS20Instruction(registerType, true, reg[i], branch, card));
      //cout << "BinaryCompiler::MakerReadFeeRegisterBinary: binData["<<i+2<<"]: " << hex << binData[i+2] << dec<< endl;
    }

  binData.push_back(RcuRegisterMap::END);
  //cout << "BinaryCompiler::MakerReadFeeRegisterBinary: binData[N+2] " << hex << binData[N+2] << dec << " N: " << N << endl;
  binData.push_back(RcuRegisterMap::ENDMEM);
  //cout << "BinaryCompiler::MakerReadFeeRegisterBinary: binData[N+3] " << hex << binData[N+3] << dec << " N: " << N << endl;
  binData.push_back(RcuRegisterMap::CE_CMD_TRAILER);
  //cout << "BinaryCompiler::MakerReadFeeRegisterBinary: binData[N+4] " << hex << binData[N+4] << dec << " N: " << N << endl;

  return 0; 
}

int
BinaryCompiler::MakeReadResultMemoryBinary(vector<unsigned long> & binData, const int N)
{
  return MakeReadRcuRegisterBinary(REGTYPE_RCU, binData, RcuRegisterMap::Result_MEM, N);
}
