#include "mac_mode.h"
#include "motions.h"
#include "numbered_actions.h"
#include "vim.h"
#include "../../../akeyhd_keycodes.h"

#ifdef BETTER_VISUAL_MODE
visual_direction_t visual_direction = V_NONE;
#endif

void set_visual_direction(visual_direction_t dir) {
#ifdef BETTER_VISUAL_MODE
    if (vim_emulation && visual_direction == V_NONE) visual_direction = dir;
#endif
}

void register_motion(uint16_t keycode, const keyrecord_t *record) {
    if (vim_emulation) {
        if (record->event.pressed) {
#ifdef QMK_VIM_NUMBERED_JUMPS
            extern int16_t motion_counter;
            if (motion_counter > 1) {
                tap_code16(keycode);
                return;
            }
#endif
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

bool process_motions(uint16_t keycode, const keyrecord_t *record, uint16_t qk_mods) {
    // This macro duplicates the code inside if QMK_VIM_FOR_ALL is enabled
    // Calling it on only a subset of the larger switch statement saves some space
    QMK_VIM_REDUCE_MAC_NOMAC_TO_CONST(switch (keycode) {
        case QMK_VIM_B:
            keycode = KC_B;
            break;
        case QMK_VIM_W:
            keycode = KC_W;
            break;
        case QMK_VIM_0:
            keycode = KC_0;
            break;
        case QMK_VIM_DLR:
            keycode = KC_DLR;
            break;
    });
    DO_NUMBERED_ACTION(switch (keycode) {
        case KC_H:
        case QMK_VIM_H:
            set_visual_direction(V_BACKWARD);
            register_motion(qk_mods | QMK_VIM_H, record);
            break;
        case KC_J:
        case QMK_VIM_J:
            set_visual_direction(V_FORWARD);
            register_motion(qk_mods | QMK_VIM_J, record);
            break;
        case KC_K:
        case QMK_VIM_K:
            set_visual_direction(V_BACKWARD);
            register_motion(qk_mods | QMK_VIM_K, record);
            break;
        case KC_L:
        case QMK_VIM_L:
            set_visual_direction(V_FORWARD);
            register_motion(qk_mods | QMK_VIM_L, record);
            break;
        case KC_B:
        case LSFT(KC_B):
            set_visual_direction(V_BACKWARD);
            register_motion(qk_mods | QMK_VIM_B, record);
            break;
        case KC_W:
        case LSFT(KC_W):
#ifdef QMK_VIM_W_BEGINNING_OF_WORD
            set_visual_direction(V_FORWARD);
            register_motion(qk_mods | QMK_VIM_W, record);
            if (vim_emulation && !record->event.pressed) {
                /* unregister_code16(qk_mods | QMK_VIM_W); */
                tap_code16(qk_mods | QMK_VIM_W);
                tap_code16(qk_mods | QMK_VIM_B);
            }
            break;
#endif
        case KC_E:
        case LSFT(KC_E):
            set_visual_direction(V_FORWARD);
            register_motion(qk_mods | QMK_VIM_E, record);
            break;
        case KC_0:
        case KC_CIRC: // ^
            set_visual_direction(V_BACKWARD);
            register_motion(qk_mods | QMK_VIM_0, record);
            break;
        case KC_DLR: // $
            set_visual_direction(V_FORWARD);
            register_motion(qk_mods | QMK_VIM_DLR, record);
            break;
        default:
            /* motion_counter = 0; */
            return true;
    });
    return false;
}
