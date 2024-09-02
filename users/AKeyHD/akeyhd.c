#include "akeyhd.h"
#include "_wait.h"
#include "action.h"
#include "action_util.h"
#include "config.h"
#include "features/eristocrates/modal_keys.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum.h"
#include "secret.h"
#include "features/andrewjrae/qmk-vim/vim.h"
#include "features/andrewjrae/qmk-vim/motions.h"
#include "features/andrewjrae/qmk-vim/modes.h"
#include "features/possumvibes/smart_layer.h"
#include "features/eristocrates/utilities.h"
#include "features/eristocrates/rgb_matrix_stuff.h"
#include "features/getreuer/layer_lock.h"
#include "features/callum/oneshot.h"
#include "features/callum/swapper.h"
#include "akeyhd_keycodes.h"
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
/*
// TODO finish this
typedef union {
    uint32_t raw;
    struct {
        uint8_t    color_scheme_index : 4;
        vim_mode_t vim_mode_index : 3;
        bool       semicolon_mode : 1;
        bool       smart_space_mode : 1;
        bool       last_smart_space : 1;
        bool       autopair_mode : 1;
        bool       ampersand_mode : 1;
        bool       delete_word_mode : 1;
        bool       kana_input_mode : 1;
        bool       work_mode : 1;
        bool       roll_reversal_mode : 1;
        uint8_t roll_reversal_state : 2;
        uint32_t   reserved : 17;
    }
} keeb_state_config_t;
keeb_state_config = {
    .color_scheme_index = 0,
    .vim_mode_index     = INSERT_MODE,
};
*/

static uint8_t  color_scheme_max;
static uint8_t  current_mode;
static uint16_t color_scheme_index           = 0;
vim_mode_t      vim_mode_index               = INSERT_MODE;
uint16_t        transport_color_scheme_index = 0;
vim_mode_t      transport_vim_mode_index     = INSERT_MODE;
static uint8_t  roll_reversal_state          = 0;
// https://leanrada.com/notes/my-personalised-keyboard/
// https://github.com/Kalabasa/qmk_firmware/blob/2d1608287bb8b52669255266472975875f7c2423/keyboards/lily58/keymaps/Kalabasa/main.c#L56
const uint16_t bitwise_f_keys[]   = {KC_F1, KC_F2, KC_F3, KC_F4, KC_F5};
uint8_t        NUM_BITWISE_F_KEYS = sizeof(bitwise_f_keys) / sizeof(uint16_t);
const uint16_t bitwise_num_keys[] = {
    BN1_DOT, BN2_DC1, BN4_DC2, BN8_DC3, BN16_ET,

};
uint8_t NUM_BITWISE_NUM_KEYS = sizeof(bitwise_num_keys) / sizeof(uint16_t);

// taken from https://github.com/moutis/HandsDown/blob/9e4bf52d013d5a7981d61ff1f5f36d9a3144aa73/moutis.c#L17
uint16_t preprior_keycode = KC_NO;
uint16_t prior_keycode    = KC_NO;
uint16_t prior_keydown    = 0; // timer of keydown for adaptive threshhold.

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
bool restore_motion_layer = false;

// swapper
bool sw_win_active = false;

// piercing holds
uint16_t tap_keycode;
uint16_t hold_keycode;
uint16_t hold_mod;

