#pragma once

#define LAYER_STATE_32BIT
#define COMBO_VARIABLE_LEN

// rgb
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_COLOR_SCHEME_SYNC, RPC_ID_VIM_MODE_SYNC
#define FORCED_SYNC_THROTTLE_MS 250
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BAND_PINWHEEL_VAL // Sets the default mode, if none has been set
/* https://docs.qmk.fm/features/rgb_matrix#rgb-matrix-effect-typing-heatmap
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
#define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
*/
/* https://docs.qmk.fm/features/rgb_matrix#additional-configh-options
#define RGB_MATRIX_KEYRELEASES // reactive effects respond to keyreleases (instead of keypresses)
#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_MATRIX_SLEEP // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_ON true // Sets the default enabled state, if none has been set
#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#define RGB_MATRIX_DEFAULT_FLAGS LED_FLAG_ALL // Sets the default LED flags, if none has been set
#define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
#define RGB_MATRIX_SPLIT { X, Y } 	// (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                                    // If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards
*/

// https://htmlcolorcodes.com/colors/shades-of-red/
#define RGB_BLOOD_RED 0x88, 0x08, 0x08
#define RGB_BRICK_RED 0xAA, 0x4A, 0x44
#define RGB_BRIGHT_RED 0xEE, 0x4B, 0x2B
#define RGB_BROWN 0xA5, 0x2A, 0x2A
#define RGB_BURGUNDY 0x80, 0x00, 0x20
#define RGB_BURNT_UMBER 0x6E, 0x26, 0x0E
#define RGB_BURNT_ORANGE 0xCC, 0x55, 0x00
#define RGB_BURNT_SIENNA 0xE9, 0x74, 0x51
#define RGB_BYZANTIUM 0x70, 0x29, 0x63
#define RGB_CADMIUM_RED 0xD2, 0x2B, 0x2B
#define RGB_CARDINAL_RED 0xC4, 0x1E, 0x3A
#define RGB_CARMINE 0xD7, 0x00, 0x40
#define RGB_CERISE 0xDE, 0x31, 0x63
#define RGB_CHERRY 0xD2, 0x04, 0x2D
#define RGB_CHESTNUT 0x95, 0x45, 0x35
#define RGB_CLARET 0x81, 0x13, 0x31
#define RGB_CORAL_PINK 0xF8, 0x83, 0x79
#define RGB_CORDOVAN 0x81, 0x41, 0x41
#define RGB_CRIMSON 0xDC, 0x14, 0x3C
#define RGB_DARK_RED 0x8B, 0x00, 0x00
#define RGB_FALU_RED 0x7B, 0x18, 0x18
#define RGB_GARNET 0x9A, 0x2A, 0x2A
#define RGB_MAHOGANY 0xC0, 0x40, 0x00
#define RGB_MAROON 0x80, 0x00, 0x00
#define RGB_MARSALA 0x98, 0x68, 0x68
#define RGB_MULBERRY 0x77, 0x07, 0x37
#define RGB_NEON_RED 0xFF, 0x31, 0x31
#define RGB_OXBLOOD 0x4A, 0x04, 0x04
#define RGB_PASTEL_RED 0xFA, 0xA0, 0xA0
#define RGB_PERSIMMON 0xEC, 0x58, 0x00
#define RGB_POPPY 0xE3, 0x53, 0x35
#define RGB_PUCE 0xA9, 0x5C, 0x68
#define RGB_RASPBERRY 0xE3, 0x0B, 0x5C
#define RGB_RED 0xFF, 0x00, 0x00
#define RGB_RED_BROWN 0xA5, 0x2A, 0x2A
#define RGB_RED_OCHRE 0x91, 0x38, 0x31
#define RGB_RED_ORANGE 0xFF, 0x44, 0x33
#define RGB_RED_PURPLE 0x95, 0x35, 0x53
#define RGB_ROSE_RED 0xC2, 0x1E, 0x56
#define RGB_RUBY_RED 0xE0, 0x11, 0x5F
#define RGB_RUSSET 0x80, 0x46, 0x1B
#define RGB_SALMON 0xFA, 0x80, 0x72
#define RGB_SCARLET 0xFF, 0x24, 0x00
#define RGB_SUNSET_ORANGE 0xFA, 0x5F, 0x55
#define RGB_TERRA_COTTA 0xE3, 0x73, 0x5E
#define RGB_TUSCAN_RED 0x7C, 0x30, 0x30
#define RGB_TYRIAN_PURPLE 0x63, 0x03, 0x30
#define RGB_VENETIAN_RED 0xA4, 0x2A, 0x04
#define RGB_VERMILLION 0xE3, 0x42, 0x34
#define RGB_WINE 0x72, 0x2F, 0x37

