#include "RcuRegisterMap.h" 
class RcuALTROIF_t
{
  RcuALTROIF_t();
  RcuALTROIF_t(short nSamples, int sampleFreq, short cstbDelay = 2, short instructionErrorCheck = 0);
  
  RcuALTROIF_t(const RcuALTROIF_t& v):
    fNSamples(v.GetNumberOfSamples()),
    fSampleFreq(v.GetSampleFrequency()),
    fCstbDelay(v.GetCstbDelay()),
    fInstructionErrorCheck(v.InstructionErrorCheck())
  {
  }
  
  RcuALTROIF_t& operator=(const RcuALTROIF_t)
  {
    return *this;
  }
 
  short GetNumberOfSamples() const { return fNSamples; }
  int GetSampleFrequency() const { return fSampleFreq; }
  short GetCstbDelay() const { return fCstbDelay; }
  short InstructionErrorCheck() const { return fInstructionErrorCheck; }

  int GetRegisterValue();

  void SetNumberOfSamples(short nSamples) { fNSamples = nSamples; }
  void SetSampleFrequency(int freq) { fSampleFreq = freq; }
  void SetCstbDelay(short cstbd) { fCstbDelay = cstbd; } 
  void SetInstructionErrorCheck(short val) { fInstructionErrorCheck = val; }

  void SetByRegisterValue(int value);


private:
  
  short fNSamples;
  int fSampleFreq;
  short fCstbDelay;
  short fInstructionErrorCheck;
  
  static const int fRegAddress = RcuRegisterMap::ALTROIF; // 0x5101
};

class RcuTRGCONF_t
{
  // If one of the three different triggers are enabled the RCU is ready to recieve triggers
  // Trigger mode is 
  // 0 for TPC (L1 from CTP is mapped to L1 on FECs
  // 1 for PHOS (L0 from CTP is mapped to L1 on FECs

  RcuTRGCONF_t();

  RcuTRGCONF_t(bool softwareTrigger, bool auxTrigger, bool ttcrxTrigger, bool phosTriggerMode = true, short latency = 0xfff);

  RcuTRGCONF_t(const RcuTRGCONF_t& v):
    fSoftwareTrigger(v.IsSoftwareTriggerEnabled()),
    fAuxTrigger(v.IsAuxTriggerEnabled()),
    fTTCrxTrigger(v.IsTTCrxTriggerEnabled()),
    fPHOSTriggerMode(v.IsPHOSTriggerMode()),
    fL2LatencyWrtL1(v.GetL2LatencyWrtL1())
  {
    
  }
  
  RcuTRGCONF_t& operator=(const RcuTRGCONF_t)
  {
    return *this;
  }

  bool IsSoftwareTriggerEnabled() const { return fSoftwareTrigger; }
  bool IsAuxTriggerEnabled() const { return fAuxTrigger; } 
  bool IsTTCrxTriggerEnabled() const { return fTTCrxTrigger; }
  bool IsPHOSTriggerMode() const { return fPHOSTriggerMode; }

  short GetL2LatencyWrtL1() const { return fL2LatencyWrtL1; }

  int GetRegisterValue();

  void EnableSoftwareTrigger()
  {
    DisableAllTriggers();
    fSoftwareTrigger = true;
  }

  void EnableAuxTrigger()
  {
    DisableAllTriggers();
    fAuxTrigger = true;
  }

  void EnableTTCrxTrigger()
  {
    DisableAllTriggers();
    fTTCrxTrigger = true;
  }

  void DisableAllTriggers()
  {
    fSoftwareTrigger = false;
    fAuxTrigger = false;
    fTTCrxTrigger = false;
  }

  void SetPHOSTriggerMode(bool ptm = true) { fPHOSTriggerMode = true; }

  void SetL2LatencyWrtL1(int latency) { fL2LatencyWrtL1 = latency; }

  void SetByRegisterValue(int value);
 
private: 

  bool fSoftwareTrigger;
  bool fAuxTrigger;
  bool fTTCrxTrigger;
  bool fPHOSTriggerMode;
  
  short fL2LatencyWrtL1;

  int fRegisterValue;

  static const int fRegAddress = RcuRegisterMap::TRCFG; //0x5102
  
};

class RcuRDOMOD_t
{
  RcuRDOMOD_t();
  RcuRDOMOD_t(bool maskRDYRX, bool sparseReadoutEnabled, bool executeSequencer, bool mebMode);

