#export PATH=$PATH:
#export PHOS_DCS_DIR=$PWD
#export PHOS_DCS_SCRIPTDIR=$PWD/scripts
#export PHOS_DCS_BINDIR=$PWD/bin/
#export PHOS_DCS_LIBDIR=$PWD/lib
#export PHOS_DCS_SOURCEDIR=$PWD/src/
#export PHOS_DCS_GUIDIR=$PWD/apdgui_src/
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PHOS_DCS_LIBDIR

#echo "PHOS_DCS_DIR="        $PHOS_DCS_DIR        >  config.txt
#echo "PHOS_DCS_SCRIPTDIR="  $PHOS_DCS_SCRIPTDIR  >>  config.txt
#echo "PHOS_DCS_BINDIR="     $PHOS_DCS_BINDIR     >>  config.txt
#echo "PHOS_DCS_LIBDIR="     $PHOS_DCS_LIBDIR     >>  config.txt
#echo "PHOS_DCS_SOURCEDIR="  $PHOS_DCS_SOURCEDIR  >>  config.txt
#echo "PHOS_DCS_GUIDIR="     $PHOS_DCS_GUIDIR     >>  config.txt

#make -f src/Makefile
rm lib/libPhosDcs.so
rm lib/libApdGui.so

cd apdgui_src
sh makedict.sh
cd ..

#make -f src/Makefile
#make -f apdgui_src/Makefile

cd src
make
cd ..
cd apdgui_src
make
cd ..



ln -s  $PWD/src/lib/libPhosDcs.so   lib/libPhosDcs.so
ln -s  $PWD/apdgui_src/lib/libApdGui.so   lib/libApdGui.so

make

ln -s bin/apdgui apdgui

