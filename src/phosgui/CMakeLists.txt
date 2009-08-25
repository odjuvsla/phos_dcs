PROJECT(phosgui)

INSTALL(FILES
startgui.sh
DESTINATION $ENV{PHOS_DCS}/bin/)

INSTALL(FILES 
phos_gui.py
phos_main_window.py
buttons/PhosModulePushButton.py
buttons/ModulePropertiesButton.py
buttons/PhosPushButton.py
buttons/RcuToggleOnOffPushButton.py
buttons/ModuleEnableTriggerButton.py
buttons/ModuleConfigureElectronicsButton.py
buttons/TruPushButton.py
buttons/ModuleTurnOffButton.py
buttons/ModuleDisableTriggerButton.py
buttons/FeePushButton.py
buttons/RcuViewPushButton.py
buttons/RcuUpdateStatusPushButton.py
buttons/ModuleTurnOnButton.py
dialogs/RcuDialog.py
dialogs/ConnectSettingsDialog.py
dialogs/ConfigureElectronicsDialog.py
interface/FeeCardHandler.py
interface/TruCardHandler.py
interface/PHOSHandler.py
interface/RcuHandler.py
interface/ModuleHandler.py
interface/DatabaseHandler.py
interface/DetectorHandler.py
interface/LogHandler.py
interface/DcsInterfaceThreadWrapper.py
utilities/PhosIdConverter.py
widgets/Rcu.py
widgets/RcuTopFrame.py
widgets/ReadoutMEBWidget.py
widgets/ReadoutRegionSettingsWidget.py
widgets/ReadoutZeroSuppressionWidget.py
widgets/ModuleTabWidget.py
widgets/StatusTabWidget.py
widgets/RcuGeneralInfoWidget.py
widgets/ConnectionSettingsBusyboxTabWidget.py
widgets/ConnectionSettingsModuleTabWidget.py
widgets/RcuRegistersWidget.py
widgets/APDSettingsSelectorWidget.py
widgets/ReadoutSamplesSettingsWidget.py
widgets/PhosTabWidget.py
widgets/ModulesFrame.py
widgets/Module.py
DESTINATION $ENV{PHOS_DCS}/gui_files/)

INSTALL(FILES
../GuiConfigurationFiles/feeServerNames.cfg
../GuiConfigurationFiles/feeServerNames.cfg.bak
DESTINATION $ENV{PHOS_DCS}/GuiConfigurationFiles/)

INSTALL(FILES
../graphics/5_mods_0_on.png
../graphics/5_mods_1_on.png
../graphics/5_mods_2_on.png
../graphics/5_mods_3_on.png
../graphics/5_mods_4_on.png
../graphics/5_mods_no_on.png
../graphics/modules.svg
DESTINATION $ENV{HOME}/phos_dcs/graphics)

#INSTALL(CODE "FILE(MAKE_DIRECTORY \${ENV}\$ENV{HOME}/phos_dcs/log  )")
