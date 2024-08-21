#include "smart_layer.h"
#include "brainrot_keycodes.h"

/*--------- Left Shift Gr Mode ---------------*/
static bool     _ctrlgr_mode_active = false;
static uint16_t ctrlgr_mode_timer;
// Turn nav mode on. To be called from a custom keycode.
bool ctrlgr_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_CTRLGR);
        ctrlgr_mode_timer = timer_read();
    } else {
        if (timer_elapsed(ctrlgr_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _ctrlgr_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_CTRLGR);
        }
    }
    return false;
}

// Turn nav mode off.
void ctrlgr_mode_disable(void) {
    _ctrlgr_mode_active = false;
    layer_off(_CTRLGR);
}

void ctrlgr_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case ML_LCTL ... ML_LGUI:
        case CW_TOGG:
        case TD(TDW):
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
                ctrlgr_mode_disable();
            }
            break;
    }
}
/*--------- Left Shift Gr Mode ---------------*/
static bool     _shiftgr_mode_active = false;
static uint16_t shiftgr_mode_timer;
// Turn nav mode on. To be called from a custom keycode.
bool shiftgr_mode_enable(keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_SHIFTGR);
        shiftgr_mode_timer = timer_read();
    } else {
        if (timer_elapsed(shiftgr_mode_timer) < TAPPING_TERM) {
            // Tapping enables layer mode
            _shiftgr_mode_active = true;
        } else {
            // Holding treats as a normal LT
            layer_off(_SHIFTGR);
        }
    }
    return false;
}

// Turn nav mode off.
void shiftgr_mode_disable(void) {
    _shiftgr_mode_active = false;
    layer_off(_SHIFTGR);
}

void shiftgr_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        case ML_LCTL ... ML_LGUI:
        case KC_CAPS:
        case TD(TDW):
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
                shiftgr_mode_disable();
            }
            break;
    }
}

/* -------- Pointer Mode -------- */
bool _pointer_mode_active = false;
// Turn number mode on. To be called from a custom keycode
bool pointer_mode_enable(keyrecord_t *record) {
    _pointer_mode_active = true;
    layer_on(_POINTER);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
    rgb_matrix_sethsv_noeeprom(HSV_RED);
#endif // RGB_MATRIX_ENABLE
    return false;
}

// Turn number mode off.
void pointer_mode_disable(void) {
    _pointer_mode_active = false;
    layer_off(_POINTER);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#endif // RGB_MATRIX_ENABLE
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
        case DRG_TOG:
        case KC_LEFT:
        case KC_RGHT:
        case KC_DOWN:
        case KC_UP:
        case PNTROPT:
        case PNTRNAV:
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
        case MATH:
        case KC_H:
        case KC_K:
        case KC_J:
        case KC_L:
        case LBM_ARC:
        case SHFGR_R:
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
    if (_ctrlgr_mode_active) {
        ctrlgr_mode_process(keycode, record);
    } else if (_shiftgr_mode_active) {
        shiftgr_mode_process(keycode, record);
    } else if (_pointer_mode_active) {
        pointer_mode_process(keycode, record);
    } else if (_vim_motion_mode_active) {
        vim_motion_mode_process(keycode, record);
    } else if (_math_mode_active) {
        math_mode_process(keycode, record);
    } else if (_func_mode_active) {
        func_mode_process(keycode, record);
    } else if (_macro_mode_active) {
        macro_mode_process(keycode, record);
    }
}
