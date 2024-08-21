#pragma once
#include QMK_KEYBOARD_H

/* -------- Pointer Mode -------- */
// Turn number mode on. To be called from a custom keycode
bool pointer_mode_enable(keyrecord_t *record);

// Turn number mode off.
void pointer_mode_disable(void);

// Handle each key for number mode.
void pointer_mode_process(uint16_t keycode, keyrecord_t *record);

extern bool _pointer_mode_active;

/* -------- Vim Motion Mode -------- */
// Turn number mode on. To be called from a custom keycode
bool vim_motion_mode_enable(keyrecord_t *record);

// Turn number mode off.
void vim_motion_mode_disable(void);

// Handle each key for number mode.
void vim_motion_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Number Mode -------- */
// Turn number mode on. To be called from a custom keycode
bool math_mode_enable(keyrecord_t *record);

// Turn number mode off.
void math_mode_disable(void);

// Handle each key for number mode.
void math_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Function Mode -------- */
// Turn Func mode on. To be called from a custom keycode.
bool func_mode_enable(keyrecord_t *record);

// Turn func mode off.
void func_mode_disable(void);

// Handle each key for func mode.
void func_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Sym Mode -------- */
// Turn Sym mode on. To be called from a custom keycode.
bool sym_mode_enable(keyrecord_t *record);

// Turn sym mode off.
void sym_mode_disable(void);

// Handle each key for sym mode.
void sym_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Macro Mode -------- */
// Turn Macro mode on. To be called from a custom keycode.
bool macro_mode_enable(keyrecord_t *record);

// Turn macro mode off.
void macro_mode_disable(void);

// Handle each key for macro mode.
void macro_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record);
