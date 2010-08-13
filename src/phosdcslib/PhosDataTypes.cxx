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
//#include "PhosConst.h"

#include "PhosDataTypes.h"

#include <iostream>

using namespace std;



/***********************************************/
/********** PhosSimpleDataType_t ***************/
/***********************************************/
PhosSimpleDataType_t::PhosSimpleDataType_t() : fVal ( 0 )
{

}



PhosSimpleDataType_t::~PhosSimpleDataType_t()
{

}


// PhosSimpleDataType_t::Save(FILE *fp)
// {
//   if(fp !=0)
//     {
//       fprintf(fp, "%s\t=%d\n", name, fval);
//     }
// }

// PhosSimpleDataType_t::Load(FILE *fp)
// {


// }

/***********************************************/
/********** ModNumber_t ************************/
/***********************************************/
ModNumber_t::ModNumber_t ( const int value ) : PhosSimpleDataType_t() //,
    //  fVal(0),
    //				   fIsinitialized(true)
{
  //  sprintf(name, "MODULE_NUMBER");
  SetIntValue ( value );
}


ModNumber_t::ModNumber_t() //:
//fVal(0),
//		    fIsinitialized(false)
{
  //  sprintf(name, "MODULE_NUMBER");
  SetIntValue ( 0 );
}


ModNumber_t::~ModNumber_t()
{

}


void
ModNumber_t::SetIntValue ( const int value )
{
  if ( ( value < PHOS_MODS ) && ( value >= 0 ) )
    {
      fVal = value;
    }

  else
    {
      cout <<"ModNumber_t::SetIntValue ;ERROR: attempt to set moduleID to" << value  <<endl;
      cout <<"ModNumber_t::SetIntValue; but the module ID has to be between zero and less than" << PHOS_MODS  <<endl;
      fVal = 0;
      cout <<"Setting module ID to "<<  fVal   <<endl;
    }
}



//   if(fIsinitialized == false)
//     {
//       if( (value < PHOS_MODS) && (value >= 0 ) )
// 	{
// 	  fVal = value;
// 	}

//       else
// 	{
// 	  cout <<"ModNumber_t::SetIntValue ;ERROR: attempt to set moduleID to" << value  <<endl;
// 	  cout <<"ModNumber_t::SetIntValue; but the module ID has to be between zero and less than" << PHOS_MODS  <<endl;
// 	  fVal = 0;
// 	  cout <<"Setting module ID to "<<  fVal   <<endl;
// 	}
//     }
//   else
//     {
//       cout << "Warning: object can pnly be initialized once, ignoring attaemt to set module ID, the ID is still"<< fVal << endl;
//     }




/***********************************************/
/*************** RcuNumber_t *******************/
/***********************************************/
RcuNumber_t::RcuNumber_t ( const int value ) : fVal ( 0 ),
    fIsinitialized ( false )
{
  SetIntValue ( value );

  fXMin = value * N_XCOLUMNS_BRANCH;
  fXMax = fXMin + N_XCOLUMNS_BRANCH;

  fZMin = value % BRANCHES_PER_RCU * N_ZROWS_BRANCH;
  fZMax = fZMin + N_ZROWS_BRANCH;

}


RcuNumber_t::~RcuNumber_t()
{

}


void
RcuNumber_t::SetIntValue ( const int value )
{
  if ( ( value < RCUS_PER_MODULE ) && ( value >= 0 ) )
    {
      fVal = value;
    }

  else
    {
      cout <<"RcuNumber_t::SetIntValue; ERROR: attempt to set rcu Number to" << value  <<endl;
      cout <<"RcuNumber_t::SetIntValue; but the module ID has to be between zero and " << RCUS_PER_MODULE  <<endl;
      fVal = 0;
      cout <<"Setting Rcu Number to "<< fVal << endl;
    }

//   if(fIsinitialized == false)
//     {
//       if( (value < RCUS_PER_MODULE) && (value >= 0 ) )
// 	{
// 	  fVal = value;
// 	}

//       else
// 	{
// 	  cout <<"RcuNumber_t::SetIntValue; ERROR: attempt to set rcu Number to" << value  <<endl;
// 	  cout <<"RcuNumber_t::SetIntValue; but the module ID has to be between zero and " << RCUS_PER_MODULE  <<endl;
// 	  fVal = 0;

// 	  cout <<"Setting Rcu Number to "<< fVal << endl;
// 	}
//     }
//   else
//     {
//       cout << "Warning: object can pnly be initialized once, ignoring attaemt to set module ID, the ID is still"<< fVal << endl;
//     }
}



