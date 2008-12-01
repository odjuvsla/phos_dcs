#ifndef LOGVIEWER_H
#define LOGVIEWER_H

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

#include <TGFrame.h>
#include "RQ_OBJECT.h"

class  TGTextView;
class  TGText; 

class LogViewer : public TGGroupFrame
{
  RQ_OBJECT("LogViewer")

 public:
  LogViewer();
  ~LogViewer(); 
  LogViewer(TGMainFrame *framePtr, int X, int Y, int W, int H);
  void DisplayMessage(const char *message);
  void AddText(char *text);
  void HandleMessage(const char *message);

 private:
  long lineCount;
  TGTextView      *textPtr;
  TGText *addTextPtr;
  time_t timePtr;
  tm *tmPtr;
  size_t maxDateLength;
  char *timeString;
  char logMessage[200];

  ClassDef(LogViewer, 1)
};


#endif

