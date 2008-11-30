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

#include "PhosHexNumberEntry.h"

ClassImp(PhosHexNumberEntry)


PhosHexNumberEntry::~PhosHexNumberEntry()
{

}


PhosHexNumberEntry::PhosHexNumberEntry(const TGWindow* parent, Double_t val, Int_t digitwidth, Int_t id, 
				       TGNumberFormat::EStyle style, TGNumberFormat::EAttribute attr, 
				       TGNumberFormat::ELimit limits,
				       Double_t min, Double_t max):  
  TGNumberEntry(parent , val, digitwidth, id, style, attr, limits, min, max)
{
  fButtonToNum = kFALSE;
}


void
PhosHexNumberEntry::ValueChanged(Long_t t)
{
  int tmp = GetHexNumber();

  if(t == 10000)
    {
      if(tmp > lowLimit)
	{
	  SetHexNumber(tmp -1);
	} 
      else
	{

	}
    }
  else if(t == 0)
    {
      if(tmp < (highLimit))
	{
	  SetHexNumber(tmp +1); 
	}
      else 
	{ 

	}
    }
}


void
PhosHexNumberEntry::ValueSet(Long_t t)
{
  int tmp = GetHexNumber();

  if(t == 10000)
    {
      if(tmp > highLimit)
	{
	  SetHexNumber(highLimit);
	  tmp = highLimit;
	}
      else if(tmp < lowLimit)
	{         
	  SetHexNumber(lowLimit); 
	  tmp = lowLimit;
	}
    }
  else if(t == 0)
    {
      if(tmp > highLimit)
	{
	  SetHexNumber(highLimit);
	  tmp = highLimit;
	}
      else if(tmp < lowLimit)
	{
	  SetHexNumber(lowLimit); 
	  tmp = lowLimit;
	}
    }
}


void
PhosHexNumberEntry::SetLimits(int low, int high)
{
  lowLimit  = low;
  highLimit = high;
}
