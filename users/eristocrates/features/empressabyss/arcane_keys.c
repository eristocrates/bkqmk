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
uint16_t arcane_tap(uint16_t keycode) {
    set_last_keycode(keycode); // 2024-03-09 Disabled sending of string for mag-rep / rep-mag consistency.
    return keycode;
}

#define LAST_LEFT_TOP_OUTER (last_key.col == 0 && last_key.row == 0)
#define LAST_LEFT_TOP_PINKY (last_key.col == 1 && last_key.row == 0)
#define LAST_LEFT_TOP_RING (last_key.col == 2 && last_key.row == 0)
#define LAST_LEFT_TOP_MIDDLE (last_key.col == 3 && last_key.row == 0)
#define LAST_LEFT_TOP_INDEX (last_key.col == 4 && last_key.row == 0)
#define LAST_LEFT_HOME_OUTER (last_key.col == 0 && last_key.row == 1)
#define LAST_LEFT_HOME_PINKY (last_key.col == 1 && last_key.row == 1)
#define LAST_LEFT_HOME_RING (last_key.col == 2 && last_key.row == 1)
#define LAST_LEFT_HOME_MIDDLE (last_key.col == 3 && last_key.row == 1)
#define LAST_LEFT_HOME_INDEX (last_key.col == 4 && last_key.row == 1)
#define LAST_LEFT_BOTTOM_OUTER (last_key.col == 0 && last_key.row == 2)
#define LAST_LEFT_BOTTOM_PINKY (last_key.col == 1 && last_key.row == 2)
#define LAST_LEFT_BOTTOM_RING (last_key.col == 2 && last_key.row == 2)
#define LAST_LEFT_BOTTOM_MIDDLE (last_key.col == 3 && last_key.row == 2)
#define LAST_LEFT_BOTTOM_INDEX (last_key.col == 4 && last_key.row == 2)
#define LAST_RIGHT_TOP_OUTER (last_key.col == 0 && last_key.row == 4)
#define LAST_RIGHT_TOP_PINKY (last_key.col == 1 && last_key.row == 4)
#define LAST_RIGHT_TOP_RING (last_key.col == 2 && last_key.row == 4)
#define LAST_RIGHT_TOP_MIDDLE (last_key.col == 3 && last_key.row == 4)
#define LAST_RIGHT_TOP_INDEX (last_key.col == 4 && last_key.row == 4)
#define LAST_RIGHT_HOME_OUTER (last_key.col == 0 && last_key.row == 5)
#define LAST_RIGHT_HOME_PINKY (last_key.col == 1 && last_key.row == 5)
#define LAST_RIGHT_HOME_RING (last_key.col == 2 && last_key.row == 5)
#define LAST_RIGHT_HOME_MIDDLE (last_key.col == 3 && last_key.row == 5)
#define LAST_RIGHT_HOME_INDEX (last_key.col == 4 && last_key.row == 5)
#define LAST_RIGHT_BOTTOM_OUTER (last_key.col == 0 && last_key.row == 6)
#define LAST_RIGHT_BOTTOM_PINKY (last_key.col == 1 && last_key.row == 6)
#define LAST_RIGHT_BOTTOM_RING (last_key.col == 2 && last_key.row == 6)
#define LAST_RIGHT_BOTTOM_MIDDLE (last_key.col == 3 && last_key.row == 6)
#define LAST_RIGHT_BOTTOM_INDEX (last_key.col == 4 && last_key.row == 6)
#define LAST_LEFT_INNER_THUMB (last_key.col == 3 && last_key.row == 3)
#define LAST_LEFT_MIDDLE_THUMB (last_key.col == 4 && last_key.row == 3)
#define LAST_LEFT_OUTER_THUMB (last_key.col == 1 && last_key.row == 3)
#define LAST_RIGHT_OUTER_THUMB (last_key.col == 1 && last_key.row == 7)
#define LAST_RIGHT_MIDDLE_THUMB (last_key.col == 3 && last_key.row == 7)

