PROJECT(APDGUI)

# Adding libraries 

LINK_DIRECTORIES(${ROOTSYS}/lib)

FIND_LIBRARY(PHOSDCSLIB PhosDcs ../PhosDcs)

SET(RLIBS Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint 
	  Postscript Matrix Physics MathCore Thread VMC Geom 
	  EG dl pthread TreePlayer ProofPlayer Proof Minuit)

# Adding sources
SET(SRCS PhosDcsDICT.cxx PhosDcsWidget.cxx AltroMenu.cxx 
#SET(SRCS PhosDcsWidget.cxx AltroMenu.cxx 
  ElectronicsMenu.cxx ElectronicsMenuApply.cxx ElectronicsMenuRCU.cxx
  ElectronicsMenuReadout.cxx ElectronicsMenuGetUserData.cxx SandboxMenu.cxx
  LogViewer.cxx RcuButton.cxx RcuManager.cxx MainMenu.cxx TruMenu.cxx
  FeeCardButton.cxx FeeCardOnOffButton.cxx PhosNumberEntry 
  PhosHexNumberEntry.cxx PhosMenuButton.cxx ApdInput.cxx MainGui.cxx)

ADD_LIBRARY(ApdGui SHARED ${SRCS})
ADD_EXECUTABLE(apdgui apdgui.cxx)
TARGET_LINK_LIBRARIES(PHOSDCSLIB)
