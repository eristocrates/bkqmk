// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "combos/keymap_combo.h"
#include "features/achordion.h"
#include "features/custom_shift_keys.h"

enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
};

#define NDRSL    TO(0) // Layers
#define GAME     TO(1)
#define QWERTY   TO(2)
#define NUM_DEL  LT(5, KC_DEL)
#define NAV MO(6)

#define HRL_A LT(4,  KC_A) // Homerow mods and layers
#define HRM_E LSFT_T(KC_E)
#define HRM_I LCTL_T(KC_I)
#define HRM_H LGUI_T(KC_H)
#define HRM_X LALT_T(KC_X)

#define HRL_D LT(3,  KC_D)
#define HRM_R RSFT_T(KC_R)
#define HRM_S RCTL_T(KC_S)
#define HRM_L RGUI_T(KC_L)
#define HRM_V RALT_T(KC_V)

#define TH_1  LT(0, KC_1) // Tap for number, hold for F-key.
#define TH_2  LT(0, KC_2)
#define TH_3  LT(0, KC_3)
#define TH_4  LT(0, KC_4)
#define TH_5  LT(0, KC_5)
#define TH_6  LT(0, KC_6)
#define TH_7  LT(0, KC_7)
#define TH_8  LT(0, KC_8)
#define TH_9  LT(0, KC_9)
#define TH_10 LT(0, KC_0)
#define TH_11 LT(1, KC_0) // Layer 1/2 to prevent duplicate case
#define TH_12 LT(2, KC_0)


#define UNDO   LCTL(KC_Z) // Shortcuts
#define REDO_Y LCTL(KC_Y)
#define REDO_Z RCS(KC_Z)
#define CTL_L  LCTL(KC_LEFT) // Skip words
#define CTL_D  LCTL(KC_DOWN)
#define CTL_U  LCTL(KC_UP)
#define CTL_R  LCTL(KC_RGHT)
#define HYPR_0 HYPR(KC_0) // Screenshot keys for Flameshot
#define HYPR_1 HYPR(KC_1)
#define HYPR_2 HYPR(KC_2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_singlearc_let( // NDRSL LAYER
        KC_TAB,  KC_Q,    KC_Y,    KC_O,    KC_U,    KC_MINS,                         KC_BSPC, KC_G,    KC_N,    KC_F,    KC_K,    KC_TAB,
        KC_Z,    HRM_H,   HRM_I,   HRM_E,   HRL_A,   KC_DOT,                          KC_P,    HRL_D,   HRM_R,   HRM_S,   HRM_L,   KC_J,
        KC_ESC,  HRM_X,   KC_SLSH, KC_QUOT, KC_COMM, KC_SCLN,                         KC_B,    KC_C,    KC_M,    KC_W,    HRM_V,   KC_ESC,
        KC_ENT,  REDO_Z,  UNDO,    REDO_Y,  NUM_DEL, KC_SPC,  LMAGIC,        RMAGIC,  KC_T,    NAV,     GAME,    QWERTY,  _______, KC_ENT
    ),

    [1] = LAYOUT_singlearc_let( // GAME LAYER
        KC_TAB,  KC_Q,    KC_Y,    KC_O,    KC_U,    KC_MINS,                         KC_J,    KC_G,    KC_N,    KC_F,    KC_K,    KC_TAB,
        KC_Z,    KC_H,    KC_I,    KC_E,    KC_A,    KC_DOT,                          KC_P,    HRL_D,   HRM_R,   HRM_S,   HRM_L,   KC_BSPC,
        KC_V,	 KC_X,    KC_SLSH, KC_QUOT, KC_COMM, KC_SCLN,                         KC_B,    KC_C,    KC_M,    KC_W,    HRM_V,   KC_DEL,
        _______, _______, _______, _______, NUM_DEL, KC_SPC,  KC_LCTL,       _______, KC_T,    NAV,     NDRSL,   QWERTY,  _______, KC_ENT
    ),

    [2] = LAYOUT_singlearc_let( // QWERTY LAYER
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_COLN,
        KC_LCTL, _______, _______, _______, _______, KC_SPC,  KC_LCTL,       _______, KC_RSFT, KC_ENT,  GAME,    NDRSL,   _______, KC_ENT
    ),

    [3] = LAYOUT_singlearc_let( // SYM_L LAYER
        _______, KC_LCBR, KC_AMPR, KC_GRV,  KC_AT,   XXXXXXX,                         _______, _______, _______, _______, _______, _______,
        _______, KC_LBRC, KC_CIRC, KC_TILD, KC_LPRN, KC_DOT,                          _______, _______, _______, _______, _______, _______,
        _______, KC_LT,   KC_PIPE, KC_BSLS, KC_3,    XXXXXXX,                         _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______
    ),

    [4] = LAYOUT_singlearc_let( // SYM_R LAYER
        _______, _______, _______, _______, _______, _______,                         XXXXXXX, KC_DLR,  KC_SLSH, KC_ASTR, KC_RCBR, _______,
        _______, _______, _______, _______, _______, _______,                         KC_DOT,  KC_RPRN, KC_MINS, KC_PLUS, KC_RBRC, _______,
        _______, _______, _______, _______, _______, _______,                         XXXXXXX, KC_HASH, KC_PERC, KC_EQL,  KC_GT,   _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______
    ),

    [5] = LAYOUT_singlearc_let( // NUM LAYER
        _______, TH_10,  TH_7,    TH_8,    TH_9,     KC_MINS,                         _______, _______, _______, _______, _______, _______,
        _______, TH_11,  TH_4,    TH_5,    TH_6,     KC_DOT,                          _______, _______, KC_RSFT, KC_RCTL, KC_RGUI, _______,
        _______, TH_12,  TH_1,    TH_2,    TH_3,     KC_COLN,                         _______, _______, _______, _______, KC_RALT, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, KC_SPC,  _______, _______, _______, _______, _______
    ),

    [6] = LAYOUT_singlearc_let( // NAV LAYER
        _______, _______, _______, _______, _______, _______,                         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
        _______, KC_LGUI, KC_LCTL, KC_LSFT, _______, _______,                         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, KC_LALT, _______, _______, _______, _______,                         _______, CTL_L,   CTL_D,   CTL_U,   CTL_R,   _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, HYPR_0,  HYPR_1,  HYPR_2,  _______
    ),

    [7] = LAYOUT_singlearc_let( // BALANCE LAYER
        _______, _______, RGB_VAD, RGB_VAI, _______, _______,                         _______, _______, _______, _______, _______, _______,
        _______, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, _______,                         _______, CM_TOGG, KC_CAPS, _______, _______, _______,
        _______, _______, RGB_TOG, RGB_MOD, _______, _______,                         _______, QK_BOOT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, 5, 6, 7); // Balance layer
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
	switch (keycode) {
		case CW_TOGG:
        case KC_ESC:
        case KC_BSPC:
        case KC_DEL:

        case LMAGIC:
        case RMAGIC:
            return false;  // Magic keys will ignore the above keycodes.
    }
    return true;  // Other keys can be repeated.
}

