#ifndef PHOSDCSWIDGET_H
#define PHOSDCSWIDGET_H

#include "PhosDcsBase.h"
#include <TGTextView.h>
#include <TDialogCanvas.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include <TGTextEdit.h>
#include <TGFrame.h>
#include <TGButton.h>
#include <TMemberInspector.h>

class PhosDcsWidget : public PhosDcsBase
//class PhosDcsWidget
{

 public:
  PhosDcsWidget();
  virtual ~PhosDcsWidget();
  ClassDef(PhosDcsWidget,1)
};


#endif
