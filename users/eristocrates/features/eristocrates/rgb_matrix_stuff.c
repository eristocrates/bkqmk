#include "rgb_matrix_stuff.h"
#include <ctype.h>
#include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;

// const led_point_t   k_rgb_matrix_center = {112, 32};

// static uint32_t hypno_timer;
RGB rgb_matrix_hsv_to_rgb(HSV hsv);

static HSV BAND_PINWHEEL_VAL_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.v = scale8(hsv.v - time - atan2_8(dy, dx) * 3, hsv.v);
    return hsv;
}

//----------------------------------------------------------
// RGB Matrix naming
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
#undef RGB_MATRIX_EFFECT
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
#undef RGB_MATRIX_EFFECT
        default:
            return "UNKNOWN";
    }
}

// Array of LED index to key matrix rows and columns
const int led_to_key_matrix[42][2] = {
    {0, 0}, // LED 0
    {1, 0}, // LED 1
    {2, 0}, // LED 2
    {2, 1}, // LED 3
    {1, 1}, // LED 4
    {0, 1}, // LED 5
    {0, 2}, // LED 6
    {1, 2}, // LED 7
    {2, 2}, // LED 8
    {2, 3}, // LED 9
    {1, 3}, // LED 10
    {0, 3}, // LED 11
    {0, 4}, // LED 12
    {1, 4}, // LED 13
    {2, 4}, // LED 14
    {0, 5}, // LED 15
    {1, 5}, // LED 16
    {2, 5}, // LED 17
    {3, 3}, // LED 18
    {3, 4}, // LED 19
    {3, 1}, // LED 20
    {4, 0}, // LED 21
    {5, 0}, // LED 22
    {6, 0}, // LED 23
    {6, 1}, // LED 24
    {5, 1}, // LED 25
    {4, 1}, // LED 26
    {4, 2}, // LED 27
    {5, 2}, // LED 28
    {6, 2}, // LED 29
    {6, 3}, // LED 30
    {5, 3}, // LED 31
    {4, 3}, // LED 32
    {4, 4}, // LED 33
    {5, 4}, // LED 34
    {6, 4}, // LED 35
    {4, 5}, // LED 36
    {5, 5}, // LED 37
    {6, 5}, // LED 38
    {7, 3}, // LED 39
    {7, 4}, // LED 40
    {7, 1}, // LED 41
};
void rgb_matrix_layer_helper(bool vim_emulation, rgb_color_scheme_t color_scheme, vim_mode_t vim_mode_index, uint8_t layer, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
    // static effect_params_t rgb_effect_params_user = {0, LED_FLAG_ALL, false};
    HSV main_hsv       = color_scheme.main_hsv;
    HSV accent1_hsv    = color_scheme.accent1_hsv;
    HSV accent2_hsv    = color_scheme.accent2_hsv;
    HSV highlight1_hsv = color_scheme.highlight1_hsv;
    HSV highlight2_hsv = color_scheme.highlight2_hsv;

    if (main_hsv.v > rgb_matrix_get_val()) {
        main_hsv.v = rgb_matrix_get_val();
    }
    if (accent1_hsv.v > rgb_matrix_get_val()) {
        accent1_hsv.v = rgb_matrix_get_val();
    }
    if (accent2_hsv.v > rgb_matrix_get_val()) {
        accent2_hsv.v = rgb_matrix_get_val();
    }
    if (highlight1_hsv.v > rgb_matrix_get_val()) {
        highlight1_hsv.v = rgb_matrix_get_val();
    }
    if (highlight2_hsv.v > rgb_matrix_get_val()) {
        highlight2_hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        case RGB_MATRIX_EFFECT_BREATHING: // breathing
                                          /*
                                          {
                              
    HSV      hsv  = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
                              
                                          }
                                          */
            {
                uint16_t time      = scale16by8(g_rgb_timer, speed / 8);
                main_hsv.v         = scale8(abs8(sin8(time) - 128) * 2, main_hsv.v);
                accent1_hsv.v      = scale8(abs8(sin8(time) - 128) * 2, accent1_hsv.v);
                accent2_hsv.v      = scale8(abs8(sin8(time) - 128) * 2, accent2_hsv.v);
                highlight1_hsv.v   = scale8(abs8(sin8(time) - 128) * 2, highlight1_hsv.v);
                highlight2_hsv.v   = scale8(abs8(sin8(time) - 128) * 2, highlight2_hsv.v);
                RGB main_rgb       = rgb_matrix_hsv_to_rgb(main_hsv);
                RGB accent1_rgb    = rgb_matrix_hsv_to_rgb(accent1_hsv);
                RGB accent2_rgb    = rgb_matrix_hsv_to_rgb(accent2_hsv);
                RGB highlight1_rgb = rgb_matrix_hsv_to_rgb(highlight1_hsv);
                RGB highlight2_rgb = rgb_matrix_hsv_to_rgb(highlight2_hsv);
                for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                    uint8_t row = led_to_key_matrix[i][0];
                    uint8_t col = led_to_key_matrix[i][1];
                    SET_RGB_MATRIX_COLOR_SCHEME(vim_emulation, vim_mode_index, layer, col, row, i, main_rgb, accent1_rgb, accent2_rgb, highlight1_rgb, highlight2_rgb);
                }
            }
            break;
        case RGB_MATRIX_EFFECT_BAND_PINWHEEL_VAL: {
            {
                uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 2);
                for (uint8_t i = led_min; i < led_max; i++) {
                    int16_t dx             = g_led_config.point[i].x - k_rgb_matrix_center.x;
                    int16_t dy             = g_led_config.point[i].y - k_rgb_matrix_center.y;
                    uint8_t row            = led_to_key_matrix[i][0];
                    uint8_t col            = led_to_key_matrix[i][1];
                    RGB     main_rgb       = rgb_matrix_hsv_to_rgb(BAND_PINWHEEL_VAL_math(main_hsv, dx, dy, time));
                    RGB     accent1_rgb    = rgb_matrix_hsv_to_rgb(BAND_PINWHEEL_VAL_math(accent1_hsv, dx, dy, time));
                    RGB     accent2_rgb    = rgb_matrix_hsv_to_rgb(BAND_PINWHEEL_VAL_math(accent2_hsv, dx, dy, time));
                    RGB     highlight1_rgb = rgb_matrix_hsv_to_rgb(BAND_PINWHEEL_VAL_math(highlight1_hsv, dx, dy, time));
                    RGB     highlight2_rgb = rgb_matrix_hsv_to_rgb(BAND_PINWHEEL_VAL_math(highlight2_hsv, dx, dy, time));

                    SET_RGB_MATRIX_COLOR_SCHEME(vim_emulation, vim_mode_index, layer, col, row, i, main_rgb, accent1_rgb, accent2_rgb, highlight1_rgb, highlight2_rgb);
                }
            }
            /*
            uint16_t time = scale16by8(g_rgb_timer, speed / 2);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                int16_t dx            = g_led_config.point[i].x - k_rgb_matrix_center.x;
                int16_t dy            = g_led_config.point[i].y - k_rgb_matrix_center.y;
                main_hsv.v         = scale8(main_hsv.v - time - atan2_8(dy, dx) * 3, main_hsv.v);
                accent1_hsv.v       = scale8(accent1_hsv.v - time - atan2_8(dy, dx) * 3, accent1_hsv.v);
                RGB     main_rgb   = rgb_matrix_hsv_to_rgb(main_hsv);
                RGB     accent1_rgb = rgb_matrix_hsv_to_rgb(accent1_hsv);
                uint8_t row           = led_to_key_matrix[i][0];
                uint8_t col           = led_to_key_matrix[i][1];
                if (keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, main_rgb.r, main_rgb.g, main_rgb.b);
                } else {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, accent1_rgb.r, accent1_rgb.g, accent1_rgb.b);
                }
            }
        }
            */
            break;
            /*
            default: // Solid Color
            {
                for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                    RGB     main_rgb   = rgb_matrix_hsv_to_rgb(main_hsv);
                    RGB     accent1_rgb = rgb_matrix_hsv_to_rgb(accent1_hsv);
                    uint8_t row           = led_to_key_matrix[i][0];
                    uint8_t col           = led_to_key_matrix[i][1];
                    if (keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                        RGB_MATRIX_INDICATOR_SET_COLOR(i, main_rgb.r, main_rgb.g, main_rgb.b);
                    } else {
                        RGB_MATRIX_INDICATOR_SET_COLOR(i, accent1_rgb.r, accent1_rgb.g, accent1_rgb.b);
                    }
                }
                break;
            }
            */
        }
    }
}

/*
// from drashna's rgb_matrix_layer_helper
HSV hsv = {HSV_DARK_RED};
if (hsv.v > rgb_matrix_get_main_val()) {
    hsv.v = rgb_matrix_get_main_val();
}
uint8_t speed = rgb_matrix_get_speed();

uint16_t time = scale16by8(g_rgb_timer, speed / 8);
hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
RGB rgb       = hsv_to_rgb(hsv);

if (get_highest_layer(layer_state) > 0) {
    uint8_t layer = get_highest_layer(layer_state);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                // rgb_matrix_set_color(index, RGB_CADMIUM_RED);
                RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
}
return false;
*/
