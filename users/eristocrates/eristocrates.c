#include "eristocrates.h"
#include "_wait.h"
#include "action.h"
#include "action_layer.h"
#include "action_util.h"
#include "config.h"
#include "features/eristocrates/modal_keys.h"
#include "keycodes.h"
#include "repeat_key.h"
#include "keymap_us.h"
#include "quantum.h"
#include "secret.h"
#include "features/andrewjrae/qmk-vim/vim.h"
#include "features/andrewjrae/qmk-vim/motions.h"
#include "features/andrewjrae/qmk-vim/modes.h"
#include "features/possumvibes/smart_layer.h"
#include "features/eristocrates/utilities.h"
#include "features/eristocrates/rgb_matrix_stuff.h"
#include "features/anantoghosh/skip_bigrams.h"
#include "features/getreuer/layer_lock.h"
// #include "features/getreuer/custom_shift_keys.h"
#include "features/callum/oneshot.h"
#include "features/callum/swapper.h"
#include "eristocrates_keycodes.h"
// #include "smtd_keycodes.h"
#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"
#include "send_string_keycodes.h"
#include "transactions.h"
//----------------------------------------------------------
// RGB Matrix naming
#include <rgb_matrix.h>
#include <stdint.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
#undef RGB_MATRIX_EFFECT
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char *rgb_matrix_names(uint8_t effect) { // disgusting hack to avoid collision with rgb_matrix_stuff
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
#undef RGB_MATRIX_EFFECT
        default:
            return "UNKNOWN";
    }
}
// TODO collect any and all state into config
typedef union {
    uint16_t raw;
    struct {
        uint8_t    color_scheme_index : 4;
        vim_mode_t vim_mode_index : 3;
        bool       vim_emulation : 1;
        bool       semicolon_mode : 1;
        bool       smart_space_mode : 1;
        bool       autopair_mode : 1;
        bool       ampersand_mode : 1;
        bool       delete_word_mode : 1;
        bool       kana_input_mode : 1;
        bool       work_mode : 1;
        bool       roll_reversal_mode : 1;
    };
} keeb_state_config_t;

enum syncs {
    SYNC_FORCE,
    SYNC_KEEB_STATE,
    SYNC_COLOR_SCHEME,
    SYNC_VIM_MODE,
};
// _Static_assert(sizeof(keeb_state_config_t) == sizeof(uint32_t), "keeb_state EECONFIG out of spec.");
// TODO actually use all of these
// clang-format off
keeb_state_config_t keeb_state = {
    .color_scheme_index = 0,
    .vim_mode_index = INSERT_MODE,
    .vim_emulation = false,
    .semicolon_mode = 0,
    .smart_space_mode = 0,
    .autopair_mode = 0,
    .ampersand_mode = 0,
    .delete_word_mode = 0,
    .kana_input_mode = 0,
    .work_mode = 0,
    .roll_reversal_mode = 0
};
// clang-format on

static uint8_t color_scheme_max;
static uint8_t current_mode;
uint16_t       transport_keeb_state         = 0;
uint16_t       transport_color_scheme_index = 0;
static uint8_t roll_reversal_state          = 0;
// https://leanrada.com/notes/my-personalised-keyboard/
// https://github.com/Kalabasa/qmk_firmware/blob/2d1608287bb8b52669255266472975875f7c2423/keyboards/lily58/keymaps/Kalabasa/main.c#L56
const uint16_t bitwise_f_keys[]   = {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5};
uint8_t        NUM_BITWISE_F_KEYS = sizeof(bitwise_f_keys) / sizeof(uint16_t);
const uint16_t bitwise_num_keys[] = {
    BIN___1, BIN___2, BIN___4, BIN___8, BIN__16, BIN__32, BIN__64, BIN_128, BIN_256, BIN_512,

};
uint8_t NUM_bitwise_num_KEYS = sizeof(bitwise_num_keys) / sizeof(uint16_t);

// taken from https://github.com/moutis/HandsDown/blob/9e4bf52d013d5a7981d61ff1f5f36d9a3144aa73/moutis.c#L17
uint16_t     preprior_keycode = KC_NO;
uint16_t     prior_keycode    = KC_NO;
keyrecord_t *last_record;
keypos_t     last_key = {0, 0};
// uint16_t     last_keydown = 0; // timer of keydown for adaptive threshhold.

// https://getreuer.info/posts/keyboards/triggers/index.html#when-another-key-is-held
static bool is_back_held   = false;
static bool is_down_held   = false;
static bool is_jump_held   = false;
static bool is_front_held  = false;
static bool is_bb_motion   = false;
static bool is_dd_motion   = false;
static bool is_ff_motion   = false;
static bool is_jj_motion   = false;
static bool is_bf_motion   = false;
static bool is_fb_motion   = false;
static bool is_dj_motion   = false;
static bool is_jd_motion   = false;
static bool is_qcf_motion  = false;
static bool is_qcb_motion  = false;
static bool is_dpf_motion  = false;
static bool is_dpb_motion  = false;
static bool is_dqcf_motion = false;
static bool is_dqcb_motion = false;
static bool is_hcf_motion  = false;
static bool is_hcb_motion  = false;
static bool is_hcbf_motion = false;
static bool is_hcfb_motion = false;
static void clear_motions(void) {
    /*
    is_back_held   = false;
    is_down_held   = false;
    is_jump_held   = false;
    is_front_held  = false;
    */
    is_bb_motion   = false;
    is_dd_motion   = false;
    is_ff_motion   = false;
    is_jj_motion   = false;
    is_bf_motion   = false;
    is_fb_motion   = false;
    is_dj_motion   = false;
    is_jd_motion   = false;
    is_qcf_motion  = false;
    is_qcb_motion  = false;
    is_dpf_motion  = false;
    is_dpb_motion  = false;
    is_dqcf_motion = false;
    is_dqcb_motion = false;
    is_hcf_motion  = false;
    is_hcb_motion  = false;
    is_hcbf_motion = false;
    is_hcfb_motion = false;
}

bool is_char_pending      = false;
bool is_text_object       = false;
bool pending_insert       = false;
bool restore_motion_layer = false;

// swapper
bool sw_win_active = false;

// piercing holds
uint16_t tap_keycode;
uint16_t hold_keycode;
uint16_t hold_mod;

// for SCN
bool is_scan_toggled = false;

uint8_t saved_mods = 0; // for custom shift keys

uint8_t  current_slice   = VIM;
uint16_t sl_indx_keycode = KC_NO;
uint16_t sl_mdle_keycode = KC_NO;
uint16_t sl_ring_keycode = KC_NO;
uint16_t sl_pnky_keycode = KC_NO;

static uint16_t input_buffer[INPUT_BUFFER_SIZE]   = {KC_NO};
static uint16_t motion_buffer[MOTION_BUFFER_SIZE] = {KC_NO}; // holds time of all keydowns of the input buffer
static uint16_t input_buffer_deadline             = 0;
static uint16_t motion_buffer_deadline            = 0;
static void     clear_input_buffer(void) {
    memset(input_buffer, 0, sizeof(input_buffer)); // Set all zeros (KC_NO).
}
static void clear_motion_buffer(void) {
    memset(motion_buffer, 0, sizeof(motion_buffer)); // Set all zeros (KC_NO).
    clear_motions();
}

// Generates a pseudorandom value in 0-255.
static uint8_t simple_rand(void) {
    static uint16_t random = 1;
    random *= UINT16_C(36563);
    return (uint8_t)(random >> 8);
}

static bool process_quopostrokey(uint16_t keycode, keyrecord_t *record) {
    static bool within_word = false;

    if (keycode == KC_QUOP) {
        if (record->event.pressed) {
            if (within_word) {
                tap_code(KC_QUOT);
            } else { // SEND_STRING("\"\"" SS_TAP(X_LEFT));
                // send_autopair(KC_DQUO, KC_DQUO, record);
                tap_code16(KC_DQUO);
            }
        }
        return false;
    }

    switch (keycode) { // Unpack tapping keycode for tap-hold keys.
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->tap.count == 0) {
                return true;
            }
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
#    ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) {
                return true;
            }
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
#    endif // NO_ACTION_LAYER
#endif // NO_ACTION_TAPPING
    }

    // Determine whether the key is a letter.
    switch (keycode) {
        case KC_A ... KC_Z:
        case SFSHL_R:
        case ALT___T:
            within_word = true;
            break;

        default:
            within_word = false;
    }

    // disgusting hack to account for no option to ignore arcane key
    // TODO incorporate ignore functionality
    // Determine whether the key is a letter.
    switch (get_last_keycode()) {
        case KC_A ... KC_Z:
            within_word = true;
            break;

        default:
            within_word = false;
    }

    return true;
}

const key_override_t dot_override       = ko_make_basic(MOD_MASK_SHIFT, RMEH_DT, KC_EXLM); // . !
const key_override_t comma_override     = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUES); // , ?
const key_override_t quote_override     = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_DQUO); // ' "
const key_override_t minus_override     = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_NEQL); // - !=
const key_override_t grave_override     = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_ASTR);  // ` *
const key_override_t tilde_override     = ko_make_basic(MOD_MASK_SHIFT, KC_TILD, KC_CIRC); // ~ ^
const key_override_t r_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_ESLH); // ] \/

// clang-format off
// This globally defines all key overrides to be used
const key_override_t  *key_overrides_list[] = {
&dot_override,
&comma_override,
&quote_override,
&minus_override,
&grave_override,
&tilde_override,
&r_bracket_override,
NULL};

// clang-format on
const key_override_t **key_overrides = key_overrides_list;

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
                tap_code(KC_BSPC);
                unregister_code(KC_LCTL);
            } else {
                register_code(KC_BSPC);
            }
            break;
        case TD_DOUBLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                register_code(KC_BSPC);
            } else {
                register_code(KC_LCTL);
                tap_code(KC_BSPC);
                unregister_code(KC_LCTL);
            }
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
                clear_oneshot_mods();
                clear_mods();
            } else {
                unregister_code(KC_BSPC);
            }
            break;
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                unregister_code(KC_BSPC);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_BSPC);
                clear_oneshot_mods();
                clear_mods();
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
                tap_code(KC_DEL);
                unregister_code(KC_LCTL);
            } else {
                register_code(KC_DEL);
            }
            break;
        case TD_DOUBLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                tap_code(KC_DEL);
            } else {
                register_code(KC_LCTL);
                tap_code(KC_DEL);
                unregister_code(KC_LCTL);
            }
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
                clear_oneshot_mods();
                clear_mods();
            } else {
                unregister_code(KC_DEL);
            }
            break;
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                unregister_code(KC_DEL);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_DEL);
                clear_oneshot_mods();
                clear_mods();
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
// static keyrecord_t prev_record;

