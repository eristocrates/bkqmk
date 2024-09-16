#pragma once
#include QMK_KEYBOARD_H

uint16_t extract_basic_keycode(uint16_t keycode, keyrecord_t *record, bool check_hold);
