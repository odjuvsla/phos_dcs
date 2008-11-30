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

#include "PhosNumberEntry.h"
#include <iostream>

using namespace std;

ClassImp(PhosNumberEntry)


PhosNumberEntry::~PhosNumberEntry()
{

}


PhosNumberEntry::PhosNumberEntry(const TGWindow* parent, Double_t val, Int_t digitwidth, Int_t id, 
				 TGNumberFormat::EStyle style, TGNumberFormat::EAttribute attr, 
				 TGNumberFormat::ELimit limits,
				 Double_t min, Double_t max):  
  TGNumberEntry(parent , val, digitwidth, id, style, attr, limits, min, max)
{
  fButtonToNum = kFALSE;
}


void
PhosNumberEntry::ValueChanged(Long_t t) //*SIGNAL*
{
  int tmp = GetIntNumber();
  Long_t args[1];
  args[0] = t;

  if(t == 10000)
    {
      if(tmp > lowLimit)
	{
	  SetIntNumber(tmp -1);
	} 
    }
  else if(t == 0)
    {
      if(tmp < (highLimit))
	{
	  SetIntNumber(tmp +1); 

	}
    }
  //  cout << "PhosNumberEntry::ValueChanged(Long_t t)"   << endl;

  Emit("ValueChanged(Long_t)", t);

}


void
PhosNumberEntry::ValueSet(Long_t t)
{
  int tmp = GetIntNumber();

  if(t == 10000)
    {
      if(tmp > highLimit)
	{
	  SetIntNumber(highLimit);
	  tmp = highLimit;
	}
      else if(tmp < lowLimit)
	{         
	  SetIntNumber(lowLimit); 
	  tmp = lowLimit;
	}
    }
  else if(t == 0)
    {
      if(tmp > highLimit)
	{
	  SetIntNumber(highLimit);
	  tmp = highLimit;
	}
      else if(tmp < lowLimit)
	{
	  SetIntNumber(lowLimit); 
	  
	  tmp = lowLimit;
	}
    }
  //  cout << "PhosNumberEntry::ValueSet(Long_t t)"   << endl;
  //  ValueChanged(t);
}


void
PhosNumberEntry::SetLimits(int low, int high)
{
  lowLimit  = low;
  highLimit = high;
}
