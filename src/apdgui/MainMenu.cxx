#include "MainMenu.h"
#include "PhosConst.h"
#include <TGNumberEntry.h>
#include <TGText.h> 
#include <TGTextView.h>
#include <TGTextEdit.h>
#include "PhosMenuButton.h"
#include "PhosNumberEntry.h"
#include "PhosDataTypes.h"

#include <iostream>

using namespace PhosConst;
using std::cout;
using std::endl;

ClassImp(MainMenu)


MainMenu::MainMenu() 
{
  // never called
}


MainMenu:: ~MainMenu()
{

}


MainMenu::MainMenu(TGMainFrame *framePtr, int X, int Y, int W, int H) 
{
  fConfigInfoPtr = new  ConfigInfo_t();
  configInfoTextPtr = 0;
  menuGroupPtr=new TGGroupFrame(framePtr,"Menu"); 
  menuGroupPtr->MoveResize(    X, Y,  W, H); 
  exitButtPtr   = new PhosMenuButton(menuGroupPtr,        "Exit");
  exitButtPtr->MoveResize(     20,  20,  130, 20); 
  saveButtPtr   = new PhosMenuButton(menuGroupPtr,        "Save Configuration");
  saveButtPtr->MoveResize(     20,  45,  130, 20); 
  loadButtPtr   = new PhosMenuButton(menuGroupPtr,        "load Configuration");
  loadButtPtr->MoveResize(     20,  70,  130, 20); 

  configIdInputPtr  = new PhosNumberEntry(menuGroupPtr, 0, 5, -1, (TGNumberFormat::EStyle) 5);
  configIdInputPtr->MoveResize(160, 70,  80,  20);

  DisplayConfigInfo(menuGroupPtr);
  menuGroupPtr->MapSubwindows();
  configInfoInputMainframePtr = new TGTransientFrame();
  configInputPtr = new TGGroupFrame(configInfoInputMainframePtr, "Write Configuration Comments Here");;

  getConfigInfoOKButtPtr = new  PhosMenuButton(configInputPtr, "OK");
  getConfigInfoCANCELButtPtr = new PhosMenuButton(configInputPtr,  "CANCEL");

  //  getConfigInfoOKButtPtr->Connect("HandleButton(Event_t*)", "MainMenu", this, "HandleSignalOK(Event_t*)");
  getConfigInfoOKButtPtr->Connect("HandleButton(Event_t*)", "MainMenu", this, "HandleSignalOK(ConfigInfo_t*)");

  configIdInputPtr->Connect("ValueChanged(Long_t)", "MainMenu", this, "EmitRequestConfigInfoSignal(ConfigInfo_t*)");
  loadButtPtr->Connect("HandleButton(Event_t*)", "MainMenu", this,  "EmitRequestConfigLoadSignal(ConfigInfo_t*)"); 
  saveButtPtr->Connect("HandleButton(Event_t*)", "MainMenu", this,  "EmitRequestConfigSaveSignal(ConfigInfo_t*)");
  
  getConfigInfoCANCELButtPtr->Connect("HandleButton(Event_t*)", "MainMenu", this, "HandleSignalCancel(Event_t*)" );
  EmitRequestConfigInfoSignal(fConfigInfoPtr);
}


void 
MainMenu::EmitRequestConfigInfoSignal(ConfigInfo_t *t)  //*SIGNAL*
{
  fConfigInfoPtr->fID =  configIdInputPtr->GetIntNumber(); 
  Emit("EmitRequestConfigInfoSignal(ConfigInfo_t*)",(Long_t)fConfigInfoPtr);
}


void 
MainMenu::EmitRequestConfigLoadSignal(ConfigInfo_t *t)  //*SIGNAL*
{
  Emit("EmitRequestConfigLoadSignal(ConfigInfo_t*)",(Long_t)fConfigInfoPtr); 
}


void      
MainMenu::EmitRequestConfigSaveSignal(ConfigInfo_t *t)  //*SIGNAL*
{
  cout << "MainMenu::EmitRequestConfigSave(ConfigInfo_t *t)" << endl;
  
  //  *fConfigInfoPtr = *t;

  // GetConfigInfoFromUser(t->fInfo, 1000);
  GetConfigInfoFromUser();

  //  Emit("EmitRequestConfigSaveSignal(ConfigInfo_t*)",(Long_t)fConfigInfoPtr); 
}


