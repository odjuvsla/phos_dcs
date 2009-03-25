#ifndef PHOSFEECLIENT_H
#define PHOSFEECLIENT_H

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


#include <FeeSampleClient.hpp>
#include "PhosDcsBase.h"

class ScriptCompiler;
class BinaryCompiler;

using namespace dcs;
using namespace dcs::fee;
using std::vector;


class PhosFeeClient :public FeeSampleClient, public PhosDcsBase
{
 public:
  PhosFeeClient();
  virtual ~PhosFeeClient();
  void SetScripFileName(const char *filename);

  const int WriteReadRegisters(const int regtype, const char *feeServerName, const unsigned long *regs, const unsigned long *values, const bool *verify, 
			 const int N, const int branch = 999, const int card = 999);
  int ReadRegisters(const int regtype, const char *feeServerName, const unsigned long *regs, unsigned long *rbValues,  const int N, const int branch = 999, const int card = 999);

  /**
   * Executes a script given on a given feeserver.
   * @param scriptFilename name of the script that should be executed.
   * @param feeServerName name of the feeserver where the script should
   * be executed.
   * @param resultBuffer pointer to a character buffer to store the command line
   * output from the invocation of rcu-sh at the feeserver.
   * @param N the number of characters to copy into the resultBuffer.
   * if the script does not involve any read operation then N can be set to zero. 
   **/

  void ExecuteScript(const char *scriptFilename, const char *feeServerName, char *resultBuffer, const int N);

  int ExecuteBinary(const char* feeServerName, const vector<unsigned long> & binData, vector<unsigned long> & resultBuffer);
  void ExecuteInstruction(const char* feeServerName);
  
  const unsigned int CheckFeeState(const char *feeServerName,  const int branch, const int cardNumber, unsigned long int *pcmv = 0);
  const unsigned int CheckTruState(const char *feeServerName, const int tru);

  unsigned int ActivateFee(unsigned long afl, const char* serverName, const unsigned long branch, const unsigned long cardIndex, const int onOff);
  
  bool ActivateFeeByBranch(unsigned long afl, const char* serverName, const unsigned branch, const int onOff);

  //  bool ActivateAllFee(unsigned long afl, const char* feeServerName, const int onOff);

  //bool ActivateAllTru(unsigned long afl, const char* feeServerName, const int onOff);

  void SendWaitCommand(const int nCycles, const char* feeServerName);

  void Reset(const char* feeServerName, int type);
  
  
 private:
  PhosFeeClient(const PhosFeeClient & );
  PhosFeeClient & operator = (const PhosFeeClient &)
    {
      return *this;
    };

  //  char fFormatString[10000];

  char formatString[10000];

  char fScriptFilename[1024];

  /** must be changed for RCU_fw2 */
  void ScanValues(unsigned long *values, const char *resultBuffer, const int bufferSize, const unsigned long baseAddress, const int N);

  int  VerifyValues(const vector<unsigned long> values1, const unsigned long *values2, const bool  *verify, const int N) const;

  /** must be changed for RCU_fw2 */
  void MakeFormatString(const int N, char *formatString, const int baseAddress);


  bool WriteAFL(unsigned long activeFeeList, const char* feeServerName);

  void ReadExecutionResult(const char* feeServerName, vector<unsigned long> & resultBuffer, int N);  
  
  int GetExecutionResult(const char* feeServerName, int N); 

  ScriptCompiler *scriptCompilerPtr;
  BinaryCompiler *binaryCompilerPtr;

  bool fPrintDebug;
};


#endif

