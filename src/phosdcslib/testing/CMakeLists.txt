 PROJECT(APDGUI)

# Adding sources
SET(SRCS 
	 PhosDcsLogging.cxx 
)

ADD_LIBRARY(PhosDcsLogging SHARED ${SRCS})
ADD_EXECUTABLE(testLog testLog.cxx)
TARGET_LINK_LIBRARIES(testLog PhosDcsLogging)


