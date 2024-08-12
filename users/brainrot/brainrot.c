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
bool               pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
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
            return 250;
        default:
            return TAPPING_TERM; // Default tapping term
    }
}
