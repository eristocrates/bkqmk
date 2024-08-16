#pragma once
#include "charybdis.h"

enum layers {
    LAYER_BRAINROT = 0,
    LAYER_LSHIFTGR,
    LAYER_VIMNUM,
    LAYER_RSHIFTGR,
    LAYER_QWERTY,
    LAYER_GAME,
    LAYER_LAYER,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

// layers & their behavior
// TODO consider decoupling this, maybe a modular wrapper macro to assign behavior
#define BASE TO(LAYER_BRAINROT)
#define DFGAME DF(LAYER_GAME)
#define DFBASE DF(LAYER_BRAINROT)
#define LAYER TT(LAYER_LAYER)
#define LOWER TG(LAYER_LOWER)
#define RAISE TG(LAYER_RAISE)
#define VIMNUM MO(LAYER_VIMNUM)

// default LTs
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// shortcuts
#define S_SNAP S(G(KC_S))

// custom LTs
#define PNT_T(k0) LT(LAYER_POINTER, k0)
#define LSHGR_T(k0) LT(LAYER_LSHIFTGR, k0)
#define RSHGR_T(k0) LT(LAYER_RSHIFTGR, k0)

// Adapted from https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/layout.h#L79
// Macros to add mods

#define URM_L(k0) LGUI_T(k0)
#define URM_R(k0) RGUI_T(k0)
#define HRM_L(k0, k1, k2, k3) PNT_T(k0), LALT_T(k1), LCTL_T(k2), LSFT_T(k3)
#define HRM_R(k0, k1, k2, k3) PNT_T(k0), RALT_T(k1), RCTL_T(k2), RSFT_T(k3)
#define BRM(k0, k1) MEH_T(k0), HYPR_T(k1)
#define TRM_L(k0) LSHGR_T(k0)
#define TRM_R(k0) RSHGR_T(k0)
// TODO consider adding meh and hyper to bottom row

// TODO remember if i add a new mod to update combo.def

#define HRM(k) HR_MODTAP(k)

// clang-format off
// just following the labels from https://github.com/Bastardkb/bastardkb-qmk/blob/f4166fca223f500c5e048617a619e01c66db96db/keyboards/bastardkb/charybdis/3x6/info.json#L41
/*
 L = Left split
 R = Right split

 T = Top row
 M = Middle row
 B = Bottom row

 Out = Outer column
 Pin = Pinky column
 Rin = Ring column
 Ind = Index column
 Inn = Inner column

 LThmb = Left Thumb button
 MThmb = Middle Thumb  button
 RThmb = Right Thumb button

   ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
     L_T_Out, L_T_Pin, L_T_Rin, L_T_Mid, L_T_Ind, L_T_Inn,    R_T_Inn, R_T_Ind, R_T_Mid, R_T_Rin, R_T_Pin, R_T_Out,
   ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     L_H_Out, L_H_Pin, L_H_Rin, L_H_Mid, L_H_Ind, L_H_Inn,    R_H_Inn, R_H_Ind, R_H_Mid, R_H_Rin, R_H_Pin, R_H_Out,
   ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     L_B_Out, L_B_Pin, L_B_Rin, L_B_Mid, L_B_Ind, L_B_Inn,    R_M_Inn, R_M_Ind, R_M_Mid, R_M_Rin, R_M_Pin, R_M_Out,
   ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                L_LThmb, L_MThmb, L_RThmb,    R_LThmb, R_MThmb
                              ╰───────────────────────────╯ ╰──────────────────╯


*/

#define HR_MODTAP( \
L_T_Out, L_T_Pin, L_T_Rin, L_T_Mid, L_T_Ind, L_T_Inn,       L_H_Out, L_H_Pin, L_H_Rin, L_H_Mid, L_H_Ind, L_H_Inn, \
L_B_Out, L_B_Pin, L_B_Rin, L_B_Mid, L_B_Ind, L_B_Inn,       k5F, L_RThmb, k5D, L_LThmb, L_MThmb, k5A, \
R_T_Out, R_T_Pin, R_T_Rin, R_T_Mid, R_T_Ind, R_T_Inn,       R_H_Out, R_H_Pin, R_H_Rin, R_H_Mid, R_H_Ind, R_H_Inn, \
R_B_Out, R_B_Pin, R_B_Rin, R_B_Mid, R_B_Ind, R_B_Inn,       K7F, R_LThmb, K7D, R_MThmb, K7B, K7A \
) \
L_T_Out, L_T_Pin, L_T_Rin, URM_L(L_T_Mid), L_T_Ind, L_T_Inn,       L_H_Out, HRM_L(L_H_Pin, L_H_Rin, L_H_Mid, L_H_Ind), L_H_Inn, \
L_B_Out, L_B_Pin, L_B_Rin,   BRM(L_B_Mid, L_B_Ind), L_B_Inn,       k5F,            L_RThmb, k5D,    L_LThmb, TRM_L(L_MThmb), k5A, \
R_T_Out, R_T_Pin, R_T_Rin, URM_R(R_T_Mid), R_T_Ind, R_T_Inn,       R_H_Out, HRM_R(R_H_Pin, R_H_Rin, R_H_Mid, R_H_Ind), R_H_Inn, \
R_B_Out, R_B_Pin, R_B_Rin,   BRM(R_B_Mid, R_B_Ind), R_B_Inn,       K7F,            R_LThmb, K7D,  TRM_R(R_MThmb), K7B,     K7A

/*/
from I:\coding\bastardkb-qmk\.build\obj_bastardkb_charybdis_3x6_brainrot\src\default_keyboard.h
#define LAYOUT(k0A, k0B, k0C, k0D, k0E, k0F, k4F, k4E, k4D, k4C, k4B, k4A, k1A, k1B, k1C, k1D, k1E, k1F, k5F, k5E, k5D, k5C, k5B, k5A, k2A, k2B, k2C, k2D, k2E, k2F, k6F, k6E, k6D, k6C, k6B, k6A, k3D, k3E, k3B, k7B, k7D) { \
	 {k0A, k0B, k0C, k0D, k0E, k0F}, \
	 {k1A, k1B, k1C, k1D, k1E, k1F}, \
	 {k2A, k2B, k2C, k2D, k2E, k2F}, \
	 {KC_NO, k3B, KC_NO, k3D, k3E, KC_NO}, \
	 {k4A, k4B, k4C, k4D, k4E, k4F}, \
	 {k5A, k5B, k5C, k5D, k5E, k5F}, \
	 {k6A, k6B, k6C, k6D, k6E, k6F}, \
	 {KC_NO, k7B, KC_NO, k7D, KC_NO, KC_NO} \
}
*/

// clang-format on