/***********************************************/
/*************** BranchNumber_t ****************/
/***********************************************/
BranchNumber_t::BranchNumber_t ( const int value ) : fVal ( 0 ),
    fIsinitialized ( false )
{
  SetIntValue ( value );
}


void
BranchNumber_t::SetIntValue ( const int value )
{
  if ( fIsinitialized == false )
    {
      if ( ( value < BRANCHES_PER_RCU ) && ( value >= 0 ) )
        {
          fVal = value;
        }
      else
        {
          cout <<"BranchNumber_t::SetIntValue; ERROR: attempt to set rcu Number to" << value  <<endl;
          cout <<"BranchNumber_t::SetIntValue; but the module ID has to be between zero and " << BRANCHES_PER_RCU  <<endl;
          fVal = 0;
          cout <<"Setting branch number to  to "<<  fVal  << endl;
        }
    }
  else
    {
      cout << "Warning: object can only be initialized once, ignoring attaemt to set module ID, the ID is still"<< fVal << endl;
    }
}


/***********************************************/
/************ FeeSlotNumber_t ******************/
/***********************************************/
FeeSlotNumber_t::FeeSlotNumber_t ( const int value ) : fVal ( 0 ),
    fIsinitialized ( false )
{
  SetIntValue ( value );
}

void
FeeSlotNumber_t::SetIntValue ( const int value )
{
  if ( fIsinitialized == false )
    {
      if ( ( value < CARDS_PER_BRANCH+1 ) && ( value >= 1 ) )
        {
          fVal = value;
        }

      else
        {
          cout <<"FeeSlotNumber_t::SetIntValue; ERROR: attempt to set rcu Number to" << value  <<endl;
          cout <<"FeeSlotNumber_t::SetIntValue; but the module ID has to be between zero and " << CARDS_PER_BRANCH +1 <<endl;
          fVal = 0;
          cout <<"Setting branch number to  to "<<  fVal   << endl;
        }
    }
  else
    {
      cout << "Warning: object can pnly be initialized once, ignoring attempt to set feeslot number it remains" << fVal << endl;
    }
}



/***********************************************/
/************ FeePos_t *************************/
/***********************************************/
FeePos_t::FeePos_t() : fModuleID ( 0 ),
    fRcuID ( 0 ),
    fBranch ( 0 ),
    fCardSlot ( 0 ),
    fIsinitialized ( false )
{

}


FeePos_t::FeePos_t ( const ModNumber_t mod, const  RcuNumber_t rcu,
                     const BranchNumber_t  branch,  const FeeSlotNumber_t cardSlot ) :  fModuleID ( mod ),
    fRcuID ( rcu ),
    fBranch ( branch ),
    fCardSlot ( cardSlot ),
    fIsinitialized ( true )
{
  SetCardArrayIndex();
  SetAFLBitPosition();
}


FeePos_t::~FeePos_t()
{

}


void
FeePos_t::SetCardArrayIndex()
{
  if ( fIsinitialized == false )
    {
      fCardArrayIndex = ( fBranch.GetIntValue() ) *BRANCHES_PER_RCU + ( fCardSlot.GetIntValue()  -1 );
    }
  else
    {
      cout <<"FeePos_t::SetCardArrayIndex;ERROR: attempt to initialize a card that was allready initialized" <<endl;
    }
}



const int
FeePos_t::SetAFLBitPosition()
{
  int iRet = 0;

  if ( fIsinitialized == false )
    {
      fAFLBitPosition = ( fBranch.GetIntValue() ) *MAX_CARDS_PER_BRANCH + fCardSlot.GetIntValue();
      fAFLMask = 1 << fAFLBitPosition;
      iRet = 1;
    }
  else
    {
      cout <<"FeePos_t::SetAFLBitOsition; ERROR: attempt to initialize a card that was allready initialized"  <<endl;
      iRet = -1;
    }
  return iRet;
}


/***********************************************/
/************** NSamples_t *********************/
/***********************************************/
NSamples_t::NSamples_t() :fVal ( 0 )
{

}


NSamples_t::~NSamples_t()
{

}


NSamples_t::NSamples_t ( const unsigned long int n )
{
  SetIntValue ( n );
}



