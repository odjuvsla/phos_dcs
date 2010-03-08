
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
#include "RcuRegisterMap.h"
//using namespace PhosConst;
#include <iostream>
#include <string>
#include <cstdio>

using namespace PhosConst;


class PhosSimpleDataType_t
  {
  public:
    PhosSimpleDataType_t();
    ~PhosSimpleDataType_t();
    const int GetIntValue() const
      {
        return fVal;
      };
    virtual void SetIntValue ( const int value ) = 0;
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
    ModNumber_t ( const int value );
    ~ModNumber_t();
    //  const int GetIntValue() const {return fVal;};
    void SetIntValue ( const int value );
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
    RcuNumber_t ( const int value );
    ~RcuNumber_t();
    const int GetIntValue() const
      {
        return fVal;
      };
    const int GetMinX() const
      {
        return fXMin;
      }
    const int GetMinZ() const
      {
        return fZMin;
      }
    const int GetMaxX() const
      {
        return fXMax;
      }
    const int GetMaxZ() const
      {
        return fZMax;
      }

  private:
    void SetIntValue ( const int value );
    RcuNumber_t();
    int fVal;
    int fXMin;
    int fZMin;
    int fXMax;
    int fZMax;
    bool fIsinitialized;
  };


/*
 *Branchh can be either A (0) or B (1)
 */
class BranchNumber_t
  {
  public:
    BranchNumber_t ( const int value );
    const int GetIntValue() const
      {
        return fVal;
      };

  private:
    BranchNumber_t();
    void SetIntValue ( const int branch );
    int fVal;
    bool fIsinitialized;
  };


class FeeSlotNumber_t
  {
  public:
    FeeSlotNumber_t ( const int value );
    const int GetIntValue() const
      {
        return  fVal;
      };
  private:
    FeeSlotNumber_t();
    void SetIntValue ( const int branch );
    int fVal;
    bool fIsinitialized;
  };

// class TruSlotNumber_t
// {
//  public:
//   TruSlotNumber_t(const int value);
//   const int GetIntValue() const {return  fVal;};
//  private:
//   TruSlotNumber_t();
//   void SetIntValue(const int value);
//   int fVal;
//   bool fIsinitialized;
// };


class FeePos_t
  {
  public:
    //  FeePos_t(const int mod, const int rcu, const int branch, const int card);
    FeePos_t ( ModNumber_t  mod, RcuNumber_t rcu,  BranchNumber_t branch,  FeeSlotNumber_t card );
    ~FeePos_t();
    const ModNumber_t  GetModuleID() const
      {
        return fModuleID;
      };
    const RcuNumber_t  GetRcuID()  const
      {
        return fRcuID;
      };
    const BranchNumber_t  GetBranch() const
      {
        return fBranch;
      };
    const FeeSlotNumber_t GetCardPos() const
      {
        return fCardSlot;
      };
    const int GetCardArrayIndex() const
      {
        return fCardArrayIndex;
      };
    const int GetAFLBitPosition() const
      {
        return  fAFLBitPosition;
      };
    const unsigned long int GetfAFLMask()
    {
      return  fAFLMask;
    };

  private:
    FeePos_t();
    void SetModuleID ( const ModNumber_t  mod )
    {
      fModuleID = mod;
    };
    void SetRcuID ( const RcuNumber_t  rcu )
    {
      fRcuID = rcu;
    } ;
    void SetBranch ( const BranchNumber_t branch )
    {
      fBranch = branch;
    };
    void SetCardSlot ( const FeeSlotNumber_t slot )
    {
      fCardSlot = slot;
    } ;

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
    NSamples_t ( const unsigned long int n );
    NSamples_t();
    ~NSamples_t();
    void SetIntValue ( const int val );
    const unsigned long  GetIntValue() const
      {
        return  fVal;
      };

  private:
    unsigned long fVal;
  };


class NPreSamples_t
  {
  public:
    NPreSamples_t ( const unsigned long int n );
    NPreSamples_t();
    ~NPreSamples_t();
    void SetIntValue ( const int val );
    const unsigned long  GetIntValue() const
      {
        return  fVal;
      };

  private:
    unsigned long fVal;
  };


class ZeroSuppressionTreshold_t
  {
  public:
    ZeroSuppressionTreshold_t ( const unsigned long int n );
    ZeroSuppressionTreshold_t();
    ~ ZeroSuppressionTreshold_t();
    void SetIntValue ( const int val );
    const unsigned long  GetIntValue() const
      {
        return  fVal;
      };

  private:
    unsigned long fVal;
  };


