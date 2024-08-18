#include "smart_layer.h"
#include "brainrot_keycodes.h"
#include "brainrot_tap_dances.h"

// TODO keep this in sync with the defines in brainrot.c & keymap.c
#define BSPC_WD TD(TD_BSPC)
#define DEL_WRD TD(TD_DEL)
#define N_LEAD TD(TD_N_LEAD)
#define E_LEAD TD(TD_E_LEAD)

/*--------- Left Shift Gr Mode ---------------*/
static bool     _rshiftgr_mode_active = false;
static uint16_t rshiftgr_mode_timer;
// Turn nav mode on. To be called from a custom keycode.
bool rshiftgr_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_RSHIFTGR);
        rshiftgr_mode_timer = timer_read();
    } else {
        if (timer_elapsed(rshiftgr_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _rshiftgr_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_RSHIFTGR);
        }
    }
    return false;
}

// Turn nav mode off.
void rshiftgr_mode_disable(void) {
    _rshiftgr_mode_active = false;
    layer_off(_RSHIFTGR);
}

void rshiftgr_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case ML_LCTL ... ML_LGUI:
        case CW_TOGG:
        case DEL_WRD:
        case KC_UNDS:
        case MD_CRPO:
        case KC_EXLM:
        case KC_SLSH:
        case MD_CRPC:
        case KC_MHEN:
            break;
        default:
            // All other keys disable the layer mode.
            if (!record->event.pressed) {
                rshiftgr_mode_disable();
            }
            break;
    }
}
/*--------- Left Shift Gr Mode ---------------*/
static bool     _lshiftgr_mode_active = false;
static uint16_t lshiftgr_mode_timer;
// Turn nav mode on. To be called from a custom keycode.
bool lshiftgr_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_LSHIFTGR);
        lshiftgr_mode_timer = timer_read();
    } else {
        if (timer_elapsed(lshiftgr_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _lshiftgr_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_LSHIFTGR);
        }
    }
    return false;
}

// Turn nav mode off.
void lshiftgr_mode_disable(void) {
    _lshiftgr_mode_active = false;
    layer_off(_LSHIFTGR);
}

void lshiftgr_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case ML_LCTL ... ML_LGUI:
        case KC_CAPS:
        case DEL_WRD:
        case MD_NO:
        case KC_PMNS:
        case MD_SQPO:
        case KC_COLN:
        case KC_QUES:
        case MD_SQPC:
        case KC_HENK:
        case KC_UNDS:

            break;
        default:
            // All other keys disable the layer mode.
            if (!record->event.pressed) {
                lshiftgr_mode_disable();
            }
            break;
    }
}

/* -------- Pointer Mode -------- */
static bool _pointer_mode_active = false;
// Turn number mode on. To be called from a custom keycode
bool pointer_mode_enable(keyrecord_t *record) {
    _pointer_mode_active = true;
    layer_on(_POINTER);
    return false;
}

// Turn number mode off.
void pointer_mode_disable(void) {
    _pointer_mode_active = false;
    layer_off(_POINTER);
}

void pointer_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case KC_1 ... KC_0:
        case KC_BTN1:
        case KC_BTN2:
        case KC_BTN3:
        case S_D_MOD:
        case S_D_RMOD:
        case DPI_MOD:
        case DPI_RMOD:
        case DRGSCRL:
        case SNIPING:
        case SNP_TOG:
        case SM_SNAP:
        case KC_LEFT:
        case KC_RGHT:
        case KC_DOWN:
        case KC_UP:
            // process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                pointer_mode_disable();
            }
            break;
    }
}

/* -------- Vim Motion Mode -------- */
static bool _vim_motion_mode_active = false;
// Turn number mode on. To be called from a custom keycode
bool vim_motion_mode_enable(keyrecord_t *record) {
    _vim_motion_mode_active = true;
    layer_on(_VIMMOTION);
    return false;
}

// Turn number mode off.
void vim_motion_mode_disable(void) {
    _vim_motion_mode_active = false;
    layer_off(_VIMMOTION);
}

void vim_motion_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case KC_1 ... KC_0:
        case KC_P:
        case KC_Y:
        case VIMNUM:
        case MATH:
        case KC_H:
        case KC_K:
        case KC_J:
        case KC_L:
            // process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                vim_motion_mode_disable();
            }
            break;
    }
}

/* -------- Number Mode -------- */
static bool _math_mode_active = false;
// Turn number mode on. To be called from a custom keycode
bool math_mode_enable(keyrecord_t *record) {
    _math_mode_active = true;
    layer_on(_MATH);
    return false;
}

// Turn number mode off.
void math_mode_disable(void) {
    _math_mode_active = false;
    layer_off(_MATH);
}

