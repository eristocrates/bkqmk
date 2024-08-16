#pragma once

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define COMBO_VARIABLE_LEN
#define AUTO_MOUSE_THRESHOLD 100
// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// Tapping settings
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 2

// Charybdis-specific features.
/* Charybdis-specific features. */
#define CHARYBDIS_CONFIG_SYNC
#define MOUSE_EXTENDED_REPORT

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 2
#    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#endif // POINTING_DEVICE_ENABLE
