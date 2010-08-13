
#ifndef PHOSREGISTERS_H
#define PHOSREGISTERS_H

#include "RcuRegisterMap.h"
#include "AltroRegisterMap.h"
#include <iostream>

class RcuALTROIF_t;
class RcuRDOMOD_t;
class RcuALTROCFG1_t;
class RcuALTROCFG2_t;
class RcuTRGCONF_t;

class RcuL1LAT_t;
class RcuL1MSGLAT_t;

class AltroTRCFG_t;
class AltroZSTHR_t;
class AltroDPCFG_t;
class AltroDPCFG2_t;


class AltroSettings_t
{
public:

    static const int fBSFixedMode = 0x0;
    static const int fBSAutomaticMode = 0x4;
};

class RcuALTROIF_t
{

public:

    RcuALTROIF_t();
    RcuALTROIF_t ( short nSamples, int sampleFreq = 10000000, short cstbDelay = 0, short instructionErrorCheck = 0 );

    RcuALTROIF_t ( const RcuALTROIF_t& v ) :
            fNSamples ( v.GetNumberOfSamples() ),
            fSampleFreq ( v.GetSampleFrequency() ),
            fCstbDelay ( v.GetCstbDelay() ),
            fInstructionErrorCheck ( v.InstructionErrorCheck() )
    {
    }

    short GetNumberOfSamples() const
    {
        return fNSamples;
    }
    int GetSampleFrequency() const
    {
        return fSampleFreq;
    }
    short GetCstbDelay() const
    {
        return fCstbDelay;
    }
    short InstructionErrorCheck() const
    {
        return fInstructionErrorCheck;
    }

    int GetRegisterValue();

    void SetNumberOfSamples ( short nSamples )
    {
        fNSamples = nSamples;
    }
    void SetSampleFrequency ( int freq )
    {
        fSampleFreq = freq;
    }
    void SetCstbDelay ( short cstbd )
    {
        fCstbDelay = cstbd;
    }
    void SetInstructionErrorCheck ( short val )
    {
        fInstructionErrorCheck = val;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = RcuRegisterMap::ALTROIF; // 0x5101

private:

    short fNSamples;
    int fSampleFreq;
    short fCstbDelay;
    short fInstructionErrorCheck;


};

class RcuTRGCONF_t
{
    // If one of the three different triggers are enabled the RCU is ready to recieve triggers
    // Trigger mode is
    // 0 for TPC (L1 from CTP is mapped to L1 on FECs
    // 1 for PHOS (L0 from CTP is mapped to L1 on FECs

public:

    RcuTRGCONF_t();

    RcuTRGCONF_t ( bool softwareTrigger, bool auxTrigger, bool ttcrxTrigger, bool phosTriggerMode = true, short latency = 0xfff );

    RcuTRGCONF_t ( const RcuTRGCONF_t& v ) :
            fSoftwareTrigger ( v.IsSoftwareTriggerEnabled() ),
            fAuxTrigger ( v.IsAuxTriggerEnabled() ),
            fTTCrxTrigger ( v.IsTTCrxTriggerEnabled() ),
            fPHOSTriggerMode ( v.IsPHOSTriggerMode() ),
            fL2LatencyWrtL1 ( v.GetL2LatencyWrtL1() )
    {

    }

    bool IsSoftwareTriggerEnabled() const
    {
        return fSoftwareTrigger;
    }
    bool IsAuxTriggerEnabled() const
    {
        return fAuxTrigger;
    }
    bool IsTTCrxTriggerEnabled() const
    {
        return fTTCrxTrigger;
    }
    bool IsPHOSTriggerMode() const
    {
        return fPHOSTriggerMode;
    }

    short GetL2LatencyWrtL1() const
    {
        return fL2LatencyWrtL1;
    }

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

    void SetPHOSTriggerMode ( bool ptm = true )
    {
        fPHOSTriggerMode = true;
    }

    void SetL2LatencyWrtL1 ( int latency )
    {
        fL2LatencyWrtL1 = latency;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = RcuRegisterMap::TRCFG; //0x5102

private:

    bool fSoftwareTrigger;
    bool fAuxTrigger;
    bool fTTCrxTrigger;
    bool fPHOSTriggerMode;

    short fL2LatencyWrtL1;

    int fRegisterValue;

};

class RcuRDOMOD_t
{

public:

