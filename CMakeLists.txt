cmake_minimum_required(VERSION 2.6)

PROJECT(phos_dcs)

SET(CMAKE_BUILD_TYPE Debug)

ENABLE_TESTING()

SET(ROOTSYS $ENV{ROOTSYS})

#FIND_LIBRARY(FEELIB libFeeClient.so FEECLIENT/lib)
#FIND_LIBRARY(DIMLIB libdim.so FEECLIENT/lib)
SET(SVNINC /usr/include/subversion-1/)
SET(APRINC /usr/include/apr-1/)

INCLUDE_DIRECTORIES(src/phosdcslib $ENV{FEECLIENT}/include ${SVNINC} ${APRINC})

ADD_SUBDIRECTORY(src/phosdcslib)
ADD_SUBDIRECTORY(src/phosgui)
#ADD_SUBDIRECTORY(src/scriptmanager)

INSTALL(DIRECTORY scripts DESTINATION /home/odjuvsla/phos_dcs)
#INSTALL(CODE "FILE(MAKE_DIRECTORY \${ENV}\$ENV{HOME}/phos_dcs/scripts  )")SET(FEECLIENT $ENV{FEECLIENT})

#add_subdirectory(test)

