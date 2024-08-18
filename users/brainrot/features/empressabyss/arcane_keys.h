// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H
// https://github.com/empressabyss/nordrassil?tab=readme-ov-file#implementation

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`.
#define ARCANE_STRING(str, repeat_keycode) arcane_send_string_P(PSTR(str), (repeat_keycode))
// TODO arcane keycode? arcane macro? essentially any other feature with repeate functionality

void arcane_send_string_P(const char* str, uint16_t repeat_keycode);
void process_top_left_arcane(uint16_t keycode, uint8_t mods);
void process_top_right_arcane(uint16_t keycode, uint8_t mods);
void process_bottom_left_arcane(uint16_t keycode, uint8_t mods);
void process_bottom_right_arcane(uint16_t keycode, uint8_t mods);