// TODO move this into my own feature

static bool update_motion_buffer(uint16_t keycode, const keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        uprintf("update_motion_buffer pressed: \t%s\t col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", key_name(keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    } // else {
    //    uprintf("update_motion_buffer keyup: \t%s\t col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", key_name(keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    //}
#endif
    if (!record->event.pressed) {
        return false;
    }

    if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
        clear_motion_buffer(); // Avoid interfering with hotkeys.
        return false;
    }

    // Handle tap-hold keys.
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) {
                return false;
            }
            keycode &= 0xff; // Get tapping keycode.
    }

    switch (keycode) {
        // motion inputs for vim
        case MI_DOWN:
        case MI_BACK:
        case MI_FRNT:
        case MI_JUMP:
        // vim "buttons"
        case VM_LEFT:
        case VM_DOWN:
        case VM___UP:
        case VM_RGHT:
        case VM_NTRL:
            break;

        case KC_LSFT: // These keys don't type anything on their own.
        case KC_RSFT:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return false;

        default: // Avoid acting otherwise, particularly on navigation keys.
            clear_motion_buffer();
            return false;
    }

    // Slide the buffer left by one element.
    memmove(motion_buffer, motion_buffer + 1, (MOTION_BUFFER_SIZE - 1) * sizeof(*motion_buffer));

    motion_buffer[MOTION_BUFFER_SIZE - 1] = keycode;
    motion_buffer_deadline                = record->event.time + MOTION_BUFFER_TIMEOUT_MS;
    return true;
}

// Handles one event. Returns true if the key was appended to `recent`.
static bool update_input_buffer(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }

    if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
        clear_input_buffer(); // Avoid interfering with hotkeys.
        return false;
    }

    // Handle tap-hold keys.
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) {
                return false;
            }
            keycode &= 0xff; // Get tapping keycode.
    }

    switch (keycode) {
        case KC_A ... KC_SLASH: // These keys type letters, digits, symbols.
            break;

        case KC_LSFT: // These keys don't type anything on their own.
        case KC_RSFT:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return false;

        default: // Avoid acting otherwise, particularly on navigation keys.
            clear_input_buffer();
            return false;
    }

    // Slide the buffer left by one element.
    memmove(input_buffer, input_buffer + 1, (INPUT_BUFFER_SIZE - 1) * sizeof(*input_buffer));

    input_buffer[INPUT_BUFFER_SIZE - 1] = keycode;
    input_buffer_deadline               = record->event.time + INPUT_BUFFER_TIMEOUT_MS;
    return true;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t prev_keycode;
    if (record->event.pressed) {
        // store previous keycode for instant tap decisions
        preprior_keycode = prev_keycode;
        prev_keycode     = next_keycode;

        // Cache the next input for mod-tap decisions
        next_keycode = keycode;
        next_record  = *record;
        // last_keydown = timer_read();
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
            if (is_caps_word_on()) {
                register_code(KC_LSFT);
            }
            tap_code16(long_press_keycode);
            if (is_caps_word_on()) {
                unregister_code(KC_LSFT);
            }
        }
        return false; // Skip default handling.
    }
    return true; // Continue default handling.
}

/*
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
void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(LWKEY_K, KC_K, KC_LEFT_GUI)
        SMTD_MT(LTALT_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(LCTRL_N, KC_N, KC_LEFT_CTRL)
        SMTD_MT(LSHFT_D, KC_D, KC_LSFT)
        SMTD_MT(RWKEY_H, KC_H, KC_RIGHT_GUI)
        SMTD_MT(RTALT_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT(RCTRL_E, KC_E, KC_RIGHT_CTRL)
        SMTD_MT(RSHFT_A, KC_A, KC_RSFT)
    }
}
*/
// TODO blindly calling false on these keycodes has prevented things like caps_word_press_user from working. Make sure to actually evaluate what keycodes do not require further processingr
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /*
    static bool     tapped    = false;
    static uint16_t tap_timer = 0;
    */

    uint16_t basic_keycode      = extract_basic_keycode(keycode, record, false);
    uint16_t last_basic_keycode = extract_basic_keycode(get_last_keycode(), last_record, false);
    bool     is_shifted         = (get_mods() & MOD_MASK_SHIFT) || (get_oneshot_mods() & MOD_MASK_SHIFT);

    slice_state_t slices[] = {
        VIM,
        ARROW,
        NAV,
        SLICE_END,
    };

    switch (current_slice) {
        case VIM:
            sl_indx_keycode = KC_H;
            sl_mdle_keycode = KC_J;
            sl_ring_keycode = KC_K;
            sl_pnky_keycode = KC_L;
            break;
        case ARROW:
            sl_indx_keycode = KC_LEFT;
            sl_mdle_keycode = KC_DOWN;
            sl_ring_keycode = KC_UP;
            sl_pnky_keycode = KC_RIGHT;
            break;
        case NAV:
            sl_indx_keycode = KC_HOME;
            sl_mdle_keycode = KC_PGDN;
            sl_ring_keycode = KC_PGUP;
            sl_pnky_keycode = KC_END;
            break;
    }