void
NSamples_t::SetIntValue ( const int val )
{
  if ( ( val <MAX_ALTRO_SAMPLES )  || ( val < 1 ) )
    {
      fVal =  val;
    }
  else
    {
      cout << "Warning: attempt to set the number of samples to " << val << " wich is out of range" << endl;
      cout << "The  number of presamples has to be between " << 0 <<"  and" << MAX_ALTRO_SAMPLES  << endl;

      if ( val <  MAX_ALTRO_SAMPLES )
        {
          fVal = MAX_ALTRO_SAMPLES;
          cout << "the number of samples was set to the maximum value " <<  MAX_ALTRO_SAMPLES  << endl;
        }
      else
        {
          fVal = 10;
          cout << "The number of samples was set to " << 1 <<  " wich is the smallest reasonable number of samples  "<<endl ;
        }

    }

}


/***********************************************/
/************** NPreSamples_t *********************/
/***********************************************/
NPreSamples_t::NPreSamples_t() :fVal ( 0 )
{

}


NPreSamples_t::NPreSamples_t ( const unsigned long int n ) :fVal ( 0 )
{
  SetIntValue ( n );
}


NPreSamples_t::~NPreSamples_t()
{

}


void
NPreSamples_t::SetIntValue ( const int val )
{
  if ( ( val < MAX_ALTRO_SAMPLES )  || ( val < 0 ) )
    {
      fVal =  val;
    }
  else
    {
      cout << "Warning: attempt to set the number of presamples to " << val << " wich is out of range" << endl;
      cout << "The  number of presamples has to be between " << 0 <<"  and" << MAX_ALTRO_SAMPLES << endl;

      if ( val < MAX_ALTRO_PRESAMPLES )
        {
          fVal = MAX_ALTRO_PRESAMPLES;
          cout << "the number of presamples was set to the maximum value " <<  MAX_ALTRO_PRESAMPLES  << endl;
        }
      else
        {
          fVal = 0;
          cout << "The number of presamples was set to " << 0 <<  " wich is the smallest reasonable number of samples  "<<endl ;
        }

    }
}



/***********************************************/
/******  ZeroSuppressionTreshold_t  *************/
/***********************************************/
ZeroSuppressionTreshold_t::ZeroSuppressionTreshold_t() : fVal ( 0 )
{

}


ZeroSuppressionTreshold_t::~ZeroSuppressionTreshold_t()
{

}


ZeroSuppressionTreshold_t::ZeroSuppressionTreshold_t ( const unsigned long  n ) : fVal ( 0 )
{
  SetIntValue ( n );
}

void
ZeroSuppressionTreshold_t::SetIntValue ( const int val )
{
  if ( ( val < MAX_ZEROSUPRESSION_THR )  || ( val < 0 ) )
    {
      fVal =  val;
    }
  else
    {
      cout << "Warning: attempt to set the zero supression  to " << val << " wich is out of range" << endl;
      cout << "The zero supression treshold to be between " << 0 <<"  and" <<   MAX_ZEROSUPRESSION_THR << endl;

      if ( val <   MAX_ZEROSUPRESSION_THR )
        {
          fVal =  MAX_ZEROSUPRESSION_THR;
          cout << "the number zero supression treshold   the maximum value " <<  MAX_ZEROSUPRESSION_THR << endl;
        }
      else
        {
          fVal = 0;
          cout << "The  zero supression treshold  was set to " << 0 <<endl ;
        }

    }
}


/***********************************************/
/******  ZeroSuppressionMode_t  *************/
/***********************************************/

ZeroSuppressionMode_t::ZeroSuppressionMode_t ( const unsigned long int val )
{
  SetIntValue ( val );
}


ZeroSuppressionMode_t::~ZeroSuppressionMode_t()
{

}

void
ZeroSuppressionMode_t::SetIntValue ( const int val )
{
  if ( ( val == 0 ) || ( val == 1 ) || ( val == 2 ) || ( val == 3 ) )
    {
      fVal = val;
    }
  else
    {

      fVal = 0;
      cout << " ZeroSuppressionMode_t::SetIntValue " << val << "out of range " <<endl;
      cout << "zerosupression mode set to "<< val  <<endl;
    }
}


/***********************************************/
/************ ReadoutMode_t ********************/
/***********************************************/
ReadoutMode_t::ReadoutMode_t() :fVal ( 0 )
{

}


