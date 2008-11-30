#ifndef TRUMENU_H
#define TRUMENU_H

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

#include "PhosConst.h"
#include "Rtypes.h"
#include "PhosDataTypes.h"
#include "RQ_OBJECT.h"

using namespace PhosConst;

class PhosMenuButton;
class DatabaseDummy;
class PhosHexNumberEntry;
class TGGroupFrame; 
class TGLabel;
class TGMainFrame;


class TruMenu
{
  RQ_OBJECT("TruMenu") 

 public:
  ~TruMenu();
  TruMenu(TGMainFrame *framePtr, TRUSettings_t trusettings, int X, int Y, int W, int H); 
  void EmitSaveSettingsSignal(const TRUSettings_t *t);

  void DrawRegisters(TGGroupFrame *framePtr);
  int GetTruRegisterValue(int index);
  int GetTruRegisterAddress(int index);
  Bool_t GetTruVerify(int index);
  void SetTruRegValue(int index, int value);
  
  const TRUSettings_t GetTRUSettings();
  void  SetTRUSettings(const TRUSettings_t t); 

  // private:
  TruMenu();
  int fTruRegisterMap[N_TRU_REGS];
  int fTruRegValue[N_TRU_REGS];
  Bool_t fVerify[N_TRU_REGS];

  char fTruLabeltxt[N_TRU_REGS][100];

  TGLabel *fTruRegLabelPtr[N_TRU_REGS];
  PhosHexNumberEntry *fTruRegInputPtr[N_TRU_REGS];
  PhosMenuButton *fAllTruOnButtPtr;
  PhosMenuButton *fAllTruOffButtPtr;
  TGGroupFrame    *fElectronicsMenuPtr;
  PhosMenuButton *fSaveButtPtr;
  PhosMenuButton *fApplyButtPtr;

  ClassDef(TruMenu, 1)
};

#endif