#ifdef CONSOLE_ENABLE
    // if (record->event.pressed) uprintf("process_last_record_user: last_basic_keycode: 0x%04X, last key name: %s, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", last_basic_keycode, key_name(last_basic_keycode, false), last_record->event.key.col, last_record->event.key.row, last_record->event.pressed, last_record->event.time, last_record->tap.interrupted, last_record->tap.count);
    // if (record->event.pressed) uprintf("process_record_user: basic_keycode: 0x%04X, key name: %s, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", basic_keycode, key_name(basic_keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    if (record->event.pressed) uprintf("process_record_user: keycode: 0x%04X, key name: %s, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, key_name(keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    // TODO see if i can ifdef this
    /*
      if (!process_achordion(keycode, record)) { return false; }

    */
    // TODO find where this gets used
    // I think it was part of the string mappings?
    // TODO send github issue on how destructive this is to get_last_keycode()
    /*
    if (!process_smtd(keycode, record)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
    */

    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    if (!process_skip_bigrams(keycode, record)) {
        return false;
    }
    if (binary_mode && !process_bitwise_num(keycode, record)) return false;
    if (!process_bitwise_f(keycode, record)) return false;
    if (!process_quopostrokey(keycode, record)) {
        return false;
    }

    process_nshot_state(keycode, record);
    if (vim_emulation_enabled() && !process_vim_mode(keycode, record)) {
        return !vim_emulation_enabled();
    }

    process_mod_lock(keycode, record);
    if (!process_layer_lock(keycode, record, LR_LOCK)) {
        return false;
    }
    /*

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_RCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS__ALT, keycode, record);
    update_oneshot(&os_gui_state, KC_LCMD, OS__GUI, keycode, record);
    */

    process_layermodes(keycode, record);

    /*------------------------------input buffer------------------------------*/
    if (update_input_buffer(keycode, record)) {
        // "qumk" to qmk
        if (input_buffer[INPUT_BUFFER_SIZE - 3] == KC_Q && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_M && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_K) {
            SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC) SS_TAP(X_BSPC) "qmk");
            return false;
        }
        // "squl" to sql
        if (input_buffer[INPUT_BUFFER_SIZE - 3] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_Q && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_L) {
            SEND_STRING(SS_TAP(X_BSPC) "l");
            return false;
        }

        // konami code
        if (input_buffer[INPUT_BUFFER_SIZE - 10] == KC_R && input_buffer[INPUT_BUFFER_SIZE - 9] == KC_R && input_buffer[INPUT_BUFFER_SIZE - 8] == KC_T && input_buffer[INPUT_BUFFER_SIZE - 7] == KC_T && input_buffer[INPUT_BUFFER_SIZE - 6] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 5] == KC_N && input_buffer[INPUT_BUFFER_SIZE - 4] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 3] == KC_N && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_B && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_A) {
            register_code(KC_LSFT);
            tap_code(KC_HOME);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
            // SEND_STRING("30 lives");
            layer_on(_SECRET);
            return false;
        }
    }
    switch (keycode) {
        case LWKEY_C:
        case LTALT_S:
        case LCTRL_T:
        case LSHFT_N:
        case RSHFT_U:
        case RCTRL_A:
        case RTALT_I:
        case RWKEY_H:
        case SFSHL_R:
        case SFSHR_E:
            if ((IS_LAYER_ON(_SHIFTISHL) || IS_LAYER_ON(_SHIFTISHR)) && record->tap.count && record->event.pressed) {
                register_code(KC_LSFT);
                tap_code16(basic_keycode);
                unregister_code(KC_LSFT);
                pointer_mode_disable();
                return false;
            }
            return true;

        case KC_A ... KC_R:
        case KC_T ... KC_Z:

            tap_keycode = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            if ((IS_LAYER_ON(_SHIFTISHL) || IS_LAYER_ON(_SHIFTISHR)) && record->event.pressed) {
                if (IS_LAYER_ON(_SHIFTISHR)) {
                    switch (keycode) {
                        case KC_H:
                        case KC_J:

                        case KC_K:
                        case KC_L:
                            return true;
                    }
                }
                register_code(KC_LSFT);
                tap_code(tap_keycode);
                unregister_code(KC_LSFT);
                return false;
            }
            return true;

        case KC_S:
            // TODO decide what to do with last smart space
            tap_keycode = keymap_key_to_keycode(get_highest_layer(default_layer_state), (keypos_t){record->event.key.col, record->event.key.row});
            if ((IS_LAYER_ON(_SHIFTISHL) || IS_LAYER_ON(_SHIFTISHR)) && record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(tap_keycode);
                unregister_code(KC_LSFT);
                return false;
            } else if (record->event.pressed && last_smart_space) {
                tap_code(KC_BSPC);
                tap_code(KC_S);
                tap_code(KC_SPC);
            }
            return true;

        case KC_P00:
            if (record->event.pressed) {
                SEND_STRING("00");
            }
            return false;

            /*------------------------------slice------------------------------*/
        case SL_INDX:
            if (record->event.pressed) {
                register_code16(sl_indx_keycode);
            } else {
                unregister_code16(sl_indx_keycode);
            }
            return false;
        case SL_MDLE:
            if (record->event.pressed) {
                register_code16(sl_mdle_keycode);
            } else {
                unregister_code16(sl_mdle_keycode);
            }
            return false;
        case SL_RING:
            if (record->event.pressed) {
                register_code16(sl_ring_keycode);
            } else {
                unregister_code16(sl_ring_keycode);
            }
            return false;
        case SL_PNKY:
            if (record->event.pressed) {
                register_code16(sl_pnky_keycode);
            } else {
                unregister_code16(sl_pnky_keycode);
            }
            return false;
        case SL_STEP:
            if (record->event.pressed) {
                uint8_t index = is_shifted ? current_slice - 1 < 0 ? SLICE_END - 1 : current_slice - 1 : current_slice + 1 == SLICE_END ? 0 : current_slice + 1;
                current_slice = slices[index];
            }
            return false;
        case SL_RSTP:
            if (record->event.pressed) {
                uint8_t index = current_slice - 1 < 0 ? SLICE_END - 1 : current_slice - 1;
                current_slice = slices[index];
            }
            return false;

            /*------------------------------Pointer codes ------------------------------*/

        case KC_DBCL:
            if (record->event.pressed) {
                tap_code(KC_BTN1);
                wait_ms(180);
                tap_code(KC_BTN1);
            }
            return false;
        case KC_DGSC:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) charybdis_set_pointer_dragscroll_enabled(!charybdis_get_pointer_dragscroll_enabled());
            } else { // Key is being held.
                charybdis_set_pointer_dragscroll_enabled(record->event.pressed);
            }
            return false; // Skip default handling.
        case KC_SNPE:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) charybdis_set_pointer_sniping_enabled(!charybdis_get_pointer_sniping_enabled());
            } else { // Key is being held.
                charybdis_set_pointer_sniping_enabled(record->event.pressed);
            }
            return false; // Skip default handling.
        /*------------------------------Break pointer mode on hold of tap hold------------------------------*/
        case ALTLSPC:
            if (record->event.pressed) {
                pointer_mode_disable();
            }
            return true;

            /*------------------------------consequtive keys------------------------------*/
            /* ya now i see why tap dances need tapping term（︶^︶）
            BUT! from that realization i still think this can be pretty useful
            if (!process_consecutive_key(record, keycode, KC_LCTL)) {
                return false;
            }
            return true;
            */
        /*------------------------------smart layers------------------------------*/
        case POINTERMODE:
            return pointer_mode_enable(record);
        case NUMPAD:
            layer_on(_NUMPAD);
            return false;
        case BITWISE:
            layer_on(_BITNUM);
            return false;

        case K_CLEAR:
            clear_oneshot_mods();
            clear_mods();
            pointer_mode_disable();
            return false;

        case PANIC:
            clear_oneshot_mods();
            clear_mods();
            if (get_oneshot_layer() != 0) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            }
            layer_move(0);
            caps_word_off();
            return false;

            /*------------------------DIGRAPHS------------------------------*/
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
        case KC___WH:
            if (record->event.pressed) {
                send_string_with_caps_word("wh");
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
        // TODO decide if these are worth it
        case KC_LSPC:
            if (record->event.pressed) {
                tap_code(KC_SPC);
            }
            return true;
        case KC_RSPC:
            if (record->event.pressed) {
                tap_code(KC_SPC);
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
                if (is_scan_toggled) {
                    unregister_mods(MOD_BIT(KC_LSFT)); // Unregister Shift
                    is_scan_toggled = false;
                } else {
                    register_mods(MOD_BIT(KC_LSFT)); // Register Shift
                    is_scan_toggled = true;
                }
            }
            return false; // Skip all further processing of this key
        /*------------------------------semantic keys------------------------------*/
        // TODO figure out raw hid
        // TODO figure out appropriate shift overrides/holds for vim versions of semantic keys eg save tap/save all hold
        case SM_COPY:
            if (record->event.pressed) {
                // Send Ctrl+C for copy
                register_code(KC_LCTL);
                tap_code(KC_C);
                unregister_code(KC_LCTL);
            }
            return false;
        case SM_CUT:
            if (record->event.pressed) {
                // Send Ctrl+X for cut
                register_code(KC_LCTL);
                tap_code(KC_X);
                unregister_code(KC_LCTL);
            }
            return false;
        case SM_PASTE:
            if (record->event.pressed) {
                // Send Ctrl+V for paste
                register_code(KC_LCTL);
                tap_code(KC_V);
                unregister_code(KC_LCTL);
            }
            return false;
        case SM_SAVE:
            if (record->event.pressed) {
                // Send Ctrl+S for save
                register_code(KC_LCTL);
                tap_code(KC_S);
                unregister_code(KC_LCTL);
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

        case MD_A:
            if (record->event.pressed) {
                send_string_with_caps_word("A");
            }
            return true;
        case MD_I:
            if (record->event.pressed) {
                send_string_with_caps_word("I");
            }
            return true;
        case MD_PS:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'s");
            }
            return true;
        case MD_PLL:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'ll");
            }
            return true;
        case MD_PVE:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'ve");
            }
            return true;
        case MD_PT:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'t");
            }
            return true;
        case MD_PD:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'d");
            }
            return true;
        case MD_PM:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'m");
            }
            return true;
        case MD_PALL:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'all");
            }
            return true;
        case MD_SCLN:
            if (record->event.pressed) {
                tap_code(KC_SCLN);
            }
            return true;
        case MD_BSPC:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
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
            /*

        case KC_ENT:
            if (record->event.pressed) {
                if (work_mode) {
                    register_code(KC_LCTL);
                    tap_code(KC_H);
                    unregister_code(KC_LCTL);
                    return false;
                }
            }
            return false;
            */
        /*
                https://github.com/Kalabasa/qmk_firmware/blob/2d1608287bb8b52669255266472975875f7c2423/keyboards/lily58/keymaps/Kalabasa/main.c#L160-L167
        Put cursor inside after typing empty pair of brackets
        roll_reversal_state machine:
          (0) -- '[' down --> (1) -- ']' down --> (2) -- ']' up --> ((KC_LEFT))
           ^                   |                   |
           |                   | '[' up            | '[' or ']' up
           '---------------------------------------'
        */
        // roll in
        case KC_DQUO:
            if (record->event.pressed) {
                if (autopair_mode) {
                    send_autopair(KC_DQUO, KC_DQUO, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_DQUO);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
        case KC_QUOT:
            if (record->event.pressed) {
                if (autopair_mode) {
                    send_autopair(KC_QUOT, KC_QUOT, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_QUOT);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
        case KC_GRV:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("*");
                    return false;
                }

                if (autopair_mode) {
                    send_autopair(KC_GRV, KC_GRV, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_GRV);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
        case KC_LPRN:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("/*");
                    return false;
                }
                if (autopair_mode) {
                    send_autopair(KC_LPRN, KC_RPRN, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_LPRN);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
        case KC_LBRC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("/>");
                    return false;
                }

                if (autopair_mode) {
                    send_autopair(KC_LBRC, KC_RBRC, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_LBRC);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
        case KC_LCBR:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("{{/*");
                    tap_code(KC_ENT);
                    return false;
                }
                if (autopair_mode) {
                    send_autopair(KC_LCBR, KC_RCBR, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_LCBR);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;

        case KC_SCLN:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(";");
                    tap_code(KC_ENT);
                    return false;
                }
            }
            return true;
        case KC_SLSH:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("//");
                    return false;
                }
            }
            return true;
        case KC_COLN:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("::");
                    return false;
                }
            }
            return true;
        case KC_PIPE:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("||");
                    return false;
                }
            }
            return true;
        case KC_BSLS:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("\\");
                    return false;
                }
            }
            return true;
        case KC_LABK:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("<<");
                    return false;
                }
                if (autopair_mode) {
                    send_autopair(KC_LABK, KC_RABK, record);
                } else if (roll_reversal_mode) {
                    roll_reversal_state = 1;
                } else {
                    tap_code16(KC_LABK);
                }
            } else {
                if (roll_reversal_mode) {
                    roll_reversal_state = 0;
                }
            }
            return true;
            // roll out
        case KC_QUES:
            if (record->event.pressed) {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_QUES);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code16(KC_DQUO);
                        tap_code(KC_LEFT);
                    } else {
                        tap_code16(KC_QUES);
                    }
                }
            }
            return false;
        case KC_EXLM:
            if (record->event.pressed) {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_EXLM);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code16(KC_QUOT);
                        tap_code(KC_LEFT);
                    } else {
                        tap_code16(KC_EXLM);
                    }
                }
            }
            return false;
        case KC_RPRN:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("*/");
                    return false;
                }
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_RPRN);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code(KC_LEFT);
                        return false;
                    }
                }
            }
            return true;
        case KC_RBRC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("\\/");
                    return false;
                }
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_RBRC);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code(KC_LEFT);
                        return false;
                    }
                }
            }
            return true;
        case KC_RCBR:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("/*}}");
                    tap_code(KC_ENT);
                    return false;
                }
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_RCBR);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code(KC_LEFT);
                        return false;
                    }
                }
            }
            return true;
        case KC_RABK:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(">>");
                    return false;
                }
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_RABK);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code(KC_LEFT);
                        return false;
                    }
                }
            }
            return true;
        /*------------------------------arcane------------------------------*/
        case LTP_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("::");
                    return false;
                }
                tap_code16(process_top_left_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_COLN));
            }
            return true;
        case RTP_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("||");
                    return false;
                }
                tap_code16(process_top_right_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_PIPE));
            }
            return true;
        case LHM_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("{");
                    return false;
                }
                tap_code16(process_home_left_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_LPRN));
            }
            return true;
        case RHM_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("}");
                    return false;
                }
                tap_code16(process_home_right_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_RPRN));
            }
            return true;
        case LBM_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("\\\\");
                    return false;
                }
                tap_code16(process_bottom_left_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_BSLS)); // KC_WAVE (inuyasha ppl will get it)
            }
            return true;
        case RBM_ARC:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("//");
                    return false;
                }
                tap_code16(process_bottom_right_arcane(last_basic_keycode, last_key, last_keydown, get_last_mods(), KC_SLSH));
            }
            return true;

            // TODO replicate logic i was doing with autoshift via linger key
        case COM_ARC:
            if (record->event.pressed) {
                process_comma_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), last_keydown);
            }
            return false;
        case DOT_ARC:
            if (record->event.pressed) {
                process_dot_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), last_keydown);
            }
            return false;
        /*------------------------------secrets------------------------------*/
        case SECRET1: {
            if (record->event.pressed) {
                SEND_STRING(SECRET_ONE);
                tap_code(KC_ENT);
                layer_off(_SECRET);
            }
        }
            return false;
        case SECRET2: {
            if (record->event.pressed) {
                SEND_STRING(SECRET_TWO);
                tap_code(KC_ENT);
                layer_off(_SECRET);
            }
        }
            return false;
        /*------------------------------vim------------------------------*/
        case VIM_TOG:
            if (record->event.pressed) {
                toggle_vim_emulation();
                keeb_state.vim_emulation = !keeb_state.vim_emulation;
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

        /*-----------------------------other------------------------------*/
        case KC_RTAB:
            if (record->event.pressed) {
                tap_code(KC_TAB);
            }
            return true;
        case KC_LTAB:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            return true;
        case UP__DIR: // Types ../ to go up a directory on the shell.
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
        case CUR_DIR: // Types ./ to go up a directory on the shell.
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("../");
                    return false;
                }
                SEND_STRING("./");
            }
            return false;
        case HOM_DIR: // Types ~/ to go to home directory
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;
        case SRCHSEL: // Searches the current selection in a new tab.
            if (record->event.pressed) {
                // Mac users, change LCTL to LGUI.
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
            }
            return false;

        case KC_ESLH:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("/>");
                    return false;
                }
                SEND_STRING("\\/");
            }
            return false;
        case KC_DSLH:
            if (record->event.pressed) {
                SEND_STRING("//");
            }
            return false;
        case KC_DBSL:
            if (record->event.pressed) {
                SEND_STRING("\\\\");
            }
            return false;
        case KC_DPIP:
            if (record->event.pressed) {
                SEND_STRING("||");
            }
            return false;
        case KC_SARW:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("=>");
                    return false;
                }
                SEND_STRING("->");
            }
            return false;
        case KC_DARW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
        case KC_TGRV:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            return false;
        case KC_DAMP:
            if (record->event.pressed) {
                SEND_STRING("&&");
            }
            return false;
        case KC_NEQL:
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            return false;
        case KC_DEQL:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("!==");
                    return false;
                }
                SEND_STRING("==");
            }
            return false;
        case KCNDEQL:
            if (record->event.pressed) {
                SEND_STRING("!==");
            }
            return false;
        case KC_TEQL:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("!===");
                    return false;
                }
                SEND_STRING("===");
            }
            return false;
        case KCNTEQL:
            if (record->event.pressed) {
                SEND_STRING("!===");
            }
            return false;
        case KC_LEQL:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("<==");
                    return false;
                }
                SEND_STRING("<=");
            }
            return false;
        case KC_AMPR:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("&&");
                    return false;
                }
            }
            return true;
        case KC_PPLS:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("++");
                    return false;
                }
            }
            return true;
        case KC_PMNS:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING("--");
                    return false;
                }
            }
            return true;
        case KCDLEQL:
            if (record->event.pressed) {
                SEND_STRING("<==");
            }
            return false;
        case KC_GEQL:
            if (record->event.pressed) {
                if ((get_weak_mods() & MOD_MASK_SHIFT) || (get_mods() & MOD_MASK_SHIFT)) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(">==");
                    return false;
                }
                SEND_STRING(">=");
            }
            return false;
        case KCDGEQL:
            if (record->event.pressed) {
                SEND_STRING(">==");
            }
            return false;
        case KC_CEQL:
            if (record->event.pressed) {
                SEND_STRING(":=");
            }
            return false;
        case KC_DCLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
        case KC_DPLS:
            if (record->event.pressed) {
                SEND_STRING("++");
            }
            return false;
        case KC_DMNS:
            if (record->event.pressed) {
                SEND_STRING("--");
            }
            return false;
        case KC_LCCM:
            if (record->event.pressed) {
                SEND_STRING("/*");
            }
            return false;
        case KC_RCCM:
            if (record->event.pressed) {
                SEND_STRING("*/");
            }
            return false;
        case KC_LGCM:
            if (record->event.pressed) {
                SEND_STRING("{{/*");
            }
            return false;
        case KC_RGCM:
            if (record->event.pressed) {
                SEND_STRING("*/}}");
            }
            return false;
        case KCDLABK:
            if (record->event.pressed) {
                SEND_STRING("<<");
            }
            return false;
        case KCDRABK:
            if (record->event.pressed) {
                SEND_STRING(">>");
            }
            return false;
        case KC_RTAG:
            if (record->event.pressed) {
                SEND_STRING("/>");
            }
            return false;
        case KC_DTCM:
            if (record->event.pressed) {
                SEND_STRING(".com");
            }
            return false;
        case KC_GMIL:
            if (record->event.pressed) {
                SEND_STRING("@gmail.com");
            }
            return false;

        case KC_DTGV:
            if (record->event.pressed) {
                SEND_STRING(".gov");
            }
            return false;
        case RGX_NCG:
            if (record->event.pressed) {
                SEND_STRING("(?:)");
                tap_code(KC_LEFT);
            }
            return false;
        case RGX_PLA:
            if (record->event.pressed) {
                SEND_STRING("(?=)");
                tap_code(KC_LEFT);
            }
            return false;
        case RGX_NLA:
            if (record->event.pressed) {
                SEND_STRING("(?!)");
                tap_code(KC_LEFT);
            }
            return false;
        case RGX_PLB:
            if (record->event.pressed) {
                SEND_STRING("(?<=)");
                tap_code(KC_LEFT);
            }
            return false;
        case RGX_NLB:
            if (record->event.pressed) {
                SEND_STRING("(?<!)");
                tap_code(KC_LEFT);
            }
            return false;
        case KC_ELIP:
            if (record->event.pressed) {
                SEND_STRING("...");
            }
            return false;

            /*------------------------------ ngram keys ------------------------------*/
        case NG_ATE:
            if (record->event.pressed) {
                SEND_STRING("ate");
            }
            return false;
        case NG_ANCE:
            if (record->event.pressed) {
                SEND_STRING("ance");
            }
            return false;
        case NG_BL:
            if (record->event.pressed) {
                SEND_STRING("bl");
            }
            return false;
        case NG_BY:
            if (record->event.pressed) {
                SEND_STRING("by");
            }
            return false;
        case NG_COM:
            if (record->event.pressed) {
                SEND_STRING("com");
            }
            return false;
        case NG_CON:
            if (record->event.pressed) {
                SEND_STRING("con");
            }
            return false;
        case NG_DON:
            if (record->event.pressed) {
                SEND_STRING("don");
            }
            return false;
        case NG_DAY:
            if (record->event.pressed) {
                SEND_STRING("day");
            }
            return false;
        case NG_ERS:
            if (record->event.pressed) {
                SEND_STRING("ers");
            }
            return false;
        case NG_FRO:
            if (record->event.pressed) {
                SEND_STRING("fro");
            }
            return false;
        case NG_FUL:
            if (record->event.pressed) {
                SEND_STRING("ful");
            }
            return false;
        case NG_GER:
            if (record->event.pressed) {
                SEND_STRING("ger");
            }
            return false;
        case NG_GRE:
            if (record->event.pressed) {
                SEND_STRING("gre");
            }
            return false;
        case NG_HER:
            if (record->event.pressed) {
                SEND_STRING("her");
            }
            return false;
        case NG_HEA:
            if (record->event.pressed) {
                SEND_STRING("hea");
            }
            return false;
        case NG_IN:
            if (record->event.pressed) {
                SEND_STRING("in");
            }
            return false;
        case NG_ING:
            if (record->event.pressed) {
                SEND_STRING("ing");
            }
            return false;
        case NG_JOY:
            if (record->event.pressed) {
                SEND_STRING("joy");
            }
            return false;
        case NG_JECT:
            if (record->event.pressed) {
                SEND_STRING("ject");
            }
            return false;
        case NG_KNO:
            if (record->event.pressed) {
                SEND_STRING("kno");
            }
            return false;
        case NG_CK:
            if (record->event.pressed) {
                SEND_STRING("ck");
            }
            return false;
        case NG_LIN:
            if (record->event.pressed) {
                SEND_STRING("lin");
            }
            return false;
        case NG_LEA:
            if (record->event.pressed) {
                SEND_STRING("lea");
            }
            return false;
        case NG_MAN:
            if (record->event.pressed) {
                SEND_STRING("man");
            }
            return false;
        case NG_MEN:
            if (record->event.pressed) {
                SEND_STRING("men");
            }
            return false;
        case NG_NTI:
            if (record->event.pressed) {
                SEND_STRING("nti");
            }
            return false;
        case NG_NTE:
            if (record->event.pressed) {
                SEND_STRING("nte");
            }
            return false;
        case NG_OME:
            if (record->event.pressed) {
                SEND_STRING("ome");
            }
            return false;
        case NG_ONE:
            if (record->event.pressed) {
                SEND_STRING("one");
            }
            return false;
        case NG_PRO:
            if (record->event.pressed) {
                SEND_STRING("pro");
            }
            return false;
        case NG_PLA:
            if (record->event.pressed) {
                SEND_STRING("pla");
            }
            return false;
        case NG_QUA:
            if (record->event.pressed) {
                SEND_STRING("qua");
            }
            return false;
        case NG_QUE:
            if (record->event.pressed) {
                SEND_STRING("que");
            }
            return false;
        case NG_RAT:
            if (record->event.pressed) {
                SEND_STRING("rat");
            }
            return false;
        case NG_STR:
            if (record->event.pressed) {
                SEND_STRING("str");
            }
            return false;
        case NG_STI:
            if (record->event.pressed) {
                SEND_STRING("sti");
            }
            return false;
        case NG_TER:
            if (record->event.pressed) {
                SEND_STRING("ter");
            }
            return false;
        case NG_TED:
            if (record->event.pressed) {
                SEND_STRING("ted");
            }
            return false;
        case NG_UST:
            if (record->event.pressed) {
                SEND_STRING("ust");
            }
            return false;
        case NG_ULD:
            if (record->event.pressed) {
                SEND_STRING("uld");
            }
            return false;
        case NG_VES:
            if (record->event.pressed) {
                SEND_STRING("ves");
            }
            return false;
        case NG_VEN:
            if (record->event.pressed) {
                SEND_STRING("ven");
            }
            return false;
        case NG_WAY:
            if (record->event.pressed) {
                SEND_STRING("way");
            }
            return false;
        case NG_WAS:
            if (record->event.pressed) {
                SEND_STRING("was");
            }
            return false;
        case NG_XPL:
            if (record->event.pressed) {
                SEND_STRING("xpl");
            }
            return false;
        case NG_XPE:
            if (record->event.pressed) {
                SEND_STRING("xpe");
            }
            return false;
        case NG_YTH:
            if (record->event.pressed) {
                SEND_STRING("yth");
            }
            return false;
        case NG_YEA:
            if (record->event.pressed) {
                SEND_STRING("yea");
            }
            return false;
        case NG_ZED:
            if (record->event.pressed) {
                SEND_STRING("zed");
            }
            return false;

        // TODO explore this fancy key
        case FANCY_KEY:
            if (record->tap.count > 0) { // Key is being tapped.
                if (record->event.pressed) {
                    // Handle tap press event...
                } else {
                    // Handle tap release event...
                }
            } else { // Key is being held.
                if (record->event.pressed) {
                    // Handle hold press event...
                } else {
                    // Handle hold release event...
                }
            }
            return false; // Skip default handling.
        case UCHAPPY:     // Types a happy random emoji.
                          // TODO set up wincompose
            if (record->event.pressed) {
                static const char *emojis[]   = {"🤩", "🌞", "👾", "👍", "😁"};
                const int          NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

                // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
                uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

                // Don't pick the same emoji twice in a row.
                static uint8_t last_index = 0;
                if (index >= last_index) {
                    ++index;
                }
                last_index = index;

                // Produce the emoji.
                send_unicode_string(emojis[index]);
            }
            return false;
        case RGB_MDE:

