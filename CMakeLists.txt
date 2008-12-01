cmake_minimum_required(VERSION 2.6)

PROJECT(phos_dcs)

ENABLE_TESTING()

#SET(CMAKE_CXX_FLAGS "-W -Wall -Weffc++ -Woverloaded-virtual -fPIC -pipe -fmessage-length=0 -Wno-long-long -Dlinux")
#SET(CMAKE_EXE_LINKER_FLAGS "-Wall,--warn-unresolved-symbols")
#SET(CMAKE_SHARED_LINKER_FLAGS "-Wall,--warn-unresolved-symbols")

SET(FEECLIENT $ENV{FEECLIENT})
SET(ROOTSYS $ENV{ROOTSYS})

FIND_LIBRARY(FEELIB libFeeClient.so FEECLIENT/lib)
FIND_LIBRARY(DIMLIB libdim.so FEECLIENT/lib)

INCLUDE_DIRECTORIES(src/phosdcs src/apdgui ${FEECLIENT}/include ${ROOTSYS}/include)

ADD_SUBDIRECTORY(src/phosdcs)
ADD_SUBDIRECTORY(src/apdgui)