    RcuRDOMOD_t();
    RcuRDOMOD_t ( bool maskRDYRX, bool sparseReadoutEnabled, bool sparseReadoutEnabledRcu, bool executeSequencer, bool mebMode );

    RcuRDOMOD_t ( const RcuRDOMOD_t& v ) :
            fMaskRDYRX ( v.IsMaskRDYRXEnabled() ),
            fSparseReadout ( v.IsSparseReadoutEnabled() ),
            fSparseReadoutRcu ( v.IsSparseReadoutRcuEnabled() ),
            fExecuteSequencer ( v.IsExecuteSequencerEnabled() ),
            fMEBMode ( v.GetMEBMode() )
    {
    }

    bool IsMaskRDYRXEnabled() const
    {
        return fMaskRDYRX;
    }
    bool IsSparseReadoutEnabled() const
    {
        return fSparseReadout;
    }
    bool IsSparseReadoutRcuEnabled() const 
    {
       return fSparseReadoutRcu;
    }
    bool IsExecuteSequencerEnabled() const
    {
        return fExecuteSequencer;
    }
    bool GetMEBMode() const
    {
        return fMEBMode;
    }

    short GetRegisterValue();

    void SetMaskRDYRX ( bool value = true )
    {
        fMaskRDYRX = value;
    }
    void SetSparseReadout ( bool value = true )
    {
        fSparseReadout = value;
    }
    void SetSparseReadoutRcu ( bool value = true )
    {
       fSparseReadoutRcu = value;
    }
    void SetExecuteSeqencer ( bool value = true )
    {
        fExecuteSequencer = value;
    }
    void SetMEBMode ( bool value = true )
    {
        fMEBMode = value;
    }

    void SetByRegisterValue ( short value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const short fRegAddress = RcuRegisterMap::RDOMOD; //0x5103

private:

    bool fMaskRDYRX;
    bool fSparseReadout;
    bool fSparseReadoutRcu;
    bool fExecuteSequencer;
    bool fMEBMode;

    int fRegisterValue;

};

class RcuALTROCFG1_t
{
    // Re-defining content of the ALTROCFG1 register on the RCU
    // Width is 16 bits

public:

    RcuALTROCFG1_t();
    RcuALTROCFG1_t ( bool zsEnabled, bool automaticBS, short offset, short zsThreshold );

    RcuALTROCFG1_t ( const RcuALTROCFG1_t& v ) :
            fZeroSuppressionEnabled ( v.IsZeroSuppressionEnabled() ),
            fAutomaticBaselineSubtraction ( v.UsingAutomaticBaselineSubtraction() ),
            fOffset ( v.GetOffset() ),
            fThreshold ( v.GetThreshold() )
    {
    }

    bool IsZeroSuppressionEnabled() const
    {
        return fZeroSuppressionEnabled;
    }
    
    bool UsingAutomaticBaselineSubtraction() const
    {
        return fAutomaticBaselineSubtraction;
    }
    
    short GetOffset() const
    {
        return fOffset;
    }
    
    short GetThreshold() const
    {
        return fThreshold;
    }

    short GetRegisterValue();

    void SetZerosSupressionEnabled ( bool zs = true )
    {
        fZeroSuppressionEnabled = zs;
    }
    
    void SetAutomaticBaselineSubtractionEnabled ( bool abs = true )
    {
        fAutomaticBaselineSubtraction = abs;
    }

    void SetOffset ( short offset )
    {
        fOffset = offset;
    }
    
    void SetThreshold ( short threshold )
    {
        fThreshold = threshold;
    }

    void SetByRegisterValue ( short value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const short fRegAddress = RcuRegisterMap::ALTROCFG1; // 0x5104

private:

    bool fZeroSuppressionEnabled; // 1 bit reserved
    bool fAutomaticBaselineSubtraction; // 1 bit reserved
    short fOffset; // 4 bits reserved (reduced to facilitate for the possibility for a high threshold)
    short fThreshold; // 10 bits reserved (may want to use threshold up to 1023 to test readout performance)

    int fRegisterValue;

};

class RcuALTROCFG2_t
{
    // Content of the ALTROCFG2 register on the RCU from the RCU manual
    // Width is 25 bits

public:

    RcuALTROCFG2_t() :
    fNAltroBuffers()
            ,fNPreSamples ( 11 )
            ,fNSamples(51)
            ,fSparseReadout(false)
            ,fSampleFreq(10000000)
    {}

    RcuALTROCFG2_t ( short nAltroBuffers, short nPreSamples, short nSamples, bool sparseReadout, int sampleFreq);

