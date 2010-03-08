#ifndef BINARYCOMPILER_H
#define BINARYCOMPILER_H

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

#include "PhosDcsBase.h"
#include <vector>
#include <string>

using namespace std;

class ScriptCompiler;

class BinaryCompiler : public PhosDcsBase
  {
  public:
    BinaryCompiler();
    ~BinaryCompiler();

    int MakeWriteReadRegisterBinary ( const unsigned int regType, vector<unsigned long> & binData, const unsigned long *reg,
                                      const unsigned long *value,  const bool *verify, const int N,
                                      const int branch = 0, const int card = 0,
                                      const bool writeZeroes = 0 );

    int MakeWriteReadRcuMemoryBlockBinary ( vector<unsigned long> & binData, const unsigned long baseReg, const unsigned long* value,
                                            const int N );

    int MakeWriteReadFeeRegisterBinary ( const unsigned int registerType, vector<unsigned long> & binData,
                                         const unsigned long *reg, const unsigned long *value, const bool *verify,
                                         const int N, const  int branch = 0, const  int card = 0,
                                         const  int chip = 0, const  int channel = 0, const bool writeZeroes = 0 );

    int MakeReadRegisterBinary ( const int regType, vector<unsigned long> & binData,
                                 const unsigned long *reg, const int N,
                                 const unsigned long branch = 0, const unsigned long card = 0,
                                 const unsigned long chip = 0, const unsigned long channel = 0 );

    int MakeReadRcuRegisterBinary ( vector<unsigned long> & binData,
                                    const unsigned long baseAddress,  const int N );

    int MakeReadFeeRegisterBinary ( const int registerType, vector<unsigned long> & binData, const unsigned long *reg,
                                    const int N, const unsigned long branch = 0, const unsigned long card = 0,
                                    const unsigned long chip = 0, const unsigned long channel = 0 );

    int MakeReadResultMemoryBinary ( vector<unsigned long> & binData, const int N );

  private:

  };

#endif

//(const int, unsigned long*, const unsigned long*, const int , const unsigned long, const unsigned long, const unsigned long, const unsigned long)
//(const int, long unsigned int*, const long unsigned int*, const int, const long unsigned int, const long unsigned int)

//(int, const long unsigned int*, const long unsigned int*, int, long unsigned int, long unsigned int, long unsigned int, long unsigned int)

//(const int, long unsigned int*, const long unsigned int*, const int, const long unsigned int, const long unsigned int)