void math_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case KC_1 ... KC_0:
        case LGUI_T(KC_8):
        case LALT_T(KC_4):
        case LCTL_T(KC_5):
        case LSFT_T(KC_6):
        case KC_DLR:
        case KC_QUOT:
        case KC_SLSH:
        case KC_SCLN:
        case KC_COLN:
        case KC_COMM:
        case KC_DOT:
        case KC_MINS:
        case KC_ASTR:
        case KC_EQL:
        case KC_PLUS:
        case BRCKETS:
        case KC_V:
        case KC_X:
            // process the code and stay in the mode *dabs*
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                math_mode_disable();
            }
            break;
    }
}

/* -------- Function Mode -------- */
static bool _func_mode_active = false;

// Turn Func mode on. To be called from a custom keycode.
bool func_mode_enable(keyrecord_t *record) {
    _func_mode_active = true;
    layer_on(_FUNCTION);
    return false;
}

// Turn func mode off.
void func_mode_disable(void) {
    _func_mode_active = false;
    layer_off(_FUNCTION);
}

// Handle each key for func mode.
void func_mode_process(uint16_t keycode, keyrecord_t *record) {
    // todo possum strip keycode from lt/modtaps if needed

    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case KC_F3:
        case F5_TH:
        case KC_F8:
        case KC_F10:
        case F11_TH:
        case F12_TH:
        case OS_LSFT ... OSR_SFT:
            break;
        default:
            // All other keys disable the layer mode.
            if (!record->event.pressed) {
                func_mode_disable();
            }
            break;
    }
}

/*--------- Nav Mode ---------------*/
static bool     _nav_mode_active = false;
static uint16_t nav_mode_timer;
// Turn nav mode on. To be called from a custom keycode.
bool nav_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_VIMMOTION);
        nav_mode_timer = timer_read();
    } else {
        if (timer_elapsed(nav_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _nav_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_VIMMOTION);
        }
    }
    return false;
}

// Turn nav mode off.
void nav_mode_disable(void) {
    _nav_mode_active = false;
    layer_off(_VIMMOTION);
}

void nav_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case ML_LCTL ... ML_LGUI:
        case KC_HOME ... KC_UP:
        case KC_MS_U ... KC_ACL2:
        case CLEAR:
            // case F12_TH:
            // case CTL_U:
            break;
        default:
            // All other keys disable the layer mode.
            if (!record->event.pressed) {
                nav_mode_disable();
            }
            break;
    }
}

/*--------- Sym Mode ---------------*/
static bool _sym_mode_active = false;

// Turn sym mode on. To be called from a custom keycode.
bool sym_mode_enable(keyrecord_t *record) {
    _sym_mode_active = true;
    layer_on(_LSHIFTGR);
    return false;
}

// Turn sym mode off.
void sym_mode_disable(void) {
    _sym_mode_active = false;
    layer_off(_LSHIFTGR);
}

void sym_mode_process(uint16_t keycode, keyrecord_t *record) {
    // todo possum strip keycode from lt/modtaps if needed

    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        // SYMMODE is a glorified oneshot layer that lets you hit shift without breaking.
        case OS_LSFT ... OSR_SFT:
            break;
        default:
            // All other keys disable the layer mode.
            if (!record->event.pressed) {
                sym_mode_disable();
            }
            break;
    }
}

/* -------- Macro Mode -------- */
static bool _macro_mode_active = false;
// Turn macro mode on. To be called from a custom keycode
bool macro_mode_enable(keyrecord_t *record) {
    _macro_mode_active = true;
    layer_on(_KEYBOARD);
    return false;
}

// Turn macro mode off.
void macro_mode_disable(void) {
    _macro_mode_active = false;
    layer_off(_KEYBOARD);
}

void macro_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
            break;
        default:
            // All other keys disable the layer mode on keyup.
            if (!record->event.pressed) {
                macro_mode_disable();
            }
            break;
    }
}

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record) {
    if (_rshiftgr_mode_active) {
        rshiftgr_mode_process(keycode, record);
    } else if (_lshiftgr_mode_active) {
        lshiftgr_mode_process(keycode, record);
    } else if (_pointer_mode_active) {
        pointer_mode_process(keycode, record);
    } else if (_vim_motion_mode_active) {
        vim_motion_mode_process(keycode, record);
    } else if (_math_mode_active) {
        math_mode_process(keycode, record);
    } else if (_func_mode_active) {
        func_mode_process(keycode, record);
    } else if (_nav_mode_active) {
        nav_mode_process(keycode, record);
    } else if (_sym_mode_active) {
        sym_mode_process(keycode, record);
    } else if (_macro_mode_active) {
        macro_mode_process(keycode, record);
    }
}
