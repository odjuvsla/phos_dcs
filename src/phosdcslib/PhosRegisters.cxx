 
#include "PhosRegisters.h"
#include <iostream>


RcuALTROIF_t::RcuALTROIF_t() :
  fNSamples(81),
  fSampleFreq(10000000),
  fCstbDelay(2),
  fInstructionErrorCheck(0)
{
}

RcuALTROIF_t::RcuALTROIF_t(short nSamples, int sampleFreq, short cstbDelay, short instructionErrorCheck) :
  fNSamples(nSamples),
  fSampleFreq(sampleFreq),
  fCstbDelay(cstbDelay),
  fInstructionErrorCheck(instructionErrorCheck)
{
  
}

int RcuALTROIF_t::GetRegisterValue()
{
  int sampleSetting = -1;

  switch(fSampleFreq) 
    {
    case 20000000:
      sampleSetting = 0x0;
      break;
    case 10000000:
      sampleSetting = 0x1;
      break;
    case 5000000:
      sampleSetting = 0x2;
      break;
    case 2500000:
      sampleSetting = 0x3;
      break;
    default:
      return 0;
    } 
  
  return (fInstructionErrorCheck & 0x3) << 16 | 
    (fCstbDelay & 0x3) << 14 | 
    (sampleSetting & 0xf) << 10 | 
    fNSamples & 0x2ff;
}

void RcuALTROIF_t::SetByRegisterValue(int value)
{
  fNSamples = value & 0x2ff;
  int samplesetting = value >> 10 & 0x3;
  fCstbDelay = value >> 14 & 0x3;
  fInstructionErrorCheck = value >> 16 & 0x3;

  switch(samplesetting) 
    {
    case 0x0:
      fSampleFreq = 20000000;
      break;
    case 0x1:
      fSampleFreq = 10000000;
      break;
    case 0x2:
      fSampleFreq = 5000000;
      break;
    case 0x3:
      fSampleFreq = 2500000;
      break;
    default:
      fSampleFreq = 10000000;
    } 
  
}

RcuTRGCONF_t::RcuTRGCONF_t() :
  fSoftwareTrigger(false),
  fAuxTrigger(false),
  fTTCrxTrigger(false),
  fPHOSTriggerMode(true),
  fL2LatencyWrtL1(0xfff)
{
  
}

RcuTRGCONF_t::RcuTRGCONF_t(bool softwareTrigger, bool auxTrigger, bool ttcrxTrigger, bool phosTriggerMode, short latency) :
  fSoftwareTrigger(softwareTrigger),
  fAuxTrigger(auxTrigger),
  fTTCrxTrigger(ttcrxTrigger),
  fPHOSTriggerMode(phosTriggerMode),
  fL2LatencyWrtL1(latency)
{

}  

int RcuTRGCONF_t::GetRegisterValue()
{
  short triggerSource = 0;
  if(fSoftwareTrigger)
    {
      if(fAuxTrigger) return 0;
      if(fTTCrxTrigger) return 0;
      triggerSource = 0x1;
    }
  else if(fAuxTrigger) 
    {
      if(fTTCrxTrigger) return 0;
      triggerSource = 0x2;
    }
  else if(fTTCrxTrigger)
    {
      triggerSource = 0x4;
    }

  return (triggerSource & 0x7) << 14 | 
    (fPHOSTriggerMode & 0x1) << 13 | 
    fL2LatencyWrtL1 & 0xfff;

}

void RcuTRGCONF_t::SetByRegisterValue(int value)
{
  short triggerSource = value >> 14 & 0x3;
  fPHOSTriggerMode = value >> 13 & 0x1;
  fL2LatencyWrtL1 = value & 0xaaa;
  
  switch(triggerSource)
    {
    case 1:
      DisableAllTriggers();
      fSoftwareTrigger = true;
      break;
    case 2:
      DisableAllTriggers();
      fAuxTrigger = true;
      break;
    case 4:
      DisableAllTriggers();
      fTTCrxTrigger = true;
      break;
    default:
      DisableAllTriggers();
      break;
    }
}


RcuRDOMOD_t::RcuRDOMOD_t() :
  fMaskRDYRX(false),
  fSparseReadout(false),
  fExecuteSequencer(false),
  fMEBMode(false)
{
  
}

RcuRDOMOD_t::RcuRDOMOD_t(bool maskRDYRX, bool sparseReadoutEnabled, bool executeSequencer, bool mebMode) : 
  fMaskRDYRX(maskRDYRX),
  fSparseReadout(sparseReadoutEnabled),
  fExecuteSequencer(executeSequencer),
  fMEBMode(mebMode)
{
}

short RcuRDOMOD_t::GetRegisterValue()
{
  return fMaskRDYRX << 3 | 
    fSparseReadout << 2 |
    fExecuteSequencer << 1 | 
    fMEBMode;
}

void RcuRDOMOD_t::SetByRegisterValue(short value)
{
  fMaskRDYRX = value >> 3 & 0x1;
  fSparseReadout = value >> 2 & 0x1;
  fExecuteSequencer = value >> 1 & 0x1;
  fMEBMode = value & 0x1;
}

RcuALTROCFG1_t::RcuALTROCFG1_t():
  fZeroSuppressionEnabled(false),
  fAutomaticBaselineSubtraction(false),
  fOffset(0),
  fThreshold(0)
{
}

RcuALTROCFG1_t::RcuALTROCFG1_t(bool zsEnabled, bool automaticBS, short offset, short zsThreshold) :
  fZeroSuppressionEnabled(zsEnabled),
  fAutomaticBaselineSubtraction(automaticBS),
  fOffset(offset),
  fThreshold(zsThreshold)
{
  
}

short RcuALTROCFG1_t::GetRegisterValue()
{
  return fZeroSuppressionEnabled & 0x1 << 15 | 
    fAutomaticBaselineSubtraction & 0x1 << 14 | 
    fOffset & 0xf << 10 | 
    fThreshold & 0x2ff;
}

void RcuALTROCFG1_t::SetByRegisterValue(short value)
{
  fZeroSuppressionEnabled = value >> 15 & 0x1;
  fAutomaticBaselineSubtraction = value >> 14 & 0x1;
  fOffset = value >> 10 & 0xf;
  fThreshold = value & 0x2ff;
}

short RcuALTROCFG2_t::GetRegisterValue()
{
  return fNPreSamples & 0xf;
}

void RcuALTROCFG2_t::SetByRegisterValue(short value)
{
  fNPreSamples = value & 0xf;
}


