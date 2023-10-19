SET(SOURCES screens/ui_SettingTemperature.c
    screens/ui_SettingAlarm.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})