#define MAGIC_LEFT_TOP_OUTER \
    magic.col = 0;           \
    magic.row = 0;

#define MAGIC_LEFT_TOP_PINKY \
    magic.col = 1;           \
    magic.row = 0;

#define MAGIC_LEFT_TOP_RING \
    magic.col = 2;          \
    magic.row = 0;

#define MAGIC_LEFT_TOP_MIDDLE \
    magic.col = 3;            \
    magic.row = 0;

#define MAGIC_LEFT_TOP_INDEX \
    magic.col = 4;           \
    magic.row = 0;

#define MAGIC_LEFT_HOME_OUTER \
    magic.col = 0;            \
    magic.row = 1;

#define MAGIC_LEFT_HOME_PINKY \
    magic.col = 1;            \
    magic.row = 1;

#define MAGIC_LEFT_HOME_RING \
    magic.col = 2;           \
    magic.row = 1;

#define MAGIC_LEFT_HOME_MIDDLE \
    magic.col = 3;             \
    magic.row = 1;

#define MAGIC_LEFT_HOME_INDEX \
    magic.col = 4;            \
    magic.row = 1;

#define MAGIC_LEFT_BOTTOM_OUTER \
    magic.col = 0;              \
    magic.row = 2;

#define MAGIC_LEFT_BOTTOM_PINKY \
    magic.col = 1;              \
    magic.row = 2;

#define MAGIC_LEFT_BOTTOM_RING \
    magic.col = 2;             \
    magic.row = 2;

#define MAGIC_LEFT_BOTTOM_MIDDLE \
    magic.col = 3;               \
    magic.row = 2;

#define MAGIC_LEFT_BOTTOM_INDEX \
    magic.col = 4;              \
    magic.row = 2;

#define MAGIC_RIGHT_TOP_OUTER \
    magic.col = 0;            \
    magic.row = 4;

#define MAGIC_RIGHT_TOP_PINKY \
    magic.col = 1;            \
    magic.row = 4;

#define MAGIC_RIGHT_TOP_RING \
    magic.col = 2;           \
    magic.row = 4;

#define MAGIC_RIGHT_TOP_MIDDLE \
    magic.col = 3;             \
    magic.row = 4;

#define MAGIC_RIGHT_TOP_INDEX \
    magic.col = 4;            \
    magic.row = 4;

#define MAGIC_RIGHT_HOME_OUTER \
    magic.col = 0;             \
    magic.row = 5;

#define MAGIC_RIGHT_HOME_PINKY \
    magic.col = 1;             \
    magic.row = 5;

#define MAGIC_RIGHT_HOME_RING \
    magic.col = 2;            \
    magic.row = 5;

#define MAGIC_RIGHT_HOME_MIDDLE \
    magic.col = 3;              \
    magic.row = 5;

#define MAGIC_RIGHT_HOME_INDEX \
    magic.col = 4;             \
    magic.row = 5;

#define MAGIC_RIGHT_BOTTOM_OUTER \
    magic.col = 0;               \
    magic.row = 6;

#define MAGIC_RIGHT_BOTTOM_PINKY \
    magic.col = 1;               \
    magic.row = 6;

#define MAGIC_RIGHT_BOTTOM_RING \
    magic.col = 2;              \
    magic.row = 6;

#define MAGIC_RIGHT_BOTTOM_MIDDLE \
    magic.col = 3;                \
    magic.row = 6;

#define MAGIC_RIGHT_BOTTOM_INDEX \
    magic.col = 4;               \
    magic.row = 6;

#define MAGIC_LEFT_INNER_THUMB \
    magic.col = 3;             \
    magic.row = 3;

#define MAGIC_LEFT_MIDDLE_THUMB \
    magic.col = 4;              \
    magic.row = 3;

#define MAGIC_LEFT_OUTER_THUMB \
    magic.col = 1;             \
    magic.row = 3;

