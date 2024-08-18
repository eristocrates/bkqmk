#pragma once

#define LAYER_STATE_32BIT

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define COMBO_VARIABLE_LEN

// leader key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 1000
#define LEADER_NO_TIMEOUT

// Tapping settings
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 2

#define LAST_KEYCODE_TIMEOUT_MS 5000

// caps word
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 3000

/* Charybdis-specific features. */
#define CHARYBDIS_CONFIG_SYNC
#define MOUSE_EXTENDED_REPORT

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
#define VIM_PASTE_BEFORE
#define VIM_I_TEXT_OBJECTS
#define VIM_A_TEXT_OBJECTS
#define VIM_G_MOTIONS
#define VIM_COLON_CMDS
#define VIM_REPLACE
#define VIM_DOT_REPEAT
#define VIM_W_BEGINNING_OF_WORD
#define VIM_NUMBERED_JUMPS
#define ONESHOT_VIM
