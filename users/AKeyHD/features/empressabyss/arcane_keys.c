// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "arcane_keys.h"
#include "akeyhd_keycodes.h"
#include "features/eristocrates/modal_keys.h"
#include "features/andrewjrae/qmk-vim/vim.h"
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
        /* repeats */
        // left outer column
        case KC_X:
            ARCANE_STRING("x", KC_X);
            break;

        // left pinky column
        case KC_V:
            ARCANE_STRING("v", KC_V);
            break;

        // left ring column
        case KC_G:
            ARCANE_STRING("g", KC_G);
            break;

        // left middle column
        case KC_M:
            ARCANE_STRING("m", KC_M);
            break;

        // left index column
        case KC_P:
            ARCANE_STRING("p", KC_P);
            break;

            // left thumb

            /* anti sfb magic */
            // right outer column
        case TH___QU:
            ARCANE_STRING("z", KC_Z);
            break;
            // right pinky column

        case KC_H:
            ARCANE_STRING("b", KC_B);
            break;
            // right ring column

        case KC_I:
            ARCANE_STRING("y", KC_Y);
            break;
            // right middle column
        case KC_E:
            ARCANE_STRING("o", KC_O);
            break;

            // right index column
        case KC_A:
            ARCANE_STRING("u", KC_U);
            break;

            // right thumb

        default:
            tap_code(KC_EQL);
    }
}

void process_top_right_arcane(uint16_t keycode, uint8_t mods) {
#ifdef CONSOLE_ENABLE
    uprintf("arcane_keys.c: kc: 0x%04X\n", keycode);
#endif
    switch (keycode) {
            /* anti sfb magic */
            // left outer column
        case KC_J:
            ARCANE_STRING("x", KC_X);
            break;

            // left pinky column
        case KC_K:
        case KC_W:
            ARCANE_STRING("v", KC_V);
            break;

        // left ring column
        case KC_S:
        case KC_F:
            ARCANE_STRING("g", KC_G);
            break;

        // left middle column
        case KC_N:
        case KC_L:
            ARCANE_STRING("m", KC_M);
            break;

        // left index column
        case KC_D:
        case KC_C:
            ARCANE_STRING("p", KC_P);
            break;

            // left thumb

            /* repeats */
        // right outer column
        case KC_Z:
            ARCANE_STRING("z", KC_Z);
            break;

        // right pinky column
        case KC_B:
            ARCANE_STRING("b", KC_B);
            break;

        // right ring column
        case KC_Y:
            ARCANE_STRING("y", KC_Y);
            break;

        // right middle column
        case KC_O:
            ARCANE_STRING("o", KC_O);
            break;

        // right index column
        case KC_U:
            ARCANE_STRING("u", KC_U);
            break;

            // right thumb

        default:
            tap_code16(KC_AT);
    }
}

void process_middle_left_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            /* repeats */
            // left outer column
        case KC_J:
            ARCANE_STRING("j", KC_J);
            break;

        // left pinky column
        case KC_K:
            ARCANE_STRING("k", KC_K);
            break;

        // left ring column
        case KC_S:
            ARCANE_STRING("s", KC_S);
            break;

        // left middle column
        case KC_N:
            ARCANE_STRING("n", KC_N);
            break;

        // left index column
        case KC_D:
            ARCANE_STRING("d", KC_D);
            break;

            // left thumb

            /*  anti sfb magic */
        // right outer column
        case KC_Z:
            ARCANE_STRING("qu", TH___QU);
            break;

            // right pinky column
        case KC_B:
            ARCANE_STRING("h", KC_H);
            break;

        // right ring column
        case KC_Y:
            ARCANE_STRING("i", KC_I);
            break;

        // right middle column
        case KC_O:
            ARCANE_STRING("e", KC_E);
            break;

            // right index column
        case KC_U:
            ARCANE_STRING("a", KC_A);
            break;

            // right thumb

        default:
            tap_code(KC_NUHS);
    }
}

