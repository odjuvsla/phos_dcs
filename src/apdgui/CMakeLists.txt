PROJECT(APDGUI)

# Adding libraries 

LINK_DIRECTORIES(${ROOTSYS}/lib $ENV{FEECLIENT}/lib)

FIND_LIBRARY(PHOSDCSLIB PhosDcs ../PhosDcs)

SET(DINCLUDEPATH -I${CMAKE_CURRENT_SOURCE_DIR}/ -I${CMAKE_CURRENT_SOURCE_DIR}/../phosdcs/)

SET(DHEADERS AltroMenu.h ApdInput.h 
  ElectronicsMenu.h  ElectronicsMenuApply.h  ElectronicsMenuRCU.h   
  ElectronicsMenuReadout.h  ElectronicsMenuGetUserData.h  FeeCardButton.h 
  FeeCardOnOffButton.h LogViewer.h  PhosDcsWidget.h PhosHexNumberEntry.h 
  PhosMenuButton.h PhosNumberEntry.h  RcuManager.h  MainGui.h MainMenu.h 
  RcuButton.h SandboxMenu.h TruMenu.h LinkDef.h)

SET(DHEADERS PhosConst.h PhosDcsBase.h PhosDcsBase.cxx ${DHEADERS})

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/PhosDcsDICT.cxx
   COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && rootcint -f PhosDcsDICT.cxx -c ${DINCLUDEPATH} ${DHEADERS}
   )

SET(RLIBS Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Gui
	  Postscript Matrix Physics MathCore Thread VMC Geom 
	  EG dl pthread TreePlayer ProofPlayer Proof Minuit)

# Adding sources
SET(SRCS PhosDcsDICT.cxx PhosDcsWidget.cxx AltroMenu.cxx 
  ElectronicsMenu.cxx ElectronicsMenuApply.cxx ElectronicsMenuRCU.cxx
  ElectronicsMenuReadout.cxx ElectronicsMenuGetUserData.cxx SandboxMenu.cxx
  LogViewer.cxx RcuButton.cxx RcuManager.cxx MainMenu.cxx TruMenu.cxx
  FeeCardButton.cxx FeeCardOnOffButton.cxx PhosNumberEntry 
  PhosHexNumberEntry.cxx PhosMenuButton.cxx ApdInput.cxx MainGui.cxx)

ADD_LIBRARY(ApdGui SHARED ${SRCS})
ADD_EXECUTABLE(apdgui apdgui.cxx)
TARGET_LINK_LIBRARIES(apdgui PhosDcs ApdGui dim FeeClient ${RLIBS})

SET_TARGET_PROPERTIES(
  apdgui
 PROPERTIES
   VERSION 0.9.0
 )
SET_TARGET_PROPERTIES(
  ApdGui
 PROPERTIES
   SOVERSION 0.2.0
 )

INSTALL(TARGETS apdgui ApdGui 
  RUNTIME DESTINATION $ENV{HOME}/phos_dcs/bin
  LIBRARY DESTINATION $ENV{HOME}/phos_dcs/lib
  ARCHIVE DESTINATION $ENV{HOME}/phos_dcs/lib
)

INSTALL(CODE "FILE(MAKE_DIRECTORY \${ENV}\${CMAKE_BINARY_DIR}/bin/log	)")