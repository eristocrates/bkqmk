// HEAVILY based on https://github.com/drashna/qmk_userspace/blob/6a794b50a586e67bd48822e175d97e3e46b7e8bd/users/drashna/rgb/rgb_matrix_stuff.c#L1

#pragma once
#include "akeyhd_colors.h"
#include "quantum.h"
#include "../andrewjrae/qmk-vim/vim.h"
#include "../andrewjrae/qmk-vim/modes.h"
#include "utilities.h"

void rgb_matrix_layer_helper(rgb_color_scheme_t color_scheme, vim_mode_t vim_mode_index, uint8_t layer, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max);
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
// TODO strangely, despite being listed as 40 and working when i == 40, 40 always fails keymap_key_to_keycode. gotta figure that out
// TODO mod indicators, or at least caps
// TODO other vim modes
// TODO fix 23 vim indicator on pointer breathing. maybe pass mode
// TODO KEEP IN SYNC WITH LAYERS
#define SET_RGB_MATRIX_COLOR_SCHEME(vim_mode_index, layer, col, row, i, main_rgb, accent1_rgb, accent2_rgb, highlight1_rgb, highlight2_rgb) \
    do {                                                                                                                                    \
        if (i == 40 || keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {                                                      \
            RGB_MATRIX_INDICATOR_SET_COLOR(i, main_rgb.r, main_rgb.g, main_rgb.b);                                                          \
        } else {                                                                                                                            \
            RGB_MATRIX_INDICATOR_SET_COLOR(i, accent2_rgb.r, accent2_rgb.g, accent2_rgb.b);                                                 \
        }                                                                                                                                   \
                                                                                                                                            \
        if (i == 15 || i == 16 || i == 17 || i == 36 || i == 37 || i == 38) {                                                               \
            RGB_MATRIX_INDICATOR_SET_COLOR(i, accent1_rgb.r, accent1_rgb.g, accent1_rgb.b);                                                 \
        }                                                                                                                                   \
                                                                                                                                            \
        if (i == 23) {                                                                                                                      \
            /*targeting pointer layer*/                                                                                                     \
            if (IS_LAYER_ON(9)) {                                                                                                           \
                RGB_MATRIX_INDICATOR_SET_COLOR(i, accent2_rgb.r, accent2_rgb.g, accent2_rgb.b);                                             \
            } else if (vim_emulation) {                                                                                                     \
                RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight2_rgb.r, highlight2_rgb.g, highlight2_rgb.b);                                    \
            }                                                                                                                               \
        }                                                                                                                                   \
                                                                                                                                            \
        if (vim_mode_index == INSERT_MODE && (i == 8 || i == 9)) {                                                                          \
            RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight1_rgb.r, highlight1_rgb.g, highlight1_rgb.b);                                        \
        } else if (vim_mode_index == NORMAL_MODE) {                                                                                         \
            /*targeting vimmotion layer*/                                                                                                   \
            if ((i == 35 || i == 30 || i == 29 || i == 24) || (IS_LAYER_ON(3) && (i == 7 || i == 10 || i == 13 || i == 19 || i == 40))) {   \
                RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight1_rgb.r, highlight1_rgb.g, highlight1_rgb.b);                                    \
            }                                                                                                                               \
            if (i == 39) {                                                                                                                  \
                if (IS_LAYER_ON(3)) {                                                                                                       \
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, highlight2_rgb.r, highlight2_rgb.g, highlight2_rgb.b);                                \
                } else {                                                                                                                    \
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, main_rgb.r, main_rgb.g, main_rgb.b);                                                  \
                }                                                                                                                           \
            }                                                                                                                               \
        }                                                                                                                                   \
    } while (0)
