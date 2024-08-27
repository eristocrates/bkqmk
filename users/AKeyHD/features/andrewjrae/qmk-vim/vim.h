/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include QMK_KEYBOARD_H
bool vim_insert_mode_enabled(void);
bool vim_normal_mode_enabled(void);
// Check to see if vim mode is enabled
bool vim_mode_enabled(void);
// Enable vim mode
void enable_vim_mode(void);
// Disable vim mode
void disable_vim_mode(void);
// Toggle vim mode
void toggle_vim_mode(void);

// Check to see if vim should be emulated with qmk_vim
bool vim_emulation_enabled(void);
// Enable vim emulation
void enable_vim_emulation(void);
// Disable vim emulation
void disable_vim_emulation(void);
// Toggle vim emulation
void toggle_vim_emulation(void);

#ifdef ONESHOT_QMK_VIM
// Start vim mode
void start_oneshot_vim(void);
// Stop vim mode
void stop_oneshot_vim(void);
#endif

#ifdef QMK_VIM_FOR_ALL
// Check to see if mac mode is enabled
bool vim_for_mac_enabled(void);
// Enable mac mode
void enable_vim_for_mac(void);
// Disable mac mode
void disable_vim_for_mac(void);
// Toggle mac mode
void toggle_vim_for_mac(void);
#endif
// Process keycode for vim mode
bool process_vim_mode(uint16_t keycode, const keyrecord_t *record);

extern bool qmk_vim_enabled;
extern bool vim_emulation; // false when in a genuine vim environment