#ifdef CONSOLE_ENABLE

            if (record->event.pressed) {
                uprintf("rgb_matrix_get_mode(): %d\n", rgb_matrix_get_mode());
                uprintf("RGB_MATRIX_EFFECT_BREATHING: %d\n", RGB_MATRIX_EFFECT_BREATHING);
                uprintf("RGB_MATRIX_EFFECT_BAND_PINWHEEL_VAL: %d\n", RGB_MATRIX_EFFECT_BAND_PINWHEEL_VAL);
            }
#endif

        case CS__STP:
            if (record->event.pressed) {
                uint8_t index                 = keeb_state.color_scheme_index + 1 > 7 ? 0 : keeb_state.color_scheme_index + 1;
                keeb_state.color_scheme_index = index;
                // uint8_t color_scheme_max = sizeof(color) / sizeof(nshot_state_t);
            }
            return false;
        case CS_RSTP:
            if (record->event.pressed) {
                uint8_t index                 = keeb_state.color_scheme_index - 1 < 0 ? 6 : keeb_state.color_scheme_index - 1;
                keeb_state.color_scheme_index = index;
                // uint8_t color_scheme_max = sizeof(color) / sizeof(nshot_state_t);
            }
            return false;
        case KC_ESC:
            if (IS_LAYER_ON(_POINTER)) {
                pointer_mode_disable();
            }
            tap_code(KC_ESC);
            return false;
        case SKP_GRM:
            return false;
        default:
            return true; // Process all other keycodes normally
    }
    /*
    // https://getreuer.info/posts/keyboards/triggers/index.html
    // TODO figure out how to make this work via main switch cases
    if (keycode == KC_TEST) {
        if (tapped && !timer_expired(record->event.time, tap_timer)) {
            // The key was double tapped.
            clear_mods(); // If needed, clear the mods.
                          // Do something interesting...
        }
        tapped    = true;
        tap_timer = record->event.time + TAPPING_TERM;
    } else {
        // On an event with any other key, reset the double tap state.
        tapped = false;
    }
    */

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // TODO try moving smart space cases here
            case KC_QUES:
            case KC_EXLM:
                if (smart_space_mode) {
                    tap_code(KC_SPC);
                }
                last_smart_space = true;
                break;
            case MD_SCLN:

                if (smart_space_mode) {
                    tap_code(KC_ENT);
                    last_smart_space = true;
                }
                break;
            default:
                last_smart_space = false;
        }

        // vim {char} https://neovim.io/doc/user/intro.html#%7Bchar1-char2%7D
        switch (keycode) {
            // top row
            case KC____X:
            case KC____V:
            case KC____G:
            case KC____M:
            case KC____P:
            case KC____U:
            case KC____O:
            case KC____Y:
            case KC____B:
            case KC____Z:
                // home row
            case KC____J:
            case KC____K:
            case KC____S:
            case KC____N:
            case KC____D:
            case KC____A:
            case KC____E:
            case KC____I:
            case KC____H:
            case TH___QU:
                // bottom row
            case KC____W:
            case KC____F:
            case KC____L:
            case KC____C:
                // thumb row
            case SFSHL_R:
            case ALTLSPC:
            case ALTRSPC:
            case ALT___T:
            case KC_ESC:
                if (is_char_pending) {
                    is_char_pending = false;
                    set_vim_mode(NORMAL_MODE);
                    clear_motion_buffer();
                }
                break;
            default:
                if (is_char_pending) {
                    set_vim_mode(INSERT_MODE);
                    clear_motion_buffer();
                }
        }
    } else {
        switch (keycode) { // clear motion buffer on every release of an acction
            case VM_LEFT:
            case VM_DOWN:
            case VM___UP:
            case VM_RGHT:
            case VM_NTRL:
            case VM_HORI:
            case VM_VERT:
            case VM_CHAN:
            case VM_DELE:
            case VM_YANK:
            case VM_VISU:
            case VM_MRKQ:
            case VM_MRKG:
            case VM_FRMT:
            case VM_FOLD:
            case VM_SRCH:
                clear_motion_buffer();
                if (pending_insert) insert_mode();
            default:
                break;
        }
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    switch (keycode) {
        // case QK_LEAD:
        case LTP_ARC:
        case RTP_ARC:
        case LHM_ARC:
        case RHM_ARC:
        case LBM_ARC:
        case RBM_ARC:
        case COM_ARC:
        case DOT_ARC:
        case OSLBASE:
            return false; // Arcane keys will ignore the above keycodes.
    }
    last_keydown = timer_read();
    last_record  = record;
    last_key     = (keypos_t){record->event.key.col, record->event.key.row};
    return true; // Other keys can be repeated.
}

