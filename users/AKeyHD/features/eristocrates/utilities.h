#pragma once
// #include QMK_KEYBOARD_H
#include "quantum.h"
#include "../../akeyhd_keycodes.h"

void send_string_with_caps_word(const char *str);
void call_keycode(uint16_t keycode);

// Define the default value for the second variable
#define DEFAULT_VALUE KC_STOP

// normal directions
#define BACK_HELD 0x01
#define DOWN_HELD 0x02
#define FRNT_HELD 0x03
#define JUMP_HELD 0x04
// diagonal directions
#define DOWN_BACK_HELD 0x05
#define DOWN_FRNT_HELD 0x06
#define JUMP_FRNT_HELD 0x07
#define JUMP_BACK_HELD 0x08
// double directional inputs
#define BB_MOTION 0x09
#define DD_MOTION 0x0A
#define FF_MOTION 0x0B
#define JJ_MOTION 0x0C
// opposite directional inputs
#define BF_MOTION 0x0D
#define FB_MOTION 0x0E
#define DJ_MOTION 0x0F
#define JD_MOTION 0x11
// motion inputs
#define QCF_MOTION 0x12
#define QCB_MOTION 0x13
#define DPF_MOTION 0x14
#define DPB_MOTION 0x15
#define DQCF_MOTION 0x16
#define DQCB_MOTION 0x17
#define HCF_MOTION 0x18
#define HCB_MOTION 0x19
#define HCBF_MOTION 0x1A

#define HCFB_MOTION 0x17
// TODO dare i attempt charge inputs?

// clang-format off

// directional conditions
#define DIRECTIONS ((is_down_held && is_back_held ? DOWN_BACK_HELD : 0) | \
                    (is_down_held && is_front_held ? DOWN_FRNT_HELD : 0) | \
                    (is_jump_held && is_front_held ? JUMP_FRNT_HELD : 0) | \
                    (is_jump_held && is_back_held ? JUMP_BACK_HELD : 0) | \
                    (is_back_held ? BACK_HELD : 0) | \
                    (is_down_held ? DOWN_HELD : 0) | \
                    (is_front_held ? FRNT_HELD : 0) | \
                    (is_jump_held ? JUMP_HELD : 0) | \
                    (is_bb_motion ? BB_MOTION : 0) | \
                    (is_dd_motion ? DD_MOTION : 0) | \
                    (is_ff_motion ? FF_MOTION : 0) | \
                    (is_jj_motion ? JJ_MOTION : 0) | \
                    (is_bf_motion ? BF_MOTION : 0) | \
                    (is_fb_motion ? FB_MOTION : 0) | \
                    (is_dj_motion ? DJ_MOTION : 0) | \
                    (is_jd_motion ? JD_MOTION : 0) | \
                    (is_qcf_motion ? QCF_MOTION : 0) | \
                    (is_qcb_motion ? QCB_MOTION : 0) | \
                    (is_dpf_motion ? DPF_MOTION : 0) | \
                    (is_dpb_motion ? DPB_MOTION : 0) | \
                    (is_dqcf_motion ? DQCF_MOTION : 0) | \
                    (is_dqcb_motion ? DQCB_MOTION : 0) | \
                    (is_hcf_motion ? HCF_MOTION : 0) | \
                    (is_hcb_motion ? HCB_MOTION : 0) | \
                    (is_hcbf_motion ? HCBF_MOTION : 0) |\
                    (is_hcfb_motion ? HCFB_MOTION : 0))

#define ACTIONS (\
   motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_LEFT               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_DOWN               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM___UP               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_RGHT               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_NTRL               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_HORI               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_VERT               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_CHAN               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_DELE               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_YANK               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_VISU               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_MRKQ               \
|| motion_buffer[MOTION_BUFFER_SIZE - 1] == VM_MRKG               \
)

#define VIM_EXCLUSIONS (keycode != VM_LEFT\
         && keycode != VM_DOWN\
         && keycode != VM___UP\
         && keycode != VM_RGHT\
         && keycode != VM_NTRL\
         && keycode != VM_HORI\
         && keycode != VM_VERT\
         && keycode != VM_CHAN\
         && keycode != VM_DELE\
         && keycode != VM_YANK\
         && keycode != VM_VISU\
         && keycode != VM_MRKQ\
         && keycode != VM_MRKG\
         && keycode != MI_BACK\
         && keycode != MI_DOWN\
         && keycode != MI_JUMP\
         && keycode != MI_FRNT)
