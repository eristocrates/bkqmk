#pragma once
#include "color.h"
#include "quantum.h"

// converts from quantum
extern HSV hsv_azure;
extern HSV hsv_black;
extern HSV hsv_blue;
extern HSV hsv_chartreuse;
extern HSV hsv_coral;
extern HSV hsv_cyan;
extern HSV hsv_gold;
extern HSV hsv_goldenrod;
extern HSV hsv_green;
extern HSV hsv_magenta;
extern HSV hsv_orange;
extern HSV hsv_pink;
extern HSV hsv_purple;
extern HSV hsv_red;
extern HSV hsv_springgreen;
extern HSV hsv_teal;
extern HSV hsv_turquoise;
extern HSV hsv_white;
extern HSV hsv_yellow;

typedef struct PACKED {
    HSV main_hsv;
    HSV accent1_hsv;
    HSV accent2_hsv;
    HSV highlight1_hsv;
    HSV highlight2_hsv;
} rgb_color_scheme_t;

extern rgb_color_scheme_t defaults_rcs;
extern rgb_color_scheme_t classic_rcs;
extern rgb_color_scheme_t voluptuous_rcs;
extern rgb_color_scheme_t earthy_rcs;
extern rgb_color_scheme_t positive_rcs;
extern rgb_color_scheme_t jeweled_rcs;
extern rgb_color_scheme_t composed_rcs;
extern rgb_color_scheme_t afternoon_rcs;