void matrix_scan_user(void) {
    if (input_buffer[INPUT_BUFFER_SIZE - 1] && timer_expired(timer_read(), input_buffer_deadline)) {
        clear_input_buffer(); // Timed out; clear the buffer.
    }

    if (motion_buffer[MOTION_BUFFER_SIZE - 1] && timer_expired(timer_read(), motion_buffer_deadline)) {
        clear_motion_buffer(); // Timed out; clear the buffer.
    }
    /*
    if (timer_elapsed(last_keycode_timer) == LAST_KEYCODE_TIMEOUT_MS) {
        set_last_keycode(KC_CANCEL);
    }
    */

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
    // slices
        if (leader_sequence_one_key(KC_V)) {
             layer_on(_SLICE);
        current_slice = VIM;
    } else
            if (leader_sequence_one_key(KC_A)) {
             layer_on(_SLICE);
        current_slice = ARROW;
    } else
            if (leader_sequence_one_key(KC_N)) {
             layer_on(_SLICE);
        current_slice = NAV;
    } else
            if (leader_sequence_one_key(KC_T)) {
             layer_off(_SLICE);
    } else
    // modes
    if (leader_sequence_two_keys(KC_N, KC_4)) {
        work_mode = !work_mode;
    } else
    if (leader_sequence_three_keys(KC_D, KC_O, KC_T)) {
        smart_dot_mode = !smart_dot_mode;
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
    if (leader_sequence_four_keys(KC_S, KC_C, KC_R, KC_T)) {
            layer_on(_SECRET);
    } else

    // shortcuts
    if (leader_sequence_two_keys(KC_F, KC_L)) { // bootloader
            reset_keyboard();
    }
    if (leader_sequence_two_keys(KC_V, KC_K)) { // bootloader
            reset_keyboard();
    }
    if (leader_sequence_one_key(KC_F)) { // bootloader
            reset_keyboard();
    }
    if (leader_sequence_three_keys(KC_R, KC_D, KC_T)) {
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
        case ALTLSPC:
        case ALTRSPC:
        case KC_MINS:
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
    // if (timer_elapsed(last_keydown) > REPEAT_TERM) {
    if ((keycode == TD(TBW) || keycode == TD(TDW) || keycode == TH___QU) || timer_elapsed(last_keydown) > MAGIC_TERM) {
        return TAPPING_TERM; // Default tapping term
    } else {
        return TAPPING_TERM + REPEAT_TERM + MAGIC_TERM;
    }
    /*
        switch (keycode) {
            default:
                return TAPPING_TERM; // Default tapping term
        }
    */
}
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // if (timer_elapsed(last_keydown) > MAGIC_TERM) {
    if (timer_elapsed(last_keydown) > REPEAT_TERM) {
        return true;
    } else {
        return false;
    }
    /*
    switch (keycode) {
        case LT(1, KC_BSPC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
    */
}
bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    // TODO keep in sync with combos
    switch (combo_index) {
        /*
        case WORD_COMBO_AL:
        case WORD_COMBO_AR:
        case WORD_COMBO_IL:
        case WORD_COMBO_IR:
        case WORD_COMBO_PS:
        case WORD_COMBO_PLL:
        case WORD_COMBO_PVE:
        case WORD_COMBO_PT:
        case WORD_COMBO_PD:
        */
        case WORD_COMBO_START ... WORD_COMBO_END:
            if (smart_space_mode) {
                tap_code(KC_SPC);
                last_smart_space = true;
            }
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _ALTISHL, _ALTISHR, _ALTISHB);
    // TODO might as well find an excuse to put layer taps on my spaces and add a tri layer here
    return state;
}
/*
// TODO think of cool things arcane could do on hold
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFSHL_R:
        case ALT___T:
        case DOT_ARC:
        case COM_ARC:
        case ALTLSPC:
        case ALTRSPC:
            return true;
        default:
            return false;
    }
}
void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch (keycode) {
        case DOT_ARC:
            if (!shifted) {
                process_dot_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            } else {
                if (semicolon_mode) {
                    tap_code16(KC_SCLN);
                    tap_code16(KC_ENT);
                } else {
                    tap_code16(KC_DOT);
                }
            }
            break;
        case COM_ARC:
            if (!shifted) {
                process_comma_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods());
            } else {
                tap_code16(KC_COMM);
            }
            break;
        case ALTLSPC:
            if (!shifted) {
                tap_code16(KC_SPC);
            } else {
                tap_code16(KC_UNDS);
            }
            break;
        case ALTRSPC:
            if (!shifted) {
                tap_code16(KC_SPC);
            } else {
                tap_code16(KC_UNDS);
            }

            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

*/
// TODO figure out why this isn't turning off the layer
void insert_mode_user(void) {
    if (IS_LAYER_ON(_VIMFIGHTER)) {
        restore_motion_layer = true;
        layer_off(_VIMFIGHTER);
    }
    layer_off(_SLICE);
    keeb_state.vim_mode_index = INSERT_MODE;
}
void normal_mode_user(void) {
    layer_on(_SLICE);
    if (restore_motion_layer) {
        layer_on(_VIMFIGHTER);
        restore_motion_layer = false;
    }
    keeb_state.vim_mode_index = NORMAL_MODE;
}
void visual_mode_user(void) {
    if (IS_LAYER_OFF(_SLICE)) {
        layer_on(_SLICE);
    }
}
void visual_line_mode_user(void) {
    if (IS_LAYER_OFF(_SLICE)) {
        layer_on(_SLICE);
    }
}
uint16_t process_normal_mode_user(uint16_t keycode, const keyrecord_t *record, bool recursive) {
    if (recursive) return keycode;

    /*
    parsing priority:
    motion input
    diagonal command normal
    cardinal command normal
    neutral
    */

    // TODO  revisit offloading vert to up & down
    // TODO fix diagonals
    // TODO figure out why only command normals work with combo keycodes
    // TODO consider jumps like method and comment https://neovim.io/doc/user/motion.html#%5Dm
    // TODO consider substitution logic. prob needs a dedicated mohttps://neovim.io/doc/user/change.html#%3As
    // TODO maybe fix diagonals by lifting roll reversal state for each 2 pair hold. 4 hold directions x 3 tap directions = 12 diagonal states
    // TODO figure out why MI_ keycodes are sending as media keys??? prob something to do with qmk-vim
    /*
    if (record->event.pressed) {
        switch (keycode) {
            case MI_BACK:
                is_back_held = true;
                return keycode;
            case MI_DOWN:
                is_down_held = true;
                return keycode;
            case MI_JUMP:
                is_jump_held = true;
                return keycode;
            case MI_FRNT:
                is_front_held = true;
                return keycode;
        }
    } else {
        switch (keycode) {
            case MI_BACK:
                is_back_held = false;
                return keycode;
            case MI_DOWN:
                is_down_held = false;
                return keycode;
            case MI_JUMP:
                is_jump_held = false;
                return keycode;
            case MI_FRNT:
                is_front_held = false;
                return keycode;
        }
        }
    */
    /*------------------------------motion inputs------------------------------*/

    if (update_motion_buffer(keycode, record)) {
        // TODO figure out why a dpf that doesn't fully release is parsed as a hcbf
        // TODO maybe rewrite with keydown keyup processing?
        if (motion_buffer[MOTION_BUFFER_SIZE - 5] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_hcbf_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 5] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_dqcb_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_hcb_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_dpb_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_qcb_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_bf_motion = true;
        }

        if (motion_buffer[MOTION_BUFFER_SIZE - 5] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_hcfb_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 5] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_dqcf_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_hcf_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_dpf_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_qcf_motion = true;
        } else if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_fb_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_FRNT && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_FRNT && ACTIONS) {
            is_ff_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_BACK && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_BACK && ACTIONS) {
            is_bb_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_DOWN && ACTIONS) {
            is_dd_motion = true;
        }
        // TODO test combo
        if (motion_buffer[MOTION_BUFFER_SIZE - 4] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && ACTIONS) {
            is_dd_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_JUMP && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_JUMP && ACTIONS) {
            is_jj_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_DOWN && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_JUMP && ACTIONS) {
            is_dj_motion = true;
        }
        if (motion_buffer[MOTION_BUFFER_SIZE - 3] == MI_JUMP && motion_buffer[MOTION_BUFFER_SIZE - 2] == MI_DOWN && ACTIONS) {
            is_jd_motion = true;
        }
    }

    // TODO figure out how to handle command command mode for  https://neovim.io/doc/user/motion.html#%3A%5Brange%5D
    switch (keycode) {
            /*case KC_ENT:
                if (vim_emulation_enabled() && record->event.pressed) tap_code16(KC_ENT);
                return KC_CANCEL;*/

        case VIM_TOG:
            if (record->event.pressed) toggle_vim_emulation();
            return KC_CANCEL;
        // TODO add join lines section https://getreuer.info/posts/keyboards/macros/index.html
        // TODO ensure . repetition, and gn gN are accessible
        //  TODO add section mappings to vim https://neovim.io/doc/user/motion.html#section
        // TODO figure out how to handle visual being both a quasi operator and mode

        /*------------------------------command normals------------------------------*/

        // normal directions
        // TODO lock motion inputs as "held" so long as the final direction is held. qcf action should repeat so long as the forward is still being held.
        case MI_BACK:
            is_back_held = record->event.pressed;
            return KC_CANCEL;
        case MI_DOWN:
            is_down_held = record->event.pressed;
            return KC_CANCEL;
        case MI_JUMP:
            is_jump_held = record->event.pressed;
            return KC_CANCEL;
        case MI_FRNT:
            is_front_held = record->event.pressed;
            return KC_CANCEL;

        case VM_LEFT: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCBF_MOTION: // https://neovim.io/doc/user/motion.html#%5E
                        key_1 = KC_CIRC;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/motion.html#0
                        key_1 = KC_0;
                        break;
                    case DPB_MOTION:                                      // https://neovim.io/doc/user/motion.html#)
                        key_1          = is_text_object ? KC_S : KC_RPRN; // sentence object https://neovim.io/doc/user/motion.html#as
                        is_text_object = false;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/motion.html#B
                        key_1 = S(KC_B);
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#gE
                        key_1 = KC_G;
                        key_2 = S(KC_E);
                        break;
                    case FB_MOTION: // https://neovim.io/doc/user/motion.html#T
                        key_1           = S(KC_T);
                        is_char_pending = true;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#F
                        key_1           = S(KC_F);
                        is_char_pending = true;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#b
                        key_1 = KC_B;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#ge
                        key_1 = KC_G;
                        key_2 = KC_E;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#h
                        key_1 = KC_H;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);

                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }
            // clear_motions();
        }
        case VM_DOWN: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION: // https://neovim.io/doc/user/motion.html#g_
                        key_1 = KC_G;
                        key_2 = KC_UNDS;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/motion.html#H
                        key_1 = KC_H;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/fold.html#zj
                        key_1 = KC_Z;
                        key_2 = KC_J;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#CTRL-X
                        key_1 = C(KC_X);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/motion.html#M
                        key_1 = S(KC_M);
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/change.html#v_g_CTRL-X
                        key_1 = KC_G;
                        key_2 = C(KC_X);
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#%2B
                        key_1 = KC_PLUS;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#gj
                        key_1 = KC_G;
                        key_2 = KC_J;
                        break;
                    case DOWN_HELD:                                       // https://neovim.io/doc/user/motion.html#%7D
                        key_1          = is_text_object ? KC_P : KC_RCBR; // paragraph object https://neovim.io/doc/user/motion.html#ap
                        is_text_object = false;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#j
                        key_1 = KC_J;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }
            // clear_motions();
        }
        case VM___UP: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#L
                        key_1 = KC_L;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/fold.html#zk
                        key_1 = KC_Z;
                        key_2 = KC_K;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#v_g_CTRL-A
                        key_1 = KC_G;
                        key_2 = C(KC_A);
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#M
                        key_1 = S(KC_M);
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/change.html#CTRL-A
                        key_1 = C(KC_A);
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#-
                        key_1 = KC_MINUS;
                        break;
                    case JUMP_HELD:                                       // https://neovim.io/doc/user/motion.html#%7B
                        key_1          = is_text_object ? KC_P : KC_LCBR; // paragraph object https://neovim.io/doc/user/motion.html#ap
                        is_text_object = false;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#gk
                        key_1 = KC_G;
                        key_2 = KC_K;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#k
                        key_1 = KC_K;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_RGHT: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION:            // https://neovim.io/doc/user/motion.html#g%24
                        if (is_down_held) break; // guard against false dpf
                        key_1 = KC_G;
                        key_2 = KC_END;
                        break;
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#%24
                        key_1 = KC_DLR;
                        break;
                    case DPF_MOTION:                                      // https://neovim.io/doc/user/motion.html#(
                        key_1          = is_text_object ? KC_S : KC_LPRN; // sentence object https://neovim.io/doc/user/motion.html#as
                        is_text_object = false;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#%3CC-Right%3E
                        key_1 = S(KC_W);
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/motion.html#E
                        key_1 = S(KC_E);
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/motion.html#f
                        key_1           = KC_F;
                        is_char_pending = true;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/motion.html#t
                        key_1           = KC_T;
                        is_char_pending = true;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#~
                        key_1 = KC_TILDE;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#w
                        key_1 = KC_W;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#e
                        key_1 = KC_E;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#l
                        key_1 = KC_L;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_VERT: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case FB_MOTION: // https://neovim.io/doc/user/motion.html#%5D%5B
                        key_1 = KC_RBRC;
                        key_2 = KC_LBRC;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/motion.html#%5B%5D
                        key_1 = KC_LBRC;
                        key_2 = KC_RBRC;
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#G
                        key_1 = S(KC_G);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/motion.html#gg
                        key_1 = KC_G;
                        key_2 = KC_G;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/motion.html#%5D%7D
                        key_1 = KC_RBRC;
                        key_2 = KC_RCBR;
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/motion.html#%5B%7B
                        key_1 = KC_LBRC;
                        key_2 = KC_LCBR;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#%5D%5D
                        key_1 = KC_RBRC;
                        key_2 = KC_RBRC;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#%5B%5B
                        key_1 = KC_LBRC;
                        key_2 = KC_LBRC;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#%5D%7D
                        key_1 = KC_RBRC;
                        key_2 = KC_RPRN;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#%5D%7D
                        key_1 = KC_LBRC;
                        key_2 = KC_LPRN;
                        break;
                    default: // https://neovim.io/doc/user/scroll.html#z.
                        key_1 = KC_Z;
                        key_2 = KC_DOT;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_HORI: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            static uint16_t key_3 = KC_CANCEL;
            // TODO decide if rot13 is worth adding
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#bar
                        key_1 = KC_BAR;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/fold.html#%5Bz
                        key_1 = KC_LBRC;
                        key_2 = KC_Z;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/fold.html#%5Dz
                        key_1 = KC_RBRC;
                        key_2 = KC_Z;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#m%3C
                        key_1 = KC_M;
                        key_2 = KC_LABK;
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/motion.html#m%3E
                        key_1 = KC_M;
                        key_2 = KC_RABK;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/change.html#gqq
                        key_1 = KC_G;
                        key_2 = KC_Q;
                        key_3 = KC_Q;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#g~~
                        key_1 = KC_G;
                        key_2 = KC_TILDE;
                        key_3 = KC_TILDE;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#guu
                        key_1 = KC_G;
                        key_2 = KC_U;
                        key_3 = KC_U;
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/change.html#gUU
                        key_1 = KC_G;
                        key_2 = S(KC_U);
                        key_3 = S(KC_U);
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#m%5B
                        key_1 = KC_M;
                        key_2 = KC_LBRC;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#m%5D
                        key_1 = KC_M;
                        key_2 = KC_RBRC;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#M
                        key_1 = S(KC_M);
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    if (key_3 != KC_CANCEL) tap_code16(key_3);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = key_3 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                // TODO double check this covers key 3 case
                if (key_1 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                }
                if (key_2 == KC_CANCEL) {
                    return key_2;
                } else {
                    process_normal_mode_user(key_2, record, true);
                }
                if (key_3 != KC_CANCEL) {
                    return key_3;
                } else {
                    process_normal_mode_user(key_3, record, true);
                }
                // TODO add emulated ge with ctrl+left left
                if (!record->event.pressed) return key_1 = key_2 = key_3 = KC_CANCEL;
            }

            // clear_motions();
        }
        case VM_NTRL: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    // TODO find non text object commands and overload these. use ternary operator to check against is_text_object
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#g%3B
                        key_1 = KC_G;
                        key_2 = KC_SCLN;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#quote
                        key_1           = KC_DQUO;
                        is_char_pending = true;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/motion.html#g%2C
                        key_1 = KC_G;
                        key_2 = KC_COMMA;
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/repeat.html#.
                        key_1 = KC_DOT;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/motion.html#%3B
                        key_1          = KC_SCLN;
                        is_text_object = false;
                        break;
                    case FB_MOTION: // https://neovim.io/doc/user/motion.html#%2C
                        key_1          = KC_COMMA;
                        is_text_object = false;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#a'
                        key_1          = KC_QUOT;
                        is_text_object = false;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/motion.html#aquote
                        key_1          = KC_DQUO;
                        is_text_object = false;
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/motion.html#a%60
                        key_1          = KC_GRV;
                        is_text_object = false;
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/motion.html#at
                        key_1          = KC_T;
                        is_text_object = false;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#a%7B
                        key_1          = KC_LCBR;
                        is_text_object = false;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#i(
                        key_1          = KC_LPRN;
                        is_text_object = false;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#a%5B
                        key_1          = is_text_object ? KC_LBRC : KC_N;
                        is_text_object = false;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#a%3C
                        key_1          = KC_LABK;
                        is_text_object = false;
                        break;
                    default: // https://neovim.io/doc/user/intro.html#i_esc
                        key_1 = KC_ESC;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_CHAN: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#C
                        key_1 = S(KC_C);
                        break;
                    // TODO double check replace mode is working properly
                    case JJ_MOTION: // https://neovim.io/doc/user/change.html#R
                        key_1 = S(KC_R);
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/change.html#gR
                        key_1 = KC_G;
                        key_2 = S(KC_R);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#gr
                        key_1           = KC_G;
                        key_2           = KC_R;
                        is_char_pending = true;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#S
                        key_1 = S(KC_S);
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_C;
                        key_2          = KC_A;
                        is_text_object = pending_insert = true;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_C;
                        key_2          = KC_I;
                        is_text_object = pending_insert = true;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/change.html#s
                        key_1 = KC_S;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/change.html#v_r
                        key_1           = KC_R;
                        is_char_pending = true;
                        break;
                    default: // https://neovim.io/doc/user/change.html#c
                        key_1 = KC_C;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_DELE: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#D
                        key_1 = S(KC_D);
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/change.html#X
                        key_1 = S(KC_X);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#gJ
                        key_1 = KC_G;
                        key_2 = S(KC_J);
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#dd
                        key_1 = KC_D;
                        key_2 = KC_D;
                        break;
                        // pefectly balanced, as all things should be
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_D;
                        key_2          = KC_A;
                        is_text_object = pending_insert = true;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_D;
                        key_2          = KC_I;
                        is_text_object = pending_insert = true;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/change.html#x
                        key_1 = KC_X;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/change.html#J
                        key_1 = S(KC_J);
                        break;
                    default: // https://neovim.io/doc/user/change.html#d
                        key_1 = KC_D;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        // TODO Separate is_char_pending and is_register_pending for automatic easier access to punctuation registers on base layer
        // TODO maybe dedicated register one shot layer?
        // https://neovim.io/doc/user/change.html#registers
        case VM_YANK: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#Y
                        key_1 = S(KC_Y);
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/change.html#gp
                        key_1 = KC_G;
                        key_2 = KC_P;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/change.html#gP
                        key_1 = KC_G;
                        key_2 = S(KC_P);
                        break;
                    case DPF_MOTION: // https://neovim.io/doc/user/change.html#zp
                        key_1 = KC_Z;
                        key_2 = KC_P;
                        break;
                    case DPB_MOTION: // https://neovim.io/doc/user/change.html#zP
                        key_1 = KC_Z;
                        key_2 = S(KC_P);
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/change.html#yy
                        key_1           = KC_Y;
                        key_2           = KC_Y;
                        is_char_pending = true;
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#%5DP
                        key_1 = KC_RBRC;
                        key_2 = S(KC_P);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#zy
                        key_1 = KC_Z;
                        key_2 = KC_Y;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_Y;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_Y;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/change.html#%5Dp
                        key_1 = KC_RBRC;
                        key_2 = KC_P;
                        break;
                    default: // https://neovim.io/doc/user/change.html#y
                        key_1 = KC_Y;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_VISU: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case JUMP_HELD: // https://neovim.io/doc/user/visual.html#V
                        key_1 = S(KC_V);
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/visual.html#CTRL-V
                        key_1 = C(KC_V);
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_V;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_V;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    default: // https://neovim.io/doc/user/visual.html#v
                        key_1 = KC_V;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_MRKQ: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION: // https://neovim.io/doc/user/motion.html#%5D'
                        key_1 = KC_RBRC;
                        key_2 = KC_QUOT;
                        break;
                    case HCBF_MOTION: // https://neovim.io/doc/user/motion.html#%5B'
                        key_1 = KC_LBRC;
                        key_2 = KC_QUOT;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/motion.html#'%3C
                        key_1 = KC_QUOT;
                        key_2 = KC_LABK;
                        break;
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#'%3E
                        key_1 = KC_QUOT;
                        key_2 = KC_RABK;
                        break;
                    case DPB_MOTION: // https://neovim.io/doc/user/motion.html#'(
                        key_1 = KC_QUOT;
                        key_2 = KC_LPRN;
                        break;
                    case DPF_MOTION: // https://neovim.io/doc/user/motion.html#')
                        key_1 = KC_QUOT;
                        key_2 = KC_RPRN;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#'
                        key_1           = KC_QUOT;
                        is_char_pending = true;
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#'%5E
                        key_1 = KC_QUOT;
                        key_2 = KC_CIRC;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#''
                        key_1 = KC_QUOT;
                        key_2 = KC_QUOT;
                        break;
                    case FB_MOTION: // https://neovim.io/doc/user/motion.html#m'
                        key_1 = KC_M;
                        key_2 = KC_QUOT;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/motion.html#'.
                        key_1 = KC_QUOT;
                        key_2 = KC_DOT;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/motion.html#g'
                        key_1           = KC_G;
                        key_2           = KC_QUOT;
                        is_char_pending = true;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#'%5B
                        key_1 = KC_QUOT;
                        key_2 = KC_LBRC;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#'%5D
                        key_1 = KC_QUOT;
                        key_2 = KC_RBRC;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#'(
                        key_1 = KC_QUOT;
                        key_2 = KC_LCBR;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#'%7D
                        key_1 = KC_QUOT;
                        key_2 = KC_RCBR;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#m
                        key_1           = KC_M;
                        is_char_pending = true;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_MRKG: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION: // https://neovim.io/doc/user/motion.html#%5D%60
                        key_1 = KC_RBRC;
                        key_2 = KC_GRV;
                        break;
                    case HCBF_MOTION: // https://neovim.io/doc/user/motion.html#%5B%60
                        key_1 = KC_LBRC;
                        key_2 = KC_GRV;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/motion.html#%60%3C
                        key_1 = KC_GRV;
                        key_2 = KC_LABK;
                        break;
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#%60%3E
                        key_1 = KC_GRV;
                        key_2 = KC_RABK;
                        break;
                    case DPB_MOTION: // https://neovim.io/doc/user/motion.html#%60(
                        key_1 = KC_GRV;
                        key_2 = KC_LPRN;
                        break;
                    case DPF_MOTION: // https://neovim.io/doc/user/motion.html#%60)
                        key_1 = KC_GRV;
                        key_2 = KC_RPRN;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#%60
                        key_1           = KC_GRV;
                        is_char_pending = true;
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#%60%5E
                        key_1 = KC_GRV;
                        key_2 = KC_CIRC;
                        break;
                    case DJ_MOTION: // https: // https://neovim.io/doc/user/motion.html#g%60
                        key_1           = KC_G;
                        key_2           = KC_GRV;
                        is_char_pending = true;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#%60%60
                        key_1 = KC_GRV;
                        key_2 = KC_GRV;
                        break;
                    case FB_MOTION: // https://neovim.io/doc/user/motion.html#m%60
                        key_1 = KC_M;
                        key_2 = KC_GRV;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/motion.html#%60.
                        key_1 = KC_GRV;
                        key_2 = KC_DOT;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#%60%5B
                        key_1 = KC_GRV;
                        key_2 = KC_LBRC;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#%60%5D
                        key_1 = KC_GRV;
                        key_2 = KC_RBRC;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#%60%7B
                        key_1 = KC_GRV;
                        key_2 = KC_LCBR;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#%60%7D
                        key_1 = KC_GRV;
                        key_2 = KC_RCBR;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#m
                        key_1           = KC_M;
                        is_char_pending = true;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
        case VM_FRMT: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            static uint16_t key_3 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCBF_MOTION: // https://neovim.io/doc/user/change.html#gqap
                        key_1          = KC_G;
                        key_2          = KC_W;
                        key_3          = KC_A;
                        is_text_object = true;
                        break;
                    case HCFB_MOTION: // https://neovim.io/doc/user/change.html#gqap
                        key_1          = KC_G;
                        key_2          = KC_W;
                        key_3          = KC_I;
                        is_text_object = true;
                        break;
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#%3E%3E
                        key_1 = KC_RABK;
                        key_2 = KC_RABK;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/change.html#%3C%3C
                        key_1 = KC_LABK;
                        key_2 = KC_LABK;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/change.html#gw
                        key_1 = KC_G;
                        key_2 = KC_W;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/change.html#g~
                        key_1 = KC_G;
                        key_2 = KC_TILD;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/change.html#%3C
                        key_1 = KC_LABK;
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/change.html#%3E
                        key_1 = KC_RABK;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/change.html#gU
                        key_1 = KC_G;
                        key_2 = S(KC_U);
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/change.html#gu
                        key_1 = KC_G;
                        key_2 = KC_U;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_G;
                        key_2          = KC_Q;
                        key_3          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_G;
                        key_2          = KC_Q;
                        key_3          = KC_I;
                        is_text_object = true;
                        break;
                    default: // https://neovim.io/doc/user/change.html#gq
                        key_1 = KC_G;
                        key_2 = KC_Q;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    if (key_3 != KC_CANCEL) tap_code16(key_3);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = key_3 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                // TODO double check this covers key 3 case
                if (key_1 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                }
                if (key_2 == KC_CANCEL) {
                    return key_2;
                } else {
                    process_normal_mode_user(key_2, record, true);
                }
                if (key_3 != KC_CANCEL) {
                    return key_3;
                } else {
                    process_normal_mode_user(key_3, record, true);
                }
                if (!record->event.pressed) return key_1 = key_2 = key_3 = KC_CANCEL;
            }

            // clear_motions();
        }

        case VM_FOLD: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case DQCB_MOTION: // https://neovim.io/doc/user/fold.html#zE
                        key_1 = KC_Z;
                        key_2 = S(KC_E);
                        break;
                    case HCBF_MOTION: // https://neovim.io/doc/user/fold.html#zf
                        key_1 = KC_Z;
                        key_2 = KC_F;
                        break;
                    case HCFB_MOTION: // https://neovim.io/doc/user/fold.html#zF
                        key_1 = KC_Z;
                        key_2 = S(KC_F);
                        break;
                    case HCF_MOTION: // https://neovim.io/doc/user/fold.html#zd
                        key_1 = KC_Z;
                        key_2 = KC_D;
                        break;
                    case HCB_MOTION: // https://neovim.io/doc/user/fold.html#zD
                        key_1 = KC_Z;
                        key_2 = S(KC_D);
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/fold.html#zr
                        key_1 = KC_Z;
                        key_2 = KC_R;
                        break;
                    case DPF_MOTION: // https://neovim.io/doc/user/fold.html#zR
                        key_1 = KC_Z;
                        key_2 = S(KC_R);
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/fold.html#zm
                        key_1 = KC_Z;
                        key_2 = KC_M;
                        break;
                    case DPB_MOTION: // https://neovim.io/doc/user/fold.html#zM
                        key_1 = KC_Z;
                        key_2 = S(KC_M);
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/fold.html#zO
                        key_1 = KC_Z;
                        key_2 = S(KC_O);
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/fold.html#zC
                        key_1 = KC_Z;
                        key_2 = S(KC_C);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/fold.html#za
                        key_1 = KC_Z;
                        key_2 = KC_A;
                        break;
                    case JD_MOTION: // https://neovim.io/doc/user/fold.html#zA
                        key_1 = KC_Z;
                        key_2 = S(KC_A);
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/fold.html#zx
                        key_1 = KC_Z;
                        key_2 = KC_X;
                        break;
                    case BF_MOTION: // https://neovim.io/doc/user/fold.html#zX
                        key_1 = KC_Z;
                        key_2 = S(KC_X);
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/fold.html#zN
                        key_1 = KC_Z;
                        key_2 = S(KC_N);
                        break;
                    case FB_MOTION: // https://neovim.io/doc/user/fold.html#zn
                        key_1 = KC_Z;
                        key_2 = KC_N;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/fold.html#zo
                        key_1 = KC_Z;
                        key_2 = KC_O;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/fold.html#zc
                        key_1 = KC_Z;
                        key_2 = KC_C;
                        break;

                    default: // https://neovim.io/doc/user/fold.html#zi
                        key_1 = KC_Z;
                        key_2 = KC_I;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }

        case VM_SRCH: {
            static uint16_t key_1 = KC_CANCEL;
            static uint16_t key_2 = KC_CANCEL;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case QCF_MOTION: // https://neovim.io/doc/user/pattern.html#n
                        key_1 = KC_N;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/pattern.html#n
                        key_1 = S(KC_N);
                        break;
                    case JJ_MOTION: // https://neovim.io/doc/user/tagsrch.html#%5B_CTRL-I
                        key_1 = KC_LBRC;
                        key_2 = C(KC_I);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/tagsrch.html#CTRL-T
                        key_1 = C(KC_T);
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/pattern.html#%23
                        key_1 = KC_HASH;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/pattern.html#star
                        key_1 = KC_ASTR;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/tagsrch.html#%5BI
                        key_1 = KC_LBRC;
                        key_2 = S(KC_I);
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/tagsrch.html#CTRL-%5D
                        key_1 = C(KC_RBRC);
                        break;
                    default: // https://neovim.io/doc/user/motion.html#%25
                        key_1 = KC_PERC;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_CANCEL) tap_code16(key_2);
                    return KC_CANCEL;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_CANCEL;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_CANCEL) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_CANCEL;
                }
            }

            // clear_motions();
        }
    }
    return keycode;
}

