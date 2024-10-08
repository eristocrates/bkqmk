#pragma once

#include "quantum.h"

extern const uint16_t bitwise_num_keys[];
extern uint8_t        NUM_bitwise_num_KEYS;

bool process_bitwise_num(uint16_t keycode, keyrecord_t *record);
