ObjSuf		= o
SrcSuf		= cxx
HeadSuf		= h

FEECLIENT 		= /home/phos/feeclient-0.6

SRC_INCLUDE             = -I$(FEECLIENT)/include -Isrc -I$(ROOTSYS)/include
GUI_INCLUDE		= -I$(PWD)/src -I$(ROOTSYS)/include -Iapsgui_src


#ROOTLIBS		=   -L/home/phs/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lGui -pthread -lm -ldl -rdynamic

#ROOTLIBS	 	= `root-config --glibs`


FEELIBS	  		=   -L$(FEECLIENT)/lib -lFeeClient   -L/home/phos/lib -ldim  -lpthread
GUILIBS			=   -L/home/phos/phos_dcs_new/lib -lPhosDcs -lApdGui


PHOSGUIO		= apdgui_src/apdgui.$(ObjSuf)
PHOSGUIS		= apdgui_src/apdgui.$(SrcSuf)


OBJS	= $(PHOSGUIO)




bin/apdgui:$(OBJS)
	g++ -ggdb   $(GUILIBS) $(ROOTLIBS) $(FEELIBS) $(OBJS)  -o bin/apdgui



$(PHOSGUIO):$(PHOSGUIS) $(PHOSGUIH)
	g++ -ggdb   $(GUI_INCLUDE) $(SRC_INCLUDE)  -c $(PHOSGUIS) -o $(PHOSGUIO)



clean:
	@rm -f apdgui_src/*o   apdgui_src/obj/*  apdgui_src/lib/*   src/*o src/obj/*  src/lib/* *~ *#

