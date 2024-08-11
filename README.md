# MINGW64 error output

qmk compile -c -j 0 -kb bastardkb/charybdis/3x6 -km brainrot
Ψ Cleaning with make clean
QMK Firmware 0.24.7
Deleting .build/ ... done.
Ψ Compiling keymap with make --jobs --output-sync=target -r -R -f builddefs/build_keyboard.mk -s KEYBOARD=bastardkb/charybdis/3x6 KEYMAP=brainrot KEYBOARD_FILESAFE=bastardkb_charybdis_3x6 TARGET=bastardkb_charybdis_3x6_brainrot INTERMEDIATE_OUTPUT=.build/obj_bastardkb_charybdis_3x6_brainrot VERBOSE=false COLOR=true SILENT=false QMK_BIN="qmk" QMK_USERSPACE=I:/coding/bkqmk MAIN_KEYMAP_PATH_1=I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot MAIN_KEYMAP_PATH_2=I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot MAIN_KEYMAP_PATH_3=I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot MAIN_KEYMAP_PATH_4=I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot MAIN_KEYMAP_PATH_5=I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot

Generating: .build/obj_bastardkb_charybdis_3x6_brainrot/src/info_deps.d [OK]
arm-none-eabi-gcc.exe (GCC) 13.3.0
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Generating: .build/obj*bastardkb_charybdis_3x6_brainrot/src/info_config.h [OK]
Generating: .build/obj_bastardkb_charybdis_3x6_brainrot/src/default_keyboard.c [OK]
Generating: .build/obj_bastardkb_charybdis_3x6_brainrot/src/default_keyboard.h [OK]
Compiling: keyboards/bastardkb/charybdis/3x6/3x6.c [OK]
Compiling: keyboards/bastardkb/charybdis/charybdis.c [OK]
Compiling: .build/obj_bastardkb_charybdis_3x6_brainrot/src/default_keyboard.c [OK]
Compiling: quantum/keymap_introspection.c [OK]
Compiling: quantum/quantum.c [OK]
Compiling: quantum/bitwise.c [OK]
Compiling: quantum/led.c [OK]
Compiling: quantum/action_layer.c [OK]
Compiling: quantum/action.c [OK]
Compiling: quantum/action_tapping.c [OK]
Compiling: quantum/eeconfig.c [OK]
Compiling: quantum/action_util.c [OK]
Compiling: quantum/keyboard.c [OK]
Compiling: quantum/keymap_common.c [OK]
Compiling: quantum/keycode_config.c [OK]
Compiling: quantum/logging/debug.c [OK]
Compiling: quantum/logging/sendchar.c [OK]
Compiling: quantum/sync_timer.c [OK]
Compiling: quantum/logging/print.c [OK]
Compiling: quantum/matrix_common.c [OK]
Compiling: quantum/debounce/sym_defer_g.c [OK]
Compiling: quantum/matrix.c [OK]
Compiling: quantum/split_common/split_util.c [OK]
Compiling: quantum/split_common/transport.c [OK]
Compiling: quantum/main.c [OK]
Compiling: quantum/split_common/transactions.c [OK]
Compiling: quantum/pointing_device/pointing_device.c [OK]
Compiling: quantum/pointing_device/pointing_device_drivers.c [OK]
Compiling: lib/printf/src/printf/printf.c [OK]
Compiling: drivers/sensors/pmw3360.c [OK]
Compiling: quantum/pointing_device/pointing_device_auto_mouse.c [OK]
Compiling: drivers/sensors/pmw33xx_common.c [OK]
Compiling: drivers/eeprom/eeprom_driver.c [OK]
Compiling: drivers/eeprom/eeprom_wear_leveling.c [OK]
Compiling: platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash.c [OK]
Compiling: quantum/wear_leveling/wear_leveling.c [OK]
Compiling: quantum/rgb_matrix/rgb_matrix_drivers.c [OK]
Compiling: quantum/rgb_matrix/rgb_matrix.c In file included from quantum/rgb_matrix/animations/rgb_matrix_effects.inc:33, from quantum/rgb_matrix/rgb_matrix.c:50:
quantum/rgb_matrix/animations/typing_heatmap_anim.h: In function 'process_rgb_matrix_typing_heatmap':
quantum/rgb_matrix/animations/typing_heatmap_anim.h:33:17: error: 'g_rgb_frame_buffer' undeclared (first use in this function)
33 | g_rgb_frame_buffer[row][col] = qadd8(g_rgb_frame_buffer[row][col], RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP);
| ^~~~~~~~~~~~~~~~~~
quantum/rgb_matrix/animations/typing_heatmap_anim.h:33:17: note: each undeclared identifier is reported only once for each function it appears in
quantum/rgb_matrix/animations/typing_heatmap_anim.h: In function 'TYPING_HEATMAP':
quantum/rgb_matrix/animations/typing_heatmap_anim.h:61:16: error: 'g_rgb_frame_buffer' undeclared (first use in this function)
61 | memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
| ^~~~~~~~~~~~~~~~~~
In file included from quantum/rgb_matrix/animations/rgb_matrix_effects.inc:34:
quantum/rgb_matrix/animations/digital_rain_anim.h: In function 'DIGITAL_RAIN':
quantum/rgb_matrix/animations/digital_rain_anim.h:23:16: error: 'g_rgb_frame_buffer' undeclared (first use in this function)
23 | memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
| ^~~~~~~~~~~~~~~~~~
quantum/rgb_matrix/rgb_matrix.c: In function 'process_rgb_matrix':
quantum/rgb_matrix/rgb_matrix.c:202:39: error: 'RGB_MATRIX_TYPING_HEATMAP' undeclared (first use in this function); did you mean 'ENABLE_RGB_MATRIX_TYPING_HEATMAP'?
202 | if (rgb_matrix_config.mode == RGB_MATRIX_TYPING_HEATMAP) {
| ^~~~~~~~~~~~~~~~~~~~~~~~~
| ENABLE_RGB_MATRIX_TYPING_HEATMAP
quantum/rgb_matrix/animations/typing_heatmap_anim.h: In function 'rgb_task_render':
quantum/rgb_matrix/rgb_matrix.c:299:10: error: 'RGB_MATRIX_TYPING_HEATMAP' undeclared (first use in this function); did you mean 'ENABLE_RGB_MATRIX_TYPING_HEATMAP'?
299 | case RGB_MATRIX*##name: \
 | ^~~~~~~~~~~
quantum/rgb*matrix/animations/typing_heatmap_anim.h:2:1: note: in expansion of macro 'RGB_MATRIX_EFFECT'
2 | RGB_MATRIX_EFFECT(TYPING_HEATMAP)
| ^~~~~~~~~~~~~~~~~
quantum/rgb_matrix/rgb_matrix.c:299:10: error: 'RGB_MATRIX_DIGITAL_RAIN' undeclared (first use in this function); did you mean 'RGB_MATRIX_PIXEL_RAIN'?
299 | case RGB_MATRIX*##name: \
 | ^~~~~~~~~~~
quantum/rgb*matrix/animations/digital_rain_anim.h:2:1: note: in expansion of macro 'RGB_MATRIX_EFFECT'
2 | RGB_MATRIX_EFFECT(DIGITAL_RAIN)
| ^~~~~~~~~~~~~~~~~
[ERRORS]
|
|
|
make: *** [builddefs/common_rules.mk:370: .build/obj_bastardkb_charybdis_3x6_brainrot/quantum/rgb_matrix/rgb_matrix.o] Error 1
make: *** Waiting for unfinished jobs....
Compiling: quantum/led_tables.c [OK]
Compiling: lib/fnv/qmk_fnv_type_validation.c [OK]
Compiling: quantum/process_keycode/process_rgb.c [OK]
Compiling: quantum/color.c [OK]
Compiling: lib/fnv/hash_64a.c [OK]
Compiling: lib/fnv/hash_32a.c [OK]
Compiling: lib/lib8tion/lib8tion.c [OK]
Compiling: quantum/crc.c [OK]
Compiling: quantum/bootmagic/bootmagic.c [OK]
Compiling: platforms/chibios/drivers/vendor/RP/RP2040/ws2812_vendor.c In file included from ./lib/pico-sdk/src/common/pico_base/include/pico/types.h:12,
from ./lib/pico-sdk/src/common/pico_base/include/pico.h:24,
from ./lib/pico-sdk/src/rp2_common/hardware_clocks/include/hardware/clocks.h:10,
from ./lib/chibios/os/hal/ports/RP/RP2040/hal_lld.h:34,
from ./lib/chibios/os/hal/include/hal.h:249,
from platforms/chibios/platform_deps.h:18,
from quantum/quantum.h:18,
from keyboards/bastardkb/charybdis/charybdis.h:21,
from I:/coding/bkqmk/users/brainrot/keycodes.h:3,
from I:/coding/bkqmk/users/brainrot/mods.h:2,
from I:/coding/bkqmk/users/brainrot/config.h:14,
from <command-line>:
./lib/pico-sdk/src/rp2_common/hardware_timer/include/hardware/timer.h: In function 'check_hardware_alarm_num_param':
./lib/pico-sdk/src/common/pico_base/include/pico/assert.h:32:39: error: pasting "PARAM_ASSERTIONS_ENABLED*" and "(" does not give a valid preprocessing token
32 | #define PARAM*ASSERTIONS_ENABLED(x) ((PARAM_ASSERTIONS_ENABLED* ## x || PARAM*ASSERTIONS_ENABLE_ALL) && !PARAM_ASSERTIONS_DISABLE_ALL)
| ^~~~~~~~~~~~~~~~~~~~~~~~~
./lib/pico-sdk/src/common/pico_base/include/pico/assert.h:34:42: note: in expansion of macro 'PARAM_ASSERTIONS_ENABLED'
34 | #define invalid_params_if(x, test) ({if (PARAM_ASSERTIONS_ENABLED(x)) assert(!(test));})
| ^~~~~~~~~~~~~~~~~~~~~~~~
./lib/pico-sdk/src/rp2_common/hardware_timer/include/hardware/timer.h:54:5: note: in expansion of macro 'invalid_params_if'
54 | invalid_params_if(TIMER, alarm_num >= NUM_TIMERS);
| ^~~~~~~~~~~~~~~~~
./lib/pico-sdk/src/common/pico_base/include/pico/assert.h:32:39: error: implicit declaration of function 'PARAM_ASSERTIONS_ENABLED*'; did you mean 'PARAM*ASSERTIONS_ENABLED'? [-Werror=implicit-function-declaration]
32 | #define PARAM_ASSERTIONS_ENABLED(x) ((PARAM_ASSERTIONS_ENABLED* ## x || PARAM_ASSERTIONS_ENABLE_ALL) && !PARAM_ASSERTIONS_DISABLE_ALL)
| ^~~~~~~~~~~~~~~~~~~~~~~~~
./lib/pico-sdk/src/common/pico_base/include/pico/assert.h:34:42: note: in expansion of macro 'PARAM_ASSERTIONS_ENABLED'
34 | #define invalid_params_if(x, test) ({if (PARAM_ASSERTIONS_ENABLED(x)) assert(!(test));})
| ^~~~~~~~~~~~~~~~~~~~~~~~
./lib/pico-sdk/src/rp2_common/hardware_timer/include/hardware/timer.h:54:5: note: in expansion of macro 'invalid_params_if'
54 | invalid_params_if(TIMER, alarm_num >= NUM_TIMERS);
| ^~~~~~~~~~~~~~~~~
cc1.exe: all warnings being treated as errors
[ERRORS]
|
|
|
make: \*\*\* [builddefs/common_rules.mk:369: .build/obj_bastardkb_charybdis_3x6_brainrot/ws2812_vendor.o] Error 1
Compiling: quantum/process_keycode/process_grave_esc.c [OK]
Compiling: quantum/process_keycode/process_magic.c [OK]
Compiling: quantum/process_keycode/process_space_cadet.c [OK]
Compiling: quantum/process_keycode/process_tap_dance.c [OK]
Compiling: quantum/send_string/send_string.c [OK]
Compiling: tmk_core/protocol/host.c [OK]
