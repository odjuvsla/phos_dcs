PROJECT(phosgui)

INSTALL(FILES
startgui.sh
DESTINATION $ENV{HOME}/phos_dcs/bin/)

INSTALL(FILES 
phos_buttons.py
phos_dialogs.py
phos_gui.py
phos_gui.ui
phos_interface.py
phos_main_window.py
phos_utilities.py
phos_widgets.py
DESTINATION $ENV{HOME}/phos_dcs/gui_files/)

INSTALL(FILES
../GuiConfigurationFiles/feeServerNames.cfg
../GuiConfigurationFiles/feeServerNames.cfg.bak
DESTINATION $ENV{HOME}/phos_dcs/GuiConfigurationFiles/)

INSTALL(FILES
../graphics/5_mods_0_on.png
../graphics/5_mods_1_on.png
../graphics/5_mods_2_on.png
../graphics/5_mods_3_on.png
../graphics/5_mods_4_on.png
../graphics/5_mods_no_on.png
../graphics/modules.svg
DESTINATION $ENV{HOME}/phos_dcs/graphics)

INSTALL(CODE "FILE(MAKE_DIRECTORY \${ENV}\$ENV{HOME}/phos_dcs/log  )")
