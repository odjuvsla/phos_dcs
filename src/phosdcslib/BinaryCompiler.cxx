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
#include "InstructionMaker.h"
#include "PhosDcsLogging.h"

BinaryCompiler::BinaryCompiler() : PhosDcsBase()
{

}

BinaryCompiler::~BinaryCompiler()
{

}

int
BinaryCompiler::MakeWriteReadRegisterBinary ( const unsigned int regType, vector<unsigned long> & binData, const unsigned long *reg,
    const unsigned long *value,  const bool *verify, const int N,
    const int branch ,  const int card ,
    const bool writeZeroes )
{
  int ret = 0;
  if ( regType == REGTYPE_RCU_MEM )
    {
      ret = MakeWriteReadRcuMemoryBlockBinary ( binData, reg[0], value, N );
    }
  if ( regType == REGTYPE_ALTRO )
    {
      //      ret = MakeWriteReadFeeRegisterBinary(regType, binData, reg, value, verify, N, branch, card, 1, writeZeroes);
    }
  if ( regType == REGTYPE_BC || REGTYPE_ALTRO )
    {
      ret = MakeWriteReadFeeRegisterBinary ( regType, binData, reg, value, verify, N, branch, card, 1, writeZeroes );
    }
  if ( regType == REGTYPE_TRU )
    {
    }

  char name[128];
  sprintf ( name, "tmp/binblock_0x%X\0", reg[0] );
  ofstream outfile ( name );
  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      outfile << "0x" << hex << binData.at ( i ) << endl;
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadRegisterBinary: Final block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return ret;
}


int
BinaryCompiler::MakeReadRegisterBinary ( const int regType, vector<unsigned long> & binData,
    const unsigned long *reg, const int N,
    const unsigned long branch , const unsigned long card ,
    const unsigned long chip , const unsigned long channel )
{
  int ret = 0;

  if ( ( regType == REGTYPE_BC ) || ( regType ==  REGTYPE_ALTRO ) || ( regType == REGTYPE_TRU ) )
    {
      ret = MakeReadFeeRegisterBinary ( regType, binData , reg, N, branch, card );
    }
  else if ( ( regType == REGTYPE_RCU ) || ( regType == REGTYPE_RCU_ACL ) || ( regType == REGTYPE_TOR ) || ( regType == REGTYPE_BUSY ) )
    {
      ret =  MakeReadRcuRegisterBinary ( binData, reg[0], N );
    }
  stringstream log;

  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeReadRegisterBinary: Final block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return ret;
}

int
BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary ( vector<unsigned long> & binData, const unsigned long baseReg, const unsigned long* value,
    const int N )
{
  binData.push_back ( RcuRegisterMap::RCU_WRITE_MEMBLOCK|N );

  binData.push_back ( baseReg );

  for ( int i = 0; i < N; i++ )
    {
      binData.push_back ( value[i] );
    }

  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  MakeReadRcuRegisterBinary ( binData, baseReg, N );

  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadRcuMemoryBlockBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return 0;
}


int
BinaryCompiler::MakeWriteReadFeeRegisterBinary ( const unsigned int registerType, vector<unsigned long> & binData,
    const unsigned long *reg, const unsigned long *value, const bool *verify,
    const int N, const int branch , const int card ,
    const int chip , const int channel , const bool writeZeroes )
{
  int ret = 0;

  if ( ( registerType == REGTYPE_BC ) || ( registerType ==  REGTYPE_ALTRO ) || ( registerType == REGTYPE_TRU ) )
    {

//       if(*verify)  binData.push_back((RcuRegisterMap::RCU_WRITE_MEMBLOCK | (N*3+3)));
//       else binData.push_back((RcuRegisterMap::RCU_WRITE_MEMBLOCK | (N*2+2)));

      binData.push_back ( ( RcuRegisterMap::RCU_WRITE_MEMBLOCK | ( N*2+2 ) ) );
      binData.push_back ( RcuRegisterMap::Instruction_MEM );

      int j = 0;

      for ( int i=0; i<N; i++ )
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, false, reg[j], branch, card ) );
          binData.push_back ( InstructionMaker::MakeLS20Instruction ( false, value[j] ) );
          j++;
        }
      binData.push_back ( RcuRegisterMap::END );
//       if(*verify == true)
// 	{
// 	  for(int i = 0; i < N; i++)
// 	    {
// 	      binData.push_back(InstructionMaker::MakeMS20Instruction(registerType, true, reg[i], branch, card));
// 	    }
// 	  binData.push_back(RcuRegisterMap::END);
// // 	  MakeReadFeeRegisterBinary(registerType, binData, reg, N, branch, card, chip, channel);
// // 	  ret = N+2;
// 	}
      binData.push_back ( RcuRegisterMap::ENDMEM );
      binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );
    }
  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return ret;
}

int
BinaryCompiler::MakeReadRcuRegisterBinary ( vector<unsigned long> & binData,
    const unsigned long baseAddress,  const int N )
{
  binData.push_back ( RcuRegisterMap::RCU_READ_MEMBLOCK|N );

  binData.push_back ( baseAddress );

  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeReadRcuRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return 0;
}

int
BinaryCompiler::MakeReadFeeRegisterBinary ( const int registerType, vector<unsigned long> & binData, const unsigned long *reg,
    const int N, const unsigned long branch , const unsigned long card ,
    const unsigned long chip , const unsigned long channel )
{

  binData.push_back ( RcuRegisterMap::RCU_WRITE_MEMBLOCK| ( N+2 ) );
  binData.push_back ( RcuRegisterMap::Instruction_MEM );

  for ( int i=0; i<N;i++ )
    {
      if ( registerType == REGTYPE_ALTRO )
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, true, reg[i], branch, card, chip, channel ) );
        }
      else
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, true, reg[i], branch, card ) );
        }

    }

  binData.push_back ( RcuRegisterMap::END );
  binData.push_back ( RcuRegisterMap::ENDMEM );
  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      PhosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
    }

  return 0;
}

int
BinaryCompiler::MakeReadResultMemoryBinary ( vector<unsigned long> & binData, const int N )
{
  return MakeReadRcuRegisterBinary ( binData, RcuRegisterMap::Result_MEM, N );
}