    RcuALTROCFG2_t ( const RcuALTROCFG2_t& v ) :
    fNAltroBuffers(v.GetNAltroBuffers())
      ,fNPreSamples(v.GetNPreSamples())
      ,fNSamples(v.GetNSamples())
      ,fSparseReadout(v.IsSparseReadoutEnabled())
      ,fSampleFreq(v.GetSampleFrequency())
    {
    }

   short GetNAltroBuffers() const
   {
	 return fNAltroBuffers;
   }

    short GetNPreSamples() const
    {
        return fNPreSamples;
    }

    short GetNSamples() const 
      {
	return fNSamples;
      }
    
    short IsSparseReadoutEnabled() const 
    {
       return fSparseReadout;
    }

   int GetSampleFrequency() const 
   {
      return fSampleFreq;
   }

    short GetRegisterValue();

    void SetNAltroBuffers(short nAltroBuffers);
    
    void SetNPreSamples ( short nPreSamples )
    {
        fNPreSamples = nPreSamples;
    }

   void SetSparseReadout(bool sparseReadout)
   {
      fSparseReadout = sparseReadout;
   }

   void SetSampleFrequency(int sampleFreq);

    void SetByRegisterValue ( short value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = RcuRegisterMap::ALTROCFG2; // 0x5105

private:
    short  fNAltroBuffers; //1 bit, (0 = 4 buffers, 1 = 8 buffers
    short fNPreSamples; // 4 bits reserved
    short fNSamples; // 10 bits reserved
    bool fSparseReadout; // 1 bit reserved
    int fSampleFreq; // (20 MHz, 10 MHz, 5 MHz, 2.5 MHz) 4 bits reserved in register

};


class RcuL1LAT_t
{

    // Register contains the L0 - L1 latency and the uncertainty
    // given in number of bunch crossings (25 ns).
    // Width is 16 bits

public:
    RcuL1LAT_t() :
            fLatency ( 260 ),
            fUncertainty ( 2 )
    {
    }

    RcuL1LAT_t ( short latency, short uncertainty = 2 ) :
            fLatency ( latency ),
            fUncertainty ( uncertainty )
    {
    }

    RcuL1LAT_t ( const RcuL1LAT_t& v ) :
            fLatency ( v.GetLatency() ),
            fUncertainty ( v.GetUncertainty() )
    {
    }

    short GetLatency() const
    {
        return fLatency;
    }
    short GetUncertainty() const
    {
        return fUncertainty;
    }

    short GetRegisterValue() const
    {
        return ( fUncertainty << 12 ) | fLatency;
    }

    float GetLatencyInUs() const
    {
        return static_cast<float> ( fLatency ) * 0.025;
    }

    void SetByRegisterValue ( short value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = RcuRegisterMap::L1_LATENCY;

private:

    short fLatency; //12 bits
    short fUncertainty; //4 bits

};

class RcuL1MSGLAT_t
{

    // Register contains the L1 message minimum and maximum latency wrt BC0 in
    // bunch crossings
    // Width is 32 bits

public:
    RcuL1MSGLAT_t() :
            fMinLatency ( 260 ),
            fMaxLatency ( 3200 )
    {
    }

    RcuL1MSGLAT_t ( short min, short max ) :
            fMinLatency ( min ),
            fMaxLatency ( max )
    {
    }
    RcuL1MSGLAT_t ( const RcuL1MSGLAT_t& v ) :
            fMinLatency ( v.GetMinLatency() ),
            fMaxLatency ( v.GetMaxLatency() )
    {
    }

    int GetMinLatency() const
    {
        return fMinLatency;
    }

    int GetMaxLatency() const
    {
        return fMaxLatency;
    }

    int GetRegisterValue() const
    {
        return ( fMinLatency << 16 ) | fMaxLatency;
    }

    float GetMinLatencyInUs() const
    {
        return static_cast<float> ( fMinLatency ) * 0.025;
    }

    float GetMaxLatencyInUs() const
    {
        return static_cast<float> ( fMaxLatency ) * 0.025;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = RcuRegisterMap::L1_MSG_LATENCY;

private:

    short fMaxLatency; // 16 bits
    short fMinLatency; // 16 bits

};

class AltroZSTHR_t
{
    // The ZSTHR register on the ALTRO chip contains the threshold for zerosuppression and
    // the offset added to the data

public:

