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

/* -------- Number Mode -------- */
// Turn number mode on. To be called from a custom keycode
bool math_mode_enable(keyrecord_t *record);

// Turn number mode off.
void math_mode_disable(void);

// Handle each key for number mode.
void math_mode_process(uint16_t keycode, keyrecord_t *record);

/* -------- Process Record -------- */
void process_layermodes(uint16_t keycode, keyrecord_t *record);
