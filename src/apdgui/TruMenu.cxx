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

#include "TruMenu.h"
#include "PhosMenuButton.h" 
#include "PhosHexNumberEntry.h"
#include "TGFrame.h"
#include "TGLabel.h"

ClassImp(TruMenu)

TruMenu::TruMenu()
{

}


TruMenu::~TruMenu()
{

}


//TruMenu::TruMenu(TGMainFrame *framePtr, int X, int Y, int W, int H)
TruMenu::TruMenu(TGMainFrame *framePtr, TRUSettings_t trusettings, int X, int Y, int W, int H)
{
//   for(int i=0; i< N_TRU_REGS; i++)
//     { 
//       fTruRegisterMap[i] = 0;
//       fVerify[i] = 0;
//       fTruRegValue[i] = 0; 
//     }

  SetTRUSettings(trusettings);


//   fTruRegisterMap[0] = 0x72,  fVerify[0] = kTRUE;
//   fTruRegisterMap[1] = 0x73,  fVerify[1] = kFALSE;
//   fTruRegisterMap[2] = 0x74;  fVerify[2] = kFALSE;
//   fTruRegisterMap[3] = 0x75;  fVerify[3] = kFALSE;
//   fTruRegisterMap[4] = 0x76;  fVerify[4] = kFALSE;
//   fTruRegisterMap[5] = 0x77;  fVerify[5] = kFALSE;
//   fTruRegisterMap[6] = 0x78;  fVerify[6] = kFALSE;

  fVerify[0] = kTRUE;
  fVerify[1] = kFALSE;
  fVerify[2] = kFALSE;
  fVerify[3] = kFALSE;
  fVerify[4] = kFALSE;
  fVerify[5] = kFALSE;
  fVerify[6] = kFALSE;



  fElectronicsMenuPtr=new TGGroupFrame(framePtr,"TRU Registers"); 
  fElectronicsMenuPtr->MoveResize(20, 160,  250, 250); 
  fSaveButtPtr = new PhosMenuButton(fElectronicsMenuPtr,  "Save");
  fSaveButtPtr->MoveResize(20, 20, 50,20 );
  fApplyButtPtr = new PhosMenuButton(fElectronicsMenuPtr,  "Apply");
  fApplyButtPtr->MoveResize(120, 20, 50,20 );
  DrawRegisters(fElectronicsMenuPtr);
  fElectronicsMenuPtr->MapSubwindows();

  //   fNSamplesInputPtr->Connect("ValueChanged(Long_t)", "ElectronicsMenu", this, "EmitReadoutConfigChangedSignal(ReadoutConfig_t*)"); 
  
  fSaveButtPtr->Connect("HandleButton(Event_t*)", "TruMenu", this, "EmitSaveSettingsSignal(const TRUSettings *t)" );

}

void 
TruMenu::EmitSaveSettingsSignal(const TRUSettings_t *t) //*SIGNAL*
{
  cout << "TruMenu::EmitSaveSettingsSignal"  << endl;

  const TRUSettings_t tmp =  GetTRUSettings();
  tmp.PrintInfo("TruMenu::EmitSaveSettingsSigna");

  Emit("EmitSaveSettingsSignal(const TRUSettings_t*)", (Long_t)(&tmp));
  
}

void
TruMenu::DrawRegisters(TGGroupFrame *framePtr)
{
  int vSpacing = 5;
  int width = 70;
  int heigth =20;

//   sprintf(fTruLabeltxt[0], "0x%x  THR_L0    ", 0x72);
//   sprintf(fTruLabeltxt[1], "0x%x  THR_Low   ", 0x73);
//   sprintf(fTruLabeltxt[2], "0x%x  THR_Middle", 0x74);
//   sprintf(fTruLabeltxt[3], "0x%x  THR_High  ", 0x75);
//   sprintf(fTruLabeltxt[4], "0x%x  stavg     ", 0x76);
//   sprintf(fTruLabeltxt[5], "0x%x  TRG_EN    ", 0x77);
//   sprintf(fTruLabeltxt[6], "0x%x  ?         ", 0x78);

  for(int i=0; i< N_TRU_REGS; i++)
    {
      fTruRegLabelPtr[i] = new TGLabel(framePtr, fTruLabeltxt[i]);
      fTruRegLabelPtr[i]->MoveResize(20, 50 + i*(vSpacing + heigth), width + 50, heigth);
      fTruRegInputPtr[i] = new PhosHexNumberEntry(framePtr, fTruRegValue[i], 5, -1, (TGNumberFormat::EStyle) 12 );   
      fTruRegInputPtr[i]->SetLimits(0 , 0xffff);

      fTruRegInputPtr[i]->MoveResize(140, 50 + i*(vSpacing + heigth), width, heigth);
    }
}


int
TruMenu::GetTruRegisterValue(int index)
{
  int tmp =0;
  if(index > N_TRU_REGS)
    {
      printf("Error; index out of range");
    }
  else
    { 
      tmp =fTruRegInputPtr[index]->GetHexNumber(); 
    }
  return tmp;
}


int
TruMenu::GetTruRegisterAddress(int index)
{
  int tmp =0;
  if(index > N_TRU_REGS)
    {
      printf("Error; index out of range");
      return -1;
    }
  else
    { 
      return fTruRegisterMap[index]; 
    }
}


Bool_t
TruMenu::GetTruVerify(int index)
{
  return fVerify[index];
}


void
TruMenu::SetTruRegValue(int index, int value)
{
  if(index < N_TRU_REGS)
    {
      fTruRegInputPtr[index]->SetHexNumber(value) ;
    }
  else
    {
      printf("TruMenu::SetTruRegValue(int index, int value): ERROR, index out of range \n");
    }
}


const TRUSettings_t
TruMenu::GetTRUSettings() 
{
  // TRURegister_t::TRURegister_t(const unsigned long address, const unsigned long value, const char *name); 
  TRUSettings_t t;
  
  for(int i=0; i < N_TRU_REGS; i++)
    {
      fTruRegValue[i]  = fTruRegInputPtr[i]->GetHexNumber(); 
      TRURegister_t *r = new  TRURegister_t((unsigned long)fTruRegisterMap[i], (unsigned long)fTruRegValue[i], fTruLabeltxt[i]);   
      
      t.AddRegister(*r);
      delete r;
     }
  
  return t;
}



void  
TruMenu::SetTRUSettings(const TRUSettings_t t)
{
  for(int i=0; i < N_TRU_REGS; i++)
    {
      fTruRegisterMap[i] = t.GetRegister(i).GetAddress(); 
      fTruRegValue[i] =t.GetRegister(i).GetIntValue();
      sprintf(fTruLabeltxt[i], "%s", t.GetRegister(i).GetName());
    }
}
