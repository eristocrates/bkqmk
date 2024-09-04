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

// leader key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 1000
#define LEADER_NO_TIMEOUT

// timing settings
#define TAPPING_TERM_PER_KEY // TODO do i still need this?
#define TAPPING_TOGGLE 2
// term settings
#define TAPPING_TERM 175
#define REPEAT_TERM (TAPPING_TERM / 3)
#define MAGIC_TERM (TAPPING_TERM * 3)

// Auto shift
/*
#define AUTO_SHIFT_TIMEOUT 170
#define NO_AUTO_SHIFT_SPECIAL
#define RETRO_SHIFT 500
#define AUTO_SHIFT_MODIFIERS
*/

// recency
#define INPUT_BUFFER_TIMEOUT_MS 5000 // Timeout in milliseconds.
#define INPUT_BUFFER_SIZE 16         // Number of keys in general purpose buffer.
#define MOTION_BUFFER_TIMEOUT_MS 250 // Timeout in milliseconds.
#define MOTION_BUFFER_SIZE 6         // Number of keys in motion input buffer.
#define ARCANE_TIMEOUT_MS 1000       // Timeout in milliseconds.

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