#define MAGIC_RIGHT_OUTER_THUMB \
    magic.col = 1;              \
    magic.row = 7;

#define MAGIC_RIGHT_MIDDLE_THUMB \
    magic.col = 3;               \
    magic.row = 7;

#define LEFT_TOP_ARCANE (arcane_key.col == 5 && arcane_key.row == 0)
#define LEFT_HOME_ARCANE (arcane_key.col == 5 && arcane_key.row == 1)
#define LEFT_BOTTOM_ARCANE (arcane_key.col == 5 && arcane_key.row == 2)
#define RIGHT_TOP_ARCANE (arcane_key.col == 5 && arcane_key.row == 4)
#define RIGHT_HOME_ARCANE (arcane_key.col == 5 && arcane_key.row == 5)
#define RIGHT_BOTTOM_ARCANE (arcane_key.col == 5 && arcane_key.row == 6)

// clang-format off
#define DUAL_CASES \
            if ((LAST_LEFT_OUTER_THUMB && LEFT_HOME_ARCANE)) {\
                MAGIC_LEFT_MIDDLE_THUMB\
            } else if ((LAST_LEFT_MIDDLE_THUMB && RIGHT_BOTTOM_ARCANE)) { \
                MAGIC_LEFT_INNER_THUMB\
            } else if ((LAST_LEFT_INNER_THUMB && RIGHT_BOTTOM_ARCANE)) { \
                MAGIC_LEFT_MIDDLE_THUMB\
            } else if ((LAST_LEFT_INNER_THUMB && LEFT_BOTTOM_ARCANE) || (LAST_LEFT_MIDDLE_THUMB && LEFT_BOTTOM_ARCANE) || (LAST_RIGHT_MIDDLE_THUMB && RIGHT_BOTTOM_ARCANE)) { \
                MAGIC_LEFT_OUTER_THUMB\
            } else if (LAST_RIGHT_MIDDLE_THUMB && RIGHT_TOP_ARCANE) {\
                ARCANE_STRING("ct", KC_T);\
                return KC_NO;\
            } else if (LAST_RIGHT_OUTER_THUMB && RIGHT_HOME_ARCANE) {\
                MAGIC_RIGHT_MIDDLE_THUMB\
            } else if (LAST_RIGHT_TOP_PINKY && RIGHT_HOME_ARCANE) {\
                MAGIC_RIGHT_HOME_RING\
            } else if (LAST_LEFT_TOP_PINKY && LEFT_HOME_ARCANE) {\
                MAGIC_LEFT_HOME_RING\
            } else if (LAST_LEFT_HOME_OUTER && LEFT_BOTTOM_ARCANE) {\
                MAGIC_LEFT_BOTTOM_PINKY\
            } else if (LAST_RIGHT_HOME_OUTER && RIGHT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_BOTTOM_PINKY\
            } else if ((LAST_LEFT_HOME_RING || LAST_LEFT_HOME_MIDDLE) && LEFT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_LEFT_BOTTOM_PINKY && LEFT_HOME_ARCANE) {\
                MAGIC_LEFT_HOME_OUTER\
            } else if (LAST_LEFT_BOTTOM_INDEX && LEFT_TOP_ARCANE) {\
                MAGIC_LEFT_HOME_RING\
            } else if (LAST_LEFT_TOP_MIDDLE && LEFT_HOME_ARCANE) {\
                MAGIC_LEFT_BOTTOM_RING\
            } else if (LAST_RIGHT_HOME_RING && RIGHT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_LEFT_TOP_PINKY && LEFT_BOTTOM_ARCANE) {\
                MAGIC_LEFT_HOME_OUTER\
            } else if (LAST_RIGHT_TOP_PINKY && RIGHT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_HOME_OUTER\
            } else if ((LAST_LEFT_BOTTOM_MIDDLE || LAST_LEFT_BOTTOM_RING || LAST_LEFT_HOME_OUTER) && LEFT_HOME_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_RING && LEFT_BOTTOM_ARCANE) {\
                MAGIC_LEFT_BOTTOM_PINKY\
            } else if (LAST_RIGHT_HOME_MIDDLE && RIGHT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_RIGHT_HOME_MIDDLE && RIGHT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_RIGHT_HOME_PINKY && RIGHT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_PINKY && LEFT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_PINKY && LEFT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_PINKY && LEFT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_PINKY && LEFT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_MIDDLE && LEFT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_LEFT_HOME_RING && LEFT_BOTTOM_ARCANE) {\
                MAGIC_RIGHT_TOP_PINKY\
            } else if (LAST_RIGHT_HOME_OUTER && RIGHT_TOP_ARCANE) {\
                MAGIC_LEFT_TOP_INDEX\
            } else if (LAST_LEFT_HOME_OUTER && LEFT_TOP_ARCANE) {\
                ARCANE_STRING("aybe", KC_E); \
                return KC_NO;\
            } else if (LAST_RIGHT_MIDDLE_THUMB && LEFT_TOP_ARCANE) {\
                ARCANE_STRING("nt", KC_T); \
                return KC_NO;\
            } else if (LAST_RIGHT_MIDDLE_THUMB && LEFT_HOME_ARCANE) {\
                ARCANE_STRING("re", KC_E);\
                return KC_NO;\
            } else if (LAST_RIGHT_MIDDLE_THUMB && LEFT_BOTTOM_ARCANE) {\
                ARCANE_STRING("ve", KC_E);\
                return KC_NO;\
            } else if (RIGHT_TOP_ARCANE && LAST_LEFT_MIDDLE_THUMB) {\
                ARCANE_STRING("or", KC_R);\
                return KC_NO;\
            } else if (RIGHT_HOME_ARCANE && LAST_LEFT_MIDDLE_THUMB) {\
                ARCANE_STRING("er", KC_R); \
                return KC_NO;\
            } else if (LAST_RIGHT_TOP_MIDDLE && RIGHT_HOME_ARCANE) {\
                MAGIC_RIGHT_HOME_MIDDLE} \
