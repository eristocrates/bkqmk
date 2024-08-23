#include "smart_layer.h"
#include "brainrot_keycodes.h"

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
        case KC_ENT:
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
    if (_pointer_mode_active) {
        pointer_mode_process(keycode, record);
    } else if (_math_mode_active) {
        math_mode_process(keycode, record);
    } else if (_func_mode_active) {
        func_mode_process(keycode, record);
    } else if (_macro_mode_active) {
        macro_mode_process(keycode, record);
    }
}