  RcuRDOMOD_t(const RcuRDOMOD_t& v):
    fMaskRDYRX(v.IsMaskRDYRXEnabled()),
    fSparseReadout(v.IsSparseReadoutEnabled()),
    fExecuteSequencer(v.IsExecuteSequencerEnabled()),
    fMEBMode(v.GetMEBMode())
  {
  }
  
  RcuRDOMOD_t& operator=(const RcuRDOMOD_t)
  {
    return *this;
  }

  bool IsMaskRDYRXEnabled() const { return fMaskRDYRX; }
  bool IsSparseReadoutEnabled() const { return fSparseReadout; }
  bool IsExecuteSequencerEnabled() const { return fExecuteSequencer; }
  bool GetMEBMode() const { return fMEBMode; }

  short GetRegisterValue(); 

  void SetMaskRDYRX(bool value = true) { fMaskRDYRX = value; } 
  void SetSparseReadout(bool value = true) { fSparseReadout = value; }
  void SetExecuteSeqencer(bool value = true) { fExecuteSequencer = value; }
  void SetMEBMode(bool value = true) { fMEBMode = value; } 

  void SetByRegisterValue(short value);

private:
  
  bool fMaskRDYRX;
  bool fSparseReadout;
  bool fExecuteSequencer;
  bool fMEBMode;

  int fRegisterValue;

  static const short fRegAddress = RcuRegisterMap::RDOMOD; //0x5103

};

class RcuALTROCFG1_t
{
  // Re-defining content of the ALTROCFG1 register on the RCU 
  // Width is 16 bits
  RcuALTROCFG1_t();
  RcuALTROCFG1_t(bool zsEnabled, bool automaticBS, short offset, short zsThreshold);

  RcuALTROCFG1_t(const RcuALTROCFG1_t& v):
    fZeroSuppressionEnabled(v.IsZeroSuppressionEnabled()),
    fAutomaticBaselineSubtraction(v.UsingAutomaticBaselineSubtraction()),
    fOffset(v.GetOffset()),
    fThreshold(v.GetThreshold())
  {
  }
  
  RcuALTROCFG1_t& operator=(const RcuALTROCFG1_t)
  {
    return *this;
  }

  bool IsZeroSuppressionEnabled() const { return fZeroSuppressionEnabled; }
  bool UsingAutomaticBaselineSubtraction() const { return fAutomaticBaselineSubtraction; }
  short GetOffset() const { return fOffset; } 
  short GetThreshold() const { return fThreshold; }

  short GetRegisterValue();

  void SetZerosSupressionEnabled(bool zs = true) { fZeroSuppressionEnabled = zs; }
  void SetAutomaticBaselineSubtractionEnabled(bool abs = true) { fAutomaticBaselineSubtraction = abs; } 

  void SetOffset(short offset) { fOffset = offset; }
  void SetThreshold(short threshold) {fThreshold = threshold; }

  void SetByRegisterValue(short value);

private:
  
  bool fZeroSuppressionEnabled; // 1 bit reserved
  bool fAutomaticBaselineSubtraction; // 1 bit reserved
  short fOffset; // 4 bits reserved (reduced to facilitate for the possibility for a high threshold)
  short fThreshold; // 10 bits reserved (may want to use threshold up to 1023 to test readout performance)

  int fRegisterValue;

  static const short fRegAddress = RcuRegisterMap::ALTROCFG1; // 0x5104

};

class RcuALTROCFG2_t
{
  // Re-defining content of the ALTROCFG2 register on the RCU 
  // Width is 18 bits (only 4 bits are used for the moment, which means that we have 14 bits available for more info...)
  RcuALTROCFG2_t() : 
    fNPreSamples(11)
  {}

  RcuALTROCFG2_t(short nPreSamples)
  {
    if(nPreSamples > 0xf)
      {
	fNPreSamples = 0xf;
      }
    else fNPreSamples = nPreSamples;
  }

  RcuALTROCFG2_t(const RcuALTROCFG2_t& v):
    fNPreSamples(v.GetNPreSamples())
  {
  }
  
  RcuALTROCFG2_t& operator=(const RcuALTROCFG2_t)
  {
    return *this;
  }

  short GetNPreSamples() const { return fNPreSamples; }

  short GetRegisterValue();
  
  void SetNPreSamples(int nPreSamples) { fNPreSamples = nPreSamples; }

  void SetByRegisterValue(short value);

private:
  
  short fNPreSamples; // 4 bits reserved
 
  static const int fRegAddress = RcuRegisterMap::ALTROCFG2; // 0x5105

};