ReadoutMode_t::ReadoutMode_t ( const unsigned long int n ) :fVal ( 0 )
{
  fVal = n;
}


ReadoutMode_t::~ReadoutMode_t()
{

}


void
ReadoutMode_t::SetIntValue ( const int val )
{
  fVal = val; // TODO !! check validity!
}

/***********************************************/
/***************  Pattern_t ********************/
/***********************************************/
Pattern_t::Pattern_t() :fPatternType ( RAMP_PATTERN ),
    fLength ( MAX_ALTRO_SAMPLES ),
    fStep ( 1 ),
    fMaxAmpl ( 1023 )
{

}

void Pattern_t::PrintInfo ( const char *message ) const
  {
    if ( message != 0 )
      {
        printf ( "\n%s", message );
      }

    printf ( "\nPattern_t printing values\n" );
    printf ( "Patterntype = \t%d\n", fPatternType );
    printf ( "Length = \t%d\n", fLength );
    printf ( "Step = \t%d\n", fStep );
    printf ( "Max Ampl =\t%d\n", fMaxAmpl );
  }


Pattern_t::~Pattern_t()
{

}



/***********************************************/
/************ AltroConfig_t ********************/
/***********************************************/
AltroConfig_t::AltroConfig_t() : fNSamples ( 0 ),
    fNPreSamples ( 0 ),
    fZeroSuppressionThreshold ( 0 ),
    fZeroSuppressionMode ( 0 ),
    fReadoutMode ( 0 )
{

}




AltroConfig_t::AltroConfig_t ( const NSamples_t nSamples, const NPreSamples_t  nPreSamples,
                               const ReadoutMode_t readoutmode, const  ZeroSuppressionMode_t  zmode,
                               const ZeroSuppressionTreshold_t  zthr ) : fNSamples ( 0 ),
    fNPreSamples ( 0 ),

    fZeroSuppressionThreshold ( 0 ),

    fZeroSuppressionMode ( 0 ),

    fReadoutMode ( 0 ),

    //								    fPattern(0),

    fApplyPattern ( false )




{
  SetNSamples ( nSamples );
  SetNPreSamples ( nPreSamples );
  SetReadoutMode ( readoutmode );
  SetZerosSuppressionMode ( zmode );
  SetZerosSuppressionTreshold ( zthr );

}


AltroConfig_t::~AltroConfig_t()
{

}

void
AltroConfig_t::PrintInfo ( const char *message ) const
  {
    if ( message !=0 )
      {
        cout << message;
      }

    cout <<  "AltroConfig_t printing info" << endl;
    cout <<  "NSampels = " << fNSamples.GetIntValue() << endl;
    cout <<  "NPresSampels = " << fNPreSamples.GetIntValue() << endl;
    cout <<  "ReadoutMode = " <<  fReadoutMode.GetIntValue() << endl;
    //                    GetPatternType()

    fPattern.PrintInfo();

//   cout <<  "Patterntyp =" <<  fPattern.GetPatternType()  << endl;
//   cout <<  "Pattern amplitude = "<<  fPattern.GetMaxAmpl()  << endl;
//   cout <<  "Pattern step =" << fPattern.GetStepSize()  << endl;
    cout <<  "Wether or not to apply pattern =";

    if ( GetApplyPattern() == true )
      {
        cout << "  TRUE"<< endl;
      }
    else
      {
        cout << "  FALSE" << endl;
      }

  }



void
AltroConfig_t::SetNSamples ( const NSamples_t nSamples )
{
  fNSamples = nSamples;
}


void
AltroConfig_t::SetNPreSamples ( const NPreSamples_t nPreSamples )
{
  fNPreSamples = nPreSamples;
}


void
AltroConfig_t::SetZerosSuppressionTreshold ( const ZeroSuppressionTreshold_t treshold )
{
  fZeroSuppressionThreshold =  treshold;
}


void
AltroConfig_t::SetZerosSuppressionMode ( const  ZeroSuppressionMode_t mode )
{
  fZeroSuppressionMode =  mode;
}

void
AltroConfig_t::SetReadoutMode ( const ReadoutMode_t readoutmode )
{
  fReadoutMode =  readoutmode;
}

/***********************************************/
/************* StartZ_t ************************/
/***********************************************/
StartZ_t::StartZ_t ( const int val ) : fVal ( val )
{
  SetIntValue ( val );
}