// clang-format on

#define KC_BAR KC_PIPE // Ceci n'est pas une macro

const char *key_name(uint16_t keycode, bool shifted);

/*
// Helper macros to handle default values
#define GET_SECOND_ARG(arg1, arg2, ...) arg2
#define HAS_TWO_ARGS(...) GET_SECOND_ARG(__VA_ARGS__, 1, 0)

#define DIRECTION_MACRO(name, value1, ...) value1, (HAS_TWO_ARGS(__VA_ARGS__) ? GET_SECOND_ARG(__VA_ARGS__, 0) : DEFAULT_VALUE)

#define DOWN_BACK(value1, ...) DIRECTION_MACRO(DOWN_BACK, value1, __VA_ARGS__)
#define DOWN_FRNT(value1, ...) DIRECTION_MACRO(DOWN_FRNT, value1, __VA_ARGS__)
#define JUMP_BACK(value1, ...) DIRECTION_MACRO(JUMP_BACK, value1, __VA_ARGS__)
#define JUMP_FRNT(value1, ...) DIRECTION_MACRO(JUMP_FRNT, value1, __VA_ARGS__)
#define BACK(value1, ...) DIRECTION_MACRO(BACK, value1, __VA_ARGS__)
#define DOWN(value1, ...) DIRECTION_MACRO(DOWN, value1, __VA_ARGS__)
#define FRNT(value1, ...) DIRECTION_MACRO(FRNT, value1, __VA_ARGS__)
#define JUMP(value1, ...) DIRECTION_MACRO(JUMP, value1, __VA_ARGS__)
#define NEUTRAL(value1, ...) DIRECTION_MACRO(NEUTRAL, value1, __VA_ARGS__)

// Define the main macro
#define COMMAND_NORMALS(...) COMMAND_NORMALS_IMPL(__VA_ARGS__)

#define EXPAND_ARGS(...) EXPAND_ARGS_IMPL(__VA_ARGS__)
#define EXPAND_ARGS_IMPL(...) FOR_EACH(EXPAND_ARG, __VA_ARGS__)

#define FOR_EACH(macro, ...) FOR_EACH_HELPER(macro, __VA_ARGS__, FOR_EACH_END)

#define FOR_EACH_HELPER(macro, arg, ...) macro(arg) FOR_EACH_AGAIN(macro, __VA_ARGS__)

#define FOR_EACH_AGAIN(macro, arg, ...) FOR_EACH_HELPER(macro, arg, __VA_ARGS__)

#define FOR_EACH_END

#define EXPAND_ARG(arg) EXPAND_ARG_IMPL arg

#define EXPAND_ARG_IMPL(direction, value1, value2) \
    if (DIRECTIONS == direction##_HELD) {          \
        key_1 = value1;                            \
        key_2 = value2;                            \
    } else

// Define the helper macros
#define COMMAND_NORMALS_IMPL(default_val, ...)                              \
    do {                                                                    \
        static uint16_t key_1 = DEFAULT_VALUE;                               \
        static uint16_t key_2 = DEFAULT_VALUE;                               \
        if (record->event.pressed) {                                        \
            EXPAND_ARGS(__VA_ARGS__) {                                      \
                key_1 = default_val;                                        \
                key_2 = DEFAULT_VALUE;                                      \
            }                                                               \
            if (!vim_emulation_enabled()) {                                 \
                tap_code16(key_1);                                            \
                if (key_2 != KC_STOP) tap_code16(key_2);                      \
                return KC_STOP;                                             \
            }                                                               \
        } else {                                                            \
            if (!vim_emulation_enabled()) {                                 \
                key_1 = key_2 = KC_STOP;                                    \
            }                                                               \
        }                                                                   \
                                                                            \
        if (vim_emulation_enabled()) {                                      \
            if (key_2 == KC_STOP) {                                         \
                return key_1;                                               \
            } else {                                                        \
                process_normal_mode_user(key_1, record, true);              \
                process_normal_mode_user(key_2, record, true);              \
                if (!record->event.pressed) return key_1 = key_2 = KC_STOP; \
            }                                                               \
        }                                                                   \
    } while (0)

*/
