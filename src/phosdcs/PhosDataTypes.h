
#ifndef PHOSDATATYPES_H
#define PHOSDATATYPES_H

/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
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

//  AliHLTPHOSBase & operator = (const AliHLTPHOSBase &);

//#include "PhosDataTypes.h"
#include "PhosConst.h"
//using namespace PhosConst;
#include <iostream>
#include <string>

using namespace PhosConst;
using namespace std;

class PhosSimpleDataType_t
{
 public:
  PhosSimpleDataType_t();
  ~PhosSimpleDataType_t();  
  const int GetIntValue() const {return fVal;}; 
  virtual void SetIntValue(const int value) = 0;
  //  void Save(FILE *fp);
  //  void Load(FILE *fp);
  // private:
 protected:
  int fVal;
  //  char name[100];
};


class ModNumber_t : public  PhosSimpleDataType_t
{
 public:
  ModNumber_t(const int value);
  ~ModNumber_t();
  //  const int GetIntValue() const {return fVal;};
  void SetIntValue(const int value);
  ModNumber_t();
 private:
  
  //  void SetIntValue(const int value);
  //  ModNumber_t();
  //  int fVal;
  //  bool fIsinitialized;
};

class RcuNumber_t
{
 public:
  RcuNumber_t(const int value);
  ~RcuNumber_t();
  const int GetIntValue() const {return fVal;};

 private:
  void SetIntValue(const int value);
  RcuNumber_t();
  int fVal;
  bool fIsinitialized; 
};


/*
 *Branchh can be either A (0) or B (1)
 */
class BranchNumber_t
{
 public:
  BranchNumber_t(const int value); 
  const int GetIntValue() const {return fVal;};

 private:
  BranchNumber_t();
  void SetIntValue(const int branch);
  int fVal;
  bool fIsinitialized;
};


class FeeSlotNumber_t
{
 public:
  FeeSlotNumber_t(const int value);
  const int GetIntValue() const {return  fVal;};
 private: 
  FeeSlotNumber_t(); 
  void SetIntValue(const int branch);
  int fVal;
  bool fIsinitialized; 
};


class FeePos_t
{
 public:
  //  FeePos_t(const int mod, const int rcu, const int branch, const int card);
  FeePos_t(ModNumber_t  mod, RcuNumber_t rcu,  BranchNumber_t branch,  FeeSlotNumber_t card);
  ~FeePos_t();
  const ModNumber_t  GetModuleID() const  { return fModuleID; };
  const RcuNumber_t  GetRcuID()  const { return fRcuID; };
  const BranchNumber_t  GetBranch() const    { return fBranch; };
  const FeeSlotNumber_t GetCardPos() const   { return fCardSlot; }; 
  const int GetCardArrayIndex() const {return fCardArrayIndex;};
  const int GetAFLBitPosition()const {return  fAFLBitPosition;};
  const unsigned long int GetfAFLMask() {return  fAFLMask;};

 private:
  FeePos_t();
  void SetModuleID(const ModNumber_t  mod) { fModuleID = mod;};
  void SetRcuID(const RcuNumber_t  rcu) {fRcuID = rcu;} ;
  void SetBranch(const BranchNumber_t branch) {fBranch = branch;};
  void SetCardSlot(const FeeSlotNumber_t slot) { fCardSlot = slot;} ;

  void SetCardArrayIndex();

  const int  SetAFLBitPosition();

  ModNumber_t  fModuleID;
  RcuNumber_t  fRcuID;
  BranchNumber_t fBranch;
  FeeSlotNumber_t  fCardSlot;

  int fCardArrayIndex;
  int fAFLBitPosition;
  int fAFLMask;
  bool fIsinitialized;
};



class NSamples_t
{
 public:
  NSamples_t(const unsigned long int n);
  NSamples_t();   
  ~NSamples_t(); 
  void SetIntValue(const int val);
  const unsigned long  GetIntValue() const {return  fVal;};

 private:
  unsigned long fVal;
};


class NPreSamples_t
{
 public:
  NPreSamples_t(const unsigned long int n);
   NPreSamples_t();   
  ~NPreSamples_t(); 
  void SetIntValue(const int val);
  const unsigned long  GetIntValue() const {return  fVal;};

 private:
  unsigned long fVal;
};


class ZeroSupressionTreshold_t
{
 public:
  ZeroSupressionTreshold_t(const unsigned long int n);
  ZeroSupressionTreshold_t();   
  ~ ZeroSupressionTreshold_t(); 
  void SetIntValue(const int val);
  const unsigned long  GetIntValue() const {return  fVal;};

 private:
  unsigned long fVal;
};


