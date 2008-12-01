#ifndef MAINGUI_H
#define MAINGUI_H


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

class TGTextView;
class TDialogCanvas;
class SandboxMenu;
class ElectronicsMenu;
class LogViewer;
class TruMenu;
//class DcsInterface;
class RcuManager;
class MainMenu;
class PhosMenuButton;

#include "RQ_OBJECT.h"
#include "TGFrame.h"
#include "PhosDcsBase.h"

class MainGui : public  TGMainFrame, public PhosDcsBase
{ 
  RQ_OBJECT("MainGui") 

 public:
  MainGui();
  ~MainGui();
  static MainGui* Instance();  /**<Returns the one an only instance of the PHOS APD GUI */
  void InitGraphics();
  void InitSignalSlotConnections();
  static MainGui  *fgInstancePtr;    /**<pointer to the one and only instacne of the MainGui*/


 private:
  RcuManager       *fRcuManagerPtr;
  TGGroupFrame     *rcuGroupPtr;     /**<pointer to the frame where the RCU partitions is drawn */
  SandboxMenu      *sandboxMenuPtr;  /**<ponter to the frame where the sandbox menu is drawn */
  ElectronicsMenu  *electronicsMenuPtr; /**<pointer to the frame where the electronics Menu is drawn*/
  MainMenu         *mainMenuPtr;      /**<pointer to the frame where the main menu is drawn */
  LogViewer        *logviewerPtr;     /**<pointer to the frame where the logviewer is drawn */
  TGMainFrame      *truFramePtr;
  TruMenu          *truMenuPtr; 
  //  DcsInterface    *fDcsInterfacePtr;
  PhosMenuButton  *allFeeOnButtPtr;
  PhosMenuButton  *allFeeOffButtPtr; 
  PhosMenuButton  *allTruOnButtPtr;
  PhosMenuButton  *allTruOffButtPtr;

  ClassDef(MainGui,1) 

};


#endif
