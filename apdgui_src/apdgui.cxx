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
// TQtApplication 
#include "MainGui.h"

#ifndef __CINT__
# include <stdexcept>
# include <TSystem.h>
# include <TApplication.h>
//# include "TQtApplication.h"

#endif

int
main(int argc, char** argv) 
{

  try {
    TApplication app("app", 0, 0);
    //  TQtApplication app("app", 0, 0);
    MainGui* mainGUIPtr = MainGui::Instance();
    //Main* mainGUI = new Main();
    app.Run();
  }
  
  catch (std::exception& e) {
    //    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}