void 
MainMenu::HandleConfigChangedSlot(ConfigInfo_t *t)
{
  cout << "MainMenu::HandleConfigChangedSlot(ConfigInfo_t *t) id = "<< t->fID <<"  Info = " <<t->fInfo << endl;
  fConfigInfoPtr->fIDLimit = t->fIDLimit; 
  sprintf(fConfigInfoPtr->fInfo  ,"%s",t->fInfo);

  configIdInputPtr->SetLimits(0, t->fIDLimit);
  configIdInputPtr->SetIntNumber(t->fID); 
  TGText *txt = new TGText(t->fInfo); // watch out
  configInfoTextPtr->Clear(); 
  configInfoTextPtr->AddText(txt); 
}


void 
//MainMenu::HandleSignalOK(Event_t* t)
MainMenu::HandleSignalOK(ConfigInfo_t *t)
{
  char tmpInfo[1024];

  for(int i= 0; i< 1024; i++)
    {
      tmpInfo[i] = 0;
    }

  char cat[3];
  
  for(int i= 0; i< 3; i++)
    {
      cat[i] = 0;
    }
  
  configInfoInputTextPtr->SaveFile("tmpInfo.txt", kFALSE);
  FILE *fp = fopen("tmpInfo.txt", "r");

  if(fp != 0)
    {
      char c = fgetc(fp);
      sprintf(tmpInfo,"%c", c);

      while(c != EOF)  //  configIdInputPtr->SetLimits(0, GetLatestConfigId());
	{
	   sprintf(cat, "%c", c);
	   strcat(tmpInfo, cat);
	   c = fgetc(fp); 
	}

      sprintf(cat, "%c", '\0');
      strcat(tmpInfo, cat); 
  }
  sprintf(fConfigInfoPtr->fInfo, "%s", tmpInfo); 
  configInfoInputMainframePtr->DestroyWindow();

  Emit("EmitRequestConfigSaveSignal(ConfigInfo_t*)",(Long_t)fConfigInfoPtr); 
}


void 
MainMenu::HandleSignalCancel(Event_t* t)
{
  DestroyGetConfigInfoDisplay();
  //  printf("\n HandleSignalCancel, HELLO WORLD\n");
}


void
MainMenu::DisplayConfigInfo(TGGroupFrame *groupFramePtr)
{
  char line[50];
  int length=0;
  int length2=0;
  int cnt=0;
  configInfoMenuPtr = new TGGroupFrame(groupFramePtr,"Configuration Info Preview");
  configInfoMenuPtr->MoveResize(20, 100, 240, 170);  
  configInfoTextPtr = new TGTextView(configInfoMenuPtr, 50, 50, -1, 0, groupFramePtr->GetWhitePixel());
  configInfoTextPtr->MoveResize(10, 20, 220, 130);
  configInfoMenuPtr->AddFrame(configInfoTextPtr);
  groupFramePtr->AddFrame(configInfoMenuPtr);
}


void
//MainMenu::GetConfigInfoFromUser(char *configInfo, const int size)
MainMenu::GetConfigInfoFromUser()
{
  configInfoInputMainframePtr->MapWindow();
  configInfoInputMainframePtr->MoveResize(50, 350, 300, 300);
  configInputPtr->SetWindowName("Configuration Comments"); 
  configInputPtr->MoveResize(20, 20, 260, 240);  
  configInfoInputTextPtr = new TGTextEdit(configInputPtr, 50, 50, -1, 0, configInputPtr->GetWhitePixel());
  configInfoInputTextPtr->MoveResize(20, 20, 220, 150);
  configInputPtr->AddFrame(configInfoInputTextPtr);
  getConfigInfoOKButtPtr->MoveResize(20, 190, 80, 30); 
  getConfigInfoCANCELButtPtr->MoveResize(160, 190, 80, 30); 
  configInputPtr->MapSubwindows();
  configInfoInputMainframePtr->MapSubwindows();
}  


void
MainMenu::DestroyGetConfigInfoDisplay()
{
  configInfoInputMainframePtr->DestroyWindow();
}


