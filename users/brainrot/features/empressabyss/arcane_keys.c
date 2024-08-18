// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "arcane_keys.h"
#include "brainrot_keycodes.h"
// https://github.com/empressabyss/nordrassil?tab=readme-ov-file#implementation

void arcane_send_string_P(const char* str, uint16_t repeat_keycode) {
    uint8_t saved_mods = 0;
    if (is_caps_word_on()) { // If Caps Word is on, save the mods and hold Shift.
        saved_mods = get_mods();
        register_mods(MOD_BIT(KC_LSFT));
    }

    send_string_with_delay_P(str, TAP_CODE_DELAY); // Send the string.
    set_last_keycode(repeat_keycode);              // 2024-03-09 Disabled sending of string for mag-rep / rep-mag consistency.
                                                   // TODO ask embressabyss about his disabling of string
                                                   // TODOtry just un/register keycodes

    // If Caps Word is on, restore the mods.
    if (is_caps_word_on()) {
        set_mods(saved_mods);
    }
}

void process_top_left_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        // left outer column
        case KC_X: {
            ARCANE_STRING("x", KC_X);
        } break;
        case KC_J: {
            ARCANE_STRING("j", KC_J);
        } break;

        // left pinky column
        case KC_V: {
            ARCANE_STRING("v", KC_V);
        } break;
        case KC_K: {
            ARCANE_STRING("k", KC_K);
        } break;

        // left ring column
        case KC_G: {
            ARCANE_STRING("g", KC_G);
        } break;
        case KC_S: {
            ARCANE_STRING("s", KC_S);
        } break;

        // left middle column
        case KC_M: {
            ARCANE_STRING("m", KC_M);
        } break;
        case KC_N: {
            ARCANE_STRING("n", KC_N);
        } break;
        case KC_L: {
            ARCANE_STRING("ly", KC_SPC);
        } break;

        // left index column
        case KC_P: {
            ARCANE_STRING("p", KC_P);
        } break;
        case KC_D: {
            ARCANE_STRING("d", KC_D);
        } break;

        // left thumb

        // right outer column
        case KC_Z: {
            ARCANE_STRING("qu", TH_QU);
        } break;
        case TH_QU: {
            ARCANE_STRING("z", KC_Z);
        } break;

        // right pinky column
        case KC_B: {
            ARCANE_STRING("h", KC_H);
        } break;
        case KC_H: {
            ARCANE_STRING("b", KC_B);
        } break;

        // right ring column
        case KC_Y: {
            ARCANE_STRING("i", KC_I);
        } break;
        case KC_I: {
            ARCANE_STRING("y", KC_Y);
        } break;

        // right middle column
        case KC_O: {
            ARCANE_STRING("e", KC_E);
        } break;
        case KC_E: {
            ARCANE_STRING("o", KC_O);
        } break;

        // right index column
        case KC_U: {
            ARCANE_STRING("a", KC_A);
        } break;
        case KC_A: {
            ARCANE_STRING("u", KC_U);
        } break;

            // right thumb

        default:
            tap_code(KC_EQL);
    }
}