class ZeroSuppressionMode_t
  {
  public:
    ZeroSuppressionMode_t() {}
    ZeroSuppressionMode_t ( const unsigned long int n );
    ~ ZeroSuppressionMode_t();
    void SetIntValue ( const int val );
    const unsigned long  GetIntValue() const
      {
        return  fVal;
      };

  private:
    unsigned long fVal;
  };


class ReadoutMode_t
  {
  public:
    ReadoutMode_t ( const unsigned long int n );
    ReadoutMode_t();
    ~ ReadoutMode_t();
    void SetIntValue ( const int val );
    const unsigned long GetIntValue() const
      {
        return  fVal;
      };

  private:
    unsigned long fVal;
  };


class Pattern_t
  {
  public:
    Pattern_t();
    ~Pattern_t();
    void SetPatternType ( const int patterntype )
    {
      fPatternType = patterntype;
    };
    void SetLength ( const int length )
    {
      fLength = length;
    };
    void SetStep ( const int step )
    {
      fStep = step;
    };
    void SetAmplitude ( const int a )
    {
      fMaxAmpl = a;
    };
    //  void SetPattern(const int *pattern, const int length);
    const int GetPatternType() const
      {
        return fPatternType;
      };
    const int GetPatternLength() const
      {
        return fLength;
      } ;
    const int GetStepSize() const
      {
        return fStep;
      };
    const int GetMaxAmpl() const
      {
        return fMaxAmpl;
      } ;
    void PrintInfo ( const char *message = 0 ) const;

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
    AltroConfig_t ( const NSamples_t nSamples, const NPreSamples_t  nPreSamples,
                    const ReadoutMode_t readoutmode = 0, const  ZeroSuppressionMode_t  zmode =0,
                    const ZeroSuppressionTreshold_t zthr =0 );
    ~AltroConfig_t();
    void PrintInfo ( const char *message = 0 ) const ;
    void SetNSamples ( const  NSamples_t nSamples );
    void SetNPreSamples ( const NPreSamples_t  nPreSamples );
    void SetZerosSuppressionTreshold ( const ZeroSuppressionTreshold_t  treshold );
    void SetZerosSuppressionMode ( const  ZeroSuppressionMode_t  mode );
    void SetReadoutMode ( const  ReadoutMode_t  readoutmode );
    void SetPattern ( const Pattern_t pattern )
    {
      fPattern = pattern;
    };
    void SetApplyPattern ( bool  apply = true )
    {
      fApplyPattern =apply;
    };
    //  bool GetApplyPattern()const {return fApplyPattern;};
    const NSamples_t   GetNSamples() const
      {
        return   fNSamples;
      };
    const NPreSamples_t    GetNPreSamples() const
      {
        return fNPreSamples;
      };
    const ZeroSuppressionTreshold_t    GetZerosSuppressionTreshold() const
      {
        return fZeroSuppressionThreshold;
      };
    const ZeroSuppressionMode_t    GetZerosSuppressionMode() const
      {
        return fZeroSuppressionMode;
      };
    const ReadoutMode_t  GetReadoutMode() const
      {
        return fReadoutMode;
      };
    const Pattern_t GetPattern() const
      {
        return fPattern;
      };
    const bool GetApplyPattern() const
      {
        return fApplyPattern;
      };

  private:
    NSamples_t  fNSamples;
    NPreSamples_t   fNPreSamples;
    ZeroSuppressionTreshold_t  fZeroSuppressionThreshold;
    ZeroSuppressionMode_t  fZeroSuppressionMode;
    ReadoutMode_t  fReadoutMode;
    Pattern_t fPattern;
    bool fApplyPattern;

  };


class StartZ_t
  {
  public:
    StartZ_t ( const int val = 0 );
    void SetIntValue ( const int value );
    const int  GetIntValue() const
      {
        return fVal;
      };
  private:
    int fVal;
  };


class EndZ_t
  {
  public:
    //  EndZ_t();
    EndZ_t ( const int val = 0 );
    void SetIntValue ( const int value );
    const int  GetIntValue() const
      {
        return fVal;
      };
  private:
    // EndZ_t();
    int fVal;
  };


class StartX_t
  {
  public:
    //  StartX_t();
    StartX_t ( const int val = 0 );
    void SetIntValue ( const int value );
    const int GetIntValue() const
      {
        return fVal;
      };
  private:

    int fVal;
  };


