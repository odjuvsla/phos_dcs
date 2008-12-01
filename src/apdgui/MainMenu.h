#ifndef MAINMENU_H
#define MAINMENU_H

#include <TGFrame.h>
#include "RQ_OBJECT.h"

//class DcsInterface;
class PhosMenuButton;
class PhosNumberEntry; 
class TGTextView; 
class TGTextEdit;
struct ConfigInfo_t;

class MainMenu 
{
  RQ_OBJECT("MainMenu") 

 public:
  ~MainMenu();
  MainMenu(TGMainFrame *framePtr, int X, int Y, int W, int H);
  void DisplayConfigInfo(TGGroupFrame *groupFramePtr);
  void DestroyGetConfigInfoDisplay();
  //  void GetConfigInfoFromUser(char *configInfo, const int size);
  void GetConfigInfoFromUser();
  void HandleSignalCancel(Event_t* t);

  void HandleConfigChangedSlot(ConfigInfo_t *t);

  // void HandleSignalOK(Event_t* t);
  void HandleSignalOK(ConfigInfo_t *t);
  void EmitRequestConfigInfoSignal(ConfigInfo_t *t);
  void EmitRequestConfigLoadSignal(ConfigInfo_t *t);
  void EmitRequestConfigSaveSignal(ConfigInfo_t *t);

 private:
  MainMenu();
  TGGroupFrame      *menuGroupPtr;

  
  PhosMenuButton    *exitButtPtr;
  PhosMenuButton    *saveButtPtr; 
  PhosMenuButton    *loadButtPtr; 
  PhosMenuButton    *getConfigInfoOKButtPtr;
  PhosMenuButton    *getConfigInfoCANCELButtPtr;
  PhosNumberEntry   *configIdInputPtr; 
 

  TGGroupFrame      *configInfoMenuPtr;
  TGGroupFrame      *configInputPtr;
  TGTextView        *configInfoTextPtr;
  TGTransientFrame  *configInfoInputMainframePtr;
  TGTextEdit        *configInfoInputTextPtr;
  
  ConfigInfo_t      *fConfigInfoPtr;

  ClassDef(MainMenu,1) 
};



#endif