void process_middle_right_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            /* anti sfb magic */
            // left outer column
        case KC_X:
            ARCANE_STRING("j", KC_J);
            break;

        // left pinky column
        case KC_V:
        case KC_W:
            ARCANE_STRING("k", KC_K);
            break;

        // left ring column
        case KC_G:
        case KC_F:
            ARCANE_STRING("s", KC_S);
            break;

        // left middle column
        case KC_M:
        case KC_L:
            ARCANE_STRING("n", KC_N);
            break;

        // left index column
        case KC_P:
        case KC_C:
            ARCANE_STRING("d", KC_D);
            break;

            // left thumb

            /* repeats */
            // right outer column
            // TODO maybe something better to do on double qu?

            // right pinky column
        case KC_H:
            ARCANE_STRING("h", KC_H);
            break;

        // right ring column
        case KC_I:
            ARCANE_STRING("i", KC_I);
            break;

        // right middle column
        case KC_E:
            ARCANE_STRING("e", KC_E);
            break;

            // right index column
        case KC_A:
            ARCANE_STRING("a", KC_A);
            break;

            // right thumb

        default:
            tap_code(KC_NUHS);
    }
}

void process_bottom_left_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            /* repeats */
            // left outer column

        // left pinky column
        case KC_W:
            ARCANE_STRING("w", KC_W);
            break;

        // left ring column
        case KC_F:
            ARCANE_STRING("f", KC_F);
            break;

        // left middle column
        case KC_L:
            ARCANE_STRING("l", KC_L);
            break;

        // left index column
        case KC_C:
            ARCANE_STRING("c", KC_C);
            break;

        // left thumb
        case KC_R:
            ARCANE_STRING("r", KC_R);
            break;
        // case KC_LSPC:
        case KC_SPC:
            ARCANE_STRING("r", KC_R);
            break;

            /* anti sfb magic */
        // right outer column
        case KC_Z:
            ARCANE_STRING("qu", TH___QU);
            break;

            // right pinky column

            // right ring column

            // right middle column

            // right index column

            // right thumb

        default:
            tap_code(KC_NUHS);
    }
}

void process_bottom_right_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
            /* anti sfb magic */
            // left outer column

        // left pinky column
        case KC_V:
        case KC_K:
            ARCANE_STRING("w", KC_W);
            break;

        // left ring column
        case KC_G:
        case KC_S:
            ARCANE_STRING("f", KC_F);
            break;

        // left middle column
        case KC_M:
        case KC_N:
            ARCANE_STRING("l", KC_L);
            break;

        // left index column
        case KC_P:
        case KC_D:
            ARCANE_STRING("c", KC_C);
            break;

        // left thumb

        // right outer column

        // right pinky column

        // right ring column

        // right middle column

        // right index column

        // right thumb
        case KC_T:
            ARCANE_STRING("t", KC_T);
            break;
        // case KC_RSPC:
        case KC_SPC:
            ARCANE_STRING("t", KC_T);
            break;

        default:
            toggle_vim_emulation();
    }
}
// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/oneshot_shift_via_adaptive_keys/?share_id=J_a-r4rEr1p26tZg4lRpc&utm_content=1&utm_medium=android_app&utm_name=androidcss&utm_source=share&utm_term=1
// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/comment/l12n0qr/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
void process_comma_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_STOP:
            add_oneshot_mods(MOD_LSFT);
            ARCANE_STRING("", KC_COMM);
            break;

        default:
            ARCANE_STRING(",", KC_COMM);
            if (smart_space_mode) {
                tap_code(KC_SPC);
            }
            break;
    }
}

void process_dot_arcane(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_STOP:
            if (is_caps_word_on()) {
                ARCANE_STRING(".", KC_DOT);
                caps_word_off();
            } else {
                ARCANE_STRING("", KC_DOT);
                caps_word_on();
            }
            break;
        default:
            // last keycode is a smart combos that would need that prior space smartly removed
            if (smart_space_mode && last_smart_space) {
                tap_code(KC_BSPC);
            }
            if (semicolon_mode) {
                ARCANE_STRING(";", KC_SCLN);
                if (smart_space_mode) {
                    tap_code(KC_ENT);
                }
            } else {
                ARCANE_STRING(".", KC_DOT);
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                    add_oneshot_mods(MOD_LSFT);
                }
            }
    }
}
