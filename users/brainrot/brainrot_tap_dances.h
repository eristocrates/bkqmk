#pragma once
#include "charybdis.h"

enum tap_dances {
    TD_BSPC_WRD,
    TD_DEL_WRD,
};

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_BSPC_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_BSPC), KC_BSPC),
    [TD_DEL_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_DEL), KC_DEL),
    };
// clang-format on

#define BSPC_WRD TD(TD_BSPC_WRD)
#define DEL_WRD TD(TD_DEL_WRD)
