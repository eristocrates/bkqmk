// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "arcane_keys.h"
// https://github.com/empressabyss/nordrassil?tab=readme-ov-file#implementation

void arcane_send_string_P(const char* str, uint16_t repeat_keycode) {
    /*
        uint8_t saved_mods = 0;
      if (is_caps_word_on()) { // If Caps Word is on, save the mods and hold Shift.
        saved_mods = get_mods();
        register_mods(MOD_BIT(KC_LSFT));
      }

    */
    send_string_with_delay_P(str, TAP_CODE_DELAY); // Send the string.
    set_last_keycode(repeat_keycode);              // 2024-03-09 Disabled sending of string for mag-rep / rep-mag consistency.
    // TODO ask embressabyss about this, as well as why not just un/register keycodes as well

    /*
      // If Caps Word is on, restore the mods.
      if (is_caps_word_on()) {
        set_mods(saved_mods);
      }
    */
}

void process_left_arcane(uint16_t keycode, uint8_t mods) { // LARCANE definitions
    switch (keycode) {
        // REPEATS
        // outer column
        case KC_X: {
            ARCANE_STRING("x", KC_X);
        } break;
        case KC_J: {
            ARCANE_STRING("j", KC_J);
        } break;

        // pinky column
        case KC_V: {
            ARCANE_STRING("v", KC_V);
        } break;
        case KC_K: {
            ARCANE_STRING("k", KC_K);
        } break;
        case KC_W: {
            ARCANE_STRING("w", KC_W);
        } break;

        // ring column
        case KC_G: {
            ARCANE_STRING("g", KC_G);
        } break;
        case KC_S: {
            ARCANE_STRING("s", KC_S);
        } break;
        case KC_F: {
            ARCANE_STRING("f", KC_F);
        } break;

        // middle column
        case KC_M: {
            ARCANE_STRING("m", KC_M);
        } break;
        case KC_N: {
            ARCANE_STRING("n", KC_N);
        } break;
        case KC_L: {
            ARCANE_STRING("l", KC_L);
        } break;

        // right index column to avoid sfb
        case KC_U: {
            ARCANE_STRING("u", KC_U);
        } break;
        case KC_A: {
            ARCANE_STRING("a", KC_A);
        } break;

        // thumb
        case KC_R: {
            ARCANE_STRING("r", KC_R);
        } break;

        // MAGIC
        // outer column
        case KC_Z: {
            ARCANE_STRING("z", KC_Z);
        } break;
        case KC_Q: {
            ARCANE_STRING("q", KC_Q);
        } break;

        // pinky column
        case KC_B: {
            ARCANE_STRING("h", KC_H);
        } break;
        case KC_H: {
            ARCANE_STRING("b", KC_B);
        } break;

        // ring column
        case KC_Y: {
            ARCANE_STRING("i", KC_I);
        } break;
        case KC_I: {
            ARCANE_STRING("y", KC_Y);
        } break;

        // middle column
        case KC_O: {
            ARCANE_STRING("a", KC_A);
        } break;
        case KC_E: {
            ARCANE_STRING("u", KC_U);
        } break;

        // left index column to avoid sfb
        case KC_P: {
            ARCANE_STRING("p", KC_P);
        } break;
        case KC_D: {
            ARCANE_STRING("d", KC_D);
        } break;
        case KC_C: {
            ARCANE_STRING("c", KC_C);
        } break;

        // thumb
        case KC_T: {
            ARCANE_STRING("t", KC_T);
        } break;
    }
}

void process_right_arcane(uint16_t keycode, uint8_t mods) { // RARCANE definitions
#ifdef CONSOLE_ENABLE
    uprintf("right arcane: kc: 0x%04X\n", keycode);
#endif

    switch (keycode) {
        // REPEATS
        // outer column
        case KC_Z: {
            ARCANE_STRING("z", KC_Z);
        } break;
        case KC_Q: {
            ARCANE_STRING("q", KC_Q);
        } break;

        // pinky column
        case KC_B: {
            ARCANE_STRING("b", KC_B);
        } break;
        case KC_H: {
            ARCANE_STRING("h", KC_H);
        } break;

        // ring column
        case KC_Y: {
            ARCANE_STRING("y", KC_Y);
        } break;
        case KC_I: {
            ARCANE_STRING("i", KC_I);
        } break;

        // middle column
        case KC_O: {
            ARCANE_STRING("o", KC_O);
        } break;
        case KC_E: {
            ARCANE_STRING("e", KC_E);
        } break;

        // left index column to avoid sfb
        case KC_P: {
            ARCANE_STRING("p", KC_P);
        } break;
        case KC_D: {
            ARCANE_STRING("d", KC_D);
        } break;

        // thumb
        case KC_T: {
            ARCANE_STRING("t", KC_T);
        } break;

        // MAGIC
        // exeption
        case KC_C: {
            ARCANE_STRING("d", KC_D);
        } break;
        // outer column
        case KC_X: {
            ARCANE_STRING("x", KC_X);
        } break;
        case KC_J: {
            ARCANE_STRING("j", KC_J);
        } break;

        // pinky column
        case KC_V: {
            ARCANE_STRING("v", KC_V);
        } break;
        case KC_K: {
            ARCANE_STRING("w", KC_W);
        } break;
        case KC_W: {
            ARCANE_STRING("k", KC_K);
        } break;

        // ring column
        case KC_G: {
            ARCANE_STRING("s", KC_S);
        } break;
        case KC_S: {
            ARCANE_STRING("f", KC_F);
        } break;
        case KC_F: {
            ARCANE_STRING("s", KC_S);
        } break;

        // middle column
        case KC_M: {
            ARCANE_STRING("l", KC_L);
        } break;
        case KC_N: {
            ARCANE_STRING("n", KC_N);
        } break;
        case KC_L: {
            ARCANE_STRING("n", KC_N);
        } break;

        // right index column to avoid sfb
        case KC_U: {
            ARCANE_STRING("a", KC_A);
        } break;
        case KC_A: {
            ARCANE_STRING("u", KC_U);
        } break;

        // thumb
        case KC_R: {
            ARCANE_STRING("r", KC_R);
        } break;
    }
}