#include "brainrot.h"

// Hold Timers
static uint16_t qu_tapping_term;
static uint16_t qu_timer         = 0;
bool            is_qu_held       = false;
bool            is_shift_toggled = false; // Variable to track the toggled Shift state

// https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/possumvibes.c#L5
static uint16_t    next_keycode;
static keyrecord_t next_record;
static uint16_t    prev_keycode;

// Define the tapping term for the custom keycode
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QU:
            return 175;
        default:
            return TAPPING_TERM; // Default tapping term
    }
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t prev_keycode;
    if (record->event.pressed) {
        // store previous keycode for instant tap decisions
        prev_keycode = next_keycode;

        // Cache the next input for mod-tap decisions
        next_keycode = keycode;
        next_record  = *record;
    }
    return true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    // TODO see if i can ifdef this
    /*
      if (!process_achordion(keycode, record)) { return false; }
      if (!process_custom_shift_keys(keycode, record)) { return false; }

    */

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
        case TG_SHFT:
            if (record->event.pressed) {
                if (is_shift_toggled) {
                    unregister_mods(MOD_BIT(KC_LSFT)); // Unregister Shift
                    is_shift_toggled = false;
                } else {
                    register_mods(MOD_BIT(KC_LSFT)); // Register Shift
                    is_shift_toggled = true;
                }
            }
            return false; // Skip all further processing of this key
        case LARCANE: {
            if (record->event.pressed) {
                process_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case RARCANE: {
            if (record->event.pressed) {
                process_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;

        default:
            return true; // Process all other keycodes normally
    }
}
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    switch (keycode) {
        case KC_ESC:
        case KC_BSPC:
        case KC_DEL:

        case LARCANE:
        case RARCANE:
            return false; // Arcane keys will ignore the above keycodes.
    }
    return true; // Other keys can be repeated.
}

// TODO incorperate qu to use this
/*
    process_record_user
    case TH_1:  return process_tap_or_long_press_key(record, KC_F1); // number on tap, f-key on hold
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

*/

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
