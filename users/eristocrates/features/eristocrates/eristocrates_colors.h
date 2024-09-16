#pragma once
#include "color.h"
#include "quantum.h"

// https://htmlcolorcodes.com/colors/shades-of-red/
#define RGB_BLOOD_RED 0x88, 0x08, 0x08
#define RGB_BRICK_RED 0xAA, 0x4A, 0x44
#define RGB_BRIGHT_RED 0xEE, 0x4B, 0x2B
#define RGB_BROWN 0xA5, 0x2A, 0x2A
#define RGB_BURGUNDY 0x80, 0x00, 0x20
#define RGB_BURNT_UMBER 0x6E, 0x26, 0x0E
#define RGB_BURNT_ORANGE 0xCC, 0x55, 0x00
#define RGB_BURNT_SIENNA 0xE9, 0x74, 0x51
#define RGB_BYZANTIUM 0x70, 0x29, 0x63
#define RGB_CADMIUM_RED 0xD2, 0x2B, 0x2B
#define RGB_CARDINAL_RED 0xC4, 0x1E, 0x3A
#define RGB_CARMINE 0xD7, 0x00, 0x40
#define RGB_CERISE 0xDE, 0x31, 0x63
#define RGB_CHERRY 0xD2, 0x04, 0x2D
#define RGB_CHESTNUT 0x95, 0x45, 0x35
#define RGB_CLARET 0x81, 0x13, 0x31
#define RGB_CORAL_PINK 0xF8, 0x83, 0x79
#define RGB_CORDOVAN 0x81, 0x41, 0x41
#define RGB_CRIMSON 0xDC, 0x14, 0x3C
#define RGB_DARK_RED 0x8B, 0x00, 0x00
#define RGB_FALU_RED 0x7B, 0x18, 0x18
#define RGB_GARNET 0x9A, 0x2A, 0x2A
#define RGB_MAHOGANY 0xC0, 0x40, 0x00
#define RGB_MAROON 0x80, 0x00, 0x00
#define RGB_MARSALA 0x98, 0x68, 0x68
#define RGB_MULBERRY 0x77, 0x07, 0x37
#define RGB_NEON_RED 0xFF, 0x31, 0x31
#define RGB_OXBLOOD 0x4A, 0x04, 0x04
#define RGB_PASTEL_RED 0xFA, 0xA0, 0xA0
#define RGB_PERSIMMON 0xEC, 0x58, 0x00
#define RGB_POPPY 0xE3, 0x53, 0x35
#define RGB_PUCE 0xA9, 0x5C, 0x68
#define RGB_RASPBERRY 0xE3, 0x0B, 0x5C
#define RGB_RED 0xFF, 0x00, 0x00
#define RGB_RED_BROWN 0xA5, 0x2A, 0x2A
#define RGB_RED_OCHRE 0x91, 0x38, 0x31
#define RGB_RED_ORANGE 0xFF, 0x44, 0x33
#define RGB_RED_PURPLE 0x95, 0x35, 0x53
#define RGB_ROSE_RED 0xC2, 0x1E, 0x56
#define RGB_RUBY_RED 0xE0, 0x11, 0x5F
#define RGB_RUSSET 0x80, 0x46, 0x1B
#define RGB_SALMON 0xFA, 0x80, 0x72
#define RGB_SCARLET 0xFF, 0x24, 0x00
#define RGB_SUNSET_ORANGE 0xFA, 0x5F, 0x55
#define RGB_TERRA_COTTA 0xE3, 0x73, 0x5E
#define RGB_TUSCAN_RED 0x7C, 0x30, 0x30
#define RGB_TYRIAN_PURPLE 0x63, 0x03, 0x30
#define RGB_VENETIAN_RED 0xA4, 0x2A, 0x04
#define RGB_VERMILLION 0xE3, 0x42, 0x34
#define RGB_WINE 0x72, 0x2F, 0x37

#define HSV_BLOOD_RED 0, 240, 136
#define HSV_BRICK_RED 3, 153, 170
#define HSV_BRIGHT_RED 7, 209, 238
#define HSV_BROWN 0, 190, 165
#define HSV_BURGUNDY 244, 255, 128
#define HSV_BURNT_UMBER 11, 223, 110
#define HSV_BURNT_ORANGE 18, 255, 204
#define HSV_BURNT_SIENNA 10, 166, 233
#define HSV_BYZANTIUM 220, 162, 112
#define HSV_CADMIUM_RED 0, 203, 210
#define HSV_CARDINAL_RED 248, 216, 196
#define HSV_CARMINE 242, 255, 215
#define HSV_CERISE 243, 199, 222
#define HSV_CHERRY 247, 250, 210
#define HSV_CHESTNUT 7, 164, 149
#define HSV_CLARET 244, 217, 129
#define HSV_CORAL_PINK 4, 131, 248
#define HSV_CORDOVAN 0, 127, 129
#define HSV_CRIMSON 247, 232, 220
#define HSV_DARK_RED 0, 255, 139
#define HSV_FALU_RED 0, 205, 123
#define HSV_GARNET 0, 185, 154
#define HSV_MAHOGANY 14, 255, 192
#define HSV_MAROON 0, 255, 128
#define HSV_MARSALA 0, 81, 152
#define HSV_MULBERRY 237, 240, 119
#define HSV_NEON_RED 0, 206, 255
#define HSV_OXBLOOD 0, 241, 74
#define HSV_PASTEL_RED 0, 92, 250
#define HSV_PERSIMMON 16, 255, 236
#define HSV_POPPY 7, 195, 227
#define HSV_PUCE 249, 116, 169
#define HSV_RASPBERRY 239, 243, 227
#define HSV_RED 0, 255, 255
#define HSV_RED_BROWN 0, 190, 165
#define HSV_RED_OCHRE 3, 169, 145
#define HSV_RED_ORANGE 4, 204, 255
#define HSV_RED_PURPLE 242, 164, 149
#define HSV_ROSE_RED 241, 216, 194
#define HSV_RUBY_RED 239, 236, 224
#define HSV_RUSSET 18, 201, 128
#define HSV_SALMON 4, 139, 250
#define HSV_SCARLET 6, 255, 255
#define HSV_SUNSET_ORANGE 3, 168, 250
#define HSV_TERRA_COTTA 6, 149, 227
#define HSV_TUSCAN_RED 0, 156, 124
#define HSV_TYRIAN_PURPLE 235, 247, 99
#define HSV_VENETIAN_RED 10, 249, 164
#define HSV_VERMILLION 4, 197, 227
#define HSV_WINE 250, 150, 114

#define PRIMARY_HSV HSV_RED
#define SECONDARY_HSV HSV_BLOOD_RED
#define TERTIARY_HSV HSV_YELLOW

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