void
StartZ_t::SetIntValue ( const int value )
{
  if ( value >= 0 && value <  N_ZROWS_MOD )
    {
      fVal = value;
    }
  else
    {
      cout << "ERROR: StartZ_t::SetIntValue attampt to set StartZ to  "<< value <<" Wich is out of range" <<endl;
      cout << "Must be between zero and  " <<  N_ZROWS_MOD  << endl;
    }
}


/************* EndZ_t  *************************/
/****
EndX_t::SetIntValue(int)
*******************************************/
/***********************************************/
EndZ_t::EndZ_t ( const int val ) :fVal ( val )
{
  SetIntValue ( val );
}

void
EndZ_t::SetIntValue ( const int value )
{
  if ( value >= 0 && value <  N_ZROWS_MOD )
    {
      fVal = value;
    }
  else
    {
      cout << "ERROR: EndZ_t::SetIntValue attampt to set EndZ to  "<< value <<" Wich is out of range" <<endl;
      cout << "Must be between zero and  " <<  N_ZROWS_MOD  << endl;
    }
}


/***********************************************/
/************ StartX_t  ************************/
/***********************************************/
StartX_t::StartX_t ( const int val ) : fVal ( val )
{
  SetIntValue ( val );
}


void
StartX_t::SetIntValue ( const int value )
{
  if ( value >= 0 && value <  N_XCOLUMNS_MOD )
    {
      fVal = value;
    }
  else
    {
      cout << "ERROR: StartX_t::SetIntValue attampt to set StartX to  "<< value <<" Wich is out of range" <<endl;
      cout << "Must be between zero and  " <<  N_XCOLUMNS_MOD  << endl;
    }
}


/************** EndX_t *************************/
/***********************************************/
EndX_t::EndX_t ( const int val ) :fVal ( val )
{
  SetIntValue ( val );
}


void
EndX_t::SetIntValue ( const int value )
{
  if ( value >= 0 && value <  N_XCOLUMNS_MOD )
    {
      fVal = value;
    }
  else
    {
      cout << "ERROR: EndX_t::SetIntValue attampt to set EndX to  "<< value <<" Wich is out of range" <<endl;
      cout << "Must be between zero and  " <<  N_XCOLUMNS_MOD  << endl;
    }
}


/***********************************************/
/************* ReadoutRegion_t *****************/
/***********************************************/
ReadoutRegion_t::ReadoutRegion_t() :fHgStartZ ( 0 ),
    fHgEndZ ( 0 ),
    fHgStartX ( 0 ),
    fHgEndX ( 0 ),
    fLgStartZ ( 0 ),
    fLgEndZ ( 0 ),
    fLgStartX ( 0 ),
    fLgEndX ( 0 ),
    fIsTruEnabled ( false ),
    fTruSamplesMin ( 0 ),
    fTruSamplesMax(127)
{
  // CheckConsistency(const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx );


}



ReadoutRegion_t::ReadoutRegion_t ( const StartZ_t hgstartz, const EndZ_t hgendz, const StartX_t hgstartx, const EndX_t hgendx,
                                   const StartZ_t lgstartz, const EndZ_t lgendz, const StartX_t lgstartx, const EndX_t lgendx, const bool enableTRUFakeAltro, const int truSamplesMin, const int truSamplesMax ) :fHgStartZ ( 0 ),
    fHgEndZ ( 0 ),
    fHgStartX ( 0 ),
    fHgEndX ( 0 ),
    fLgStartZ ( 0 ),
    fLgEndZ ( 0 ),
    fLgStartX ( 0 ),
    fLgEndX ( 0 ),
    fIsTruEnabled ( enableTRUFakeAltro ),
    fTruSamplesMin ( 0 ),
    fTruSamplesMax( 0 )
  
{
  if ( CheckConsistency ( hgstartz, hgendz, hgstartx, hgendx ) == true && CheckConsistency ( lgstartz, lgendz, lgstartx, lgendx ) == true )
    {
      SetReadoutRegion ( hgstartz, hgendz, hgstartx, hgendx, lgstartz, lgendz, lgstartx, lgendx );
    }
  //  if ( fNTruSamples > 128 )
  //    {
  //      fNTruSamples = 127;
  //    }
  //  else
  //    {
  //      fNTruSamples = nTruSamples;
  //    }
  if( fTruSamplesMin > fTruSamplesMax)
    {
      fTruSamplesMin = fTruSamplesMax = 0;
    }
  else
    {
      fTruSamplesMax = truSamplesMax;
      fTruSamplesMin = truSamplesMin;
    }
  fIsTruEnabled = enableTRUFakeAltro;
}


