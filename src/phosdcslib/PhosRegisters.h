 
class RcuALTROIF_t
{
  RcuALTROIF_t();
  RcuALTROIF_t(short nSamples, int sampleFreq, short cstbDelay = 2, short instructionErrorCheck = 0);
  
  RcuALTROIF_t(const RcuALTROIF_t& v):
    fNSamples(v.GetNumberOfSamples),
    fSampleFreq(v.GetSampleFrequency()),
    fCstbDelay(v.GetCstbDelay()),
    fInstructionErrorCheck(v.GetInstructionErrorCheck())
  {
  }
  
  RcuALTROIF_t& operator=(const RcuALTROIF_t)
  {
    return *this;
  }
 
  short GetNumberOfSamples() { return fNSamples; }
  int GetSampleFrequency() { return fSampleFreq; }
  short GetCstbDelay() { return fCstbDelay; }
  short fInstructionErrorCheck() { return fInstructionErrorCheck; }

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
  
  static const fRegAddress = RcuRegisterMap::ALTROIF; // 0x5101
};

class RcuTRGCONF_t
{
  // If one of the three different triggers are enabled the RCU is ready to recieve triggers
  // Trigger mode is 
  // 0 for TPC (L1 from CTP is mapped to L1 on FECs
  // 1 for PHOS (L0 from CTP is mapped to L1 on FECs

  RcuTRGCONF_t();

  RcuTRGCONF_t(const RcuTRGCONF_t& v):
  {
  }
  
  RcuTRGCONF_t& operator=(const RcuTRGCONF_t)
  {
    return *this;
  }

  bool IsSoftwareTriggerEnabled() { return fSoftwareTrigger; }
  bool IsAuxTriggerEnabled() { return fAuxTrigger; } 
  bool IsTTCrxTriggerEnabled() { return fTTCrxTrigger; }
  bool IsPHOSTriggerMode() { return fPHOSTriggerMode; }

  short GetL2LatencyWrtL1() { return fL2LatencyWrtL1; }

  int GetRegisterValue();

  void EnableSoftwareTrigger()
  {
    DisableAllTriggers();
    fSoftwareTrigger = true;
  }

  void EnableAusTrigger()
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

  static const fRegAddress = RcuRegisterMap::TRGCONF; //0x5102
  
};

class RcuRDOMOD_t
{
  RcuRDOMOD_t();
  RcuRDOMOD_t(bool maskRDYRX, bool sparseReadoutEnabled, bool executeSequencer, bool mebMode);

  RcuRDOMOD_t(const RcuRDOMOD_t& v):
    fMaskRDYRX(v.IsRDRYXEnabled()),
    fSparseReadout(v.IsSparseReadoutEnabled()),
    fExecuteSequencer(v.IsExectureSequencerEnabled()),
    fMEB(v.GetMEBMode())
  {
  }
  
  RcuRDOMOD_t& operator=(const RcuRDOMOD_t)
  {
    return *this;
  }

private:
  
  bool fMaskRDYRX;
  bool fSparseReadout;
  bool fExecuteSequencer;
  bool fMEBMode;

  int fRegisterValue;

  static const fRegAddress = RcuRegisterMap::RDOMOD; //0x5103

};

class RcuALTROCFG1_t
{
  // Re-defining content of the ALTROCFG1 register on the RCU 
  // Width is 16 bits
  RcuALTROCFG1_t();
  RcuALTROCFG1_t(bool zsEnabled, bool automaticBS, short offset, short zsThreshold);

  RcuALTROCFG1_t(const RcuALTROCFG1_t& v):

  {
  }
  
  RcuALTROCFG1_t& operator=(const RcuALTROCFG1_t)
  {
    return *this;
  }

  bool IsZeroSuppressionEnabled() { return fZeroSuppressionEnabled; }
  bool UsingAutomaticBaselineSubtraction() { return fAutomaticBaselineSubtraction; }
  short GetOffset() { return fOffset; } 
  short GetThreshold() { return fThreshold; }

  short GetRegisterValue();

  void SetZerosSupressionEnabled(bool zs = true) { fZeroSuppressionEnabled = zs; }
  void SetAutomaticBaselineSubtractionEnabled(bool abs = true) { fAutomaticBaselineSubtraction = abs; } 

  void SetOffset(short offset);
  void SetThreshold(short threshold);

  void SetByRegisterValue(short value);

private:
  
  bool fZeroSuppressionEnabled; // 1 bit reserved
  bool fAutomaticBaselineSubtraction; // 1 bit reserved
  short fOffset; // 4 bits reserved (reduced to facilitate for the possibility for a high threshold)
  short fThreshold; // 10 bits reserved (may want to use threshold up to 1023 to test readout performance)

  int fRegisterValue;

  static const fRegAddress = RcuRegisterMap::ALTROCFG1; // 0x5104

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
	std::cout << "Number of pre-samples is to high, value is set to 0xf (max)" << std::endl;
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

  short GetNPreSamples() { return fNPreSamples; }
  
  void SetNPreSamples(int nPreSamples) { fNPreSamples = nPreSamples; }

  void SetByRegisterValue(int value);

private:
  
  short fNPreSamples; // 4 bits reserved
 
  static const fRegAddress = RcuRegisterMap::ALTROCFG2; // 0x5105

};


