// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "keycodes.h"
#include "quantum.h"
#include "timer.h"
#include QMK_KEYBOARD_H
#include "arcane_keys.h"
#include "akeyhd_keycodes.h"
#include "features/eristocrates/modal_keys.h"
#include "features/eristocrates/utilities.h"
#include "features/andrewjrae/qmk-vim/vim.h"
// #include "smtd_keycodes.h"
// #include "features/stasmarkin/sm_td.h"
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

void process_top_left_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
    if (timer_elapsed(prior_keydown) < REPEAT_TERM) {
        switch (keycode) {
            /* repeats */
            // left outer column
            case KC_X:
                ARCANE_STRING("x", KC_X);
                return;

            // left pinky column
            case KC_V:
                ARCANE_STRING("v", KC_V);
                return;

            // left ring column
            case KC_G:
                ARCANE_STRING("g", KC_G);
                return;

            // left middle column
            case KC_M:
                ARCANE_STRING("m", KC_M);
                return;

            // left index column
            case KC_P:
                ARCANE_STRING("p", KC_P);
                return;

                // left thumb
        }
    }
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
                /* anti sfb magic */
                // right outer column
            case TH___QU:
                ARCANE_STRING("z", KC_Z);
                return;
                // right pinky column

            case KC_H:
            case RWKEY_H:
                ARCANE_STRING("b", KC_B);
                return;
                // right ring column

            case KC_I:
            case RTALT_I:
                ARCANE_STRING("y", KC_Y);
                return;
                // right middle column
            case KC_E:
            case RCTRL_E:
                ARCANE_STRING("o", KC_O);
                return;

                // right index column
            case KC_A:
                ARCANE_STRING("u", KC_U);
                return;
            case RSHFT_A:
                ARCANE_STRING("u", KC_U);
                return;

                // right thumb
        }
    }
    tap_code16(default_keycode);
}

void process_top_right_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
#ifdef CONSOLE_ENABLE
    uprintf("arcane_keys.c: kc: 0x%04X\n", keycode);
#endif
    if (timer_elapsed(prior_keydown) < REPEAT_TERM) {
        switch (keycode) {
                /* repeats */
            // right outer column
            case KC_Z:
                ARCANE_STRING("z", KC_Z);
                return;

            // right pinky column
            case KC_B:
                ARCANE_STRING("b", KC_B);
                return;

            // right ring column
            case KC_Y:
                ARCANE_STRING("y", KC_Y);
                return;

            // right middle column
            case KC_O:
                ARCANE_STRING("o", KC_O);
                return;

            // right index column
            case KC_U:
                ARCANE_STRING("u", KC_U);
                return;

                // right thumb
        }
    }
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
                /* anti sfb magic */
            // right pinky column
            case KC_I:
            case RTALT_I:
                ARCANE_STRING("z", KC_Z);
                return;
                // left outer column
            case KC_J:
                ARCANE_STRING("x", KC_X);
                return;

                // left pinky column
            case KC_K:
            case LWKEY_K:
            case KC_W:
                ARCANE_STRING("v", KC_V);
                return;

            // left ring column
            case KC_S:
            case LTALT_S:
            case KC_F:
                ARCANE_STRING("g", KC_G);
                return;

            // left middle column
            case KC_N:
            case LCTRL_N:
            case KC_L:
                ARCANE_STRING("m", KC_M);
                return;

            // left index column
            case KC_D:
            case LSHFT_D:
            case KC_C:
                ARCANE_STRING("p", KC_P);
                return;

                // left thumb
        }
    }
    tap_code16(default_keycode);
}

void process_home_left_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
    if (timer_elapsed(prior_keydown) < REPEAT_TERM) {
        switch (keycode) {
                /* repeats */
                // left outer column
            case KC_J:
                ARCANE_STRING("j", KC_J);
                return;

            // left pinky column
            case KC_K:
                ARCANE_STRING("k", KC_K);
                return;
            case LWKEY_K:
                ARCANE_STRING("k", LWKEY_K);
                return;

            // left ring column
            case KC_S:
                ARCANE_STRING("s", KC_S);
                return;
            case LTALT_S:
                ARCANE_STRING("s", LTALT_S);
                return;

            // left middle column
            case KC_N:
                ARCANE_STRING("n", KC_N);
                return;
            case LCTRL_N:
                ARCANE_STRING("n", LCTRL_N);
                return;

            // left index column
            case KC_D:
                ARCANE_STRING("d", KC_D);
                return;
            case LSHFT_D:
                ARCANE_STRING("d", LSHFT_D);
                return;

                // left thumb
            case KC_R:
                ARCANE_STRING("r", KC_R);
                return;
        }
    }
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
            // case KC_LSPC:
            case KC_SPC:
                ARCANE_STRING("r", KC_R);
                return;

            // left index column
            case KC_P:
                ARCANE_STRING("l", KC_L);
                return;

            case KC_G:
                ARCANE_STRING("gl", KC_E);
                return;
                /*  anti sfb magic */
            // right outer column
            case KC_Z:
                ARCANE_STRING("qu", TH___QU);
                return;

                // right pinky column
            case KC_B:
                ARCANE_STRING("h", KC_H);
                return;

            // right ring column
            case KC_Y:
                ARCANE_STRING("i", KC_I);
                return;

            // right middle column
            case KC_O:
                ARCANE_STRING("e", KC_E);
                return;

                // right index column
            case KC_U:
                ARCANE_STRING("a", KC_A);
                return;

                // right thumb
        }
    }
    tap_code16(default_keycode);
}