static bool process_tap_or_long_press_key( // Tap for number, hold for F-key
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`.
#define MAGIC_STRING(str, repeat_keycode) \
		magic_send_string_P(PSTR(str), (repeat_keycode))

static void magic_send_string_P(const char* str, uint16_t repeat_keycode) {
	uint8_t saved_mods = 0;

  if (is_caps_word_on()) { // If Caps Word is on, save the mods and hold Shift.
    saved_mods = get_mods();
    register_mods(MOD_BIT(KC_LSFT));
  }

  send_string_with_delay_P(str, TAP_CODE_DELAY);  // Send the string.
  set_last_keycode(repeat_keycode); // 2024-03-09 Disabled sending of string for mag-rep / rep-mag consistency.

  // If Caps Word is on, restore the mods.
  if (is_caps_word_on()) {
    set_mods(saved_mods);
  }
}

static void process_left_magic(uint16_t keycode, uint8_t mods) { // LMAGIC definitions
    switch (keycode) {
		case HRL_A: { MAGIC_STRING("a", 		KC_SPC); } break;
	    case  KC_B: { MAGIC_STRING("ecause",	KC_NO); } break;
	    case  KC_C: { MAGIC_STRING("an",		KC_NO); } break;
	  //case HRL_D: { MAGIC_STRING("d", 		KC_NO); } break;
		case HRM_E: { MAGIC_STRING("e",			KC_NO); } break;
	  //case  KC_F: { MAGIC_STRING("f", 		KC_NO); } break;
	    case  KC_G: { MAGIC_STRING("eneral", 	KC_NO); } break;
		case HRM_H: { MAGIC_STRING("h", 		KC_NO); } break;
		case HRM_I: { MAGIC_STRING("i", 		KC_NO); } break;
	    case  KC_J: { MAGIC_STRING("ust",		KC_NO); } break;
	  //case  KC_K: { MAGIC_STRING("k", 		KC_NO); } break;
	  //case HRM_L: { MAGIC_STRING("l", 		KC_NO); } break;
	    case  KC_M: { MAGIC_STRING("ent",		KC_NO); } break;
	    case  KC_N: { MAGIC_STRING("ion",		KC_NO); } break;
		case  KC_O: { MAGIC_STRING("o", 		KC_NO); } break;
	    case  KC_P: { MAGIC_STRING("retty",    	KC_NO); } break;
		case  KC_Q: { MAGIC_STRING("q", 		KC_NO); } break;
	  //case HRM_R: { MAGIC_STRING("r", 		KC_NO); } break;
	  //case HRM_S: { MAGIC_STRING("s", 		KC_NO); } break;
        case  KC_T: { MAGIC_STRING("t", 		KC_NO); } break;
		case  KC_U: { MAGIC_STRING("u", 		KC_NO); } break;
	    case HRM_V: { MAGIC_STRING("azjorfia",	KC_NO); } break;
	    case  KC_W: { MAGIC_STRING("hich",		KC_NO); } break;
		case HRM_X: { MAGIC_STRING("x", 		KC_NO); } break;
		case  KC_Y: { MAGIC_STRING("y", 		KC_NO); } break;
	    case  KC_Z: { MAGIC_STRING("z", 		KC_NO); } break;

		case KC_COMM: { MAGIC_STRING(" and",    KC_NO); } break;
    }
}

static void process_right_magic(uint16_t keycode, uint8_t mods) { // RMAGIC definitions
    switch (keycode) {
	    case HRL_A: { MAGIC_STRING("nd",    	KC_SPC); } break;
	    case  KC_B: { MAGIC_STRING("b", 		KC_NO); } break;
	    case  KC_C: { MAGIC_STRING("c", 		KC_NO); } break;
	    case HRL_D: { MAGIC_STRING("d", 		KC_NO); } break;
	  //case HRM_E: { MAGIC_STRING("e", 		KC_NO); } break;
	    case  KC_F: { MAGIC_STRING("f", 		KC_NO); } break;
	    case  KC_G: { MAGIC_STRING("g", 		KC_NO); } break;
	  //case HRM_H: { MAGIC_STRING("h", 		KC_NO); } break;
	    case HRM_I: { MAGIC_STRING("on",    	KC_NO); } break;
	    case  KC_J: { MAGIC_STRING("j", 		KC_NO); } break;
	    case  KC_K: { MAGIC_STRING("k", 		KC_NO); } break;
	    case HRM_L: { MAGIC_STRING("l", 		KC_NO); } break;
	    case  KC_M: { MAGIC_STRING("m", 		KC_NO); } break;
	    case  KC_N: { MAGIC_STRING("n", 		KC_NO); } break;
	  //case  KC_O: { MAGIC_STRING("o", 		KC_NO); } break;
	    case  KC_P: { MAGIC_STRING("p", 		KC_NO); } break;
	    case  KC_Q: { MAGIC_STRING("ueen",		KC_NO); } break;
	    case HRM_R: { MAGIC_STRING("r", 		KC_NO); } break;
	    case HRM_S: { MAGIC_STRING("s", 		KC_NO); } break;
	  //case  KC_T: { MAGIC_STRING("t", 		KC_NO); } break;
	  //case  KC_U: { MAGIC_STRING("u", 		KC_NO); } break;
	    case HRM_V: { MAGIC_STRING("v", 		KC_NO); } break;
	    case  KC_W: { MAGIC_STRING("w", 		KC_NO); } break;
	    case HRM_X: { MAGIC_STRING("ex",    	KC_NO); } break;
	    case  KC_Y: { MAGIC_STRING("eah",    	KC_NO); } break;
	  //case  KC_Z: { MAGIC_STRING("z", 		KC_NO); } break;

	    case KC_COMM: { MAGIC_STRING(" but",    KC_NO); } break;
		case  KC_SPC: { MAGIC_STRING("the", 	KC_NO); } break;
		case KC_ASTR: { MAGIC_STRING("*N**or**dr**as**s**i**l**", KC_NO); } break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  if (record->event.pressed) {
  switch (keycode) {
        case LMAGIC: { process_left_magic(get_last_keycode(), get_last_mods()); set_last_keycode(KC_SPC); } return false;
        case RMAGIC: { process_right_magic(get_last_keycode(), get_last_mods()); set_last_keycode(KC_SPC); } return false;
		}
	}

  switch (keycode) {
    case TH_1:  return process_tap_or_long_press_key(record, KC_F1); // number on tap, f-key on hold
    case TH_2:  return process_tap_or_long_press_key(record, KC_F2);
    case TH_3:  return process_tap_or_long_press_key(record, KC_F3);
    case TH_4:  return process_tap_or_long_press_key(record, KC_F4);
    case TH_5:  return process_tap_or_long_press_key(record, KC_F5);
    case TH_6:  return process_tap_or_long_press_key(record, KC_F6);
    case TH_7:  return process_tap_or_long_press_key(record, KC_F7);
    case TH_8:  return process_tap_or_long_press_key(record, KC_F8);
    case TH_9:  return process_tap_or_long_press_key(record, KC_F9);
    case TH_10: return process_tap_or_long_press_key(record, KC_F10); // 0
    case TH_11: return process_tap_or_long_press_key(record, KC_F11); // 0
    case TH_12: return process_tap_or_long_press_key(record, KC_F12); // 0
		return false;
  }
  return true;
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Override opposite hands rule for thumb keys. `% (MATRIX_ROWS / 2)` needed due to split board. See dactyl.h for matrix layout.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 1 && other_record->event.key.col == 0){ return true; }
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 1 && other_record->event.key.col == 1){ return true; }
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 1 && other_record->event.key.col == 2){ return true; }
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 8 && other_record->event.key.col == 7){ return true; }
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 8 && other_record->event.key.col == 8){ return true; }
  if (other_record->event.key.row % (MATRIX_ROWS / 2) == 8 && other_record->event.key.col == 9){ return true; }
  // If none of the above apply, continue opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    case NUM_DEL:
    case NAV:
      return 0;  // Bypass Achordion for the above keys.
  }
  return 690;
}

uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode) {
  uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
  if ((mod & MOD_LSFT) != 0) {
    return 50;  // A shorter streak timeout for Shift mod-tap keys.
  } else {
    return 125;  // A longer timeout otherwise.
  }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_QUOT:
        case KC_SLSH:
        case KC_UNDS:
        case KC_SPC:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// Key overrides
const custom_shift_key_t custom_shift_keys[] = {
  {KC_COMM, KC_QUES},
  {KC_DOT,  KC_EXLM},
  {KC_SLSH, KC_BSLS},
  {KC_BSPC, KC_DEL},

  {KC_1, KC_1}, // disable shifting
  {KC_2, KC_2},
  {KC_3, KC_3},
  {KC_4, KC_4},
  {KC_5, KC_5},
  {KC_6, KC_6},
  {KC_7, KC_7},
  {KC_8, KC_8},
  {KC_9, KC_9},
  {KC_0, KC_0},
  {KC_EQL, KC_EQL},
  {KC_GRV, KC_GRV},
  {KC_LBRC, KC_LBRC},
  {KC_RBRC, KC_RBRC},

};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// RGB layer change, all keys
#define DIM_BY 18
#define DIMMED(rgb_color) DIMMED_(rgb_color)
#define DIMMED_(r, g, b) ((r)/DIM_BY), ((g)/DIM_BY), ((b)/DIM_BY)

#define NDRSL_COLOUR  DIMMED(RGB_PURPLE) // 0
#define GAME_COLOUR   DIMMED(RGB_CYAN)   // 1
#define QWERTY_COLOR  DIMMED(RGB_PINK)   // 2
#define SHADES_COLOR  DIMMED(RGB_GREEN)  // 3
#define BALANCE_COLOR DIMMED(RGB_RED)    // 6

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 1:
                rgb_matrix_set_color(i, GAME_COLOUR);
                break;
            case 2:
                rgb_matrix_set_color(i, QWERTY_COLOR);
                break;
            //case 3:
            //    rgb_matrix_set_color(i, SHADES_COLOR);
            //    break;
            //case 6:
                //rgb_matrix_set_color(i, BALANCE_COLOR);
                //break;
            default:
                break;
        }
    }
    return false;
}

void matrix_scan_user(void) {
  achordion_task();
  // Other tasks...
}