cmake_minimum_required(VERSION 2.6)

PROJECT(phos_dcs)
# The version number.
set (phos_dcs_VERSION_MAJOR 0)
set (phos_dcs_VERSION_MINOR 4)

SET(CMAKE_BUILD_TYPE Debug)

OPTION (NEW_RCU_FW  "Enable new RCU firmware, where the active channel list is separate for the two branches" ON) 

ENABLE_TESTING()

SET(ROOTSYS $ENV{ROOTSYS})

#FIND_LIBRARY(FEELIB libFeeClient.so FEECLIENT/lib)
#FIND_LIBRARY(DIMLIB libdim.so FEECLIENT/lib)
SET(SVNINC /usr/include/subversion-1/)
SET(APRINC /usr/include/apr-1/)

INCLUDE_DIRECTORIES(src/phosdcslib $ENV{FEECLIENT}/include ${PROJECT_BINARY_DIR} ${SVNINC} ${APRINC})

configure_file (
  "${PROJECT_SOURCE_DIR}/phos_dcs_config.h.in"
  "${PROJECT_BINARY_DIR}/phos_dcs_config.h"
  )

ADD_SUBDIRECTORY(src/phosdcslib)
ADD_SUBDIRECTORY(src/phosgui)

#ADD_SUBDIRECTORY(src/scriptmanager)

INSTALL(DIRECTORY scripts DESTINATION /home/odjuvsla/phos_dcs)
#INSTALL(CODE "FILE(MAKE_DIRECTORY \${ENV}\$ENV{HOME}/phos_dcs/scripts  )")SET(FEECLIENT $ENV{FEECLIENT})

#add_subdirectory(test)

