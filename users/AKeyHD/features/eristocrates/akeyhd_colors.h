#pragma once
#include "color.h"
#include "quantum.h"

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
extern rgb_color_scheme_t ed1c24_f1d302_235789_fdfffc_020100_rcs;
