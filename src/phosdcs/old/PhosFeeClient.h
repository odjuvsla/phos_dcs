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

#include <FeeClientLibImp.hpp>
class ScriptCompiler;

using namespace dcs;
using namespace dcs::fee;
using std::vector;

class PhosFeeClient :public FeeClientLibImp
{
 public:
  PhosFeeClient();
  ~PhosFeeClient();
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
  void ExecuteScript(const char *scriptFilename, const char *feeServerName, char *resultBuffer, int N);
  int VerifyApdValues(int apdValue[32] ,const char *feeServerName, char *fName);

  /**
   * Reads the active frontendard list (AFL) from the RCU
   * @param feeServerName the feeserver/RCU that you want the AFL from
   * @return The AFL.
   **/
  unsigned long int ProbeActiveFeeList(char *feeServerName);

  unsigned long int CheckFeeStatus(int *status, const char *serverName);
  int CheckPcmVersion(const char *feeServerName, int *pcmversion, int branch, int cardIndex);
 private:
  //  int CheckPcmVersion(char *feeServerName, int branch, int card);
  ScriptCompiler *scriptCompilerPtr;
};

#endif