bool process_insert_mode_user(uint16_t keycode, const keyrecord_t *record) {
    if (is_char_pending) return false;
    switch (keycode) {
        case KC_ENT:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
            }
            return true;
        case KC_ESC:
            if (record->event.pressed) {
                normal_mode();
            }
            return false;

        default:
            return true;
    }
    return true;
}
// bool process_visual_mode_user(uint16_t keycode, const keyrecord_t *record);
// bool process_visual_line_mode_user(uint16_t keycode, const keyrecord_t *record);

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer         = get_highest_layer(layer_state);
    uint8_t current_default_layer = get_highest_layer(default_layer_state);

    rgb_color_scheme_t color_schemes[] = {
        // clang-format off
        defaults_rcs,
        classic_rcs,
        voluptuous_rcs,
        earthy_rcs,
        positive_rcs,
        jeweled_rcs,
        composed_rcs,
        afternoon_rcs,
        // clang-format on
    };

    color_scheme_max = sizeof(color_schemes) / sizeof(rgb_color_scheme_t);
    switch (current_layer) {
        case _SHIFTISHL:
        case _SHIFTISHR:
        case _ALTISHB:
        case _ALTISHL:
        case _ALTISHR:
        case _NUMPAD:
        case _BITNUM:
        case _SLICE:
        case _VIMFIGHTER:
            rgb_matrix_layer_helper(keeb_state.vim_emulation, color_schemes[keeb_state.color_scheme_index], keeb_state.vim_mode_index, current_layer, rgb_matrix_get_mode(), rgb_matrix_config.speed, LED_FLAG_KEYLIGHT, led_min, led_max);
            break;
        case _POINTER:
        case _POINTEROPT:
            uint8_t speed = rgb_matrix_config.speed * 2 < 254 ? rgb_matrix_config.speed * 2 : 254;
            rgb_matrix_layer_helper(keeb_state.vim_emulation, color_schemes[keeb_state.color_scheme_index], keeb_state.vim_mode_index, current_layer, RGB_MATRIX_EFFECT_BREATHING, speed, LED_FLAG_KEYLIGHT, led_min, led_max);
            break;
        default:
            rgb_matrix_layer_helper(keeb_state.vim_emulation, color_schemes[keeb_state.color_scheme_index], keeb_state.vim_mode_index, current_default_layer, rgb_matrix_get_mode(), rgb_matrix_config.speed, LED_FLAG_KEYLIGHT, led_min, led_max);
            break;
    }
    return false;
}
void keeb_state_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_keeb_state)) {
        memcpy(&transport_keeb_state, initiator2target_buffer, sizeof(transport_keeb_state));
    }
}