    AltroZSTHR_t() :
            fThreshold ( 0 ),
            fOffset ( 0 )
    {
    }
    AltroZSTHR_t ( short threshold, short offset ) :
            fThreshold ( threshold ),
            fOffset ( offset )
    {
    }

    ~AltroZSTHR_t() {}

    AltroZSTHR_t ( const AltroZSTHR_t& v ) :
            fThreshold ( v.GetThreshold() ),
            fOffset ( v.GetOffset() )
    {
    }

    short GetThreshold() const
    {
        return fThreshold;
    }
    short GetOffset() const
    {
        return fOffset;
    }

    int GetRegisterValue() const;

    void SetThreshold ( short threshold )
    {
        fThreshold = threshold;
    }
    void SetOffset ( short offset )
    {
        fOffset = offset;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = AltroRegisterMap::ZSTHR;

private:

    short fThreshold; //10 bits
    short fOffset;  // 10 bits

};


class AltroTRCFG_t
{
    // The TRCFG register contains the start and end of the data acquisition, basically
    // it sets the number of samples recorded

public:

    AltroTRCFG_t() :
            fStart ( 0 ),
            fStop ( 0 )
    {
    }

    AltroTRCFG_t ( short start, short stop ) :
            fStart ( start ),
            fStop ( stop )
    {
    }

    AltroTRCFG_t ( short nSamples ) :
            fStart ( 0 ),
            fStop ( nSamples )
    {
    }

    ~AltroTRCFG_t() {}

    AltroTRCFG_t ( const AltroTRCFG_t& v ) :
            fStart ( v.GetStart() ),
            fStop ( v.GetStop() )
    {
    }

    short GetStart() const
    {
        return fStart;
    }
    short GetStop() const
    {
        return fStop;
    }
    short GetNSamples() const
    {
        return fStop - fStart;
    }

    int GetRegisterValue() const;

    void SetStart ( short start )
    {
        fStart = start;
    }
    void SetStop ( short Stop )
    {
        fStop = Stop;
    }
    void SetNSamples ( short nSamples )
    {
        fStart = 0;
        fStop = nSamples;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = AltroRegisterMap::TRCFG;

private:

    short fStart; //10 bits
    short fStop;  // 10 bits

};


class AltroDPCFG_t
{
    // The DPCFG register contains settings for baseline correction and zero suppression

public:

    AltroDPCFG_t() :
            fFirstBaselineCorrection ( 0 ),
            fPolarity ( false ),
            fPreExcluded2 ( 0 ),
            fPostExcluded2 ( 0 ),
            fSecondBaselineCorrection ( false ),
            fGlitchFilterConfig ( 0 ),
            fPostExcludedZS ( 0 ),
            fPreExcludedZS ( 0 ),
            fZeroSuppression ( false )
    {
    }

    ~AltroDPCFG_t() {}


    AltroDPCFG_t ( const AltroDPCFG_t& v ) :
            fFirstBaselineCorrection ( v.GetFirstBaselineCorrectionMode() ),
            fPolarity ( false ),
            fPreExcluded2 ( 0 ),
            fPostExcluded2 ( 0 ),
            fSecondBaselineCorrection ( false ),
            fGlitchFilterConfig ( 0 ),
            fPostExcludedZS ( 0 ),
            fPreExcludedZS ( 0 ),
            fZeroSuppression ( v.IsZeroSuppressed() )
    {
    }

    short GetFirstBaselineCorrectionMode() const
    {
        return fFirstBaselineCorrection;
    }
    bool IsZeroSuppressed() const
    {
        return fZeroSuppression;
    }

    bool IsAutomaticBaselineSubtracted() const
    {
        return fFirstBaselineCorrection == 0x4;
    }
    bool IsFixedBaselineSubtracted() const
    {
        return fFirstBaselineCorrection == 0;
    }

    short GetNumberOfPostSamplesExcludedFromZS()
    {
        return fPostExcludedZS;
    }

    short GetNumberOfPreSamplesExcludedFromZS()
    {
        return fPreExcludedZS;
    }

    int GetRegisterValue() const;

    void SetFirstBaselineCorrectionMode ( short mode )
    {
        fFirstBaselineCorrection = mode;
    }

    void SetZeroSuppressed ( bool value = true )
    {
        fZeroSuppression = value;
    }

    void SetAutomaticBaselineSubtraction ( bool value )
    {
        if ( value )
        {
            fFirstBaselineCorrection = AltroSettings_t::fBSAutomaticMode;
        }
        else
        {
            fFirstBaselineCorrection = AltroSettings_t::fBSFixedMode;
	}
    }
    
