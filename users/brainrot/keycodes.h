#pragma once
#include "quantum/keycodes.h"
#include "charybdis.h"
enum layers {
    LAYER_BRAINROT = 0,
    LAYER_QWERTY,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_LAYER,
};
enum keycodes {
    KC_QU = SAFE_RANGE,
    SC_RMDT,
    TG_SHFT,
};

// Tap Dance
enum tap_dances {
    TD_SPC_ENT,
    TD_SPC_ESC,
    TD_BSPC_WRD,
    TD_DEL_WRD,
    TD_DRG_TOG,
};

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
    [TD_SPC_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ESC),
    [TD_BSPC_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_BSPC), KC_BSPC),
    [TD_DEL_WRD] = ACTION_TAP_DANCE_DOUBLE(C(KC_DEL), KC_DEL),
    [TD_DRG_TOG] = ACTION_TAP_DANCE_DOUBLE(DRGSCRL, DRG_TOG)
    };
// clang-format on

/* ---------- Aliases ---------- */

// layers & their behavior
// TODO consider decoupling this, maybe a modular wrapper macro to assign behavior
#define BASE TO(LAYER_BRAINROT)
#define LAYER TT(LAYER_LAYER)
#define LOWER TG(LAYER_LOWER)
#define RAISE TG(LAYER_RAISE)

#define PT_K LT(LAYER_POINTER, KC_K)
#define PT_H LT(LAYER_POINTER, KC_H)
// default LTs
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// tap dance
#define SPC_ENT TD(TD_SPC_ENT)
#define SPC_ESC TD(TD_SPC_ESC)
#define BSPC_WRD TD(TD_BSPC_WRD)
#define DEL_WRD TD(TD_DEL_WRD)
#define DRG_TD TD(TD_DRG_TOG)
