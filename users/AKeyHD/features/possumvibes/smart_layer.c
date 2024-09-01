#include "smart_layer.h"
#include "akeyhd_keycodes.h"

/* -------- Pointer Mode -------- */
bool _pointer_mode_active = false;
// Turn number mode on. To be called from a custom keycode
bool pointer_mode_enable(keyrecord_t *record) {
    _pointer_mode_active = true;
    layer_on(_POINTER);
#ifdef RGB_MATRIX_ENABLE
    // rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
    // rgb_matrix_sethsv_noeeprom(HSV_RED);
#endif // RGB_MATRIX_ENABLE
    return false;
}

// Turn pointer mode off.
void pointer_mode_disable(void) {
    _pointer_mode_active = false;
    layer_off(_POINTER);
#ifdef RGB_MATRIX_ENABLE
    // rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#endif // RGB_MATRIX_ENABLE
}

void pointer_mode_process(uint16_t keycode, keyrecord_t *record) {
    // Assess if we should exit layermode or continue processing normally.
    switch (keycode) {
        case OS_LSFT ... OSR_SFT:
        // case KC_BTN1:
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
        case PNTROPT:
        case SMR_SPC:
        case KC_ESC:

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

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record) {
    if (_pointer_mode_active) {
        pointer_mode_process(keycode, record);
    } else if (_math_mode_active) {
        math_mode_process(keycode, record);
    }
}