void process_home_right_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
    if (timer_elapsed(prior_keydown) < REPEAT_TERM) {
        switch (keycode) {
                /* repeats */
            case KC_H:
                ARCANE_STRING("h", KC_H);
                return;
            case RWKEY_H:
                ARCANE_STRING("h", RWKEY_H);
                return;

            // right ring column
            case KC_I:
                ARCANE_STRING("i", KC_I);
                return;
            case RTALT_I:
                ARCANE_STRING("i", RTALT_I);
                return;

            // right middle column
            case KC_E:
                ARCANE_STRING("e", KC_E);
                return;
            case RCTRL_E:
                ARCANE_STRING("e", RCTRL_E);
                return;

                // right index column
            case KC_A:
                ARCANE_STRING("a", KC_A);
                return;
            case RSHFT_A:
                ARCANE_STRING("a", RSHFT_A);
                return;

                // right thumb
            case KC_T:
                ARCANE_STRING("t", KC_T);
                return;
        }
    }
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
            // case KC_RSPC:
            case KC_SPC:
                ARCANE_STRING("t", KC_T);
                return;

                /* anti sfb magic */
                // left outer column
            case KC_X:
                ARCANE_STRING("j", KC_J);
                return;

            // left pinky column
            case KC_V:
            case KC_W:
                ARCANE_STRING("k", KC_K);
                return;

            // left ring column
            case KC_G:
            case KC_F:
                ARCANE_STRING("s", KC_S);
                return;
            case KC_S:
            case LTALT_S:
                ARCANE_STRING("ion", KC_N);
                return;

            // left middle column
            case KC_M:
            case KC_L:
                ARCANE_STRING("n", KC_N);
                return;

            // left index column
            case KC_P:
            case KC_C:
                ARCANE_STRING("d", KC_D);
                return;

                // left thumb

                // right outer column

                // right pinky column
                // atypical, but that pinky + ring scissor is too gross to not eradicate
            case KC_B:
                ARCANE_STRING("i", KC_I);
                return;
        }
    }
    tap_code16(default_keycode);
}

void process_bottom_left_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
    if (timer_elapsed(prior_keydown) < REPEAT_TERM) {
        switch (keycode) {
                /* repeats */
                // left outer column

            // left pinky column
            case KC_W:
                ARCANE_STRING("w", KC_W);
                return;

            // left ring column
            case KC_F:
                ARCANE_STRING("f", KC_F);
                return;

            // left middle column
            case KC_L:
                ARCANE_STRING("l", KC_L);
                return;

            // left index column
            case KC_C:
                ARCANE_STRING("c", KC_C);
                return;

                // left thumb
        }
    }
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
                // left ring column
            case KC_G:
                ARCANE_STRING("l", KC_L);
                return;
                /* anti sfb magic */
            // right outer column
            case KC_Z:
                ARCANE_STRING("qu", TH___QU);
                return;

            // right pinky column

            // right ring column
            case KC_I:
            case RTALT_I:
                call_keycode(DOT_ARC);
                return;

                // right middle column

            case KC_E:
            case RCTRL_E:
                call_keycode(COM_ARC);
                return;
                // right index column

                // right thumb
        }
    }
    tap_code16(default_keycode);
}

void process_bottom_right_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown, uint16_t default_keycode) {
    if (timer_elapsed(prior_keydown) < MAGIC_TERM) {
        switch (keycode) {
                /* anti sfb magic */
                // left outer column
            case KC_X: // xword being a feature led to me realizing that pinky + ring scissor was even worse than the B I one
            // left pinky column
            case KC_V:
            case KC_K:
            case LWKEY_K:
                ARCANE_STRING("w", KC_W);
                return;

            // left ring column
            case KC_G:
            case KC_S:
            case LTALT_S:
                ARCANE_STRING("f", KC_F);
                return;

            // left middle column
            case KC_M:
            case KC_N:
            case LCTRL_N:
                ARCANE_STRING("l", KC_L);
                return;

            // left index column
            case KC_P:
            case KC_D:
            case LSHFT_D:
                ARCANE_STRING("c", KC_C);
                return;
                // left thumb

                // right outer column

                // right pinky column

                // right ring column

                // right middle column

                // right index column

                // right thumb

                // TODO think of something to do with what would otherwise be repeats on the sliver
        }
    }
    tap_code16(default_keycode);
}

// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/oneshot_shift_via_adaptive_keys/?share_id=J_a-r4rEr1p26tZg4lRpc&utm_content=1&utm_medium=android_app&utm_name=androidcss&utm_source=share&utm_term=1
// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/comment/l12n0qr/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
void process_comma_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown) {
    if (timer_elapsed(prior_keydown) < ARCANE_TIMEOUT_MS) {
        ARCANE_STRING(",", KC_COMM);
        if (smart_space_mode) {
            tap_code(KC_SPC);
        }
    } else {
        if (keycode == KC_COMM) {
            del_oneshot_mods(MOD_MASK_SHIFT);
            del_mods(MOD_MASK_SHIFT);
            ARCANE_STRING(",", KC_COMM);
        } else {
            ARCANE_STRING("", KC_COMM);
            call_keycode(OS_LSFT);
        }
    }
}

void process_dot_arcane(uint16_t keycode, uint8_t mods, uint16_t prior_keydown) {
    if (timer_elapsed(prior_keydown) < ARCANE_TIMEOUT_MS) {
        if (is_caps_word_on()) {
            ARCANE_STRING(".", KC_DOT);
            caps_word_off();
            return;
        }
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
                call_keycode(OS_LSFT);
            }
        }
    } else {
        if (is_caps_word_on()) {
            caps_word_off();
            ARCANE_STRING(".", KC_DOT);
        } else {
            ARCANE_STRING("", KC_DOT);
            caps_word_on();
        }
    }
}