// for SCN
bool is_scan_toggled = false;

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
#endif     // NO_ACTION_TAPPING
    }

    // Determine whether the key is a letter.
    switch (keycode) {
        case KC_A ... KC_Z:
        case CTRL__R:
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
        case CTRL__R:
        case ALT___T:
            within_word = true;
            break;

        default:
            within_word = false;
    }

    return true;
}
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
        case TD_TRIPLE_TAP:
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                register_code(KC_BSPC);
            } else {
                register_code(KC_LCTL);
                register_code(KC_BSPC);
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
        case TD_TRIPLE_TAP:
        case TD_SINGLE_HOLD:
            if (delete_word_mode) {
                register_code(KC_DEL);
            } else {
                register_code(KC_LCTL);
                register_code(KC_DEL);
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

static bool update_motion_buffer(uint16_t keycode, const keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        uprintf("update_motion_buffer keydown: \t%s\t col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", key_name(keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    } else {
        uprintf("update_motion_buffer keyup: \t%s\t col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", key_name(keycode, false), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    }
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
        // prior_keydown = timer_read();
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
    static bool     tapped    = false;
    static uint16_t tap_timer = 0;

    /*
    #ifdef CONSOLE_ENABLE
        if (record->event.pressed) uprintf("process_record_user: g_led_config_matrix_co[row][col]: %d, kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", g_led_config.matrix_co[record->event.key.row][record->event.key.col], keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    */

    // TODO see if i can ifdef this
    /*
      if (!process_achordion(keycode, record)) { return false; }
      if (!process_custom_shift_keys(keycode, record)) { return false; }

    */
    // TODO find where this gets used
    // bool is_shifted = (get_mods() & MOD_MASK_SHIFT) || (get_oneshot_mods() & MOD_MASK_SHIFT);
    if (binary_mode && !process_bitwise_num(keycode, record)) return false;
    if (!process_bitwise_f(keycode, record)) return false;
    if (!process_quopostrokey(keycode, record)) {
        return false;
    }

    if (!process_vim_mode(keycode, record)) {
        return !vim_emulation_enabled();
    }

    process_mod_lock(keycode, record);
    process_nshot_state(keycode, record);
    if (!process_layer_lock(keycode, record, LR_LOCK)) {
        return false;
    }
    /*
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_RCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS__ALT, keycode, record);
    update_oneshot(&os_gui_state, KC_LCMD, OS__GUI, keycode, record);
    */

    process_layermodes(keycode, record);

    /*------------------------------input buffer------------------------------*/
    if (update_input_buffer(keycode, record)) {
        // Expand "qumk" to qmk
        if (input_buffer[INPUT_BUFFER_SIZE - 3] == KC_Q && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_M && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_K) {
            SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC) SS_TAP(X_BSPC) "qmk");
            return false;
        }

        // konami code
        if (input_buffer[INPUT_BUFFER_SIZE - 10] == KC_R && input_buffer[INPUT_BUFFER_SIZE - 9] == KC_R && input_buffer[INPUT_BUFFER_SIZE - 8] == KC_N && input_buffer[INPUT_BUFFER_SIZE - 7] == KC_N && input_buffer[INPUT_BUFFER_SIZE - 6] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 5] == KC_D && input_buffer[INPUT_BUFFER_SIZE - 4] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 3] == KC_D && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_B && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_A) {
            register_code(KC_LSFT);
            tap_code(KC_HOME);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
            // SEND_STRING("30 lives");
            layer_on(_SECRET);
            return false;
        }
        // z erasure
        // amason -> amazon
        if (input_buffer[INPUT_BUFFER_SIZE - 6] == KC_A && input_buffer[INPUT_BUFFER_SIZE - 5] == KC_M && input_buffer[INPUT_BUFFER_SIZE - 4] == KC_A && input_buffer[INPUT_BUFFER_SIZE - 3] == KC_S && input_buffer[INPUT_BUFFER_SIZE - 2] == KC_O && input_buffer[INPUT_BUFFER_SIZE - 1] == KC_N) {
            SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC) "zon");
        }
    }
    switch (keycode) {
            /*------------------------------Pointer codes ------------------------------*/

        case KC_DBCL:
            if (record->event.pressed) {
                tap_code(KC_BTN1);
                wait_ms(180);
                tap_code(KC_BTN1);
            }
            return false;
            /*------------------------------Break pointer mode on hold of tap hold------------------------------*/
        case SML_SPC:
        case CTRL__R:
            if (record->event.pressed) {
                pointer_mode_disable();
            }
            return true;
            /*------------------------------piercing mods------------------------------*/
            // powerful stuff, unironically surprised myself with this one
            // TODO think of keys that would want to be tapped, prefereably without wanting other mods
            // TODO ensure nshot mod layer interacts properly with this

        case GLTOUTR:
        case CLTOUTR:
        case ALTOUTR:

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

        case GLTINNR:
        case CLTINNR:
        case ALTINNR:
            // arcane

        case GRTOUTR:
        case CRTOUTR:
        case ARTOUTR:

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
        case GRTPNKY:
        case CRTPNKY:
        case ARTPNKY:

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
        case GRTRING:
        case CRTRING:
        case ARTRING:

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
        case GRTMDLE:
        case CRTMDLE:
        case ARTMDLE:

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
        case GRTINDX:
        case CRTINDX:
        case ARTINDX:

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
        case GRTINNR:
        case CRTINNR:
        case ARTINNR:
            // arcane
            return false;
        case GLHOUTR:
        case CLHOUTR:
        case ALHOUTR:

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
        case GLHPNKY:
        case CLHPNKY:
        case ALHPNKY:

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
        case GLHRING:
        case CLHRING:
        case ALHRING:

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
        case GLHMDLE:
        case CLHMDLE:
        case ALHMDLE:

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
        case GLHINDX:
        case CLHINDX:
        case ALHINDX:

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
        case GLHINNR:
        case CLHINNR:
        case ALHINNR:
            // backspace
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
        case GRHOUTR:
        case CRHOUTR:
        case ARHOUTR:
            //
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
        case GRHPNKY:
        case CRHPNKY:
        case ARHPNKY:

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

        case GRHRING:
        case CRHRING:
        case ARHRING:

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
        case GRHMDLE:
        case CRHMDLE:
        case ARHMDLE:

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

        case GRHINDX:
        case CRHINDX:
        case ARHINDX:

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

        case GRHINNR:
        case CRHINNR:
        case ARHINNR:
            // delete
            return false;
        case GLBOUTR:
        case CLBOUTR:
        case ALBOUTR:
            // core leader key
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
        case GLBPNKY:
        case CLBPNKY:
        case ALBPNKY:

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
        case GLBRING:
        case CLBRING:
        case ALBRING:

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
        case GLBMDLE:
        case CLBMDLE:
        case ALBMDLE:

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
        case GLBINDX:
        case CLBINDX:
        case ALBINDX:

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
        case GLBINNR:
        case CLBINNR:
        case ALBINNR:
            // arcane
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
        case GRBOUTR:
        case CRBOUTR:
        case ARBOUTR:
            // test
            return false;
        case GRBPNKY:
        case CRBPNKY:
        case ARBPNKY:
            // parenthesis closing
            tap_keycode  = KC_NO;
            hold_keycode = tap_keycode;
            hold_mod     = 0;
            if (IS_LAYER_ON(_GUIPR)) {
            } else if (IS_LAYER_ON(_CTRLPR)) {
                tap_keycode = KC_RBRC;
            } else if (IS_LAYER_ON(_ALTPR)) {
                tap_keycode = KC_RCBR;
            } else {
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        case GRBRING:
        case CRBRING:
        case ARBRING:
            // period
            tap_keycode  = KC_NO;
            hold_keycode = tap_keycode;
            hold_mod     = 0;
            if (IS_LAYER_ON(_GUIPR)) {
            } else if (IS_LAYER_ON(_CTRLPR)) {
                tap_keycode = KC_QUES;
            } else if (IS_LAYER_ON(_ALTPR)) {
                tap_keycode = KC_EXLM;
            } else {
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                    if (is_caps_word_on()) {
                        tap_code16(KC_SPC);
                    }
                }
            }
            return false;
        case GRBMDLE:
        case CRBMDLE:
        case ARBMDLE:
            // comma
            tap_keycode  = KC_NO;
            hold_keycode = tap_keycode;
            hold_mod     = 0;
            if (IS_LAYER_ON(_GUIPR)) {
            } else if (IS_LAYER_ON(_CTRLPR)) {
                tap_keycode = KC_COLN;
            } else if (IS_LAYER_ON(_ALTPR)) {
                tap_keycode = KC_SLSH;
            } else {
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        case GRBINDX:
        case CRBINDX:
        case ARBINDX:
            // parenthesis opening
            tap_keycode  = KC_NO;
            hold_keycode = tap_keycode;
            hold_mod     = 0;
            if (IS_LAYER_ON(_GUIPR)) {
            } else if (IS_LAYER_ON(_CTRLPR)) {
                tap_keycode = KC_LBRC;
            } else if (IS_LAYER_ON(_ALTPR)) {
                tap_keycode = KC_LCBR;
            } else {
            }
            if (process_tap_or_long_mod_press_key(record, hold_keycode, hold_mod)) {
                if (record->event.pressed) {
                    tap_code16(tap_keycode);
                }
            }
            return false;
        case GRBINNR:
        case CRBINNR:
        case ARBINNR:
            // arcane
            return false;

        case GLLTHMB:
        case CLLTHMB:
        case ALLTHMB:
            // math/tab
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
        case GLMTHMB:
        case CLMTHMB:
        case ALMTHMB:

            return true;
        case GLRTHMB:
        case CLRTHMB:
        case ALRTHMB:
            // left space
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
        case GRLTHMB:
        case CRLTHMB:
        case ARLTHMB:
            // right space
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
        case GRMTHMB:
        case CRMTHMB:
        case ARMTHMB:

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
        case KC_S:
            if (record->event.pressed && last_smart_space) {
                tap_code(KC_BSPC);
                tap_code(KC_S);
                tap_code(KC_SPC);
            }
            return true;
        case MD_AND:
            if (record->event.pressed) {
                if (ampersand_mode) {
                    // Output '&' in ampersand mode
                    tap_code16(KC_AMPR);
                } else {
                    send_string_with_caps_word("and");
                }
            }
            return true;
        case MD_THE:
            if (record->event.pressed) {
                send_string_with_caps_word("the");
            }
            return true;
        case MD_FOR:
            if (record->event.pressed) {
                send_string_with_caps_word("for");
            }
            return true;
        case MD_YOU:
            if (record->event.pressed) {
                send_string_with_caps_word("you");
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
        case MD_OULD:
            if (record->event.pressed) {
                send_string_with_caps_word("ould");
            }
            return true;

        case MD_TO:
            if (record->event.pressed) {
                send_string_with_caps_word("to");
            }
            return true;
        case MD_FROM:
            if (record->event.pressed) {
                send_string_with_caps_word("from");
            }
            return true;
        case MD_BUT:
            if (record->event.pressed) {
                send_string_with_caps_word("but");
            }
            return true;
        case MD_I:
            if (record->event.pressed) {
                send_string_with_caps_word("I");
            }
            return true;
        case MD_IPD:
            if (record->event.pressed) {
                send_string_with_caps_word("I'd");
            }
            return true;
        case MD_IPLL:
            if (record->event.pressed) {
                send_string_with_caps_word("I'll");
            }
            return true;
        case MD_IPM:
            if (record->event.pressed) {
                send_string_with_caps_word("I'm");
            }
            return true;
        case MD_IPVE:
            if (record->event.pressed) {
                send_string_with_caps_word("I've");
            }
            return true;
        case MD_YOUD:
            if (record->event.pressed) {
                send_string_with_caps_word("you'd");
            }
            return true;
        case MD_YOUL:
            if (record->event.pressed) {
                send_string_with_caps_word("you'll");
            }
            return true;
        case MD_YORE:
            if (record->event.pressed) {
                send_string_with_caps_word("you're");
            }
            return true;
        case MD_YOVE:
            if (record->event.pressed) {
                send_string_with_caps_word("you've");
            }
            return true;
        case MD_YOUR:
            if (record->event.pressed) {
                send_string_with_caps_word("your");
            }
            return true;
        case MD_THEI:
            if (record->event.pressed) {
                send_string_with_caps_word("their");
            }
            return true;
        case MD_THYR:
            if (record->event.pressed) {
                send_string_with_caps_word("they're");
            }
            return true;
        case MD_THRE:
            if (record->event.pressed) {
                send_string_with_caps_word("there");
            }
            return true;
        case MD_THEY:
            if (record->event.pressed) {
                send_string_with_caps_word("they");
            }
            return true;
        case MD_THYD:
            if (record->event.pressed) {
                send_string_with_caps_word("they'd");
            }
            return true;
        case MD_THYL:
            if (record->event.pressed) {
                send_string_with_caps_word("they'll");
            }
            return true;
        case MD_HERE:
            if (record->event.pressed) {
                send_string_with_caps_word("here");
            }
            return true;
        case MD_WHRE:
            if (record->event.pressed) {
                send_string_with_caps_word("where");
            }
            return true;
        case MD_WEPR:
            if (record->event.pressed) {
                send_string_with_caps_word("we're");
            }
            return true;
        case MD_WERE:
            if (record->event.pressed) {
                send_string_with_caps_word("were");
            }
            return true;
        case MD_WEPD:
            if (record->event.pressed) {
                send_string_with_caps_word("we'd");
            }
            return true;
        case MD_WELL:
            if (record->event.pressed) {
                send_string_with_caps_word("well");
            }
            return true;
        case MD_WEPL:
            if (record->event.pressed) {
                send_string_with_caps_word("we'll");
            }
            return true;
        case MD_WEPV:
            if (record->event.pressed) {
                send_string_with_caps_word("we've");
            }
            return true;
        case MD_WHAT:
            if (record->event.pressed) {
                send_string_with_caps_word("what");
            }
            return true;
        case MD_WITH:
            if (record->event.pressed) {
                send_string_with_caps_word("with");
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
        case MD_PS:
            if (record->event.pressed) {
                if (last_smart_space) {
                    tap_code(KC_BSPC);
                }
                send_string_with_caps_word("'s");
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
        case KC_LABK:
            if (record->event.pressed) {
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
                        if (smart_space_mode) {
                            tap_code(KC_SPC);
                        }
                        last_smart_space = true;
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
                        if (smart_space_mode) {
                            tap_code(KC_SPC);
                        }
                        last_smart_space = true;
                    }
                }
            }
            return false;
        case KC_SCLN:
            if (record->event.pressed) {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 1) roll_reversal_state++;
                } else {
                    tap_code16(KC_SCLN);
                }
            } else {
                if (roll_reversal_mode) {
                    if (roll_reversal_state == 2) {
                        roll_reversal_state = 0;
                        tap_code16(KC_GRV);
                        tap_code(KC_LEFT);
                        return false;
                    } else {
                        tap_code16(KC_SCLN);
                        if (smart_space_mode) {
                            tap_code(KC_ENT);
                        }
                        last_smart_space = true;
                    }
                }
            }
            return false;
        case KC_RPRN:
            if (record->event.pressed) {
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
                process_top_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_ASTR);
            }
            return false;
        case RTP_ARC:
            if (record->event.pressed) {
                process_top_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_PERC);
            }
            return false;
        case LHM_ARC:
            if (record->event.pressed) {
                process_home_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_EQUAL);
            }

            return false;
        case RHM_ARC:
            if (record->event.pressed) {
                process_home_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_COLN);
            }

            return false;
        case LBM_ARC:
            if (record->event.pressed) {
                process_bottom_left_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_BSLS); // KC_WAVE (inuyasha ppl will get it)
            }

            return false;
        case RBM_ARC:
            if (record->event.pressed) {
                process_bottom_right_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown, KC_SLSH);
            }

            return false;
            // TODO replicate logic i was doing with autoshift via fancy key tap/hold overrides
        case COM_ARC:

            if (record->event.pressed) {
                process_comma_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown);
            }

            return false;
        case DOT_ARC:
            if (record->event.pressed) {
                process_dot_arcane(extract_basic_keycode(get_last_keycode(), record, false), get_last_mods(), prior_keydown);
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
        case SRCHSEL: // Searches the current selection in a new tab.
            if (record->event.pressed) {
                // Mac users, change LCTL to LGUI.
                SEND_STRING(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER));
            }
            return false;

        case KC_ESLH:
            if (record->event.pressed) {
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
        case KC_DAMP:
            if (record->event.pressed) {
                SEND_STRING("&&");
            }
            return false;
        case KC_DEQL:
            if (record->event.pressed) {
                SEND_STRING("==");
            }
            return false;
        case KC_TEQL:
            if (record->event.pressed) {
                SEND_STRING("===");
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
                uint8_t index      = color_scheme_index + 1 > 7 ? 0 : color_scheme_index + 1;
                color_scheme_index = index;
                // uint8_t color_scheme_max = sizeof(color) / sizeof(nshot_state_t);
            }
            return false;
        case CS_RSTP:
            if (record->event.pressed) {
                uint8_t index      = color_scheme_index - 1 < 0 ? 6 : color_scheme_index - 1;
                color_scheme_index = index;
                // uint8_t color_scheme_max = sizeof(color) / sizeof(nshot_state_t);
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
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
            case KC_SCLN:

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
            case CTRL__R:
            case SML_SPC:
            case SMR_SPC:
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
                clear_motion_buffer();
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
    prior_keydown = timer_read();
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
        set_last_keycode(KC_STOP);
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
    if (leader_sequence_four_keys(KC_S, KC_C, KC_R, KC_T)) {
            layer_on(_SECRET);
    } else

    // shortcuts
    if (leader_sequence_two_keys(KC_F, KC_L)) { // bootloader
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
        case SML_SPC:
        case SMR_SPC:
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

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    // TODO keep in sync with combos
    switch (combo_index) {
        case CB_GH:
        case CB_LY:
        case CB_THE:
        case CB_ANDL:
        case CB_ANDR:
        case CB_FOR:
        case CB_INGL:
        case CB_INGR:
        case CB_SION:
        case CB_TION:
        case CB_OULD:
        case CB_TO:
        case CB_FROM:
        case CB_BUT:
        case CB_I:
        case CB_IPD:
        case CB_IPLL:
        case CB_IPM:
        case CB_IPVE:
        case CB_YOU:
        case CB_YOUPD:
        case CB_YOUPLL:
        case CB_YOUPRE:
        case CB_YOUPVE:
        case CB_YOUR:
        case CB_THEIR:
        case CB_THEYRE:
        case CB_THERE:
        case CB_THEY:
        case CB_THEYD:
        case CB_THEYLL:
        case CB_HERE:
        case CB_WHERE:
        case CB_WEPRE:
        case CB_WERE:
        case CB_WED:
        case CB_WELL:
        case CB_WEPLL:
        case CB_WEVE:
        case CB_WHAT:
        case CB_WITH:
        case CB_PVE:
        case CB_PS:
            if (smart_space_mode) {
                tap_code(KC_SPC);
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
/*
// TODO think of cool things arcane could do on hold
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL__R:
        case ALT___T:
        case DOT_ARC:
        case COM_ARC:
        case SML_SPC:
        case SMR_SPC:
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
        case SML_SPC:
            if (!shifted) {
                tap_code16(KC_SPC);
            } else {
                tap_code16(KC_UNDS);
            }
            break;
        case SMR_SPC:
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
void insert_mode_user(void) {
    if (IS_LAYER_ON(_VIMMOTION)) {
        restore_motion_layer = true;
        layer_off(_VIMMOTION);
    }
    layer_off(_VIMNAV);
    vim_mode_index = INSERT_MODE;
}
void normal_mode_user(void) {
    layer_on(_VIMNAV);
    if (restore_motion_layer) {
        layer_on(_VIMMOTION);
        restore_motion_layer = false;
    }
    vim_mode_index = NORMAL_MODE;
}
void visual_mode_user(void) {
    if (IS_LAYER_OFF(_VIMNAV)) {
        layer_on(_VIMNAV);
    }
}
void visual_line_mode_user(void) {
    if (IS_LAYER_OFF(_VIMNAV)) {
        layer_on(_VIMNAV);
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
        case KC_ENT:
            if (vim_emulation_enabled() && record->event.pressed) tap_code16(KC_ENT);
            return KC_STOP;

        case VIM_TOG:
            if (record->event.pressed) toggle_vim_emulation();
            return KC_STOP;
        // TODO add join lines section https://getreuer.info/posts/keyboards/macros/index.html
        // TODO ensure . repetition, and gn gN are accessible
        //  TODO add section mappings to vim https://neovim.io/doc/user/motion.html#section
        // TODO figure out how to handle visual being both a quasi operator and mode

        /*------------------------------command normals------------------------------*/

        // normal directions
        // TODO lock motion inputs as "held" so long as the final direction is held. qcf action should repeat so long as the forward is still being held.
        case MI_BACK:
            is_back_held = record->event.pressed;
            return KC_STOP;
        case MI_DOWN:
            is_down_held = record->event.pressed;
            return KC_STOP;
        case MI_JUMP:
            is_jump_held = record->event.pressed;
            return KC_STOP;
        case MI_FRNT:
            is_front_held = record->event.pressed;
            return KC_STOP;

        case VM_LEFT: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
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
                    if (key_2 != KC_STOP) tap_code16(key_2);

                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }
            // clear_motions();
        }
            // TODO  revisit offloading vert to up & down
            // TODO consider jumps like method and comment https://neovim.io/doc/user/motion.html#%5Dm
        case VM_DOWN: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION: // https://neovim.io/doc/user/motion.html#g_
                        key_1 = KC_G;
                        key_2 = KC_UNDS;
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
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }
            // clear_motions();
        }
        case VM___UP: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
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
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_RGHT: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCFB_MOTION:            // https://neovim.io/doc/user/motion.html#g%3CEnd%3E
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
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_VERT: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
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
                    default: // https://neovim.io/doc/user/motion.html#%25
                        key_1 = KC_PERC;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_HORI: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/motion.html#bar
                        key_1 = KC_BAR;
                        break;
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#'
                        key_1           = KC_QUOT;
                        is_char_pending = true;
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/motion.html#%60
                        key_1           = KC_GRV;
                        is_char_pending = true;
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/motion.html#g'
                        key_1           = KC_G;
                        key_2           = KC_QUOT;
                        is_char_pending = true;
                        break;
                    case JD_MOTION: // https: // neovim.io/doc/user/motion.html#g%60
                        key_1           = KC_G;
                        key_2           = KC_GRV;
                        is_char_pending = true;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#m%3C
                        key_1 = KC_M;
                        key_2 = KC_LABK;
                        break;
                    case FF_MOTION: // https://neovim.io/doc/user/motion.html#m%3E
                        key_1 = KC_M;
                        key_2 = KC_RABK;
                        break;
                    case JUMP_HELD: // https://neovim.io/doc/user/motion.html#m%5B
                        key_1 = KC_M;
                        key_2 = KC_LBRC;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/motion.html#m%5D
                        key_1 = KC_M;
                        key_2 = KC_RBRC;
                        break;
                    case FRNT_HELD: // https://neovim.io/doc/user/motion.html#m'
                        key_1 = KC_M;
                        key_2 = KC_QUOT;
                        break;
                    case BACK_HELD: // https://neovim.io/doc/user/motion.html#m%60
                        key_1 = KC_M;
                        key_2 = KC_GRV;
                        break;
                    default: // https://neovim.io/doc/user/motion.html#m
                        key_1           = KC_M;
                        is_char_pending = true;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_NTRL: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    // TODO find non text object commands and overload these. use ternary operator to check against is_text_object
                    case QCF_MOTION: // https://neovim.io/doc/user/motion.html#g%3B
                        key_1 = KC_G;
                        key_2 = KC_SCLN;
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
                        key_1          = KC_LBRC;
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
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    // TODO add emulated ge with ctrl+left left
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_CHAN: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#C
                        key_1 = S(KC_C);
                        break;
                    case BACK_HELD: // around text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_C;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // in text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_C;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    default: // https://neovim.io/doc/user/change.html#c
                        key_1 = KC_C;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_DELE: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#D
                        key_1 = S(KC_D);
                        break;
                    case QCB_MOTION: // https://neovim.io/doc/user/change.html#X
                        key_1 = S(KC_X);
                        break;
                    case DD_MOTION: // https://neovim.io/doc/user/change.html#dd
                        key_1 = KC_D;
                        key_2 = KC_D;
                        break;
                        // pefectly balanced, as all things should be
                    case BACK_HELD: // around text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_D;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // in text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_D;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    case DOWN_HELD: // https://neovim.io/doc/user/change.html#x
                        key_1 = KC_X;
                        break;
                    default: // https://neovim.io/doc/user/change.html#d
                        key_1 = KC_D;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_YANK: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/change.html#Y
                        key_1 = S(KC_Y);
                        break;
                    case BACK_HELD: // around text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_Y;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // in text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_Y;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    default: // https://neovim.io/doc/user/change.html#y
                        key_1 = KC_Y;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_VISU: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
            if (record->event.pressed) {
                switch (DIRECTIONS) {
                    case HCF_MOTION: // https://neovim.io/doc/user/visual.html#V
                        key_1 = S(KC_V);
                        break;
                    case DJ_MOTION: // https://neovim.io/doc/user/visual.html#CTRL-V
                        key_1 = C(KC_V);
                        break;
                    case BACK_HELD: // around text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_V;
                        key_2          = KC_A;
                        is_text_object = true;
                        break;
                    case FRNT_HELD: // in text object https://neovim.io/doc/user/motion.html#_5.-text-object-motions
                        key_1          = KC_V;
                        key_2          = KC_I;
                        is_text_object = true;
                        break;
                    default: // https://neovim.io/doc/user/visual.html#v
                        key_1 = KC_V;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_MRKQ: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
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
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#'%5E
                        key_1 = KC_QUOT;
                        key_2 = KC_CIRC;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#''
                        key_1 = KC_QUOT;
                        key_2 = KC_QUOT;
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
                    default: // https://neovim.io/doc/user/motion.html#'.
                        key_1 = KC_QUOT;
                        key_2 = KC_DOT;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
                }
            }

            // clear_motions();
        }
        case VM_MRKG: {
            static uint16_t key_1 = KC_STOP;
            static uint16_t key_2 = KC_STOP;
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
                    case JD_MOTION: // https://neovim.io/doc/user/motion.html#%60%5E
                        key_1 = KC_GRV;
                        key_2 = KC_CIRC;
                        break;
                    case BB_MOTION: // https://neovim.io/doc/user/motion.html#%60%60
                        key_1 = KC_GRV;
                        key_2 = KC_GRV;
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
                    default: // https://neovim.io/doc/user/motion.html#%60.
                        key_1 = KC_GRV;
                        key_2 = KC_DOT;
                }

                if (!vim_emulation_enabled()) {
                    tap_code16(key_1);
                    if (key_2 != KC_STOP) tap_code16(key_2);
                    return KC_STOP;
                }
            } else {
                if (!vim_emulation_enabled()) {
                    key_1 = key_2 = KC_STOP;
                }
            }

            if (vim_emulation_enabled()) {
                if (key_2 == KC_STOP) {
                    return key_1;
                } else {
                    process_normal_mode_user(key_1, record, true);
                    process_normal_mode_user(key_2, record, true);
                    if (!record->event.pressed) return key_1 = key_2 = KC_STOP;
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
        case _POINTER:
        case _POINTEROPT:
            uint8_t speed = rgb_matrix_config.speed * 2 < 254 ? rgb_matrix_config.speed * 2 : 254;
            rgb_matrix_layer_helper(color_schemes[color_scheme_index], vim_mode_index, current_layer, RGB_MATRIX_EFFECT_BREATHING, speed, LED_FLAG_KEYLIGHT, led_min, led_max);
            break;
        default:
            switch (current_default_layer) {
                case _AKEYHD:
                    rgb_matrix_layer_helper(color_schemes[color_scheme_index], vim_mode_index, current_default_layer, rgb_matrix_get_mode(), rgb_matrix_config.speed, LED_FLAG_KEYLIGHT, led_min, led_max);
                    break;
            }
            break;
    }
    return false;
}

