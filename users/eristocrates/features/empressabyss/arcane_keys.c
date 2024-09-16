// Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdint.h>
#include <stdlib.h>
#include "action.h"
#include "action_layer.h"
#include "keycodes.h"
#include "quantum.h"
#include "timer.h"
#include QMK_KEYBOARD_H
#include "arcane_keys.h"
#include "eristocrates_keycodes.h"
#include "features/eristocrates/modal_keys.h"
#include "features/eristocrates/utilities.h"
#include "features/drashna/utilities.h"
#include "features/andrewjrae/qmk-vim/vim.h"
// #include "smtd_keycodes.h"
// #include "features/stasmarkin/sm_td.h"
// https://github.com/empressabyss/nordrassil?tab=readme-ov-file#implementation

void arcane_send_string_P(const char *str, uint16_t repeat_keycode) {
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

// Notably, middle arcane is considered the same row as thumb keys
#define SAME_ROW_LEFT_HAND last_key.row == arcane_key.row || (((last_key.col == 3 && last_key.row == 3) || (last_key.col == 4 && last_key.row == 3)) && arcane_key.col == 5 && arcane_key.row == 1)
#define SAME_ROW_RIGHT_HAND last_key.row == arcane_key.row || (arcane_key.col == 5 && arcane_key.row == 5 && last_key.col == 3 && last_key.row == 7)
#define SAME_ROW_SAME_HAND (arcane_key.row < 3 ? SAME_ROW_LEFT_HAND : SAME_ROW_RIGHT_HAND)
// excludes opposite an prior last key on the same row as the arcane key for other magic
#define OTHER_ROW_LEFT_HAND last_key.row <= 4 && abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row
#define OTHER_ROW_RIGHT_HAND last_key.row > 3 && abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row
#define OTHER_ROW_OTHER_HAND (arcane_key.row < 3 ? OTHER_ROW_RIGHT_HAND : OTHER_ROW_LEFT_HAND)
#define OTHER_ROW abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row

void process_arcane_matrix(keypos_t arcane_key, uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    uint8_t rowOffset = arcane_key.row < 3 ? 4 : -4;
    if (timer_elapsed(last_keydown) < REPEAT_TERM) {
        // same row same hand repeats
        if (SAME_ROW_SAME_HAND) {
#ifdef CONSOLE_ENABLE
            uprintf("arcane repeat: last_key col: %u, last_key row: %u, last_keycode: 0x%04X, key name: %s\n", last_key.col, last_key.row, last_keycode, key_name(last_keycode, false));
#endif
            ARCANE_STRING(key_name(last_keycode, false), last_keycode);
            return;
        }
    }
    // TODO add descriptive macros for conditionals
    if (timer_elapsed(last_keydown) < MAGIC_TERM) {
        if (OTHER_ROW) {
            keypos_t magic;
            /*  L_LTHMB -> LBM_ARC = L_MTHMB ||
                L_RTHMB -> LBM_ARC = L_MTHMB
            */
            if ((arcane_key.row == 2 && last_key.col == 3 && last_key.row == 3) || (arcane_key.row == 1 && last_key.col == 1 && last_key.row == 3)) {
                magic.col = 4;
                magic.row = 3;
            } else if (arcane_key.row == 2 && last_key.col == 4 && last_key.row == 3) { // L_MTHMB -> LBM_ARC = L_LTHMB
                magic.col = 3;
                magic.row = 3;
            } else if (arcane_key.row == 5 && last_key.col == 1 && last_key.row == 7) { // R_LTHMB -> RHM_ARC = R_MTHMB
                magic.col = 3;
                magic.row = 7;
            } else if (arcane_key.row == 5 && last_key.col == 1 && last_key.row == 4) { // RT_PNKY -> RHM_ARC = RH_RING
                magic.col = 2;
                magic.row = 5;
            } else if (arcane_key.row == 1 && last_key.col == 1 && last_key.row == 0) { // LT_PNKY -> LHM_ARC = LH_RING
                magic.col = 2;
                magic.row = 1;
            } else if (arcane_key.row == 2 && last_key.col == 0 && last_key.row == 1) { // LH_OUTR -> LBM_ARC = LB_PNKY
                magic.col = 1;
                magic.row = 2;
            } else if (arcane_key.row == 6 && last_key.col == 0 && last_key.row == 5) { // RH_OUTR -> RBM_ARC = RB_PNKY
                magic.col = 1;
                magic.row = 6;
            } else if (!(last_key.col == 3 && last_key.row == 3) && !(last_key.col == 4 && last_key.row == 3) && !(last_key.col == 1 && last_key.row == 3) && !(last_key.col == 3 && last_key.row == 7) && !(last_key.col == 1 && last_key.row == 7)) {
                // TODO figure out what to do about same hand different row magic that isn't defined above. below was too destructive to above exceptions to b added to OTHER_ROW
                //  && !(arcane_key.row < 3 && last_key.col < 5 && last_key.row < 3) && !(arcane_key.row > 3 && last_key.col < 5 && last_key.row > 3
                magic.col = last_key.col;
                magic.row = arcane_key.row + rowOffset;
            }
            uint16_t keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keymap_key_to_keycode(layer_switch_get_layer(magic), magic)));
            // uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(magic), magic);

#ifdef CONSOLE_ENABLE
            uprintf("arcane magic: last_key col: %u, last_key row: %u, magic col: %u, magic row: %u, keycode: 0x%04X, key name: %s\n", last_key.col, last_key.row, magic.col, magic.row, keycode, key_name(keycode, false));
#endif
            if (keycode != 0) {
                ARCANE_STRING(key_name(keycode, false), keycode);
                return;
            }
        }
    }
    // TODO consider space magic term with extra wide window?

    tap_code16(default_keycode);
}

void process_top_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 0}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
void process_home_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 1}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
void process_bottom_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 2}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
void process_top_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 4}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
void process_home_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 5}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
void process_bottom_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    process_arcane_matrix((keypos_t){5, 6}, last_keycode, last_key, last_keydown, mods, default_keycode);
}

// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/oneshot_shift_via_adaptive_keys/?share_id=J_a-r4rEr1p26tZg4lRpc&utm_content=1&utm_medium=android_app&utm_name=androidcss&utm_source=share&utm_term=1
// inspired from https://www.reddit.com/r/KeyboardLayouts/comments/1cc2yri/comment/l12n0qr/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
void process_comma_arcane(uint16_t keycode, uint8_t mods, uint16_t last_keydown) {
    if (timer_elapsed(last_keydown) < ARCANE_TIMEOUT_MS) {
        if (last_smart_space) {
            tap_code(KC_BSPC);
        }
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

void process_dot_arcane(uint16_t keycode, uint8_t mods, uint16_t last_keydown) {
    if (timer_elapsed(last_keydown) < ARCANE_TIMEOUT_MS) {
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
            if (smart_dot_mode) {
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
