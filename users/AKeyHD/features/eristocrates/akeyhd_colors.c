#include "akeyhd_colors.h"

// converts from quantum
HSV hsv_azure       = {132, 102, 255};
HSV hsv_black       = {0, 0, 0};
HSV hsv_blue        = {170, 255, 255};
HSV hsv_chartreuse  = {64, 255, 255};
HSV hsv_coral       = {11, 176, 255};
HSV hsv_cyan        = {128, 255, 255};
HSV hsv_gold        = {36, 255, 255};
HSV hsv_goldenrod   = {30, 218, 218};
HSV hsv_green       = {85, 255, 255};
HSV hsv_magenta     = {213, 255, 255};
HSV hsv_orange      = {21, 255, 255};
HSV hsv_pink        = {234, 128, 255};
HSV hsv_purple      = {191, 255, 255};
HSV hsv_red         = {0, 255, 255};
HSV hsv_springgreen = {106, 255, 255};
HSV hsv_teal        = {128, 255, 128};
HSV hsv_turquoise   = {123, 90, 112};
HSV hsv_white       = {0, 0, 255};
HSV hsv_yellow      = {43, 255, 255};

rgb_color_scheme_t defaults_rcs = {
    .main_hsv       = {HSV_RED},
    .accent1_hsv    = {HSV_PINK},
    .accent2_hsv    = {HSV_PURPLE},
    .highlight1_hsv = {HSV_CHARTREUSE},
    .highlight2_hsv = {HSV_CORAL},
};
// lifted from The color scheme bible : inspirational palettes for designing home interiors : Starmer, Anna
// https://archive.org/details/colorschemebible0000star
rgb_color_scheme_t classic_rcs = {
    .main_hsv       = {247, 207, 140},
    .accent1_hsv    = {0, 74, 41},
    .accent2_hsv    = {39, 59, 209},
    .highlight1_hsv = {251, 207, 171},
    .highlight2_hsv = {38, 122, 194},
};

rgb_color_scheme_t voluptuous_rcs = {
    .main_hsv       = {241, 219, 145},
    .accent1_hsv    = {237, 204, 74},
    .accent2_hsv    = {230, 168, 184},
    .highlight1_hsv = {44, 217, 143},
    .highlight2_hsv = {133, 128, 186},
};
rgb_color_scheme_t earthy_rcs = {
    .main_hsv       = {248, 214, 145},
    .accent1_hsv    = {25, 74, 196},
    .accent2_hsv    = {12, 18, 201},
    .highlight1_hsv = {7, 212, 176},
    .highlight2_hsv = {254, 153, 135},
};
rgb_color_scheme_t positive_rcs = {
    .main_hsv       = {247, 222, 173},
    .accent1_hsv    = {155, 130, 219},
    .accent2_hsv    = {154, 130, 222},
    .highlight1_hsv = {7, 222, 191},
    .highlight2_hsv = {17, 209, 199},
};
rgb_color_scheme_t jeweled_rcs = {
    .main_hsv       = {1, 186, 209},
    .accent1_hsv    = {252, 105, 212},
    .accent2_hsv    = {6, 148, 196},
    .highlight1_hsv = {137, 128, 189},
    .highlight2_hsv = {161, 97, 84},
};
rgb_color_scheme_t composed_rcs = {
    .main_hsv       = {254, 201, 130},
    .accent1_hsv    = {6, 171, 158},
    .accent2_hsv    = {18, 117, 196},
    .highlight1_hsv = {37, 82, 191},
    .highlight2_hsv = {39, 122, 199},
};
rgb_color_scheme_t afternoon_rcs = {
    .main_hsv       = {249, 153, 87},
    .accent1_hsv    = {244, 89, 189},
    .accent2_hsv    = {240, 66, 153},
    .highlight1_hsv = {247, 51, 201},
    .highlight2_hsv = {9, 122, 204},
};
