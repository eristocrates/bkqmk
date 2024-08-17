#include "brainrot.h"
#include "secret.h"
#include "features/qmk-vim/vim.h"

// Hold Timers
static uint16_t qu_tapping_term;
static uint16_t qu_timer           = 0;
static uint16_t last_keycode_timer = 0;
bool            is_qu_held         = false;
bool            is_shift_toggled   = false;
// modes for modal keys
bool semicolon_mode   = false;
bool smart_space_mode = false;
bool pair_mode        = false; // auto  pairs of ()[]{} '' "" `` <>
bool ampersand_mode   = false; // and/&
bool word_erase_mode  = false; // bspc+del word erase
bool kana_input_mode  = false; // romaji/kana input
bool infor_mode       = false; // swap enter with ctrl+h

// https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/possumvibes.c#L5
static uint16_t    next_keycode;
static keyrecord_t next_record;
static uint16_t    prev_keycode;

// Define the tapping term for the custom keycode
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QU:
            return 175;
        default:
            return TAPPING_TERM; // Default tapping term
    }
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t prev_keycode;
    if (record->event.pressed) {
        // store previous keycode for instant tap decisions
        prev_keycode = next_keycode;

        // Cache the next input for mod-tap decisions
        next_keycode = keycode;
        next_record  = *record;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    // TODO see if i can ifdef this
    /*
      if (!process_achordion(keycode, record)) { return false; }
      if (!process_custom_shift_keys(keycode, record)) { return false; }

    */
    if (!process_vim_mode(keycode, record)) {
        return false;
    }
    switch (keycode) {
        /*------------------------------digraphs------------------------------*/
        case KC_TH:
            if (record->event.pressed) {
                SEND_STRING("th");
            }
            return false;
        case KC_IN:
            if (record->event.pressed) {
                SEND_STRING("in");
            }
            return false;
        case KC_QU:
            qu_tapping_term = get_tapping_term(KC_QU, record);
            if (record->event.pressed) {
                if (!is_qu_held) {
                    is_qu_held = true;
                    qu_timer   = timer_read();
                }
            } else {
                is_qu_held = false;
                if (timer_elapsed(qu_timer) < qu_tapping_term) {
                    // Send "qu" if tapped
                    SEND_STRING("qu");
                }
            }
            return false; // Skip all further processing of this key
        /*------------------------------split spaces------------------------------*/
        case KC_LSPC: {
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
        }
            return false;
        case KC_RSPC: {
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
        }
            return false;
        /*------------------------------shortcuts------------------------------*/
        case SH_RMDT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                tap_code(KC_PAUSE);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            return false;
        case SCN_TOG:
            if (record->event.pressed) {
                if (is_shift_toggled) {
                    unregister_mods(MOD_BIT(KC_LSFT)); // Unregister Shift
                    is_shift_toggled = false;
                } else {
                    register_mods(MOD_BIT(KC_LSFT)); // Register Shift
                    is_shift_toggled = true;
                }
            }
            return false; // Skip all further processing of this key
        /*------------------------------semantic keys------------------------------*/
        // TODO figure out raw hid
        // TODO figure out appropriate shift overrides/holds for vim versions of semantic keys eg save tap/save all hold
        case SM_COPY:
            if (record->event.pressed) {
                if (vim_enabled) {
                    // Send 'y' for copy in Vim
                    tap_code(KC_Y);
                } else {
                    // Send Ctrl+C for copy
                    register_code(KC_LCTL);
                    tap_code(KC_C);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
        case SM_CUT:
            if (record->event.pressed) {
                if (vim_enabled) {
                    // Send 'd' for cut in Vim
                    tap_code(KC_D);
                } else {
                    // Send Ctrl+X for cut
                    register_code(KC_LCTL);
                    tap_code(KC_X);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
        case SM_PASTE:
            if (record->event.pressed) {
                if (vim_enabled) {
                    // Send 'p' for paste in Vim
                    tap_code(KC_P);
                } else {
                    // Send Ctrl+V for paste
                    register_code(KC_LCTL);
                    tap_code(KC_V);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
        case SM_SAVE:
            if (record->event.pressed) {
                if (vim_enabled) {
                    // Send ':w' for save in Vim
                    SEND_STRING(":w");
                    tap_code(KC_ENT);
                } else {
                    // Send Ctrl+S for save
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
        case SM_SNAP:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;
        /*------------------------------modal keys------------------------------*/
        case MD_DTSC:
            if (record->event.pressed) {
                if (semicolon_mode) {
                    // Output ';' in semicolon mode
                    tap_code(KC_SCLN);
                } else {
                    // Output '.' in normal mode
                    tap_code(KC_DOT);
                }
            }
            return false;
        case MD_AND:
            if (record->event.pressed) {
                if (ampersand_mode) {
                    // Output '&' in ampersand mode
                    tap_code16(KC_AMPR);
                } else {
                    SEND_STRING("and");
                }
            }
            return false;
        case MD_BSPC:
            if (record->event.pressed) {
                if (word_erase_mode) {
                    register_code(KC_LCTL);
                    tap_code(KC_BSPC);
                    unregister_code(KC_LCTL);
                } else {
                    tap_code(KC_BSPC);
                }
            }
            return false;
        case MD_DEL:
            if (record->event.pressed) {
                if (word_erase_mode) {
                    register_code(KC_LCTL);
                    tap_code(KC_DEL);
                    unregister_code(KC_LCTL);
                } else {
                    tap_code(KC_DEL);
                }
            }
            return false;
        case MD_IME:
            if (record->event.pressed) {
                if (kana_input_mode) {
                    tap_code16(KC_RO);
                } else {
                    tap_code16(KC_KANA);
                }
                kana_input_mode = !kana_input_mode;
            }
            return false;
        case MD_YES:
            if (record->event.pressed) {
                if (infor_mode) {
                    register_code(KC_LCTL);
                    tap_code(KC_H);
                    unregister_code(KC_LCTL);
                } else {
                    tap_code(KC_ENTER);
                }
            }
            return false;
        case MD_RNPO:
            if (record->event.pressed) {
                if (pair_mode) {
                    SEND_STRING("()");
                    tap_code(KC_LEFT);
                } else {
                    tap_code16(KC_LPRN);
                }
            }
            return false;
        case MD_SQPO:
            if (record->event.pressed) {
                if (pair_mode) {
                    SEND_STRING("[]");
                    tap_code(KC_LEFT);
                } else {
                    tap_code16(KC_LBRC);
                }
            }
            return false;
        case MD_CRPO:
            if (record->event.pressed) {
                if (pair_mode) {
                    SEND_STRING("{}");
                    tap_code(KC_LEFT);
                } else {
                    tap_code16(KC_LCBR);
                }
            }
            return false;
        case MD_RNPC:
            if (record->event.pressed) {
                tap_code16(KC_RPRN);
            }
            return false;
        case MD_SQPC:
            if (record->event.pressed) {
                tap_code16(KC_RBRC);
            }
            return false;
        case MD_CRPC:
            if (record->event.pressed) {
                tap_code16(KC_RCBR);
            }
            return false;
        /*------------------------------arcane------------------------------*/
        case LT_ARC: {
            if (record->event.pressed) {
                process_top_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case RT_ARC: {
            if (record->event.pressed) {
                process_top_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case LB_ARC: {
            if (record->event.pressed) {
                process_bottom_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case RB_ARC: {
            if (record->event.pressed) {
                process_bottom_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;

        /*------------------------------secrets------------------------------*/
        case SECRET1: {
            if (record->event.pressed) {
                SEND_STRING(SECRET_ONE);
            }
        }
            return false;
        case SECRET2: {
            if (record->event.pressed) {
                SEND_STRING(SECRET_TWO);
            }
        }
            return false;
        /*------------------------------vim------------------------------*/
        case VIM_TOG:
            if (record->event.pressed) {
                toggle_vim_mode();
            }
            return false;
        case VIM_G_:
            if (record->event.pressed) {
                tap_code(KC_G);
                tap_code16(KC_UNDS);
            }
            return false;
        case VIM_GG:
            if (record->event.pressed) {
                tap_code(KC_G);
                tap_code(KC_G);
            }
            return false;
        /*------------------------------math------------------------------*/
        case KC_SQRT:
            if (record->event.pressed) {
                SEND_STRING("sqrt()");
                tap_code(KC_LEFT);
            }
            return false;
        /*------------------------------randumb------------------------------*/
        case KC_RAND:
            if (record->event.pressed) {
                tap_random_base64();
            }
            return false;

        default:
            return true; // Process all other keycodes normally
    }
}
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (smart_space_mode) {
        if (record->event.pressed) {
            switch (keycode) {
                // TODO add smart space candidates
                // TODO check if combos are possible?
            }
        }
    }
}
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    switch (keycode) {
        case QK_LEAD:
        case LT_ARC:
        case RT_ARC:
        case LB_ARC:
        case RB_ARC:
            return false; // Arcane keys will ignore the above keycodes.
    }
    last_keycode_timer = timer_read();
    return true; // Other keys can be repeated.
}

// TODO incorperate qu to use this
/*
    process_record_user
    case TH_1:  return process_tap_or_long_press_key(record, KC_F1); // number on tap, f-key on hold
static bool process_tap_or_long_press_key( // Tap for number, hold for F-key
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

*/

void matrix_scan_user(void) {
    if (is_qu_held) {
        if (timer_elapsed(qu_timer) == qu_tapping_term) {
            tap_code(KC_Q);
        }
    }
    if (timer_elapsed(last_keycode_timer) >= LAST_KEYCODE_TIMEOUT_MS) {
        set_last_keycode(KC_SPC);
    }

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#    ifdef RGB_MATRIX_ENABLE
        // rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#    endif // RGB_MATRIX_ENABLE
    }
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_N, KC_4)) {
        infor_mode = !infor_mode;
    } else if (leader_sequence_three_keys(KC_D, KC_O, KC_T)) {
        semicolon_mode = !semicolon_mode;
    } else if (leader_sequence_three_keys(KC_C, KC_L, KC_N)) {
        semicolon_mode = !semicolon_mode;
    } else if (leader_sequence_three_keys(KC_A, KC_N, KC_D)) {
        ampersand_mode = !ampersand_mode;
    } else if (leader_sequence_three_keys(KC_O, KC_T, KC_O)) {
        autocorrect_toggle();
    } else if (leader_sequence_three_keys(KC_7, KC_2, KC_7)) {
        layer_on(LAYER_SECRET);
    } else if (leader_sequence_three_keys(KC_V, KC_I, KC_M)) {
        toggle_vim_mode();
    } else if (leader_sequence_two_keys(KC_F, KC_L)) {
        reset_keyboard();
    } else if (leader_sequence_two_keys(KC_W, KC_E)) {
        word_erase_mode = !word_erase_mode;
    }
}

// TODO investigate what characters need to be added
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