void process_top_right_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        // left outer column
        case KC_X: {
            ARCANE_STRING("j", KC_J);
        } break;
        case KC_J: {
            ARCANE_STRING("x", KC_X);
        } break;

            // left pinky column
        case KC_V: {
            ARCANE_STRING("k", KC_K);
        } break;
        case KC_K: {
            ARCANE_STRING("v", KC_V);
        } break;
        case KC_W: {
            ARCANE_STRING("v", KC_V);
        } break;

        // left ring column
        case KC_G: {
            ARCANE_STRING("s", KC_S);
        } break;
        case KC_S: {
            ARCANE_STRING("g", KC_G);
        } break;
        case KC_F: {
            ARCANE_STRING("g", KC_G);
        } break;

        // left middle column
        case KC_M: {
            ARCANE_STRING("n", KC_N);
        } break;
        case KC_N: {
            ARCANE_STRING("m", KC_M);
        } break;
        case KC_L: {
            ARCANE_STRING("m", KC_M);
        } break;

        // left index column
        case KC_P: {
            ARCANE_STRING("d", KC_D);
        } break;
        case KC_D: {
            ARCANE_STRING("p", KC_P);
        } break;
        case KC_C: {
            ARCANE_STRING("p", KC_P);
        } break;

        // left thumb

        // right outer column
        case KC_Z: {
            ARCANE_STRING("z", KC_Z);
        } break;

        // right pinky column
        case KC_B: {
            ARCANE_STRING("b", KC_B);
        } break;
        case KC_H: {
            ARCANE_STRING("h", KC_H);
        } break;

        // right ring column
        case KC_Y: {
            ARCANE_STRING("y", KC_Y);
        } break;
        case KC_I: {
            ARCANE_STRING("i", KC_I);
        } break;

        // right middle column
        case KC_O: {
            ARCANE_STRING("o", KC_O);
        } break;
        case KC_E: {
            ARCANE_STRING("e", KC_E);
        } break;

        // right index column
        case KC_U: {
            ARCANE_STRING("a", KC_A);
        } break;
        case KC_A: {
            ARCANE_STRING("u", KC_U);
        } break;

            // right thumb

        default:
            tap_code16(KC_AT);
    }
}
void process_bottom_left_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            // left outer column
        case KC_J: {
            ARCANE_STRING("j", KC_J);
        } break;

        // left pinky column
        case KC_V: {
            ARCANE_STRING("x", KC_X);
        } break;
        case KC_K: {
            ARCANE_STRING("k", KC_K);
        } break;
        case KC_W: {
            ARCANE_STRING("w", KC_W);
        } break;

        // left ring column
        case KC_S: {
            ARCANE_STRING("s", KC_S);
        } break;
        case KC_F: {
            ARCANE_STRING("f", KC_F);
        } break;

        // left middle column
        case KC_N: {
            ARCANE_STRING("n", KC_N);
        } break;
        case KC_L: {
            ARCANE_STRING("l", KC_L);
        } break;

        // left index column
        case KC_D: {
            ARCANE_STRING("d", KC_D);
        } break;
        case KC_C: {
            ARCANE_STRING("c", KC_C);
        } break;

        // left thumb
        case KC_R: {
            ARCANE_STRING("r", KC_R);
        } break;
        case KC_LSPC: {
            ARCANE_STRING("r", KC_R);
        } break;

        // right outer column
        case KC_Z: {
            ARCANE_STRING("qu", TH_QU);
        } break;

            // right pinky column
            // TODO add whatever bottom key becomes

        // right ring column
        case KC_I: {
            ARCANE_STRING(".", KC_DOT);
        } break;
        case KC_DOT: {
            ARCANE_STRING("i", KC_I);
        } break;

        // right middle column
        case KC_O: {
            ARCANE_STRING(",", KC_COMM);
        } break;
        case KC_E: {
            ARCANE_STRING(",", KC_COMM);
        } break;
        case KC_COMM: {
            ARCANE_STRING("e", KC_E);
        } break;

            // right index column
            // TODO add whatever bottom key becomes

            // right thumb

        default:
            tap_code(KC_NUHS);
    }
}

void process_bottom_right_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            // left outer column

            // left pinky column
        case KC_V: {
            ARCANE_STRING("w", KC_W);
        } break;
        case KC_K: {
            ARCANE_STRING("w", KC_W);
        } break;
        case KC_W: {
            ARCANE_STRING("k", KC_K);
        } break;

        // left ring column
        case KC_G: {
            ARCANE_STRING("f", KC_F);
        } break;
        case KC_S: {
            ARCANE_STRING("f", KC_F);
        } break;
        case KC_F: {
            ARCANE_STRING("s", KC_S);
        } break;

        // left middle column
        case KC_M: {
            ARCANE_STRING("l", KC_L);
        } break;
        case KC_N: {
            ARCANE_STRING("l", KC_L);
        } break;
        case KC_L: {
            ARCANE_STRING("n", KC_N);
        } break;

        // left index column
        case KC_P: {
            ARCANE_STRING("c", KC_C);
        } break;
        case KC_D: {
            ARCANE_STRING("c", KC_C);
        } break;
        case KC_C: {
            ARCANE_STRING("d", KC_D);
        } break;

        // left thumb

        // right outer column

        // right pinky column
        case KC_H: {
            ARCANE_STRING("h", KC_H);
        } break;

        // right ring column
        case KC_I: {
            ARCANE_STRING("i", KC_I);
        } break;
        case KC_COMM: {
            ARCANE_STRING(",", KC_COMM);
        } break;

        // right middle column
        case KC_E: {
            ARCANE_STRING("e", KC_E);
        } break;
        case KC_DOT: {
            ARCANE_STRING(".", KC_DOT);
        } break;

        // right index column
        case KC_A: {
            ARCANE_STRING("a", KC_A);
        } break;

        // right thumb
        case KC_T: {
            ARCANE_STRING("t", KC_T);
        } break;
        case KC_RSPC: {
            ARCANE_STRING("t", KC_T);
        } break;

        default:
            tap_code16(KC_PERC);
    }
}
