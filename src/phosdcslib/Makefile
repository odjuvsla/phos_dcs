ObjSuf		= o
SrcSuf		= cxx
HeadSuf		= h





#OBJ_DIR 		= $(PHOS_DCS_SOURCEDIR)/obj/
OBJ_DIR 		= $(PWD)/obj/

#SOURCEDIR		= $(PHOS_DCS_SOURCEDIR)
LIBDIR			= $(PHOS_DCS_SOURCEDIR)lib/



#FEECLIENT 		= /home/phs/feeclient-0.6
SRC_INCLUDE             = -I$(FEECLIENT)/include -I$(PWD)/src -I$(ROOTSYS)/include
#GUI_INCLUDE		= -I$(FEECLIENT)/include -I$(PWD)/src -I$(ROOTSYS)/include

FEELIBS	  		= -L$(FEECLIENT)/lib -lFeeClient   -L/home/phos/lib -ldim  -lpthread

# PULSEGENERATORO         = $(OBJ_DIR)PulseGenerator.$(ObjSuf)
# PULSEGENERATORS         = PulseGenerator.$(SrcSuf)
# PULSEGENERATORH         = PulseGenerator.$(HeadSuf)

# PATTERNGENERATORO      = $(OBJ_DIR)PatternGenerator.$(ObjSuf)
# PATTERNGENERATORS      = PatternGenerator.$(SrcSuf)
# PATTERNGENERATORH      = PatternGenerator.$(HeadSuf)



PHOSDATATYPESO		= $(OBJ_DIR)PhosDataTypes.$(ObjSuf)
PHOSDATATYPESS		= PhosDataTypes.$(SrcSuf)
PHOSDATATYPESH		= PhosDataTypes.$(HeadSuf)


DCSINTERFACEO		= $(OBJ_DIR)DcsInterface.$(ObjSuf)
DCSINTERFACES		= DcsInterface.$(SrcSuf)
DCSINTERFACEH		= DcsInterface.$(HeadSuf)

PHOSCONSTO		= $(OBJ_DIR)PhosConst.$(ObjSuf)
PHOSCONSTS		= PhosConst.$(SrcSuf)
PHOSCONSTH		= PhosConst.$(HeadSuf)

PHOSDCSBASEO		= $(OBJ_DIR)PhosDcsBase.$(ObjSuf)
PHOSDCSBASES		= PhosDcsBase.$(SrcSuf)
PHOSDCSBASEH		= PhosDcsBase.$(HeadSuf)

PHOSDETECTORO		= $(OBJ_DIR)PhosDetector.$(ObjSuf)
PHOSDETECTORS		= PhosDetector.$(SrcSuf)
PHOSDETECTORH		= PhosDetector.$(HeadSuf)	

PHOSMODULEO		= $(OBJ_DIR)PhosModule.$(ObjSuf)
PHOSMODULES		= PhosModule.$(SrcSuf)
PHOSMODULEH		= PhosModule.$(HeadSuf)

RCUO			= $(OBJ_DIR)Rcu.$(ObjSuf)
RCUS			= Rcu.$(SrcSuf)
RCUH			= Rcu.$(HeadSuf)

MAPPERO			= $(OBJ_DIR)Mapper.$(ObjSuf)
MAPPERS			= Mapper.$(SrcSuf)
MAPPERH			= Mapper.$(HeadSuf)

DATABASEDUMMYO		= $(OBJ_DIR)DatabaseDummy.$(ObjSuf)
DATABASEDUMMYS		= DatabaseDummy.$(SrcSuf)
DATABASEDUMMYH		= DatabaseDummy.$(HeadSuf)

SCRIPTCOMPILERO		= $(OBJ_DIR)ScriptCompiler.$(ObjSuf)
SCRIPTCOMPILERS		= ScriptCompiler.$(SrcSuf)
SCRIPTCOMPILERH		= ScriptCompiler.$(HeadSuf)

BINARYCOMPILERO		= $(OBJ_DIR)BinaryCompiler.$(ObjSuf)
BINARYCOMPILERS		= BinaryCompiler.$(SrcSuf)
BINARYCOMPILERH		= BinaryCompiler.$(HeadSuf)

