PROJECT(feeclient)

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

INSTALL(TARGETS PhosDcs
  RUNTIME DESTINATION $ENV{HOME}/phos_dcs/bin
  LIBRARY DESTINATION $ENV{HOME}/phos_dcs/lib
  ARCHIVE DESTINATION $ENV{HOME}/phos_dcs/lib
)
