#include QMK_KEYBOARD_H
#define SHIFT_KEYS (keycode == OSM(MOD_LSFT) || keycode == KC_LSFT)

bool alt_tab_pressed = false;

bool process_alt_tab(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == KC_F18) {
            if (alt_tab_pressed) {
                tap_code16(KC_TAB);
            } else {
                register_code(KC_LALT);
                tap_code16(KC_TAB);
                alt_tab_pressed = true;
            }
            return false;
        }
        if (alt_tab_pressed && !SHIFT_KEYS) {
            unregister_code(KC_LALT);
            alt_tab_pressed = false;
        }
    }

    return true;
}
