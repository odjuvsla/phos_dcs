PROJECT(feeclient)

FIND_PACKAGE(SWIG REQUIRED)	
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

SET(SRCS PhosDataTypes.cxx DcsInterface.cxx PhosFeeClient.cxx
  PhosDcsBase.cxx PhosDetector.cxx PhosModule.cxx Rcu.cxx
  Mapper.cxx DatabaseDummy.cxx ScriptCompiler.cxx 
  BinaryCompiler.cxx FeeCard.cxx InstructionMaker.cxx 
  PhosDcsLogging.cxx )

ADD_LIBRARY(PhosDcs SHARED ${SRCS})

SET_TARGET_PROPERTIES(
  PhosDcs
 PROPERTIES
   SOVERSION 0.2.0
 )

SET(FEECLIENT $ENV{FEECLIENT})

FIND_LIBRARY(FEELIB FeeClient FEECLIENT/lib)
FIND_LIBRARY(DIMLIB dim FEECLIENT/lib)

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(DcsInterface.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(DcsInterface.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(DcsInterface python DcsInterface.i DcsInterface.cxx)
#SWIG_ADD_MODULE(DcsInterface interfaces/DcsInterface.i DcsInterface.cxx)
SWIG_LINK_LIBRARIES(DcsInterface PhosDcs ${FEECLIENT}/lib/libdim.so ${FEECLIENT}/lib/libFeeClient.so ${PYTHON_LIBRARIES})


INSTALL(TARGETS PhosDcs
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
)