class ZeroSupressionMode_t
{
 public:
  ZeroSupressionMode_t() {}
  ZeroSupressionMode_t(const unsigned long int n);
  ~ ZeroSupressionMode_t(); 
  void SetIntValue(const int val);
  const unsigned long  GetIntValue() const {return  fVal;};

 private:
  unsigned long fVal;
};


class ReadoutMode_t
{
 public:
  ReadoutMode_t(const unsigned long int n);
  ReadoutMode_t();  
  ~ ReadoutMode_t(); 
  void SetIntValue(const int val);
  const unsigned long GetIntValue() const {return  fVal;};

 private:
  unsigned long fVal;
};


class Pattern_t
{
 public:
  Pattern_t();
  ~Pattern_t();
  void SetPatternType(const int patterntype) {fPatternType = patterntype;};
  void SetLength(const int length){fLength = length; };
  void SetStep(const int step) { fStep = step; };
  void SetAmplitude(const int a) {fMaxAmpl = a; };
  //  void SetPattern(const int *pattern, const int length);
  const int GetPatternType() const  {return fPatternType;};
  const int GetPatternLength() const  { return fLength;} ; 
  const int GetStepSize() const { return fStep;};
  const int GetMaxAmpl() const { return fMaxAmpl; } ;
  void PrintInfo(const char *message = 0) const;

 private:
  int fPatternType;
  int fLength;
  int fStep;
  int fMaxAmpl;
  //  int fPattern[MAX_ALTRO_SAMPLES];
};





//  void SetSetPattern(Pattern_t p) {fAltroConfig.SetPattern(p) ;};
//  void SetSetPatternApply(bool b){fAltroConfig.SetPatternApply(b);};

class AltroConfig_t
{
 public:
  AltroConfig_t();
  AltroConfig_t(const NSamples_t nSamples, const NPreSamples_t  nPreSamples, 
		const ReadoutMode_t readoutmode = 0, const  ZeroSupressionMode_t  zmode =0, 
		const ZeroSupressionTreshold_t zthr =0);
  ~AltroConfig_t();
  void PrintInfo(const char *message = 0) const ;
  void SetNSamples(const  NSamples_t nSamples);
  void SetNPreSamples(const NPreSamples_t  nPreSamples);
  void SetZerosSupressionTreshold(const ZeroSupressionTreshold_t  treshold);
  void SetZerosSupressionMode(const  ZeroSupressionMode_t  mode);
  void SetReadoutMode(const  ReadoutMode_t  readoutmode);
  void SetPattern(const Pattern_t pattern) {fPattern = pattern;};
  void SetApplyPattern(bool  apply = true){fApplyPattern =apply;};
  //  bool GetApplyPattern()const {return fApplyPattern;};
  const NSamples_t   GetNSamples() const { return   fNSamples;};
  const NPreSamples_t    GetNPreSamples() const { return fNPreSamples;};
  const ZeroSupressionTreshold_t    GetZerosSupressionTreshold() const { return fZeroSupressionThreshold;};
  const ZeroSupressionMode_t    GetZerosSupressionMode() const { return fZeroSupressionMode;};
  const ReadoutMode_t  GetReadoutMode() const { return fReadoutMode;}; 
  const Pattern_t GetPattern() const {return fPattern;};
  const bool GetApplyPattern() const {return fApplyPattern; };

 private:
  NSamples_t  fNSamples;
  NPreSamples_t   fNPreSamples;
  ZeroSupressionTreshold_t  fZeroSupressionThreshold;
  ZeroSupressionMode_t  fZeroSupressionMode;  
  ReadoutMode_t  fReadoutMode;
  Pattern_t fPattern;
  bool fApplyPattern;

};


class StartZ_t
{
 public:
  StartZ_t(const int val = 0);
  void SetIntValue(const int value);
  const int  GetIntValue() const {return fVal;}; 
 private:
  int fVal;
};


class EndZ_t
{
 public:
  //  EndZ_t();
  EndZ_t(const int val = 0);
  void SetIntValue(const int value); 
  const int  GetIntValue() const {return fVal;}; 
 private:
  // EndZ_t();
  int fVal; 
};


class StartX_t
{
 public:
  //  StartX_t();
  StartX_t(const int val = 0);
  void SetIntValue(const int value);
  const int GetIntValue() const {return fVal;}; 
 private:
  
  int fVal; 
};


class EndX_t
{
 public:
  //  EndX_t();
  EndX_t(const int val = 0);
  void SetIntValue(const int value);  
  const int  GetIntValue() const {return fVal;}; 
 private:
  int fVal;
};



/*
 * Readout region on per module basis
 * max area is  fStartZ =0,  fEndZ = 56
 * fStartX =0,  fEndX = 64
 */
