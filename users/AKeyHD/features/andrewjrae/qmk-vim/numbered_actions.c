#include "numbered_actions.h"
#include "vim.h"

int16_t motion_counter = 0;
bool    process_numbers(uint16_t keycode, const keyrecord_t *record) {
#ifdef QMK_VIM_NUMBERED_JUMPS
    if (vim_emulation && keycode >= KC_1 && keycode <= KC_0) {
        if (record->event.pressed) {
            motion_counter *= 10;
            if (keycode != KC_0) {
                motion_counter += keycode - KC_1 + 1;
            }
        }
        return motion_counter == 0;
    }
#endif
    return true;
}

inline void decrement_motion_counter(void) {
#ifdef QMK_VIM_NUMBERED_JUMPS
    motion_counter -= motion_counter > 0;
#endif
}
