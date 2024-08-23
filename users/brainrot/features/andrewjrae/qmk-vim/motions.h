#pragma once

#include QMK_KEYBOARD_H
#include "mac_mode.h"

// Define a custom variable for the common motion shortcut modifier
// ie on MAC, OPT + RIGHT is forward word, but on Windows/Linux it's CTRL + RIGHT
// This should be used whenever using one of these shortcuts
#define VMOTION(kc) QMK_VIM_MAC_NOMAC(LOPT(kc), LCTL(kc))

#define QMK_VIM_0 QMK_VIM_MAC_NOMAC(LCMD(KC_LEFT), KC_HOME)
#define QMK_VIM_HOME() QMK_VIM_MAC_NOMAC(tap_code16(QMK_VIM_0), tap_code(QMK_VIM_0));
#define QMK_VIM_SHIFT_HOME() tap_code16(LSFT(QMK_VIM_0));

#define QMK_VIM_DLR QMK_VIM_MAC_NOMAC(LCMD(KC_RIGHT), KC_END)
#define QMK_VIM_END() QMK_VIM_MAC_NOMAC(tap_code16(QMK_VIM_DLR), tap_code(QMK_VIM_DLR));
#define QMK_VIM_SHIFT_END() tap_code16(LSFT(QMK_VIM_DLR));

// The vim motions keys supported by single keystrokes/chords
#define QMK_VIM_H KC_LEFT
#define QMK_VIM_J KC_DOWN
#define QMK_VIM_K KC_UP
#define QMK_VIM_L KC_RIGHT

#define QMK_VIM_B VMOTION(KC_LEFT)
#define QMK_VIM_W VMOTION(KC_RIGHT)
#define QMK_VIM_E VMOTION(KC_RIGHT)

// An enum for the direction of the visual mode
// This is used to figure out which way to exit out of a selection
// Note that it's only ever used when BETTER_VISUAL_MODE is defined
// Also note that this will only garner expected behaviour if the
// the user doesn't double back on their original cursor position
typedef enum {
    V_NONE = 0,
    V_FORWARD,
    V_BACKWARD,
} visual_direction_t;

// Function to set the global visual direction if it is currently unset
void set_visual_direction(visual_direction_t dir);

// Register one of the basic vim motions in a fashion where they can be held down.
void register_motion(uint16_t keycode, const keyrecord_t *record);
bool process_motions(uint16_t keycode, const keyrecord_t *record, uint16_t qk_mods);
