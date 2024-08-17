#pragma once
#include "charybdis.h"

enum tap_dances {
    TD_BSPC_WD,
    TD_BSPC_CR,
    TD_DEL_WRD,
    TD_DEL_CHR,
};

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_BSPC_WD] = ACTION_TAP_DANCE_DOUBLE(C(KC_BSPC), KC_BSPC),
    [TD_BSPC_CR] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, C(KC_BSPC)),
    [TD_DEL_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_DEL), KC_DEL),
    [TD_DEL_CHR] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, C(KC_DEL)),
    };
// clang-format on

#define BSPC_WD TD(TD_BSPC_WD)
#define BSPC_CR TD(TD_BSPC_CR)
#define DEL_WRD TD(TD_DEL_WRD)
#define DEL_CHR TD(TD_DEL_CHR)