class EndX_t
  {
  public:
    //  EndX_t();
    EndX_t ( const int val = 0 );
    void SetIntValue ( const int value );
    const int  GetIntValue() const
      {
        return fVal;
      };
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
    ReadoutRegion_t ( const StartZ_t hgstartz, const EndZ_t hgendz, const StartX_t hgstartx, const EndX_t hgendx,
                      const StartZ_t lgstartz, const EndZ_t lgendz, const StartX_t lgstartx, const EndX_t lgendx, const bool enableTRUFakeAltro, const int nTruSamples = 0 );
    ~ReadoutRegion_t();
    void PrintInfo ( const char *message = 0 ) const ;
    void SetReadoutRegion ( const StartZ_t hgstartz, const EndZ_t hgendz, const StartX_t hgstartx, const EndX_t hgendx,
                            const StartZ_t lgstartz, const EndZ_t lgendz, const StartX_t lgstartx, const EndX_t lgendx );

    void SetNumberOfTruSamples ( const int nTruSamples )
    {
      fNTruSamples = nTruSamples;
    }

    const StartZ_t  GetHGStartZ() const
      {
        return fHgStartZ;
      };
    const EndZ_t    GetHGEndZ() const
      {
        return fHgEndZ;
      } ;
    const StartX_t  GetHGStartX() const
      {
        return fHgStartX;
      };
    const EndX_t    GetHGEndX() const
      {
        return fHgEndX;
      };

    const StartZ_t  GetLGStartZ() const
      {
        return fLgStartZ;
      };
    const EndZ_t    GetLGEndZ() const
      {
        return fLgEndZ;
      } ;
    const StartX_t  GetLGStartX() const
      {
        return fLgStartX;
      };
    const EndX_t    GetLGEndX() const
      {
        return fLgEndX;
      };

    const int GetNumberOfTRUSamples() const
      {
        return fNTruSamples;
      }

    const bool IsRcuEnabled ( const RcuNumber_t rcu ) const;
    const bool IsBranchEnabled ( const RcuNumber_t rcu, const BranchNumber_t branch ) const;
    const bool IsTruReadoutEnabled ( const RcuNumber_t rcu, const BranchNumber_t branch ) const;

    const bool IsTruReadoutEnabled() const
      {
        return fIsTruEnabled;
      }


  private:
    bool CheckConsistency ( const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx ) const;

    StartZ_t  fHgStartZ;
    EndZ_t    fHgEndZ;
    StartX_t  fHgStartX;
    EndX_t    fHgEndX;

    StartZ_t  fLgStartZ;
    EndZ_t    fLgEndZ;
    StartX_t  fLgStartX;
    EndX_t    fLgEndX;

    bool      fIsTruEnabled;
    int     fNTruSamples; // In the readout region class due to being set by ALTRO mapping

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
    TriggerMode_t ( const int value );
    ~TriggerMode_t();
    void PrintInfo ( const char *message = 0 ) const;

    void SetIntValue ( const int value )
    {
      if ( ( value == 0 ) || ( value == 2 ) || ( value == 3 ) )
        {
          fVal = value;
        }
      else
        {
          fVal = 0;
        };
    }

    const int GetIntValue() const
      {
        return fVal;
      }

  private:

    int fVal;

  };



class ReadoutConfig_t
  {
  public:
    ReadoutConfig_t ( const AltroConfig_t altroconfig, const ReadoutRegion_t rdoconfig, const TriggerMode_t triggerMode );
    ~ReadoutConfig_t();
    ReadoutConfig_t();

    void PrintInfo ( const char *message,
                     bool printaltroconfig = true,
                     bool printreadoutregion = true,
                     bool printtriggerconfig = true ) const;

    void SetAltroConfig ( const AltroConfig_t altroConfig )
    {
      fAltroConfig = altroConfig;
    };
    void SetReadoutRegion ( const ReadoutRegion_t readoutRegion )
    {
      fReadoutRegion = readoutRegion;
    };
    void SetTriggerConfig ( const  TriggerMode_t triggerMode )
    {
      fTriggerMode = triggerMode;
    };
    void SetPattern ( Pattern_t p )
    {
      fAltroConfig.SetPattern ( p ) ;
    };
    void SetApplyPattern ( bool b = false )
    {
      fAltroConfig.SetApplyPattern ( b );
    };
    void SetReadoutMode ( const  ReadoutMode_t  readoutmode )
    {
      fAltroConfig.SetReadoutMode ( readoutmode );
    };
    const AltroConfig_t GetAltroConfig()       const
      {
        return fAltroConfig;
      };
    const ReadoutRegion_t GetReadoutRegion()   const
      {
        return fReadoutRegion;
      };
    const TriggerMode_t GetTriggerMode()       const
      {
        return fTriggerMode;
      } ;

  private:
    // ReadoutConfig_t();
    AltroConfig_t   fAltroConfig;
    ReadoutRegion_t fReadoutRegion;
    TriggerMode_t fTriggerMode;
  };

