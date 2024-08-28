#include "bitwise_num.h"
#include <stdio.h>
#include "akeyhd_keycodes.h"

static int8_t  pressed_keys = 0;
static uint8_t accumulator  = 0;

static char buffer[10];

// TODO ALWAYS KEEP IN SYNC WITH LAYERS
#define BN1_DC1 LT(11, KC_0)
#define BN2_DC4 LT(11, KC_4)
#define BN4_DC5 LT(11, KC_5)
#define BN8_DC6 LT(11, KC_6)
#define BN16_RP LT(11, KC_RBRC) // really KC_RPRN but sending this to avoid collision

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
        switch (keycode) {
            case BN1_DC1:
                if (record->event.pressed) {
                    register_code(KC_0);
                } else {
                    unregister_code(KC_0);
                }
                return false;
            case BN2_DC4:
                if (record->event.pressed) {
                    register_code(KC_4);
                } else {
                    unregister_code(KC_4);
                }
                return false;
            case BN4_DC5:
                if (record->event.pressed) {
                    register_code(KC_5);
                } else {
                    unregister_code(KC_5);
                }
                return false;
            case BN8_DC6:
                if (record->event.pressed) {
                    register_code(KC_6);
                } else {
                    unregister_code(KC_6);
                }
                return false;
            case BN16_RP:
                if (record->event.pressed) {
                    register_code16(KC_RPRN);
                } else {
                    unregister_code16(KC_RPRN);
                }
                return false;
        }
    } else if (record->tap.count == 0) { // Key is being held
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
    }
    return false;
}
