
#include "utilities.h"
/**
 * @brief Grabs the basic keycode from a quantum keycode
 * https://github.com/drashna/qmk_userspace/blob/e57b3a9636cf740d88d8ea7ddeced5eaafa38fa7/users/drashna/drashna.c#L440
 * @param keycode extended keycode to extract from
 * @param record keyrecord used for checking tap count/hold
 * @param check_hold do we check for hold keycode status
 * @return uint16_t returns the basic keycode
 */
uint16_t extract_basic_keycode(uint16_t keycode, keyrecord_t *record, bool check_hold) {
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count || !check_hold) {
            keycode = keycode_config(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
        } else {
            keycode = keycode_config(0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10));
        }
    } else if (IS_QK_LAYER_TAP(keycode) && (record->tap.count || !check_hold)) {
        keycode = keycode_config(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
    } else if (IS_QK_MODS(keycode)) {
        keycode = keycode_config(QK_MODS_GET_BASIC_KEYCODE(keycode));
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = keycode_config(0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10));
    } else if (IS_QK_BASIC(keycode)) {
        keycode = keycode_config(keycode);
    }

    return keycode;
}