class ReadoutSettings_t
  {

  public:

    ReadoutSettings_t() :
        fNPreSamples ( 11 ),
        fNSamples ( 81 ),
        fIsZeroSuppressed ( false ),
        fZeroSuppressionThreshold ( 0 ),
        fZeroSuppressionOffset ( 0 ),
        fIsSparseReadout ( false ),
        fIsAutoBaselineSubtracted ( false ),
        fMEBMode ( false )
    {

    }

    ReadoutSettings_t ( const NPreSamples_t npresamples, NSamples_t nsamples, bool isZS = false, short zsThreshold = 0,
                        short zsOffset = 0, bool isSparse = false, bool isAutoBS = false, bool mebMode = false ) :
        fNPreSamples ( npresamples ),
        fNSamples ( nsamples ),
        fIsZeroSuppressed ( isZS ),
        fZeroSuppressionThreshold ( zsThreshold ),
        fZeroSuppressionOffset ( zsOffset ),
        fIsSparseReadout ( isSparse ),
        fIsAutoBaselineSubtracted ( isAutoBS ),
        fMEBMode ( mebMode )
    {}

    ~ReadoutSettings_t() {}

    ReadoutSettings_t ( const ReadoutSettings_t& v ) :
        fNPreSamples ( v.GetNPreSamples() ),
        fNSamples ( v.GetNSamples() ),
        fIsZeroSuppressed ( v.IsZeroSuppressed() ),
        fZeroSuppressionThreshold ( v.GetZeroSuppressionThreshold() ),
        fZeroSuppressionOffset ( v.GetZeroSuppressionOffset() ),
        fIsSparseReadout ( v.IsSparseReadout() ),
        fIsAutoBaselineSubtracted ( v.IsAutoBaselineSubtracted() ),
        fMEBMode ( v.GetMEBMode() )
    {}

    NPreSamples_t GetNPreSamples() const
      {
        return fNPreSamples;
      }
    NSamples_t GetNSamples() const
      {
        return fNSamples;
      }
    bool IsZeroSuppressed() const
      {
        return fIsZeroSuppressed;
      }
    short GetZeroSuppressionThreshold() const
      {
        return fZeroSuppressionThreshold;
      }
    short GetZeroSuppressionOffset() const
      {
        return fZeroSuppressionOffset;
      }
    bool IsSparseReadout() const
      {
        return fIsSparseReadout;
      }
    bool IsAutoBaselineSubtracted() const
      {
        return fIsAutoBaselineSubtracted;
      }
    bool GetMEBMode() const
      {
        return fMEBMode;
      }

  private:

    NPreSamples_t fNPreSamples;
    NSamples_t fNSamples;
    bool fIsZeroSuppressed;
    short fZeroSuppressionThreshold;
    short fZeroSuppressionOffset;
    bool fIsSparseReadout;
    bool fIsAutoBaselineSubtracted;
    bool fMEBMode;

  };


class ConfigInfo_t
  {
  public:
    const ConfigInfo_t & operator= ( const ConfigInfo_t &t );
    char fInfo[1024];
    int fID;
    int fIDLimit;
  };


class TRURegister_t

  {
  public:
    TRURegister_t();
    TRURegister_t ( const unsigned long address, const unsigned long value, const char *name );
    ~TRURegister_t();
    const char* GetName() const
      {
        return fName;
      };
    const unsigned long GetAddress() const
      {
        return fAddress;
      };
    const unsigned long GetIntValue() const
      {
        return fVal;
      };
    void SetName ( const char *name )
    {
      sprintf ( fName,"%s",name );
    };
    void SetAddress ( const unsigned long address )
    {
      fAddress = address;
    };
    void SetIntValue ( const unsigned long val )
    {
      fVal = val;
    };
    void SetIsReadOnly ( const bool isreadonly = true )
    {
      fReadOnly = isreadonly;
    }  ;
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
    TRUSettings_t& operator= ( const TRUSettings_t& )
    {
    }
    const TRURegister_t GetRegister ( const int index ) const;
    const int GetRegisterCount() const
      {
        return fRegCnt;
      };
    const int AddRegister ( const TRURegister_t reg );
    void PrintInfo ( const char *message = 0 ) const;
    void Reset();
  private:
    const int fNRegisters;
    int fRegCnt;
    TRURegister_t fRegisters[N_TRU_REGS];
  };

struct FeeServer
  {
    std::string fName;
    int fModId;
    int fRcuId;
    int fZ;
    int fX;
  };


//class Pattern_t


#endif
