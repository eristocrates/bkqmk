/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// layers
enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_QWERTY,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_LAYER,
};

#define BASE TO(LAYER_BASE)
#define LAYER TT(LAYER_LAYER)
#define LOWER TG(LAYER_LOWER)
#define RAISE TG(LAYER_RAISE)

#define PT_K LT(LAYER_POINTER, KC_K)
#define PT_H LT(LAYER_POINTER, KC_H)
// default LTs
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// Keycodes
enum my_keycodes {
    KC_QU = SAFE_RANGE,
    SC_RMDT,
};

// Combos
// TODO change this from enter to other more useful ones
const uint16_t PROGMEM enter_combo[] = {KC_COMM, KC_DOT, COMBO_END};
combo_t                key_combos[]  = {
    COMBO(enter_combo, KC_ENT),
};

// Tap Dance
enum {
    TD_SPC_ENT,
    TD_SPC_ESC,
    TD_BSPC_WRD,
    TD_DEL_WRD,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SPC_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
    [TD_SPC_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ESC),
    [TD_BSPC_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_BSPC), KC_BSPC),
    [TD_DEL_WRD]  = ACTION_TAP_DANCE_DOUBLE(C(KC_DEL), KC_DEL),
};

#define SPC_ENT TD(TD_SPC_ENT)
#define SPC_ESC TD(TD_SPC_ESC)
#define BSPC_WRD TD(TD_BSPC_WRD)
#define DEL_WRD TD(TD_DEL_WRD)

// Hold Timers
static uint16_t qu_tapping_term;
static uint16_t qu_timer   = 0;
bool            is_qu_held = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_X,    KC_V,    KC_G,    KC_M,    KC_P, XXXXXXX,    XXXXXXX,    KC_U,    KC_O,    KC_Y,    KC_B,    KC_Z,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          KC_J,    PT_K,    KC_S,    KC_N,    KC_D,BSPC_WRD,    DEL_WRD,    KC_A,    KC_E,    KC_I,    PT_H,   KC_QU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
          BASE,    KC_W,    KC_F,    KC_L,    KC_C, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,    LAYER,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    LAYER,    KC_R, SPC_ESC,    SPC_ENT,    KC_T
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_LGUI,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_RGUI,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_RCTL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BSPC,  KC_SPC,   LOWER,      RAISE,  KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, RGB_TOG, KC_MNXT, KC_MPLY, KC_MPRV, XXXXXXX,    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,    KC_4,    KC_5,    KC_6, KC_PMNS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,    KC_PAST,    KC_1,    KC_2,    KC_3, KC_PSLS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    LOWER, XXXXXXX, XXXXXXX,    _______, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,   RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    RAISE, XXXXXXX, XXXXXXX,    _______, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRG_TOG, SNIPING, KC_BTN3, XXXXXXX,    XXXXXXX, KC_BTN1, KC_BTN2, DRG_TOG, _______, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LAYER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(KC_S), XXXXXXX,    XXXXXXX, C(KC_S), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LOWER, XXXXXXX,    XXXXXXX,   RAISE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, C(KC_V), C(KC_X), XXXXXXX,    XXXXXXX, C(KC_C), C(KC_V), XXXXXXX, SC_RMDT, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    LAYER, XXXXXXX, XXXXXXX,     KC_ESC,  KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  /*
  [LAYER_XXXXXXX] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER________] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  */
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QU:
            qu_tapping_term = get_tapping_term(KC_QU, record);
            if (record->event.pressed) {
                if (!is_qu_held) {
                    is_qu_held = true;
                    qu_timer   = timer_read();
                }
            } else {
                is_qu_held = false;
                if (timer_elapsed(qu_timer) < qu_tapping_term) {
                    // Send "qu" if tapped
                    SEND_STRING("qu");
                }
            }
            return false; // Skip all further processing of this key
        case SC_RMDT:
            if (record->event.pressed) {
                // When keycode is pressed
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_PAUSE);
            } else {
                // When keycode is released
                unregister_code(KC_PAUSE);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}
void matrix_scan_user(void) {
    if (is_qu_held)
        if (timer_elapsed(qu_timer) == qu_tapping_term) {
            tap_code(KC_Q);
        }

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#    ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#    endif // RGB_MATRIX_ENABLE
    }
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
}

// Define the tapping term for the custom keycode
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QU:
            return 175;
        case PT_K:
        case PT_H:
            return 333;
        default:
            return TAPPING_TERM; // Default tapping term
    }
}