ReadoutRegion_t::~ReadoutRegion_t()
{

}

const bool
ReadoutRegion_t::IsRcuEnabled ( const RcuNumber_t rcu ) const
  {
    //  return fStartX.GetIntValue() >= rcu.GetMinX() && fEndX.GetIntValue() <= rcu.GetMaxX()
    //    && fStartZ.GetIntValue() >= rcu.GetMinZ() && fEndZ.GetIntValue() <= rcu.GetMaxZ();
    return true;
  }

const bool
ReadoutRegion_t::IsBranchEnabled ( const RcuNumber_t rcu, const BranchNumber_t branch ) const
  {
//   return IsRcuEnabled(rcu)
//     && fStartZ.GetIntValue() >= rcu.GetMinZ() + N_ZROWS_BRANCH*branch.GetIntValue()
//     && fEndZ.GetIntValue() <= rcu.GetMaxZ() + (branch.GetIntValue() - 1)*N_ZROWS_BRANCH;
    return true;

  }

const bool
ReadoutRegion_t::IsTruReadoutEnabled ( const RcuNumber_t rcu, const BranchNumber_t branch ) const
  {
    return IsBranchEnabled ( rcu, branch );
  }

bool
ReadoutRegion_t::CheckConsistency ( const StartZ_t startz, const EndZ_t endz, const StartX_t startx, const EndX_t endx ) const
  {
    if ( ( startz.GetIntValue() <= endz.GetIntValue() )  && ( startx.GetIntValue() <= endx.GetIntValue() ) )
      {
        return true;
      }
    else
      {
        cout << "ReadoutRegion_t::CheckConsistency: ERROR  readout region not valid "  << endl;
        cout << "The readout region specified: startz ="<< startz.GetIntValue() << " endz =" << endz.GetIntValue() << endl;
        cout << "The readout region specified: startx ="<< startx.GetIntValue() << " endx =" << endx.GetIntValue() << endl;
        cout << "cannot bee applied because ";

        if ( startz.GetIntValue() > endz.GetIntValue() )
          {
            cout << "the ending z value is bigger than the  ending z value " << endl;
          }
        else if ( startx.GetIntValue()  > endx.GetIntValue() )
          {
            cout << "the ending x value is bigger than the  ending x value " << endl;
          }

        return false;
      }
  }



void
ReadoutRegion_t::PrintInfo ( const char *message ) const
  {
    if ( message != 0 )
      {
        cout << message;
      }

    cout <<  "ReadoutRegion_t printing info"<< endl;
    cout <<  "startZ =" << fHgStartZ.GetIntValue() << endl;
    cout <<  "endZ =" << fHgEndZ.GetIntValue() << endl;
    cout <<  "startX =" << fHgStartX.GetIntValue() << endl;
    cout <<  "endX =" << fHgEndX.GetIntValue() << endl;
  }

void
ReadoutRegion_t::SetReadoutRegion ( const StartZ_t hgstartz, const EndZ_t hgendz, const StartX_t hgstartx, const EndX_t hgendx,
                                    const StartZ_t lgstartz, const EndZ_t lgendz, const StartX_t lgstartx, const EndX_t lgendx )
{
  if ( CheckConsistency ( hgstartz, hgendz, hgstartx, hgendx ) == true && CheckConsistency ( lgstartz, lgendz, lgstartx, lgendx ) == true )
    {
      fHgStartZ =hgstartz;
      fHgEndZ = hgendz;
      fHgStartX = hgstartx;
      fHgEndX = hgendx;

      fLgStartZ =lgstartz;
      fLgEndZ = lgendz;
      fLgStartX = lgstartx;
      fLgEndX = lgendx;
    }
  else
    {
      fHgStartZ.SetIntValue ( 0 );
      fHgEndZ.SetIntValue ( 0 );
      fHgStartX.SetIntValue ( 0 );
      fHgEndX.SetIntValue ( 0 );

      fLgStartZ.SetIntValue ( 0 );
      fLgEndZ.SetIntValue ( 0 );
      fLgStartX.SetIntValue ( 0 );
      fLgEndX.SetIntValue ( 0 );
    }
}



