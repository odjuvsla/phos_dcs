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

#include <iostream>
#include "ApdInput.h"
#include "TGNumberEntry.h"
#include "TGLabel.h"

using std::cout;
using std::endl; 


ApdInput::ApdInput()
{
  printf("\ncan not use class ApdInput without initialisation \n");
}


ApdInput::ApdInput(TGMainFrame *fPtr) : TGGroupFrame(fPtr,"APD DAC values"), 
					fFramePtr(0)
{
  fFramePtr = fPtr; 
  DrawInput(); 
}


ApdInput::~ApdInput()
{
  

}

void 
ApdInput::SetApdValues(int values[CSPS_PER_FEE])
{
  for(int i= 0; i< CSPS_PER_FEE; i++)
    {
      fApdEntryPtr[i]->SetIntNumber(values[i]);
      
    }
}


void 
ApdInput::ResetApdValues()
{
  for(int i= 0; i< CSPS_PER_FEE; i++)
    {
      fApdEntryPtr[i]->SetIntNumber(0);
    }
}


void
ApdInput::DrawLabels(const int rcu, const  int br, const int card)
{
  int branch = br;
  int rcuZ = rcu%2;
  int rcuX;

  if(rcu < 2)
    {
      rcuX = 0;
    }
   else  
     {
       rcuX = 1;
     }

  char tmp[20];

  for(int i=0; i<16; i++)
    {
      sprintf(tmp,"%d", i + rcuX*32 + branch*16);
      fRowLabelPtr[i]=new TGLabel(fFramePtr, tmp);
      fRowLabelPtr[i]->MoveResize(250,i*26+47,30,18); 
    }

  for(int i=0; i<2; i++)
    {
      sprintf(tmp, "%d", rcuZ*28 + (card-1)*2 + i);
      fColumnLabelPtr[i]=new TGLabel(fFramePtr, tmp);
      fColumnLabelPtr[i]->MoveResize( 280 +i*60, 470, 30, 18);
    }
  fFramePtr->MapSubwindows(); 
}


void
ApdInput::DrawInput()
{
  char temp[10];
  int x  = 10;
  int w  = 50;  //width
  int h  = 13;  //height
  int vs  = 0;   //vertival spacing
  int hs = 3;  //horizontal spacing
  int by=25;  //border in Y direction
  int bx =10;

  TGNumberFormat::ELimit limit = TGNumberFormat::kNELLimitMinMax;

  this->MoveResize(275, 20, 120, 460);

  for(int i=0; i<31; i+=2)
    {
      fApdEntryPtr[i]  = new TGNumberEntry(this, 0, 4, -1, (TGNumberFormat::EStyle) 5);
      fApdEntryPtr[i]->SetLimits(limit, 0, 1023); 
      fApdEntryPtr[i]->Move(x, i*(h+vs)+by);

      fApdEntryPtr[i+1]= new TGNumberEntry(this, 0, 4, -1, (TGNumberFormat::EStyle) 5);
      fApdEntryPtr[i+1]->SetLimits(limit, 0, 1023);
      fApdEntryPtr[i+1]->Move(x+w+hs, i*(h+vs)+by);
    }

  MapSubwindows();
  fFramePtr->MapSubwindows();
}


void 
ApdInput::GetApdValues(unsigned long *apdvalues)
{
  for(int i=0; i< CSPS_PER_FEE; i++)
    {
      apdvalues[i] = (unsigned long)fApdEntryPtr[i]->GetIntNumber();
    }
}

