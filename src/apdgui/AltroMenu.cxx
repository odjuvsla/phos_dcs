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
#include "AltroMenu.h"

ClassImp(AltroMenu)


AltroMenu::AltroMenu() : PhosDcsWidget()
{

}

AltroMenu::~AltroMenu()
{

}


AltroMenu::AltroMenu(TGMainFrame *framePtr, int X, int Y, int W, int H) : PhosDcsWidget()
{
  /*

  databasePtr = new DatabaseDummy();
  databasePtr->LoadTriggerConfig(&samples, &preSamples, &startZ, &endZ, &startX, &endX);
  electronicsMenuPtr=new TGGroupFrame(framePtr,"Electronics Configuration"); 
  electronicsMenuPtr->MoveResize(X, Y,  W, H); 
  readoutConfigMenuPtr=new TGGroupFrame(electronicsMenuPtr,"Readout Configuration"); 
  readoutConfigMenuPtr->MoveResize(20, 270, 190, 170); 
  saveButtPtr = new PhosMenuButton(readoutConfigMenuPtr, 'i', "Save");
  saveButtPtr->MoveResize(130, 20, 50,20 );
  startLabelPtr = new TGLabel(readoutConfigMenuPtr, "From");
  startLabelPtr-> MoveResize( 30, 40, 50, 20);
  endLabelPtr = new TGLabel(readoutConfigMenuPtr, "To");
  endLabelPtr-> MoveResize(100, 40, 50, 20);
  startZInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, startZ,  5, -1, (TGNumberFormat::EStyle) 5);
  startZInputPtr->MoveResize( 30, 60, 40, 18);
  startZInputPtr->SetLimits(0, 55);
  endZInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, endZ, 5, -1, (TGNumberFormat::EStyle) 5);
  endZInputPtr->MoveResize( 100,  60, 40, 18); 
  endZInputPtr->SetLimits(0, 55);
  startXInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, startX, 5, -1, (TGNumberFormat::EStyle) 5);
  startXInputPtr->MoveResize(30, 80, 40, 18);
  startXInputPtr->SetLimits(0, 63);
  endXInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, endX, 5, -1, (TGNumberFormat::EStyle) 5);
  endXInputPtr->MoveResize(  100, 80, 40, 18); 
  endXInputPtr->SetLimits(0, 63);
  zLabelPtr = new TGLabel(readoutConfigMenuPtr, "Z");
  zLabelPtr-> MoveResize(     10,   60, 20, 20);
  xLabelPtr = new TGLabel(readoutConfigMenuPtr, "X");
  xLabelPtr-> MoveResize(     10,  80, 20, 20);
  nSamplesInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, samples, 5, -1, (TGNumberFormat::EStyle) 5);
  nSamplesInputPtr->MoveResize(120, 120, 50, 18);
  nSamplesInputPtr->SetLimits(0, 1008);
  nPreSamplesInputPtr = new PhosNumberEntry(readoutConfigMenuPtr, preSamples, 5, -1, (TGNumberFormat::EStyle) 5);
  nPreSamplesInputPtr->MoveResize(120, 140, 50, 18);
  nPreSamplesInputPtr->SetLimits(0, 15);
  nSamplesLabelPtr =  new TGLabel(readoutConfigMenuPtr, "Samples");
  nSamplesLabelPtr->MoveResize(20, 120, 70, 20);
  nPreSamplesLabelPtr= new TGLabel(readoutConfigMenuPtr, "Pre-Samples");
  nPreSamplesLabelPtr->MoveResize(20, 140, 70, 20);
  readoutConfigMenuPtr->MapSubwindows();
  electronicsMenuPtr->MapSubwindows();
  */
}


void
AltroMenu::SetStartZ(int startZ)
{
  printf("\nAltroMenu::SetStartZ\n");
  startZInputPtr->SetIntNumber(startZ);
}

void
AltroMenu::SetEndZ(int endZ)
{
  endZInputPtr->SetIntNumber(endZ);
}

void
AltroMenu::SetStartX(int startX)
{
  startXInputPtr->SetIntNumber(startX);
}

void
AltroMenu::SetEndX(int endX)
{
  endXInputPtr->SetIntNumber(endX);
}

void
AltroMenu::SetNSamples(int samples)
{
  nSamplesInputPtr->SetIntNumber(samples);
}


void
AltroMenu::SetNPreSamples(int preSamples)
{
  nPreSamplesInputPtr->SetIntNumber(preSamples);
}


int
AltroMenu::GetStartZ()
{
  return startZInputPtr->GetIntNumber(); 
}


int
AltroMenu::GetEndZ()
{
  return endZInputPtr->GetIntNumber(); 
}

int
AltroMenu::GetStartX()
{
 return startXInputPtr->GetIntNumber(); 
}

int
AltroMenu::GetEndX()
{
 return endXInputPtr->GetIntNumber(); 
}

int
AltroMenu::GetNSamples()
{
   return nSamplesInputPtr->GetIntNumber(); 
}

int
AltroMenu::GetNPreSamples()
{
 return nPreSamplesInputPtr->GetIntNumber(); 
}

