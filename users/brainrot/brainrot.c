#include "brainrot.h"
#include "secret.h"
#include "features/andrewjrae/qmk-vim/vim.h"
#include "features/possumvibes/smart_layer.h"
#include "brainrot_keycodes.h"

// Timers
static uint16_t last_keycode_timer = 0;

// piercing holds
uint16_t tap_keycode;
uint16_t hold_keycode;
uint16_t hold_mod;

// for SCN
bool is_ALT___Roggled = false;

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        // TODO experiment with removing this, as i rely on arcane repeats anyways
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

static td_tap_t qutap_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t bspc_state  = {.is_press_action = true, .state = TD_NONE};
static td_tap_t del_state   = {.is_press_action = true, .state = TD_NONE};

// tap dance advanced functions
void qu_finished(tap_dance_state_t *state, void *user_data) {
    qutap_state.state = cur_dance(state);
    switch (qutap_state.state) {
        case TD_SINGLE_TAP:
            send_string_with_caps_word("qu");
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_Q);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_Q);
            break;
        default:
            break;
    }
}

void qu_reset(tap_dance_state_t *state, void *user_data) {
    switch (qutap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_Q);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_Q);
            break;
        default:
            break;
    }
    qutap_state.state = TD_NONE;
}

void bspc_finished(tap_dance_state_t *state, void *user_data) {
    bspc_state.state = cur_dance(state);
    switch (bspc_state.state) {
        case TD_SINGLE_TAP:
            if (delete_word_mode) {
                register_code(KC_LCTL);
                register_code(KC_BSPC);
            } else {
                register_code(KC_BSPC);
            }
            break;
        case TD_DOUBLE_TAP:
            if (delete_word_mode) {
                register_code(KC_BSPC);
            } else {
                register_code(KC_LCTL);
                register_code(KC_BSPC);
            }
            break;
        case TD_TRIPLE_TAP:
            delete_word_mode = !delete_word_mode;
            break;
        default:
            break;
    }
}

void bspc_reset(tap_dance_state_t *state, void *user_data) {
    switch (bspc_state.state) {
        case TD_SINGLE_TAP:
            if (delete_word_mode) {
                unregister_code(KC_LCTL);
                unregister_code(KC_BSPC);
            } else {
                unregister_code(KC_BSPC);
            }
            break;
        case TD_DOUBLE_TAP:
            if (delete_word_mode) {
                unregister_code(KC_BSPC);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_BSPC);
            }
            break;
        default:
            break;
    }
}

void del_finished(tap_dance_state_t *state, void *user_data) {
    del_state.state = cur_dance(state);
    switch (del_state.state) {
        case TD_SINGLE_TAP:
            if (delete_word_mode) {
                register_code(KC_LCTL);
                register_code(KC_DEL);
            } else {
                register_code(KC_DEL);
            }
            break;
        case TD_DOUBLE_TAP:
            if (delete_word_mode) {
                register_code(KC_DEL);
            } else {
                register_code(KC_LCTL);
                register_code(KC_DEL);
            }
            break;
        case TD_TRIPLE_TAP:
            delete_word_mode = !delete_word_mode;
            break;
        default:
            break;
    }
}

void del_reset(tap_dance_state_t *state, void *user_data) {
    switch (del_state.state) {
        case TD_SINGLE_TAP:
            if (delete_word_mode) {
                unregister_code(KC_LCTL);
                unregister_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            break;
        case TD_DOUBLE_TAP:
            if (delete_word_mode) {
                unregister_code(KC_DEL);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_DEL);
            }
            break;
        default:
            break;
    }
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TBW] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, bspc_finished, bspc_reset),
    [TDW] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, del_finished, del_reset),
    };
// clang-format on

// static bool is_windows = true;

// https://github.com/possumvibes/qmk_firmware/blob/e0e939ef77e531966c86a1dc06315458d5a5547c/users/possumvibes/possumvibes.c#L5
static uint16_t    next_keycode;
static keyrecord_t next_record;
static uint16_t    prev_keycode;

