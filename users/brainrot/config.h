#pragma once

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// Tapping settings
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 2

// Charybdis-specific features.
#define CHARYBDIS_CONFIG_SYNC
#define MOUSE_EXTENDED_REPORT

// Layout macros
#ifndef __ASSEMBLER__
#    include "mods.h"
#endif
