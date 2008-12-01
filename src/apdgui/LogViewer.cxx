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

#include <TGTextView.h>
#include <TGTextEdit.h>
#include <iostream>
#include "LogViewer.h"
#define  MAX_LINECOUNT 1000
#define  MAXLINES  9


ClassImp(LogViewer)


LogViewer::LogViewer() : textPtr(0),
			 addTextPtr(0),
			 timePtr(0),
			 tmPtr(0),
			 maxDateLength(0),
			 timeString(0)
{

}


LogViewer::~LogViewer()
{

}


void 
LogViewer::HandleMessage(const char *message)
{
  DisplayMessage(message);
}


void
LogViewer::AddText(char *text)
{
  if(addTextPtr != 0)
    {
      delete addTextPtr;
      addTextPtr = 0;
    }

  addTextPtr = new TGText(text);
  textPtr->AddText(addTextPtr);
}


void
LogViewer::DisplayMessage(const char *message)
{
  FILE *fp;
  fp = fopen("log.txt", "a");
  time(&timePtr); 
  tmPtr=localtime(&timePtr);
  timeString=asctime(tmPtr);
  char tShort [strlen(timeString)+1];
  char day[10];
  char month[10];
  int date;
  int hour;
  int min;
  int sec;
  int year;
  char sDate[5];
  char sHour[5];
  char sMin[5];
  char sSec[5];
  char sYear[10];

  sscanf(timeString, "%s %s %d %d:%d:%d %d\n", day, month, &date, &hour, &min, &sec, &year);

  if(date <10)
    {
      sprintf(sDate, "0%d",date);
    }
  else
    {
      sprintf(sDate, "%d", date);
    }

  if(hour <10)
    {
      sprintf(sHour, "0%d", hour);
    }
  else
    {
      sprintf(sHour, "%d", hour);
    }

  if(min <10)
    {
      sprintf(sMin, "0%d", min);
    }
  else
    {
      sprintf(sMin, "%d", min);
    }

  if(sec <10)
    {
      sprintf(sSec, "0%d", sec);
    }
  else
    {
      sprintf(sSec, "%d", sec);
    }

  sprintf(logMessage, "%s %s %s %s:%s:%s %d: %s", day, month, sDate, sHour, sMin, sSec, year, message);

  fprintf(fp, logMessage);
  fprintf(fp, "\n");

  textPtr->AddLine(logMessage);
  lineCount ++;

  if(lineCount > MAXLINES)
    {
      textPtr->SetVsbPosition(lineCount-4);
    }
  
  if(lineCount > MAX_LINECOUNT)
    {
      lineCount = 0;
      textPtr->Clear();
    }


  fclose(fp);

}

LogViewer::LogViewer(TGMainFrame *framePtr, int X, int Y, int W, int H)
  : TGGroupFrame(framePtr,"Logviewer")
{
  addTextPtr=0;
  lineCount = 0;
  this->MoveResize(X, Y, W, H);
  textPtr = new TGTextView(this, 50, 50, -1, 0, framePtr->GetWhitePixel());
  textPtr->MoveResize(20, 20, W-40, H-40);
  this->AddFrame(textPtr);
  this->MapSubwindows();
  
}


