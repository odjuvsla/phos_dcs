PROJECT(feeclient)

SET(SRCS PhosDataTypes.cxx DcsInterface.cxx PhosFeeClient.cxx
  PhosDcsBase.cxx PhosDetector.cxx PhosModule.cxx Rcu.cxx
  Mapper.cxx DatabaseDummy.cxx ScriptCompiler.cxx 
  BinaryCompiler.cxx FeeCard.cxx)

ADD_LIBRARY(PhosDcs SHARED ${SRCS})