PHOSFEECLIENTO		= $(OBJ_DIR)PhosFeeClient.$(ObjSuf)
PHOSFEECLIENTS		= PhosFeeClient.$(SrcSuf)
PHOSFEECLIENTH		= PhosFeeClient.$(HeadSuf)

FEECARDO		= $(OBJ_DIR)FeeCard.$(ObjSuf)
FEECARDS		= FeeCard.$(SrcSuf)
FEECARDH		= FeeCard.$(HeadSuf)




OBJS	= $(PATTERNGENERATORO)  $(PULSEGENERATORO) $(DCSINTERFACEO) $(PHOSDETECTORO) $(PHOSDCSBASEO)\
	$(PHOSMODULEO) $(RCUO) $(MAPPERO) \
	$(FEECARDO) $(SCRIPTCOMPILERO) $(DATABASEDUMMYO) $(BINARYCOMPILERO)\
	$(PHOSFEECLIENTO) $(PHOSDATATYPESO) 


$(LIBDIR)/libPhosDcs.so:$(OBJS)
	g++  -Wl --export-dynamic  -shared   --gc-sections $(ROOTLIBS) $(ROOTGLIBS) $(FEELIBS)  -o  lib/libPhosDcs.so $(OBJS) -lc

#$(PHOSCONSTO): $(PHOSCONSTH)
#	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)  -c $(PHOSCONSTH) -o $(PHOSCONSTO)


# $(PULSEGENERATORO):$(PULSEGENERATORS) $(PULSEGENERATORH)
# 	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PULSEGENERATORS) -o $(PULSEGENERATORO)


# $(PATTERNGENERATORO):$(PATTERNGENERATORS) $(PATTERNGENERATORH)
# 	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PATTERNGENERATORS) -o $(PATTERNGENERATORO)


$(PHOSDATATYPESO):$(PHOSDATATYPESS) $(PHOSDATATYPESH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PHOSDATATYPESS) -o $(PHOSDATATYPESO)


$(DCSINTERFACEO):$(DCSINTERFACES) $(DCSINTERFACEH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(DCSINTERFACES) -o $(DCSINTERFACEO)


$(PHOSDCSBASEO):$(PHOSDCSBASES) $(PHOSDCSBASEH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PHOSDCSBASES) -o $(PHOSDCSBASEO)


$(SCRIPTCOMPILERO):$(SCRIPTCOMPILERS) $(SCRIPTCOMPILERH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(SCRIPTCOMPILERS) -o $(SCRIPTCOMPILERO)

$(BINARYCOMPILERO):$(BINARYCOMPILERS) $(BINARYCOMPILERH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(BINARYCOMPILERS)   -o  $(BINARYCOMPILERO)

$(PHOSFEECLIENTO):$(PHOSFEECLIENTS) $(PHOSFEECLIENTH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PHOSFEECLIENTS)  -o $(PHOSFEECLIENTO)

$(PHOSDETECTORO):$(PHOSDETECTORS) $(PHOSDETECTORH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PHOSDETECTORS)  -o $(PHOSDETECTORO)

$(PHOSMODULEO):$(PHOSMODULES) $(PHOSMODULEH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(PHOSMODULES) -o    $(PHOSMODULEO)

$(RCUO):$(RCUS) $(RCUH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(RCUS) -o $(RCUO)

$(MAPPERO):$(MAPPERS) $(MAPPERH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(MAPPERS)  -o $(MAPPERO)

$(DATABASEDUMMYO):$(DATABASEDUMMYS) $(DATABASEDUMMYH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(DATABASEDUMMYS) -o $(DATABASEDUMMYO)


$(FEECARDO):$(FEECARDS) $(FEECARDH)
	g++ -ggdb -fPIC -ffunction-sections   $(SRC_INCLUDE)   -c $(FEECARDS) -o $(FEECARDO)

clean:
	@rm -f  $(OBJ_DIR)/*o lib/*   $(PHOS_DCS_SOURCEDIR)*~  $(PHOS_DCS_SOURCEDIR)*#
