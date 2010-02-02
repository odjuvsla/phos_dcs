#PROJECT(feeclient)

FIND_PACKAGE(SWIG REQUIRED)	
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)

SET(FEECLIENT $ENV{FEECLIENT})

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH} ${FEECLIENT})

SET(SRCS PhosDataTypes.cxx DcsInterface.cxx PhosFeeClient.cxx
  PhosDcsBase.cxx PhosDetector.cxx PhosModule.cxx Rcu.cxx
  Mapper.cxx DatabaseDummy.cxx ScriptCompiler.cxx 
  BinaryCompiler.cxx FeeCard.cxx InstructionMaker.cxx 
  PhosDcsLogging.cxx PhosRegisters.cxx)

ADD_LIBRARY(PhosDcs SHARED ${SRCS})

SET_TARGET_PROPERTIES(
  PhosDcs
 PROPERTIES
   SOVERSION 0.3.0
 )

SET(FEECLIENT $ENV{FEECLIENT})

FIND_LIBRARY(FEELIB FeeClient FEECLIENT/lib)
FIND_LIBRARY(DIMLIB dim FEECLIENT/lib)

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(PhosDataTypes.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(DcsInterface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(PhosConst.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(PhosRegisters.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(PhosDataTypes python PhosDataTypes.i PhosDataTypes.cxx)
SWIG_ADD_MODULE(DcsInterface python DcsInterface.i DcsInterface.cxx)
SWIG_ADD_MODULE(PhosConst python PhosConst.i PhosConst.h)
SWIG_ADD_MODULE(PhosRegisters python PhosRegisters.i PhosRegisters.h)
SWIG_LINK_LIBRARIES(PhosDataTypes PhosDcs ${FEECLIENT}/lib/libdim.so ${FEECLIENT}/lib/libFeeClient.so ${PYTHON_LIBRARIES})
SWIG_LINK_LIBRARIES(DcsInterface PhosDcs ${FEECLIENT}/lib/libdim.so ${FEECLIENT}/lib/libFeeClient.so ${PYTHON_LIBRARIES})
SWIG_LINK_LIBRARIES(PhosConst PhosDcs ${FEECLIENT}/lib/libdim.so ${FEECLIENT}/lib/libFeeClient.so ${PYTHON_LIBRARIES})
SWIG_LINK_LIBRARIES(PhosRegisters PhosDcs ${FEECLIENT}/lib/libdim.so ${FEECLIENT}/lib/libFeeClient.so ${PYTHON_LIBRARIES})


INSTALL(TARGETS PhosDcs
  RUNTIME DESTINATION $ENV{PHOS_DCS}/bin
  LIBRARY DESTINATION $ENV{PHOS_DCS}/lib
  ARCHIVE DESTINATION $ENV{PHOS_DCS}/lib
)

INSTALL(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/PhosDataTypes.py
  ${CMAKE_CURRENT_BINARY_DIR}/_PhosDataTypes.so
  ${CMAKE_CURRENT_BINARY_DIR}/PhosConst.py
  ${CMAKE_CURRENT_BINARY_DIR}/_PhosConst.so
  ${CMAKE_CURRENT_BINARY_DIR}/DcsInterface.py
  ${CMAKE_CURRENT_BINARY_DIR}/_DcsInterface.so
DESTINATION $ENV{PHOS_DCS}/gui_files/)

INSTALL(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/../../data
  DESTINATION $ENV{PHOS_DCS})


