// HEAVILY based on https://github.com/drashna/qmk_userspace/blob/6a794b50a586e67bd48822e175d97e3e46b7e8bd/users/drashna/rgb/rgb_matrix_stuff.c#L1

#pragma once
#include "akeyhd_colors.h"
#include "quantum.h"
#include "../andrewjrae/qmk-vim/vim.h"
#include "../andrewjrae/qmk-vim/modes.h"
#include "utilities.h"

void rgb_matrix_layer_helper(bool vim_emulation, rgb_color_scheme_t color_scheme, vim_mode_t vim_mode_index, uint8_t layer, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max);
/*
 * ╭────────────────────────╮                 ╭────────────────────────╮
 *    0   5   6  11  12  15                     36  33  32  27  26  21
 * ├────────────────────────┤                 ├────────────────────────┤
 *    1   4   7  10  13  16                     37  34  31  28  25  22
 * ├────────────────────────┤                 ├────────────────────────┤
 *    2   3   8   9  14  17                     38  35  30  29  24  23
 * ╰────────────────────────╯                 ╰────────────────────────╯
 *                       18  19  20     39  40  XX
 *                     ╰────────────╯ ╰────────────╯
 */
#define TOP_ROW_INDEXES i == 0 || i == 5 || i == 6 || i == 11 || i == 12 || i == 15 || i == 36 || i == 33 || i == 32 || i == 27 || i == 26 || i == 21

#define HOME_ROW_INDEXES i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 37 || i == 34 || i == 31 || i == 28 || i == 25 || i == 22

#define BOTTOM_ROW_INDEXES i == 2 || i == 3 || i == 8 || i == 9 || i == 14 || i == 17 || i == 38 || i == 35 || i == 30 || i == 29 || i == 24 || i == 23

#define THUMB_ROW_INDEXES i == 18 || i == 19 || i == 20 || i == 39 || i == 40

#define ARCANE_COLUMNS i == 15 || i == 16 || i == 17 || i == 36 || i == 37 || i == 38

#define SLICE i == 35 || i == 30 || i == 29 || i == 24

#define CENTER_THUMBS i == 19 || i == 40

#define ENTER_COMBO i == 8 || i == 9

#define MAIN_COLOR RGB_MATRIX_INDICATOR_SET_COLOR(i, main_rgb.r, main_rgb.g, main_rgb.b);

#define ACCENT_COLOR1 RGB_MATRIX_INDICATOR_SET_COLOR(i, accent1_rgb.r, accent1_rgb.g, accent1_rgb.b);

#define ACCENT_COLOR2 RGB_MATRIX_INDICATOR_SET_COLOR(i, accent2_rgb.r, accent2_rgb.g, accent2_rgb.b);

#define HIGHLIGHT_COLOR1 RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight1_rgb.r, highlight1_rgb.g, highlight1_rgb.b);

#define HIGHLIGHT_COLOR2 RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight2_rgb.r, highlight2_rgb.g, highlight2_rgb.b);

#define SET_VIM_COLORS    \
    if (vim_emulation) {  \
        ACCENT_COLOR1     \
    }                     \
    if (!vim_emulation) { \
        ACCENT_COLOR2     \
    }

// TODO strangely, despite being listed as 40 and working when i == 40, 40 always fails keymap_key_to_keycode. gotta figure that out
// TODO mod indicators, or at least caps
// TODO other vim modes
// TODO fix 23 vim indicator on pointer breathing. maybe pass mode
// TODO KEEP IN SYNC WITH LAYERS
#define SET_RGB_MATRIX_COLOR_SCHEME(vim_emulation, vim_mode_index, layer, col, row, i, main_rgb, accent1_rgb, accent2_rgb, highlight1_rgb, highlight2_rgb) \
    do {                                                                                                                                                   \
        /* establoish the maincolor as a "background" */                                                                                                   \
        MAIN_COLOR                                                                                                                                         \
        /* only use these indicators on base alphas */                                                                                                     \
        if (get_highest_layer(default_layer_state) == layer) {                                                                                             \
            if (vim_mode_index == INSERT_MODE) {                                                                                                           \
                if (CENTER_THUMBS || ARCANE_COLUMNS || ENTER_COMBO) {                                                                                      \
                    SET_VIM_COLORS                                                                                                                         \
                }                                                                                                                                          \
            }                                                                                                                                              \
            /* on all other layers, color keycoded keys with vim colors*/                                                                                  \
        } else if (i == 40 || keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {                                                              \
            SET_VIM_COLORS                                                                                                                                 \
        }                                                                                                                                                  \
        /* in _VIMFIGHTER layer highlight inner toggle thumb key */                                                                                        \
        if (IS_LAYER_ON(3)) {                                                                                                                              \
            if (i == 39) {                                                                                                                                 \
                if (vim_emulation) {                                                                                                                       \
                    HIGHLIGHT_COLOR1                                                                                                                       \
                } else {                                                                                                                                   \
                    HIGHLIGHT_COLOR2                                                                                                                       \
                }                                                                                                                                          \
            }                                                                                                                                              \
        }                                                                                                                                                  \
    } while (0)
