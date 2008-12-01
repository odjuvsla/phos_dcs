PROJECT(feeclient)

SET(SRCS PhosDataTypes.cxx DcsInterface.cxx PhosFeeClient.cxx
  PhosDcsBase.cxx PhosDetector.cxx PhosModule.cxx Rcu.cxx
  Mapper.cxx DatabaseDummy.cxx ScriptCompiler.cxx 
  BinaryCompiler.cxx FeeCard.cxx)

ADD_LIBRARY(PhosDcs SHARED ${SRCS})

SET_TARGET_PROPERTIES(
  PhosDcs
 PROPERTIES
   SOVERSION 2.0.0
 )

INSTALL(TARGETS PhosDcs
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/lib
)
