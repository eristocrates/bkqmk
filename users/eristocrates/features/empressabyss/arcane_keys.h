// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
// #include QMK_KEYBOARD_H
#include "quantum.h"
// https://github.com/empressabyss/nordrassil?tab=readme-ov-file#implementation

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`.
#define ARCANE_STRING(str, repeat_keycode) arcane_send_string_P(PSTR(str), (repeat_keycode))
// TODO arcane keycode? arcane macro? essentially any other feature with repeat functionality

void arcane_send_string_P(const char *str, uint16_t repeat_keycode);
void process_comma_arcane(uint16_t keycode, uint8_t mods, uint16_t last_keydown);
void process_dot_arcane(uint16_t keycode, uint8_t mods, uint16_t last_keydown);

uint16_t arcane_tap(uint16_t keycode);
uint16_t process_arcane_columns(keypos_t arcane_key, uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_top_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_home_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_bottom_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_top_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_home_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
uint16_t process_bottom_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode);
