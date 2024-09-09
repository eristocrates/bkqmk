
/*
Author: Ananto Ghosh github.com/anantoghosh
Additional details at https://blog.mein.in/reducing-skip-bigrams-strain

This feature aims to reduce the need for excessive finger movement when typing
"2u Same finger bigrams" and "2u skip bigrams",
which is typing keys in the same column separated by two rows,
either immediately or after typing vowels.

For example if your layout contains a column like:
R2  M
R3  N
R4  L
and if you need to type ML, MAL, MEAL etc. then your finger would need to move
the distance of two rows quickly.
You can use https://cyanophage.github.io/ to find out which bigrams affect you.

This implementation will set a "BIGRAM_KEY" which will type the separated letter.
So if you define a skip_bigram_pair for (M, L) then typing:
M > BIGRAM_KEY will type ML.
M > A > BIGRAM_KEY will type MAL.
M > E > A > BIGRAM_KEY will type MEAL.
M > A > BIGRAM_KEY > BIGRAM_KEY will type MALL.

You can set any pair of keys an "skip_bigram_pairs" which will type the separated key.

The first bigram letter can be followed by any number of (a, e, i, o, u, y) letters.
M > O > O > O > BIGRAM_KEY will type MOOOL.
*/
#include QMK_KEYBOARD_H
#include "../../akeyhd_keycodes.h"
#include "../drashna/utilities.h"

/*
The trigger Keycode.
Define a keycode for typing the second letter of the bigram.
You can place this key in a lesser used position in your layout.
*/
#define BIGRAM_KEY KC_DSFB

/* Define an array of bigram pairs. Adjust as per your layout */
static const uint16_t skip_bigram_pairs[][2] = {
    {KC_C, KC_F}, // C > BIGRAM_KEY will type CF
    {KC_F, KC_C}, // define pairs for both directions
    {KC_L, KC_M}, {KC_M, KC_L}, {KC_D, KC_V}, {KC_V, KC_D},
    {KC_B, KC_G}, {KC_G, KC_D}, {KC_K, KC_Y}
    // more pairs could be specified here
};

/* Determine the length of the bigram array */
static const uint8_t skip_bigram_pairs_length = sizeof(skip_bigram_pairs) / sizeof(skip_bigram_pairs[0]);

/* Flag indicating whether bigram mode is active */
bool skip_bigram_mode = false;

/* Index of the current pair being processed */
uint8_t skip_bigrams_pair_idx = 0;

/* Function to determine if a keycode is the first of a bigram pair */
static inline bool pressed_first_bigram_key(uint16_t basic_keycode) {
    for (uint8_t i = 0; i < skip_bigram_pairs_length; i++) {
        if (basic_keycode == skip_bigram_pairs[i][0]) {
            skip_bigrams_pair_idx = i;
            return true;
        }
    }

    return false;
}

/*
Function to determine which letters are ignored after pressing the first letter
of a bigram.
Eg. M > O > O > O > BIGRAM_KEY will type MOOOL. The Os do not affect the bigram mode.
Here we are ignoring (a, e, i, o, u, y), i.e. the other hand keys in handsdown
layout. Change it as per your layout needs.
*/
static inline bool is_ignore_letter(uint16_t basic_keycode) {
    switch (basic_keycode) {
        case KC_A:
        case KC_E:
        case KC_O:
        case KC_U:
        case KC_I:
        case KC_Y:
        case KC_P:
            return true;
        default:
            return false;
    }
}

/* Main entry point: Process key presses to handle bigram mode */
bool process_skip_bigrams(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t basic_keycode = keycode; // extract_basic_keycode(keycode, record, false); // keycode & 0x00FF;

        /* If the keycode is the first of a bigram pair, activate bigram mode */
        if (pressed_first_bigram_key(basic_keycode)) {
            skip_bigram_mode = true;
            return true;
        }

        /* If bigram mode is active, handle the keycode accordingly */
        if (skip_bigram_mode) {
            /* If the keycode is an ignored letter, continue as normal */
            if (is_ignore_letter(basic_keycode)) {
                return true;
            }

            /* If the keycode is the trigger key, tap the second keycode of
            the current bigram pair */
            if (basic_keycode == BIGRAM_KEY) {
                tap_code16(skip_bigram_pairs[skip_bigrams_pair_idx][1]);
                return false;
            }

            /* If the keycode is any other key, deactivate bigram mode */
            skip_bigram_mode = false;
        }
    }

    return true;
}
