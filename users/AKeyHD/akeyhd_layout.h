#pragma once
#include "charybdis.h"

// Adapted from https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/layout.h#L79
// Macros to add mods

#define URM_L(k0) LGUI_T(k0)
#define URM_R(k0) RGUI_T(k0)
#define HRM_L(k1, k2, k3) LALT_T(k1), LCTL_T(k2), LSFT_T(k3)
#define HRM_R(k1, k2, k3) RALT_T(k1), RCTL_T(k2), RSFT_T(k3)
#define BRM(k0, k1) MEH_T(k0), HYPR_T(k1)
#define TRM_LR(k0) VIMNAV_T(k0)
#define TRM_LL(k0) _T(k0)
#define TRM_RM(k0) ALT___R(k0)
#define TRM_LM(k0) LSHGR_T(k0)
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
     LT_OUTR, LT_PNKY, LT_RING, LT_MDLE, LT_INDX, LT_INNR,    RT_INNR, RT_INDX, RT_MDLE, RT_RING, RT_PNKY, RT_OUTR,
   ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     LH_OUTR, LH_PNKY, LH_RING, LH_MDLE, LH_INDX, LH_INNR,    RH_INNR, RH_INDX, RH_MDLE, RH_RING, RH_PNKY, RH_OUTR,
   ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
     LB_OUTR, LB_PNKY, LB_RING, LB_MDLE, LB_INDX, LB_INNR,    R_M_INNR, R_M_INDX, R_M_MDLE, R_M_RING, R_M_PNKY, R_M_OUTR,
   ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                L_LTHMB, L_MTHMB, L_RTHMB,    R_LTHMB, R_MTHMB
                              ╰───────────────────────────╯ ╰──────────────────╯


*/

#define HR_MODTAP( \
LT_OUTR, LT_PNKY, LT_RING, LT_MDLE, LT_INDX, LT_INNR,   LH_OUTR, LH_PNKY, LH_RING, LH_MDLE, LH_INDX, LH_INNR, \
LB_OUTR, LB_PNKY, LB_RING, LB_MDLE, LB_INDX, LB_INNR,   k5F, L_RTHMB, k5D, L_LTHMB, L_MTHMB, k5A, \
RT_OUTR, RT_PNKY, RT_RING, RT_MDLE, RT_INDX, RT_INNR,   RH_OUTR, RH_PNKY, RH_RING, RH_MDLE, RH_INDX, RH_INNR, \
RB_OUTR, RB_PNKY, RB_RING, RB_MDLE, RB_INDX, RB_INNR,   K7F, R_LTHMB, K7D, R_MTHMB, K7B, K7A \
) \
LT_OUTR, LT_PNKY, LT_RING, URM_L(LT_MDLE), LT_INDX, LT_INNR,       LH_OUTR, LH_PNKY, HRM_L(LH_RING, LH_MDLE, LH_INDX), LH_INNR, \
LB_OUTR, LB_PNKY, LB_RING,   LB_MDLE, LB_INDX, LB_INNR,       k5F,            L_RTHMB, k5D,    L_LTHMB, TRM_LM(L_MTHMB), k5A, \
RT_OUTR, RT_PNKY, RT_RING, URM_R(RT_MDLE), RT_INDX, RT_INNR,       RH_OUTR, RH_PNKY, HRM_R(RH_RING, RH_MDLE, RH_INDX), RH_INNR, \
RB_OUTR, RB_PNKY, RB_RING,   RB_MDLE, RB_INDX, RB_INNR,       K7F,            R_LTHMB, K7D,  TRM_RM(R_MTHMB), K7B,     K7A

/*/
from I:\coding\bastardkb-qmk\.build\obj_bastardkb_charybdis_3x6_akeyhd\src\default_keyboard.h
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