    void SetFixedBaselineSubtraction ( bool value )
    {
        if ( value )
        {
            fFirstBaselineCorrection = AltroSettings_t::fBSFixedMode;
        }
        else
        {
            fFirstBaselineCorrection = AltroSettings_t::fBSAutomaticMode;
        }
    }

    void SetNumberOfPostSamplesExcludedFromZS(short val)
    {
        fPostExcludedZS = val & 0x7;
    }

    void SetNumberOfPreSamplesExcludedFromZS(short val)
    {
        fPreExcludedZS = val & 0x3;
    }

    void SetByRegisterValue ( int value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = AltroRegisterMap::DPCFG;

private:

    short fFirstBaselineCorrection; /* First Baseline Correction Mode - 4 bits*/
    bool fPolarity; /* Polarity. When set, the ADC data is inverted - 1 bit */
    short fPreExcluded2; /* Number of Presamples excluded from 2 Baseline Correction - 2 bits */
    short fPostExcluded2; /* Number of Postsamples excluded from 2 Baseline Correction - 4 bits*/
    bool fSecondBaselineCorrection; /* Enable Second Baseline Correction - 1 bit */
    short fGlitchFilterConfig; /* Glitch Filter Configuration for Zero Suppression - 2 bits */
    short fPostExcludedZS; /* Number of Postsamples excluded from suppression - 3 bits */
    short fPreExcludedZS; /* Number of Presamples excluded from suppression - 2 bits */
    bool fZeroSuppression; /* Enable Zero Suppression */

};

class AltroDPCFG2_t
{

    // Register contains the number of pre samples, multi event buffer mode (4 or 8), digital filter
    // and power save

public:

    AltroDPCFG2_t() :
            fNPreTriggerSamples ( 11 ),
            fMEBMode ( 0 ),
            fDigitalFilterEnabled ( false ),
            fPowerSaveEnabled ( false )
    {
    }

    AltroDPCFG2_t ( short presamples, bool mebmode = false,
                    bool digitalfilter = false, bool powersave = false ) :
            fNPreTriggerSamples ( presamples ),
            fMEBMode ( mebmode ),
            fDigitalFilterEnabled ( digitalfilter ),
            fPowerSaveEnabled ( powersave )
    {
    }

    AltroDPCFG2_t ( const AltroDPCFG2_t& v ) :
            fNPreTriggerSamples ( v.GetNPreSamples() ),
            fMEBMode ( v.GetMEBMode() ),
            fDigitalFilterEnabled ( v.IsFilterEnabled() ),
            fPowerSaveEnabled ( v.IsPowerSaveEnabled() )
    {
    }

    short GetNPreSamples() const
    {
        return fNPreTriggerSamples;
    }
    bool GetMEBMode() const
    {
        return fMEBMode;
    }
    bool IsFilterEnabled() const
    {
        return fDigitalFilterEnabled;
    }
    bool IsPowerSaveEnabled() const
    {
        return fPowerSaveEnabled;
    }

    short GetRegisterValue() const;

    void SetNPreSamples ( short npresamples )
    {
        fNPreTriggerSamples = npresamples;
    }
    void SetMEBMode ( bool mebmode )
    {
        fMEBMode = mebmode;
    }
    void SetFilterEnabled ( bool value = true )
    {
        fDigitalFilterEnabled = value;
    }
    void SetPowerSaveEnabled ( bool value = true )
    {
        fPowerSaveEnabled = value;
    }

    void SetByRegisterValue ( short value );

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

    static const int fRegAddress = AltroRegisterMap::DPCFG2;

private:

    short fNPreTriggerSamples;
    bool fMEBMode;
    bool fDigitalFilterEnabled;
    bool fPowerSaveEnabled;

};


class ReadoutRegisters_t
{

public:

    ReadoutRegisters_t() {}

    ReadoutRegisters_t ( RcuALTROIF_t altroif, RcuRDOMOD_t rdoMod, RcuALTROCFG1_t altrocfg1,
                         RcuALTROCFG2_t altrocfg2, RcuL1LAT_t lOneLat, RcuL1MSGLAT_t lOneMsgLat );