// TODO move this into my own feature
void call_keycode(uint16_t keycode) {
    keyrecord_t record;
    record.event.pressed = true;
    process_record_user(keycode, &record);
    record.event.pressed = false;
    process_record_user(keycode, &record);
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

// TODO move this into my own feature
// TODO look for repeated keys that would benefit from evolving/expanding on every repeat. probably needs a mode toggle too
/*
static bool process_consecutive_key(keyrecord_t *record, uint16_t current_keycode, uint8_t mod_intent) {
    if (current_keycode == prev_keycode) {
        if (record->event.pressed) {
            add_weak_mods(MOD_BIT(mod_intent));
            tap_code16(current_keycode);
        }
        return false; // Skip default handling.
    }
    return true; // Continue default handling.
}
*/

static bool process_tap_or_long_press_key(keyrecord_t *record, uint16_t long_press_keycode) {
    if (record->tap.count == 0) { // Key is being held.
        if (record->event.pressed) {
            tap_code16(long_press_keycode);
        }
        return false; // Skip default handling.
    }
    return true; // Continue default handling.
}

static bool process_tap_or_long_mod_press_key(keyrecord_t *record, uint16_t long_press_keycode, uint16_t mod) {
    if (record->tap.count == 0) { // Key is being held.
        if (record->event.pressed) {
            if (mod != 0) {
                register_code(mod);
            }
            tap_code16(long_press_keycode);
            if (mod != 0) {
                unregister_code(mod);
            }
        }
        return false; // Skip default handling.
    }
    return true; // Continue default handling.
}

// TODO blindly calling false on these keycodes has prevented things like caps_word_press_user from working. Make sure to actually evaluate what keycodes do not require further processingr
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) uprintf("process_record_user: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    // TODO see if i can ifdef this
    /*
      if (!process_achordion(keycode, record)) { return false; }
      if (!process_custom_shift_keys(keycode, record)) { return false; }

    */
    // TODO find where this gets used
    // bool is_shifted = (get_mods() & MOD_MASK_SHIFT) || (get_oneshot_mods() & MOD_MASK_SHIFT);

    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    process_mod_lock(keycode, record);
    process_nshot_state(keycode, record);
    process_layermodes(keycode, record);
    switch (keycode) {
            /*------------------------------piercing mods------------------------------*/
            // powerful stuff, unironically surprised myself with this one
            // TODO think of keys that would want to be tapped, prefereably without wanting other mods
            // TODO ensure nshot mod layer interacts properly with this

        case GLTOUTR:
        case CLTOUTR:
        case ALTOUTR:
        case TH____X:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;

        case GLTPNKY:
        case CLTPNKY:
        case ALTPNKY:
        case TH____V:

            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;

        case GLTRING:
        case CLTRING:
        case ALTRING:
        case TH____G:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        case GLTMDLE:
        case CLTMDLE:
        case ALTMDLE:
        case TH____M:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        case GLTINDX:
        case CLTINDX:
        case ALTINDX:
        case TH____P:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;

        // TODO think of cool things arcane could do on hold
        case GLTINNR:
        case CLTINNR:
        case ALTINNR:
            // arcane

        case GRTOUTR:
        case CRTOUTR:
        case ARTOUTR:
            // arcane
            return false;

        case GRHINDX:
        case CRHINDX:
        case ARHINDX:
        case TH____A:
            tap_keycode  = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            hold_keycode = tap_keycode;
            if (IS_LAYER_ON(_GUIPR)) {
                hold_mod = KC_LGUI;
            } else if (IS_LAYER_ON(_CTRLPR)) {
                hold_mod = KC_LCTL;
            } else if (IS_LAYER_ON(_ALTPR)) {
                hold_mod = KC_LALT;
            } else {
                hold_mod = KC_LSFT;
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
            /*------------------------------consequtive keys------------------------------*/
            /* ya now i see why tap dances need tapping term（︶^︶）
            BUT! from that realization i still think this can be pretty useful
            if (!process_consecutive_key(record, keycode, KC_LCTL)) {
                return false;
            }
            return true;
            */
        /*------------------------------smart layers------------------------------*/
        case VIMMOTIONMODE:
            return vim_motion_mode_enable(record);

        case POINTERMODE:
            return pointer_mode_enable(record);

        case CLEAR:
            clear_oneshot_mods();
            clear_mods();
            pointer_mode_disable();
            return false;

        case PANIC: {
            clear_oneshot_mods();
            clear_mods();
            if (get_oneshot_layer() != 0) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            layer_move(0);
            caps_word_off();
            return false;
        }

        /*------------------------------digraphs------------------------------*/
        case KC_TH:
            if (record->event.pressed) {
                send_string_with_caps_word("th");
            }
            return true;
        case KC_IN:
            if (record->event.pressed) {
                send_string_with_caps_word("in");
            }
            return true;
        case TH___QU:
            if (process_tap_or_long_press_key(record, KC_Q)) {
                if (record->event.pressed) {
                    send_string_with_caps_word("qu");
                }
            }
            return false;
        case KC_PH:
            if (record->event.pressed) {
                send_string_with_caps_word("ph");
            }
            return true;
        case KC_SH:
            if (record->event.pressed) {
                send_string_with_caps_word("sh");
            }
            return true;
        case KC_WH:
            if (record->event.pressed) {
                send_string_with_caps_word("wh");
            }
            return true;
        case KC_CH:
            if (record->event.pressed) {
                send_string_with_caps_word("ch");
            }
            return true;
        /*------------------------------split spaces------------------------------*/
        case KC_LSPC: {
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
        }
            return true;
        case KC_RSPC: {
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
        }
            return true;
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
                if (is_ALT___Roggled) {
                    unregister_mods(MOD_BIT(KC_LSFT)); // Unregister Shift
                    is_ALT___Roggled = false;
                } else {
                    register_mods(MOD_BIT(KC_LSFT)); // Register Shift
                    is_ALT___Roggled = true;
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
                    if (smart_space_mode) {
                        // TODO double check if this is actually a good feel
                        tap_code(KC_O);
                        tap_code(KC_ESC);
                    }
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
        case MD_AND:
            if (record->event.pressed) {
                if (ampersand_mode) {
                    // Output '&' in ampersand mode
                    tap_code16(KC_AMPR);
                } else {
                    send_string_with_caps_word("and");
                }
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_THE:
            if (record->event.pressed) {
                send_string_with_caps_word("the");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_FOR:
            if (record->event.pressed) {
                send_string_with_caps_word("for");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_YOU:
            if (record->event.pressed) {
                send_string_with_caps_word("you");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_GH:
            if (record->event.pressed) {
                send_string_with_caps_word("gh");
            }
            return true;
        case MD_LY:
            if (record->event.pressed) {
                send_string_with_caps_word("ly");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_ING:
            if (record->event.pressed) {
                send_string_with_caps_word("ing");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_SION:
            if (record->event.pressed) {
                send_string_with_caps_word("sion");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_TION:
            if (record->event.pressed) {
                send_string_with_caps_word("tion");
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            }
            return true;
        case MD_BSPC:
            if (record->event.pressed) {
                if (delete_word_mode) {
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
                if (delete_word_mode) {
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
                if (work_mode) {
                    register_code(KC_LCTL);
                    tap_code(KC_H);
                    unregister_code(KC_LCTL);
                } else {
                    tap_code(KC_ENTER);
                }
            }
            return true;
        case MD_NO:
            if (record->event.pressed) {
                tap_code(KC_ESC);
            }
            return true;
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
        case LTP_ARC: {
            if (record->event.pressed) {
                process_top_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case RTP_ARC: {
            if (record->event.pressed) {
                process_top_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case LBM_ARC: {
            if (record->event.pressed) {
                process_bottom_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case RBM_ARC: {
            if (record->event.pressed) {
                process_bottom_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case COM_ARC: {
            if (record->event.pressed) {
                process_comma_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            }
        }
            return false;
        case DOT_ARC: {
            if (record->event.pressed) {
                process_dot_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
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
    if (record->event.pressed) {
        switch (keycode) {
            // TODO move smart space cases here
            case KC_QUES:
            case KC_EXLM:
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
            default:
                last_smart_space = false;
        }
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    switch (keycode) {
        // case QK_LEAD:
        case LTP_ARC:
        case RTP_ARC:
        case LBM_ARC:
        case RBM_ARC:
        case COM_ARC:
        case DOT_ARC:
            return false; // Arcane keys will ignore the above keycodes.
    }
    last_keycode_timer = timer_read();
    return true; // Other keys can be repeated.
}

void matrix_scan_user(void) {
    if (timer_elapsed(last_keycode_timer) == LAST_KEYCODE_TIMEOUT_MS) {
        set_last_keycode(KC_SPC);
    }

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    // if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS && _pointer_mode_active == false) {
    if (_pointer_mode_active == false) {
        auto_pointer_layer_timer = 0;
        charybdis_set_pointer_dragscroll_enabled(false);
        /*
        layer_off(_POINTER);
#    ifdef RGB_MATRIX_ENABLE
       rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#    endif // RGB_MATRIX_ENABLE
        */
    }
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
}

// clang-format off
void leader_end_user(void) {
    // modes
    if (leader_sequence_two_keys(KC_N, KC_4)) {
        work_mode = !work_mode;
    } else
    if (leader_sequence_three_keys(KC_D, KC_O, KC_T)) {
        semicolon_mode = !semicolon_mode;
    } else
    if (leader_sequence_four_keys(KC_S, KC_M, KC_L, KC_N)) {
        semicolon_mode = !semicolon_mode;
    } else
    if (leader_sequence_three_keys(KC_A, KC_N, KC_D)) {
        ampersand_mode = !ampersand_mode;
    } else
    if (leader_sequence_two_keys(KC_D, KC_W)) {
            delete_word_mode = !delete_word_mode;
    } else
    if (leader_sequence_four_keys(KC_S, KC_M, KC_S, KC_P)) {
            smart_space_mode = !smart_space_mode;
    } else
    // toggles
    if (leader_sequence_three_keys(KC_V, KC_I, KC_M)) {
            toggle_vim_mode();
    } else
    if (leader_sequence_five_keys(KC_C, KC_O, KC_M, KC_B, KC_O)) {
            combo_toggle();
    } else

    // layers
    if (leader_sequence_two_keys(KC_K, KC_B)) {
            layer_on(_KEYBOARD);
    } else
    if (leader_sequence_three_keys(KC_7, KC_2, KC_7)) {
            layer_on(_SECRET);
    } else

    // shortcuts
    if (leader_sequence_two_keys(KC_F, KC_L)) { // bootloader
            reset_keyboard();
    }
    if (leader_sequence_three_keys(KC_R, KC_D, KC_P)) {
                call_keycode(SH_RMDT);
    } else
    if (leader_sequence_two_keys(KC_C, KC_P)) {
                call_keycode(SM_COPY);
    } else
    if (leader_sequence_two_keys(KC_C, KC_T)) {
                call_keycode(SM_CUT);
    } else
    if (leader_sequence_two_keys(KC_P, KC_S)) {
                call_keycode(SM_PASTE);
    } else
    if (leader_sequence_two_keys(KC_S, KC_V)) {
                call_keycode(SM_SAVE);
    }
}
// clang-format on

// TODO investigate what characters need to be added
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case TD(TBW):
        case TD(TDW):

        // special keys that need to not break caps word but apply shift on their own
        case KC_TH:
        case KC_IN:
        case KC_PH:
        case KC_SH:
        case KC_WH:
        case KC_CH:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

// Define the tapping term for the custom keycode
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM; // Default tapping term
    }
}

bool process_combo_key_release(uint16_t combo_INDXex, combo_t *combo, uint8_t key_INDXex, uint16_t keycode) {
    // TODO keep in sync with combos
    switch (combo_INDXex) {
        case CB_GH:
        case CB_LY:
        case CB_THE:
        case CB_AND:
        case CB_FOR:
        case CB_YOU:
        case CB_INGL:
        case CB_INGR:
        case CB_SION:
        case CB_TION:
        case CB_OULD:
            if (smart_space_mode) {
                last_smart_space = true;
            }
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _CTRLPR, _ALTPR, _GUIPR);
    // TODO might as well find an excuse to put layer taps on my spaces and add a tri layer here
    return state;
}
