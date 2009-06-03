 
#include "PhosRegisters.h"
#include <iostream>

const unsigned long ReadoutRegisters_t::fRcuRegisterAddresses[] = { RcuALTROIF_t::fRegAddress, 
								 RcuRDOMOD_t::fRegAddress,
								 RcuALTROCFG1_t::fRegAddress,
								 RcuALTROCFG2_t::fRegAddress };
const unsigned long ReadoutRegisters_t::fAltroRegisterAddresses[] = { AltroZSTHR_t::fRegAddress, 
								   AltroTRCFG_t::fRegAddress,
								   AltroDPCFG_t::fRegAddress,
								   AltroDPCFG2_t::fRegAddress };
const bool ReadoutRegisters_t::fRcuVerify[] = {false, false, false, false};

const bool ReadoutRegisters_t::fAltroVerify[] = {true, true, true, true};

ReadoutRegisters_t::ReadoutRegisters_t(RcuALTROIF_t altroif, RcuRDOMOD_t rdoMod, RcuALTROCFG1_t altrocfg1, 
		     RcuALTROCFG2_t altrocfg2)
{
  SetRcuALTROIF(altroif);
  SetRcuRDOMOD(rdoMod);
  SetRcuALTROCFG(altrocfg1, altrocfg2);
}

const unsigned long* ReadoutRegisters_t::GetRcuRegisterValues() 
{
  fRcuRegisterValues[0] = fRcuALTROIF.GetRegisterValue();
  fRcuRegisterValues[1] = fRcuRDOMOD.GetRegisterValue();
  fRcuRegisterValues[2] = fRcuALTROCFG1.GetRegisterValue();
  fRcuRegisterValues[3] = fRcuALTROCFG2.GetRegisterValue();
  return fRcuRegisterValues;
}

const unsigned long* ReadoutRegisters_t::GetAltroRegisterValues() 
{
  fAltroRegisterValues[0] = fAltroZSTHR.GetRegisterValue();
  fAltroRegisterValues[1] = fAltroTRCFG.GetRegisterValue();
  fAltroRegisterValues[2] = fAltroDPCFG.GetRegisterValue();
  fAltroRegisterValues[3] = fAltroDPCFG2.GetRegisterValue();
  return fAltroRegisterValues;
}

void ReadoutRegisters_t::SetRcuALTROIF(RcuALTROIF_t altroif)
{
  fRcuALTROIF = altroif;
  fAltroTRCFG.SetNSamples(altroif.GetNumberOfSamples());
}

void ReadoutRegisters_t::SetRcuRDOMOD(RcuRDOMOD_t rdomod)
{
  fRcuRDOMOD = rdomod;
  fAltroDPCFG2.SetMEBMode(rdomod.GetMEBMode());
}

void ReadoutRegisters_t::SetRcuALTROCFG(RcuALTROCFG1_t altrocfg1, RcuALTROCFG2_t altrocfg2)
{
  fRcuALTROCFG1 = altrocfg1;

  fAltroZSTHR.SetThreshold(altrocfg1.GetThreshold());
  fAltroZSTHR.SetOffset(altrocfg1.GetOffset());

  fAltroDPCFG.SetZeroSuppressed(altrocfg1.IsZeroSuppressionEnabled());
  fAltroDPCFG.SetAutomaticBaselineSubtraction(altrocfg1.UsingAutomaticBaselineSubtraction());

  fRcuALTROCFG2 = altrocfg2;
  
  fAltroDPCFG2.SetNPreSamples(altrocfg2.GetNPreSamples());

}

