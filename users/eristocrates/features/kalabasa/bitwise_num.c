#include "bitwise_num.h"
#include <stdio.h>
#include "eristocrates_keycodes.h"
#include "../eristocrates/modal_keys.h"

static int8_t   pressed_keys = 0;
static uint16_t accumulator  = 0;

static char buffer[16];

bool process_bitwise_num(uint16_t keycode, keyrecord_t *record) {
    int index = -1;
    for (int i = 0; i < NUM_bitwise_num_KEYS; ++i) {
        if (keycode == bitwise_num_keys[i]) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return true;
    }

    if (record->event.pressed) {
        pressed_keys++;
        accumulator |= (1 << index);
    } else {
        pressed_keys--;
        if (pressed_keys <= 0) {
            pressed_keys = 0;
            snprintf(buffer, sizeof(buffer), "%d", accumulator);
            SEND_STRING(buffer);
            // TODO try using send byte?
            // send_byte(accumulator);
            accumulator = 0;
        }
    }
    return false;
}
