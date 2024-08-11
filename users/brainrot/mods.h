#pragma once
#include "keycodes.h"

#define PNT_T(k1) LT(LAYER_POINTER, k1)

// Adapted from https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/layout.h#L79
// Macros to add inverted-T GACS mods

// clang-format off
#define URM_L(k1) LGUI_T(k1)
#define URM_R(k1) RGUI_T(k1)
#define HRM_L(k0, k1, k2, k3) PNT_T(k0),LALT_T(k1),LCTL_T(k2),LSFT_T(k3)
#define HRM_R(k0, k1, k2, k3) RSFT_T(k0),RCTL_T(k1),RALT_T(k2),PNT_T(k3)

#define HRM(k) HR_MODTAP(k)

// just following the labels from https://github.com/Bastardkb/bastardkb-qmk/blob/f4166fca223f500c5e048617a619e01c66db96db/keyboards/bastardkb/charybdis/3x6/info.json#L41
#define HR_MODTAP( \
      l00, l01, l02, l03, l04, l05,  r00, r01, r02, r03, r04, r05, \
      l10, l11, l12, l13, l14, l15,  r10, r11, r12, r13, r14, r15, \
      l20, l21, l22, l23, l24, l25,  r20, r21, r22, r23, r24, r25, \
      l30, l31, l32, l33, l34, l35,  r30, r31, r32, r33, r34, r35 \
)\
      l00,       l01, l02, URM_L(l03), l04,  l05,       r00,       r01, r02, URM_R(r03), r04,  r05, \
      l10, HRM_L(l11, l12,       l13,  l14), l15,       r10, HRM_R(r11, r12,       r13,  r14), r15, \
      l20,       l21, l22,       l23,  l24,  l25,       r20,       r21, r22,       r23,  r24,  r25, \
      l30,       l31, l32,       l33,  l34,  l35,       r30,       r31, r32,       r33,  r34,  r35

// clang-format on