#define HSV_BLOOD_RED 0, 240, 136
#define HSV_BRICK_RED 3, 153, 170
#define HSV_BRIGHT_RED 7, 209, 238
#define HSV_BROWN 0, 190, 165
#define HSV_BURGUNDY 244, 255, 128
#define HSV_BURNT_UMBER 11, 223, 110
#define HSV_BURNT_ORANGE 18, 255, 204
#define HSV_BURNT_SIENNA 10, 166, 233
#define HSV_BYZANTIUM 220, 162, 112
#define HSV_CADMIUM_RED 0, 203, 210
#define HSV_CARDINAL_RED 248, 216, 196
#define HSV_CARMINE 242, 255, 215
#define HSV_CERISE 243, 199, 222
#define HSV_CHERRY 247, 250, 210
#define HSV_CHESTNUT 7, 164, 149
#define HSV_CLARET 244, 217, 129
#define HSV_CORAL_PINK 4, 131, 248
#define HSV_CORDOVAN 0, 127, 129
#define HSV_CRIMSON 247, 232, 220
#define HSV_DARK_RED 0, 255, 139
#define HSV_FALU_RED 0, 205, 123
#define HSV_GARNET 0, 185, 154
#define HSV_MAHOGANY 14, 255, 192
#define HSV_MAROON 0, 255, 128
#define HSV_MARSALA 0, 81, 152
#define HSV_MULBERRY 237, 240, 119
#define HSV_NEON_RED 0, 206, 255
#define HSV_OXBLOOD 0, 241, 74
#define HSV_PASTEL_RED 0, 92, 250
#define HSV_PERSIMMON 16, 255, 236
#define HSV_POPPY 7, 195, 227
#define HSV_PUCE 249, 116, 169
#define HSV_RASPBERRY 239, 243, 227
#define HSV_RED 0, 255, 255
#define HSV_RED_BROWN 0, 190, 165
#define HSV_RED_OCHRE 3, 169, 145
#define HSV_RED_ORANGE 4, 204, 255
#define HSV_RED_PURPLE 242, 164, 149
#define HSV_ROSE_RED 241, 216, 194
#define HSV_RUBY_RED 239, 236, 224
#define HSV_RUSSET 18, 201, 128
#define HSV_SALMON 4, 139, 250
#define HSV_SCARLET 6, 255, 255
#define HSV_SUNSET_ORANGE 3, 168, 250
#define HSV_TERRA_COTTA 6, 149, 227
#define HSV_TUSCAN_RED 0, 156, 124
#define HSV_TYRIAN_PURPLE 235, 247, 99
#define HSV_VENETIAN_RED 10, 249, 164
#define HSV_VERMILLION 4, 197, 227
#define HSV_WINE 250, 150, 114

#define PRIMARY_HSV HSV_RED
#define SECONDARY_HSV HSV_BLOOD_RED
#define TERTIARY_HSV HSV_YELLOW

// leader key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 1000
#define LEADER_NO_TIMEOUT

// Tapping settings
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 2

// Auto shift
#define AUTO_SHIFT_TIMEOUT 170
#define NO_AUTO_SHIFT_SPECIAL
#define RETRO_SHIFT 500
#define AUTO_SHIFT_MODIFIERS

// recent key
#define TIMEOUT_MS 5000 // Timeout in milliseconds.
#define RECENT_SIZE 8   // Number of keys in `recent` buffer.

// unicode
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

// combos
#define COMBO_PROCESS_KEY_RELEASE

// caps word
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 30000

/* Charybdis-specific features. */
#define CHARYBDIS_CONFIG_SYNC
// #define MOUSE_EXTENDED_REPORT

// honestly not sure if i should try to use core auto pointer or stay with bastardkb's implementation
// #define AUTO_MOUSE_THRESHOLD 100
// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 2000
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#endif // POINTING_DEVICE_ENABLE

// qmk-vim
#define BETTER_VISUAL_MODE
#define QMK_VIM_PASTE_BEFORE
#define QMK_VIM_I_TEXT_OBJECTS
#define QMK_VIM_A_TEXT_OBJECTS
#define QMK_VIM_G_MOTIONS
// #define QMK_VIM_COLON_CMDS // replace with leader keys
#define QMK_VIM_REPLACE
#define QMK_VIM_DOT_REPEAT
#define QMK_VIM_W_BEGINNING_OF_WORD
#define QMK_VIM_NUMBERED_JUMPS
#define ONESHOT_QMK_VIM