class ReadoutRegion_t
{
 public:
  ReadoutRegion_t();
  ReadoutRegion_t(const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx);
  ~ReadoutRegion_t();
  void PrintInfo(const char *message = 0) const ;
  void SetReadoutRegion(const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx);

  const StartZ_t  GetStartZ() const { return fStartZ;};
  const EndZ_t    GetEndZ() const {   return fEndZ;} ;
  const StartX_t  GetStartX() const { return fStartX;};
  const EndX_t    GetEndX() const {   return fEndX;}; 

  

 private:
  bool CheckConsistency(const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx) const;
  StartZ_t  fStartZ;
  EndZ_t    fEndZ;
  StartX_t  fStartX;
  EndX_t    fEndX;
};


/*
 *Trigger mode: the possibilities values are
 * 0) software 
 * 2) external level 1  internal  level2 after time window  
 * 3) external level 1 + level2
 */
class  TriggerMode_t
{
 public:
  TriggerMode_t();
  TriggerMode_t(const int value); 
  ~TriggerMode_t(); 
  void PrintInfo(const char *message = 0) const;

  void SetIntValue(const int value) 
    {
      if( (value == 0) || (value == 2) ||(value == 3) )
	{
	  fVal = value;
	} 
      else 
	{
	  fVal = 0;
	};
    }

  const int GetIntValue() const {return fVal;}; 
 private:
  int fVal;

};



class ReadoutConfig_t
{
 public:                                                                                                
  ReadoutConfig_t(const AltroConfig_t altroconfig, const ReadoutRegion_t rdoconfig, const TriggerMode_t triggerMode);
  ~ReadoutConfig_t();   
  ReadoutConfig_t(); 
  
  void PrintInfo(const char *message, 
		 bool printaltroconfig = true, 
		 bool printreadoutregion = true, 
		 bool printtriggerconfig = true) const;

  void SetAltroConfig(const AltroConfig_t altroConfig) { fAltroConfig = altroConfig;};
  void SetReadoutRegion(const ReadoutRegion_t readoutRegion) {fReadoutRegion = readoutRegion;};
  void SetTriggerConfig(const  TriggerMode_t triggerMode)  {fTriggerMode = triggerMode;};
  void SetPattern(Pattern_t p) {fAltroConfig.SetPattern(p) ;};
  void SetApplyPattern(bool b = false){fAltroConfig.SetApplyPattern(b);};
  void SetReadoutMode(const  ReadoutMode_t  readoutmode){fAltroConfig.SetReadoutMode(readoutmode);};
  const AltroConfig_t GetAltroConfig()       const { return fAltroConfig; }; 
  const ReadoutRegion_t GetReadoutRegion()   const { return fReadoutRegion; }; 
  const TriggerMode_t GetTriggerMode()       const { return fTriggerMode;} ; 

 private:
  // ReadoutConfig_t(); 
  AltroConfig_t   fAltroConfig;
  ReadoutRegion_t fReadoutRegion;
  TriggerMode_t fTriggerMode;
};


class ConfigInfo_t
{
 public:
  const ConfigInfo_t & operator= (const ConfigInfo_t &t);
  char fInfo[1024];
  int fID; 
  int fIDLimit;
};


class TRURegister_t
{
 public:
  TRURegister_t();
  TRURegister_t(const unsigned long address, const unsigned long value, const char *name);
  ~TRURegister_t();
  const char* GetName() const{ return fName;};
  const unsigned long GetAddress() const {return fAddress;}; 
  const unsigned long GetIntValue() const {return fVal;};
  void SetName(const char *name) { sprintf(fName,"%s",name);};
  void SetAddress(const unsigned long address) {fAddress = address; };
  void SetIntValue(const unsigned long val) {fVal = val;};
  void SetIsReadOnly(const bool isreadonly = true){fReadOnly = isreadonly;}  ;
  void PrintInfo() const;
private:
  char fName[40];
  unsigned long fAddress;
  unsigned long fVal;
  bool fReadOnly;
};

 class TRUSettings_t
{
 public:
  TRUSettings_t();
  ~TRUSettings_t();
  TRUSettings_t& operator=(const TRUSettings_t&)
  {
  }
  const TRURegister_t GetRegister(const int index) const;
  const int GetRegisterCount() const { return fRegCnt; };
  const int AddRegister(const TRURegister_t reg);
  void PrintInfo(const char *message = 0) const;
  void Reset();
 private:
  const int fNRegisters;
  int fRegCnt;
  TRURegister_t fRegisters[N_TRU_REGS];
  
  
  

};

struct FeeServer
{
  string fName;
  int fModId;
  int fRcuId;
  int fZ;
  int fX;
};


//class Pattern_t


#endif