// clang-format on

// Notably, middle arcane is considered the same row as thumb keys
#define SAME_ROW_LEFT_HAND (last_key.row == arcane_key.row) || (((LAST_LEFT_INNER_THUMB) || (LAST_LEFT_MIDDLE_THUMB)) && LEFT_HOME_ARCANE)
#define SAME_ROW_RIGHT_HAND (last_key.row == arcane_key.row) || (RIGHT_HOME_ARCANE && LAST_RIGHT_MIDDLE_THUMB)
#define SAME_ROW_SAME_HAND (arcane_key.row < 3 ? SAME_ROW_LEFT_HAND : SAME_ROW_RIGHT_HAND)
// excludes opposite an prior last key on the same row as the arcane key for other magic
#define OTHER_ROW_LEFT_HAND last_key.row <= 4 && abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row
#define OTHER_ROW_RIGHT_HAND last_key.row > 3 && abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row
#define OTHER_ROW_OTHER_HAND (arcane_key.row < 3 ? OTHER_ROW_RIGHT_HAND : OTHER_ROW_LEFT_HAND)
#define OTHER_ROW abs(last_key.row - arcane_key.row) != 4 && last_key.row != arcane_key.row

uint16_t process_arcane_columns(keypos_t arcane_key, uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    uint8_t  rowOffset = arcane_key.row < 3 ? 4 : -4;
    keypos_t magic;

    if (timer_elapsed(last_keydown) < REPEAT_TERM) {
        // same row same hand repeats
        if (SAME_ROW_SAME_HAND) {
            if (last_keycode == KC_DOT) ARCANE_STRING(".", KC_DOT);
            return arcane_tap(last_keycode);
        } else {
            if (LAST_RIGHT_HOME_MIDDLE && LEFT_TOP_ARCANE) {
                ARCANE_STRING("lways", KC_E); // a
                return KC_NO;
            } else if (LAST_RIGHT_HOME_MIDDLE && LEFT_HOME_ARCANE) {
                ARCANE_STRING("nd", KC_D); // a
                return KC_NO;
            } else if (LAST_RIGHT_HOME_MIDDLE && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("te", KC_D); // a
                return KC_NO;
            } else if (LAST_LEFT_TOP_INDEX && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("ut", KC_T); // b
                return KC_NO;
            } else if (LAST_LEFT_TOP_INDEX && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("oard", KC_D); // b
                return KC_NO;
            } else if (LAST_LEFT_TOP_INDEX && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("le", KC_E); // b
                return KC_NO;
            } else if (LAST_LEFT_HOME_PINKY && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("y", KC_M); // c
                return KC_NO;
            } else if (LAST_LEFT_HOME_PINKY && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("am", KC_N); // c
                return KC_NO;
            } else if (LAST_LEFT_HOME_PINKY && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("ky", KC_M); // c
                return KC_NO;
            } else if (LAST_LEFT_TOP_MIDDLE && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("ay", KC_Y); // d
                return KC_NO;
            } else if (LAST_LEFT_TOP_MIDDLE && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ed", KC_R); // d
                return KC_NO;
            } else if (LAST_LEFT_TOP_MIDDLE && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("er", KC_N); // d
                return KC_NO;
            } else if (LAST_LEFT_TOP_RING && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("or", KC_R); // f
                return KC_NO;
            } else if (LAST_LEFT_TOP_RING && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ul", KC_L); // f
                return KC_NO;
            } else if (LAST_LEFT_TOP_RING && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("ro", KC_O); // f
                return KC_NO;
            } else if (LAST_RIGHT_HOME_OUTER && LEFT_TOP_ARCANE) {
                ARCANE_STRING("li", KC_R); // g
                return KC_NO;
            } else if (LAST_RIGHT_HOME_OUTER && LEFT_HOME_ARCANE) {
                ARCANE_STRING("ht", KC_O); // g
            } else if (LAST_RIGHT_HOME_OUTER && LEFT_BOTTOM_ARCANE) {
                MAGIC_RIGHT_HOME_PINKY // g -> h
            } else if (LAST_RIGHT_HOME_PINKY && LEFT_TOP_ARCANE) {
                ARCANE_STRING("ol", KC_A); // h
                return KC_NO;
            } else if (LAST_RIGHT_HOME_PINKY && LEFT_HOME_ARCANE) {
                ARCANE_STRING("av", KC_E); // h
                return KC_NO;
            } else if (LAST_RIGHT_HOME_PINKY && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("ighlight", KC_R); // h
                return KC_NO;
            } else if (LAST_RIGHT_HOME_RING && LEFT_TOP_ARCANE) {
                ARCANE_STRING("on", KC_N); // i
                return KC_NO;
            } else if (LAST_RIGHT_HOME_RING && LEFT_HOME_ARCANE) {
                ARCANE_STRING("ng", KC_G); // i
                return KC_NO;
            } else if (LAST_RIGHT_HOME_RING && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("ve", KC_N); // i
                return KC_NO;
            } else if (LAST_LEFT_TOP_OUTER && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("oy", KC_Y); // j
                return KC_NO;
            } else if (LAST_LEFT_TOP_OUTER && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ust", KC_T); // j
                return KC_NO;
            } else if (LAST_LEFT_TOP_OUTER && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("ect", KC_T); // j
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_MIDDLE && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("ful", KC_O); // k
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_MIDDLE && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ey", KC_Y); // k
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_MIDDLE && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("le", KC_N); // k
                return KC_NO;
            } else if (LAST_RIGHT_TOP_PINKY && LEFT_TOP_ARCANE) {
                ARCANE_STRING("oy", KC_N); // l
                return KC_NO;
            } else if (LAST_RIGHT_TOP_PINKY && LEFT_HOME_ARCANE) {
                ARCANE_STRING("ine", KC_A); // l
                return KC_NO;
            } else if (LAST_RIGHT_TOP_PINKY && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("ike", KC_E); // l
                return KC_NO;
            } else if (LAST_LEFT_HOME_OUTER && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("fy", KC_N); // m
                return KC_NO;
            } else if (LAST_LEFT_HOME_OUTER && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ys", KC_N); // m
                return KC_NO;
            } else if (LAST_LEFT_HOME_OUTER && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("yth", KC_N); // m
                return KC_NO;
            } else if (LAST_LEFT_HOME_INDEX && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("ot", KC_E); // n
                return KC_NO;
            } else if (LAST_LEFT_HOME_INDEX && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("ce", KC_E); // n
                return KC_NO;
            } else if (LAST_LEFT_HOME_INDEX && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("gle", KC_I); // n
                return KC_NO;
            } else if (LAST_RIGHT_TOP_MIDDLE && LEFT_TOP_ARCANE) {
                ARCANE_STRING("me", KC_E); // o
                return KC_NO;
            } else if (LAST_RIGHT_TOP_MIDDLE && LEFT_HOME_ARCANE) {
                ARCANE_STRING("un", KC_S); // o
                return KC_NO;
            } else if (LAST_RIGHT_TOP_MIDDLE && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("ne", KC_E); // o
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_PINKY && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("y", KC_O); // p
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_PINKY && RIGHT_HOME_ARCANE) {
                MAGIC_LEFT_HOME_PINKY
            } else if (LAST_LEFT_BOTTOM_PINKY && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("er", KC_R); // p
                return KC_NO;
            } else if (LAST_RIGHT_TOP_OUTER && LEFT_TOP_ARCANE) {
                MAGIC_RIGHT_MIDDLE_THUMB // qu -> e
            } else if (LAST_RIGHT_TOP_OUTER && LEFT_HOME_ARCANE) {
                MAGIC_RIGHT_HOME_RING // qu -> i
            } else if (LAST_RIGHT_TOP_OUTER && LEFT_BOTTOM_ARCANE) {
                MAGIC_RIGHT_HOME_MIDDLE // qu -> a
            } else if (LAST_LEFT_HOME_RING && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("yn", KC_I); // s
                return KC_NO;
            } else if (LAST_LEFT_HOME_RING && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("m", KC_A); // s
                return KC_NO;
            } else if (LAST_LEFT_HOME_RING && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("ym", KC_R); // s
                return KC_NO;
            } else if (LAST_LEFT_HOME_MIDDLE && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("yp", KC_D); // t
                return KC_NO;
            } else if (LAST_LEFT_HOME_MIDDLE && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("he", KC_E); // t
                return KC_NO;
            } else if (LAST_LEFT_HOME_MIDDLE && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("hat", KC_R); // t
                return KC_NO;
            } else if (LAST_RIGHT_HOME_INDEX && LEFT_TOP_ARCANE) {
                ARCANE_STRING("nd", KC_T); // u
                return KC_NO;
            } else if (LAST_RIGHT_HOME_INDEX && LEFT_HOME_ARCANE) {
                ARCANE_STRING("ld", KC_D); // u
                return KC_NO;
            } else if (LAST_RIGHT_HOME_INDEX && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("gh", KC_E); // u
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_RING && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("es", KC_S); // v
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_RING && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("en", KC_N); // v
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_RING && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("er", KC_R); // v
                return KC_NO;
            } else if (LAST_RIGHT_TOP_INDEX && LEFT_TOP_ARCANE) {
                ARCANE_STRING("ay", KC_I); // w
                return KC_NO;
            } else if (LAST_RIGHT_TOP_INDEX && LEFT_HOME_ARCANE) {
                ARCANE_STRING("ith", KC_R); // w
                return KC_NO;
            } else if (LAST_RIGHT_TOP_INDEX && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("as", KC_S); // w
                return KC_NO;
            } else if (LAST_RIGHT_BOTTOM_PINKY && LEFT_TOP_ARCANE) {
                ARCANE_STRING("ol", KC_I); // wh
                return KC_NO;
            } else if (LAST_RIGHT_BOTTOM_PINKY && LEFT_HOME_ARCANE) {
                ARCANE_STRING("il", KC_R); // wh
                return KC_NO;
            } else if (LAST_RIGHT_BOTTOM_PINKY && LEFT_BOTTOM_ARCANE) {
                ARCANE_STRING("elm", KC_S); // wh
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_INDEX && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("pe", KC_E); // x
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_INDEX && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("pl", KC_L); // x
                return KC_NO;
            } else if (LAST_LEFT_BOTTOM_INDEX && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("tr", KC_R); // x
                return KC_NO;
            } else if (LAST_LEFT_TOP_PINKY && RIGHT_TOP_ARCANE) {
                ARCANE_STRING("ou", KC_U); // y
                return KC_NO;
            } else if (LAST_LEFT_TOP_PINKY && RIGHT_HOME_ARCANE) {
                ARCANE_STRING("m", KC_E); // y
                return KC_NO;
            } else if (LAST_LEFT_TOP_PINKY && RIGHT_BOTTOM_ARCANE) {
                ARCANE_STRING("th", KC_H); // y
                return KC_NO;
            } else if (RIGHT_TOP_ARCANE && LAST_LEFT_INNER_THUMB) {
                ARCANE_STRING("ar", KC_R); // z
                return KC_NO;
            } else if (RIGHT_HOME_ARCANE && LAST_LEFT_INNER_THUMB) {
                ARCANE_STRING("ero", KC_T); // z
                return KC_NO;
            } else
                DUAL_CASES
        }

        uint16_t keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keymap_key_to_keycode(layer_switch_get_layer(magic), magic)));
        // uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(magic), magic);

        return arcane_tap(keycode);
    }
    if (timer_elapsed(last_keydown) > REPEAT_TERM && timer_elapsed(last_keydown) < MAGIC_TERM) {
        if (OTHER_ROW) {
            DUAL_CASES

            // anti sfb
            else if (!(LAST_LEFT_INNER_THUMB) && !(LAST_LEFT_MIDDLE_THUMB) && !(LAST_LEFT_OUTER_THUMB) && !(LAST_RIGHT_MIDDLE_THUMB) && !(LAST_RIGHT_OUTER_THUMB)) {
                // TODO figure out what to do about same hand different row magic that isn't defined above. below was too destructive to above exceptions to b added to OTHER_ROW
                //  && !(arcane_key.row < 3 && last_key.col < 5 && last_key.row < 3) && !(arcane_key.row > 3 && last_key.col < 5 && last_key.row > 3
                magic.col = last_key.col;
                magic.row = arcane_key.row + rowOffset;
            }
        }
        uint16_t keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keymap_key_to_keycode(layer_switch_get_layer(magic), magic)));
        // uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(magic), magic);

        return arcane_tap(keycode);
    }

    // TODO consider space magic term with extra wide window?
    // tap_code16(default_keycode);
    return default_keycode;
}

uint16_t process_top_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 0}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
uint16_t process_home_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 1}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
uint16_t process_bottom_left_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 2}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
uint16_t process_top_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 4}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
uint16_t process_home_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 5}, last_keycode, last_key, last_keydown, mods, default_keycode);
}
uint16_t process_bottom_right_arcane(uint16_t last_keycode, keypos_t last_key, uint16_t last_keydown, uint8_t mods, uint16_t default_keycode) {
    return process_arcane_columns((keypos_t){5, 6}, last_keycode, last_key, last_keydown, mods, default_keycode);
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