void keeb_state_update(void) {
    if (is_keyboard_master()) {
        transport_keeb_state = keeb_state.raw;
    } else {
        keeb_state.raw = transport_keeb_state;
    }
}
void keeb_state_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to target
        static uint16_t last_keeb_state = 0;
        static uint32_t last_sync[3];
        bool            needs_sync = false;

        // Check if the state values are different
        if (memcmp(&transport_keeb_state, &last_keeb_state, sizeof(transport_keeb_state))) {
            needs_sync = true;
            memcpy(&last_keeb_state, &transport_keeb_state, sizeof(transport_keeb_state));
        }
        // Send to target every FORCED_SYNC_THROTTLE_MS regardless of state change
        if (timer_elapsed32(last_sync[SYNC_FORCE]) > FORCED_SYNC_THROTTLE_MS) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KEEB_STATE_SYNC, sizeof(transport_keeb_state), &transport_keeb_state)) {
                last_sync[SYNC_KEEB_STATE] = timer_read32();
            }
            needs_sync = false;
        }
    }
}

void keyboard_post_init_user(void) {
    enable_vim_mode();
    disable_vim_emulation();
    current_mode = RGB_MATRIX_DEFAULT_MODE;
    transaction_register_rpc(RPC_ID_KEEB_STATE_SYNC, keeb_state_sync);
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    keeb_state_update();

    // Data sync from instigator to target
    keeb_state_transport_sync();
}