void ReadoutRegisters_t::Print(std::ostream& stream)
{
//   std::cout << "ReadoutRegisters_t: " << std::endl;
//   std::cout << "-------------------" << std::endl;
//   std::cout << "RCU Registers: " << std::endl;
//   std::cout << "ALTROIF   : 0x" << std::hex << fRcuALTROIF.GetRegisterValue() << std::endl;
//   std::cout << "RDOMOD    : 0x" << fRcuRDOMOD.GetRegisterValue() << std::endl;
//   std::cout << "ALTROCFG1 : 0x" << fRcuALTROCFG1.GetRegisterValue() << std::endl;
//   std::cout << "ALTROCFG2 : 0x" << fRcuALTROCFG2.GetRegisterValue() << std::endl;
//   std::cout << "-------------------" << std::endl;
//   std::cout << "ALTRO Registers:" << std::endl;
//   std::cout << "ZSTHR     : 0x" << fAltroZSTHR.GetRegisterValue() << std::endl;
//   std::cout << "TRCFG     : 0x" << fAltroTRCFG.GetRegisterValue() << std::endl;
//   std::cout << "DPCFG     : 0x" << fAltroDPCFG.GetRegisterValue() << std::endl;
//   std::cout << "DPCFG     : 0x" << fAltroDPCFG2.GetRegisterValue() << std::dec << std::endl;

  stream << "ReadoutRegisters_t: " << std::endl;
  stream << "-------------------" << std::endl;
  stream << "RCU Registers: " << std::endl;
  stream << "ALTROIF   : 0x" << std::hex << fRcuALTROIF.GetRegisterValue() << std::endl;
  stream << "RDOMOD    : 0x" << fRcuRDOMOD.GetRegisterValue() << std::endl;
  stream << "ALTROCFG1 : 0x" << fRcuALTROCFG1.GetRegisterValue() << std::endl;
  stream << "ALTROCFG2 : 0x" << fRcuALTROCFG2.GetRegisterValue() << std::endl;
  stream << "-------------------" << std::endl;
  stream << "ALTRO Registers:" << std::endl;
  stream << "ZSTHR     : 0x" << fAltroZSTHR.GetRegisterValue() << std::endl;
  stream << "TRCFG     : 0x" << fAltroTRCFG.GetRegisterValue() << std::endl;
  stream << "DPCFG     : 0x" << fAltroDPCFG.GetRegisterValue() << std::endl;
  stream << "DPCFG     : 0x" << fAltroDPCFG2.GetRegisterValue() << std::dec << std::endl;
}

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
      break;
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
  fL2LatencyWrtL1 = value & 0xfff;
  
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

int AltroZSTHR_t::GetRegisterValue() const
{
  return fOffset << 10 | fThreshold;
}

void AltroZSTHR_t::SetByRegisterValue(int value)
{
  fThreshold = value & 0x3ff;
  fOffset = value >> 10 & 0x3ff;
}


int AltroTRCFG_t::GetRegisterValue() const
{
  return fStart << 10 | fStop;
}

void AltroTRCFG_t::SetByRegisterValue(int value)
{
  fStart = value >> 10 & 0x3ff;
  fStop = value & 0x3ff;
}

int AltroDPCFG_t::GetRegisterValue() const
{

  return fFirstBaselineCorrection |
    fPolarity << 4 |
    fPreExcluded2 << 5 | 
    fPostExcluded2 << 7 | 
    fSecondBaselineCorrection << 11 | 
    fGlitchFilterConfig << 12 | 
    fPostExcludedZS << 14 | 
    fPreExcludedZS << 17 |
    fZeroSuppression << 19;

}

void AltroDPCFG_t::SetByRegisterValue(int value)
{
  fFirstBaselineCorrection = value & 0xf;
  fPolarity = value >> 4 & 0x1;
  fPreExcluded2 = value >> 5 & 0x3;
  fPostExcluded2 = value >> 7 & 0xf;
  fSecondBaselineCorrection = value >> 11 & 0x1;
  fGlitchFilterConfig = value >> 12 & 0x3;
  fPostExcludedZS = value >> 14 & 0x7;
  fPreExcludedZS = value >> 17 & 0x3;
  fZeroSuppression = value >> 19 & 0x1;
}

short AltroDPCFG2_t::GetRegisterValue() const
{
  return fNPreTriggerSamples |
    fMEBMode << 4 | 
    fDigitalFilterEnabled << 5 |
    fPowerSaveEnabled << 6;
}

void AltroDPCFG2_t::SetByRegisterValue(short value)
{
  fNPreTriggerSamples = value & 0xf;
  fMEBMode = value >> 4 & 0x1;
  fDigitalFilterEnabled = value >> 5 & 0x1;
  fPowerSaveEnabled = value >> 6 & 0x1;
}
