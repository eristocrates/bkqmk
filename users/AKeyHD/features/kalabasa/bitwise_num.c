#include "bitwise_num.h"
#include <stdio.h>
#include "akeyhd_keycodes.h"
#include "../eristocrates/modal_keys.h"

static int8_t  pressed_keys = 0;
static uint8_t accumulator  = 0;

static char buffer[10];

// TODO ALWAYS KEEP IN SYNC WITH LAYERS
#define BN1_DOT LT(11, KC_PDOT)
#define BN2_DC1 LT(11, KC_P1)
#define BN4_DC2 LT(11, KC_P2)
#define BN8_DC3 LT(11, KC_P3)
#define BN16_ET LT(11, KC_PENT) // really KC_RPRN but sending this to avoid collision

bool process_bitwise_num(uint16_t keycode, keyrecord_t *record) {
    int index = -1;
    for (int i = 0; i < NUM_BITWISE_NUM_KEYS; ++i) {
        if (keycode == bitwise_num_keys[i]) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return true;
    }

    if (record->tap.count > 0) { // Key is being tapped.
        if (binary_mode) {
            if (record->event.pressed) {
                pressed_keys++;
                accumulator |= (1 << index);
            } else {
                pressed_keys--;
                if (pressed_keys <= 0) {
                    pressed_keys = 0;
                    snprintf(buffer, sizeof(buffer), "%d", accumulator);
                    SEND_STRING(buffer);
                    accumulator = 0;
                }
            }
        } else {
            switch (keycode) {
                // TODO see if i can reduce duplication
                case BN1_DOT:
                    if (record->event.pressed) {
                        tap_code(KC_0);
                    }
                    return false;
                case BN2_DC1:
                    if (record->event.pressed) {
                        tap_code(KC_4);
                    }
                    return false;
                case BN4_DC2:
                    if (record->event.pressed) {
                        tap_code(KC_5);
                    }
                    return false;
                case BN8_DC3:
                    if (record->event.pressed) {
                        tap_code(KC_6);
                    }
                    return false;
                case BN16_ET:
                    if (record->event.pressed) {
                        tap_code16(KC_RPRN);
                    }
                    return false;
            }
        }
    } else if (record->tap.count == 0) { // Key is being held
        if (binary_mode) {
            switch (keycode) {
                // TODO check if tap_code is preferable on hold
                case BN1_DOT:
                    if (record->event.pressed) {
                        tap_code(KC_0);
                    }
                    return false;
                case BN2_DC1:
                    if (record->event.pressed) {
                        tap_code(KC_4);
                    }
                    return false;
                case BN4_DC2:
                    if (record->event.pressed) {
                        tap_code(KC_5);
                    }
                    return false;
                case BN8_DC3:
                    if (record->event.pressed) {
                        tap_code(KC_6);
                    }
                    return false;
                case BN16_ET:
                    if (record->event.pressed) {
                        tap_code16(KC_RPRN);
                    }
                    return false;
            }
        } else {
            if (record->event.pressed) {
                pressed_keys++;
                accumulator |= (1 << index);
            } else {
                pressed_keys--;
                if (pressed_keys <= 0) {
                    pressed_keys = 0;
                    snprintf(buffer, sizeof(buffer), "%d", accumulator);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(buffer);
                    accumulator = 0;
                }
            }
        }
    }
    return false;
}
