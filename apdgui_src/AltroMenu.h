#ifndef ALTROMENU_H
#define ALTROMENU_H

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

#include <TGFrame.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include "PhosNumberEntry.h"
#include <TGTextEdit.h>
#include "PhosDcsWidget.h"
#include "DatabaseDummy.h"
#include "PhosMenuButton.h" 
//#include "TGMainFrame.h"



class  AltroMenu : public PhosDcsWidget
{
 public:
  // AltroMenu();
  AltroMenu(TGMainFrame *framePtr, int X, int Y, int W, int H);
  virtual ~AltroMenu();
  int GetStartZ();
  int GetEndZ();
  int GetStartX();
  int GetEndX();
  int GetNSamples();
  int GetNPreSamples();
  void SetStartZ(int startZ);
  void SetEndZ(int endZ);
  void SetStartX(int startX);
  void SetEndX(int endX);
  void SetNSamples(int samples);
  void SetNPreSamples(int presamples);


 private:
  AltroMenu();

  int startZ;
  int endZ;
  int startX;
  int endX;
  int samples;
  int preSamples;
  DatabaseDummy  *databasePtr;

  TGGroupFrame    *readoutConfigMenuPtr;
  TGGroupFrame      *electronicsMenuPtr;
  PhosMenuButton    *saveButtPtr;
  PhosNumberEntry   *startZInputPtr;
  PhosNumberEntry   *endZInputPtr;
  PhosNumberEntry   *startXInputPtr;
  PhosNumberEntry   *endXInputPtr;

  TGLabel         *zLabelPtr;
  TGLabel         *xLabelPtr;
  TGLabel         *startLabelPtr;
  TGLabel         *endLabelPtr;
  PhosNumberEntry   *nSamplesInputPtr;
  PhosNumberEntry   *nPreSamplesInputPtr;
  TGLabel         *nSamplesLabelPtr;
  TGLabel         *nPreSamplesLabelPtr;

  ClassDef(AltroMenu,1)

};

#endif