    ReadoutRegisters_t ( const ReadoutRegisters_t& v ) :
            fRcuALTROIF ( v.GetRcuALTROIF() ),
            fRcuRDOMOD ( v.GetRcuRDOMOD() ),
            fRcuALTROCFG1 ( v.GetRcuALTROCFG1() ),
            fRcuALTROCFG2 ( v.GetRcuALTROCFG2() ),
            fRcuL1LAT ( v.GetRcuL1LAT() ),
            fRcuL1MSGLAT ( v.GetRcuL1MSGLAT() ),
            fAltroZSTHR ( v.GetAltroZSTHR() ),
            fAltroTRCFG ( v.GetAltroTRCFG() ),
            fAltroDPCFG ( v.GetAltroDPCFG() ),
            fAltroDPCFG2 ( v.GetAltroDPCFG2() )
    {
    }

    ~ReadoutRegisters_t() {}

    const unsigned long* GetRcuRegisterAddresses() const
    {
        return fRcuRegisterAddresses;
    }
    const unsigned long* GetRcuRegisterValues();

    const int GetNRcuRegisters() const
    {
        return 6;
    }

    const unsigned long* GetAltroRegisterAddresses() const
    {
        return fAltroRegisterAddresses;
    }

    const unsigned long* GetAltroRegisterValues();

    const int GetNAltroRegisters() const
    {
        return 4;
    }

    RcuALTROIF_t GetRcuALTROIF() const
    {
        return fRcuALTROIF;
    }
    RcuRDOMOD_t GetRcuRDOMOD() const
    {
        return fRcuRDOMOD;
    }
    RcuALTROCFG1_t GetRcuALTROCFG1() const
    {
        return fRcuALTROCFG1;
    }
    RcuALTROCFG2_t GetRcuALTROCFG2() const
    {
        return fRcuALTROCFG2;
    }
    RcuL1LAT_t GetRcuL1LAT() const
    {
        return fRcuL1LAT;
    }
    RcuL1MSGLAT_t GetRcuL1MSGLAT() const
    {
        return fRcuL1MSGLAT;
    }

    const bool* GetRcuVerify() const
    {
        return fRcuVerify;
    }

    void SetRcuALTROIF ( RcuALTROIF_t altroif );
    void SetRcuRDOMOD ( RcuRDOMOD_t rdomod );
    void SetRcuALTROCFG ( RcuALTROCFG1_t altrocfg1, RcuALTROCFG2_t altrocfg2 );
    void SetRcuL1LAT ( RcuL1LAT_t lOneLat )
    {
        fRcuL1LAT = lOneLat;
    }
    void SetRcuL1MSGLAT ( RcuL1MSGLAT_t lOneMsgLat )
    {
        fRcuL1MSGLAT = lOneMsgLat;
    }

    AltroZSTHR_t GetAltroZSTHR() const
    {
        return fAltroZSTHR;
    }
    AltroTRCFG_t GetAltroTRCFG() const
    {
        return fAltroTRCFG;
    }
    AltroDPCFG_t GetAltroDPCFG() const
    {
        return fAltroDPCFG;
    }
    AltroDPCFG2_t GetAltroDPCFG2() const
    {
        return fAltroDPCFG2;
    }

    const bool* GetAltroVerify() const
    {
        return fAltroVerify;
    }

    /*   void SetAltroZSTHR(AltroZSTHR_t zsthr); */
    /*   void SetAltroTRCFG(AltroTRCFG_t trcfg); */
    /*   void SetAltroDPCFG(AltroDPCFG_t dpcfg); */
    /*   void SetAltroDPCFG2(AltroDPCFG2_t dpcfg2); */

    void Print ( std::ostream& stream, std::string level = std::string ( "" ) );

private:

    RcuALTROIF_t fRcuALTROIF;
    RcuRDOMOD_t fRcuRDOMOD;
    RcuALTROCFG1_t fRcuALTROCFG1;
    RcuALTROCFG2_t fRcuALTROCFG2;
    RcuL1LAT_t fRcuL1LAT;
    RcuL1MSGLAT_t fRcuL1MSGLAT;

    AltroZSTHR_t fAltroZSTHR;
    AltroTRCFG_t fAltroTRCFG;
    AltroDPCFG_t fAltroDPCFG;
    AltroDPCFG2_t fAltroDPCFG2;

    static const unsigned long fRcuRegisterAddresses[];
    static const unsigned long fAltroRegisterAddresses[];

    static const bool fRcuVerify[];

    static const bool fAltroVerify[];

    unsigned long fRcuRegisterValues[6];

    unsigned long fAltroRegisterValues[4];

};



#endif