void color_scheme_index_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_color_scheme_index)) {
        memcpy(&transport_color_scheme_index, initiator2target_buffer, sizeof(transport_color_scheme_index));
    }
}

void color_scheme_index_update(void) {
    if (is_keyboard_master()) {
        transport_color_scheme_index = color_scheme_index;
    } else {
        color_scheme_index = transport_color_scheme_index;
    }
}
enum syncs {
    SYNC_FORCE,
    SYNC_COLOR_SCHEME,
    SYNC_VIM_MODE,
};
void color_scheme_index_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        // TODO stop storing data  "last index" instead of "index"
        static uint16_t last_color_scheme_index = 0;

        static uint32_t last_sync[3];
        bool            needs_sync = false;

        // Check if the state values are different
        if (timer_elapsed32(last_sync[SYNC_COLOR_SCHEME]) > FORCED_SYNC_THROTTLE_MS && memcmp(&transport_color_scheme_index, &last_color_scheme_index, sizeof(transport_color_scheme_index))) {
            needs_sync = true;
            memcpy(&last_color_scheme_index, &transport_color_scheme_index, sizeof(transport_color_scheme_index));
        }
        // Send to target every FORCED_SYNC_THROTTLE_MS regardless of state change
        if (timer_elapsed32(last_sync[SYNC_FORCE]) > FORCED_SYNC_THROTTLE_MS) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_COLOR_SCHEME_SYNC, sizeof(color_scheme_index), &color_scheme_index)) {
                last_sync[SYNC_COLOR_SCHEME] = timer_read32();
            }
            needs_sync = false;
        }
    }
}