/***********************************************/
/************** TriggerMode_t ******************/
/***********************************************/
TriggerMode_t::TriggerMode_t() :fVal ( 0 )
{

}


TriggerMode_t::TriggerMode_t ( const int value ) : fVal ( value )
{
  SetIntValue ( value );
}

void
TriggerMode_t::PrintInfo ( const char *message ) const
  {
    if ( message !=0 )
      {
        cout << message;
      }

    cout <<  " TriggerMode_t printing info"<< endl;
    cout << "triggermode = "<< fVal << endl;

  }


TriggerMode_t::~TriggerMode_t()
{

}




/***********************************************/
/********** ReadoutConfig_t ********************/
/***********************************************/
ReadoutConfig_t::ReadoutConfig_t()
{

}



ReadoutConfig_t::ReadoutConfig_t ( const AltroConfig_t altroconfig, const ReadoutRegion_t rdoregion, const TriggerMode_t triggerMode )
{
  fAltroConfig = altroconfig;
  fReadoutRegion = rdoregion;
  fTriggerMode = triggerMode;
}


ReadoutConfig_t::~ReadoutConfig_t()
{

}


void
ReadoutConfig_t::PrintInfo ( const char *message, bool printaltroconfig,
                             bool printreadoutregion, bool printtriggerconfig ) const
  {
    if ( message !=0 )
      {
        cout << message << endl;
      }
    if ( printaltroconfig == true )
      {
        fAltroConfig.PrintInfo();
      }
    if ( printreadoutregion == true )
      {
        fReadoutRegion.PrintInfo();
      }
    if ( printtriggerconfig == true )
      {
        fTriggerMode.PrintInfo();
      }
//   if( printpatterninfo == true)
//     {

//     }
  }


/***********************************************/
/************** ConfigInfo_t *******************/
/***********************************************/
const ConfigInfo_t &
ConfigInfo_t::operator = ( const  ConfigInfo_t &t )
{
  fID = t.fID;
  fIDLimit = t.fIDLimit;
  sprintf ( fInfo, "%s", t.fInfo );
}




/***********************************************/
/************** TRURegister_t ******************/
/***********************************************/
/***********************************************/
TRURegister_t::TRURegister_t() : fAddress ( 0 ),
    fVal ( 0 ),
    fReadOnly ( false )
{

}


TRURegister_t::TRURegister_t ( const unsigned long address, const unsigned long value, const char *name ) : fAddress ( 0 ),
    fVal ( 0 ),
    fReadOnly ( false )
{
  SetName ( name );
  SetAddress ( address );
  SetIntValue ( value );
}



TRURegister_t::~TRURegister_t()
{

}


void
TRURegister_t::PrintInfo() const
  {
    printf ( "Name:%s\tAddress: 0x%x\tValue:0x%x\t\n", fName,fAddress, fVal );

  }


/***********************************************/
/************** TRUSettings_t ******************/
/***********************************************/
/***********************************************/
TRUSettings_t::TRUSettings_t() : fNRegisters ( N_TRU_REGS ),
    fRegCnt ( 0 )

{

}


TRUSettings_t::~TRUSettings_t()
{


}


const int
TRUSettings_t::AddRegister ( const TRURegister_t reg )
{
  int iRet = 0;

  if ( fRegCnt >=fNRegisters )
    {
      iRet = -1;
    }
  else
    {
      fRegisters[fRegCnt].SetName ( reg.GetName() );
      fRegisters[fRegCnt].SetAddress ( reg.GetAddress() );
      fRegisters[fRegCnt].SetIntValue ( reg.GetIntValue() );
      fRegCnt ++;
    }

  return iRet;
}


const TRURegister_t
TRUSettings_t::GetRegister ( const int index ) const
  {
    if ( index > N_TRU_REGS )
      {
        return fRegisters[N_TRU_REGS -1];
      }
    else
      {
        return fRegisters[index];
      }
  }

void
TRUSettings_t::PrintInfo ( const char *message ) const
  {
    printf ( "\n TRUSettings_t printing info\n" );
    if ( message !=0 )
      {
        printf ( "messag: %s\n", message );
      }

    printf ( "*******************************\n" );
    printf ( "***Printing register table*****\n" );
    printf ( "*******************************\n" );

    for ( int i=0; i < N_TRU_REGS; i++ )
      {
        fRegisters[i].PrintInfo();
      }

  }


void
TRUSettings_t::Reset()
{
  fRegCnt = 0;
}
