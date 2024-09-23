#include "piercing_keys.h"
// TODO move log_mod_press to my utilities
bool process_piercing_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRHINDX:
        case CRHINDX:
        case ARHINDX:
        case TH____A:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_SHIFTISHB)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_SHIFTISHL)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_SHIFTISHR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        default:
            return true;
    }