void vim_mode_index_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_vim_mode_index)) {
        memcpy(&transport_vim_mode_index, initiator2target_buffer, sizeof(transport_vim_mode_index));
    }
}

void vim_mode_index_update(void) {
    if (is_keyboard_master()) {
        transport_vim_mode_index = vim_mode_index;
    } else {
        vim_mode_index = transport_vim_mode_index;
    }
}
void vim_mode_index_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        // TODO stop storing data  "last index" instead of "index"
        static uint16_t last_vim_mode_index = 0;

        static uint32_t last_sync[3];
        bool            needs_sync = false;

        // Check if the state values are different
        if (timer_elapsed32(last_sync[SYNC_VIM_MODE]) > FORCED_SYNC_THROTTLE_MS && memcmp(&transport_vim_mode_index, &last_vim_mode_index, sizeof(transport_vim_mode_index))) {
            needs_sync = true;
            memcpy(&last_vim_mode_index, &transport_vim_mode_index, sizeof(transport_vim_mode_index));
        }
        // Send to target every FORCED_SYNC_THROTTLE_MS regardless of state change
        if (timer_elapsed32(last_sync[SYNC_FORCE]) > FORCED_SYNC_THROTTLE_MS) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_VIM_MODE_SYNC, sizeof(vim_mode_index), &vim_mode_index)) {
                last_sync[SYNC_VIM_MODE] = timer_read32();
            }
            needs_sync = false;
        }
    }
}

void keyboard_post_init_user(void) {
    enable_vim_mode();
    enable_vim_emulation();
    current_mode = RGB_MATRIX_DEFAULT_MODE;
    // transaction_register_rpc(RPC_ID_COLOR_SCHEME_SYNC, color_scheme_sync);
    transaction_register_rpc(RPC_ID_COLOR_SCHEME_SYNC, color_scheme_index_sync);
    transaction_register_rpc(RPC_ID_VIM_MODE_SYNC, vim_mode_index_sync);
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    color_scheme_index_update();
    vim_mode_index_update();

    // Data sync from instigator to target
    color_scheme_index_transport_sync();
    vim_mode_index_transport_sync();
}
