####################################################################
#
# Makefile
#
####################################################################
AUTOMAKE_OPTIONS = foreign
lib_LTLIBRARIES = libphosfeeclient.la
INCLUDES= -I$(srcdir) -I$(includedir) @INCLUDES@

###########################################################################
ROOT_SRCS	=	
LIB_SRCS	= 	PhosDetector.cxx PhosModule.cxx Rcu.cxx PhosFeeClient.cxx FeeCard.cxx \
			Mapper.cxx ScriptCompiler.cxx BinaryCompiler.cxx \
			ConvertAPDBias.cxx  DatabaseDummy.cxx PhosDcsBase.cxx 
EXTRA_SRCS	=
###########################################################################
libphosfeeclient_la_SOURCES	= $(ROOT_SRCS) $(LIB_SRCS)
libphosfeeclient_la_LIBADD	= $(ROOT_SRCS:.cxx=_Dict.lo) $(ROOTLIBS) -L$(prefix)/lib -lFeeClient -lpthread
BUILT_SOURCES		= $(ROOT_SRCS:.cxx=_Dict.cxx)
include_HEADERS		= $(ROOT_SRCS:.cxx=.h) $(LIB_SRCS:.cxx=.h) CommonDefs.h PhosConst.h
SCRIPTS_SOURCES		= 
CLEANFILES		= $(ROOT_SRCS:.cxx=_Dict.cxx) $(ROOT_SRCS:.cxx=_Dict.h) $(SCRIPTS_SOURCES:.csh.in=.csh)
EXTRA_DIST 		= $(ROOT_SRCS:.cxx=_LinkDef.h) $(SCRIPTS_SOURCES) $(EXTRA_SRCS)
bin_SCRIPTS		= $(SCRIPTS_SOURCES:.csh.in=.csh)

LIBOBJS = $(ROOT_SRCS:.cxx=.o) $(BUILD_SOURCES:.cxx=.o) $(LIB_SRCS:.cxx=.o)
LTLIBOBJS = $(LTBOBJS)
%_Dict.cxx: %.h
	@echo ------------------------------------- Making $@
	$(ROOTSYS)/bin/rootcint -f $@ -c $(INCLUDES) $< $(<D)/$*_LinkDef.h
	@echo ------------------------------------- Done!

%.csh : %.csh.in
	@echo ------------------------------------- Making $@
	sed 's|@_prefix_@|${prefix}|g; s|@_QUEUE_NAME_@|${QUEUE_NAME}|g;' < $< > $@
	chmod uog+x $@
	@echo ------------------------------------- Done!

###########################################################################
