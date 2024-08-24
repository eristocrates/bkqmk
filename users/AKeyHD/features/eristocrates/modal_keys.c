#include "modal_keys.h"

bool semicolon_mode   = false;
bool smart_space_mode = true;
bool last_smart_space = false;
bool autopair_mode    = false; // auto  pairs of ()[]{} '' "" `` <>
// TOOD hook into/toggle extant pair symbol implementation
bool ampersand_mode   = false; // and/&
bool delete_word_mode = true;  // bspc+del word erase
bool kana_input_mode  = false; // romaji/kana input
bool work_mode        = false; // swap enter with ctrl+h

// TODO maybe move a process modal_keys function into here? probably process off of keycode like smart layers does. except i'm using leader keys to switch modes....which means there needs to be a toggle function for each mode.
