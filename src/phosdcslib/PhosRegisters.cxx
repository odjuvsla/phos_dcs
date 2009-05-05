 
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
  
}

