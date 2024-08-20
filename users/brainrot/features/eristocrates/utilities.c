#include "utilities.h"

void send_string_with_caps_word(const char *str) {
    if (is_caps_word_on()) {
        // Add shift modifier for each character in the string
        while (*str) {
            // register_code(KC_LSFT);
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            send_char(*str);
            // unregister_code(KC_LSFT);
            str++;
        }
    } else {
        // Send the string as is
        SEND_STRING(str);
    }
}
