#pragma once
#include <string.h>

// Features
#include "features/andrewjrae/qmk-vim/actions.h"
#include "features/andrewjrae/qmk-vim/mac_mode.h"
#include "features/andrewjrae/qmk-vim/modes.h"
#include "features/andrewjrae/qmk-vim/motions.h"
#include "features/andrewjrae/qmk-vim/numbered_actions.h"
#include "features/andrewjrae/qmk-vim/process_func.h"
#include "features/andrewjrae/qmk-vim/vim.h"
// #include "features/callum/oneshot.h"
#include "features/callum/swapper.h"
#include "features/drashna/utilities.h"
#include "features/empressabyss/arcane_keys.h"
#include "features/eristocrates/modal_keys.h"
#include "features/eristocrates/utilities.h"
#include "features/eristocrates/rgb_matrix_stuff.h"
#include "features/eristocrates/eristocrates_colors.h"
#include "features/getreuer/layer_lock.h"
#include "features/kalabasa/bitwise_num.h"
#include "features/kalabasa/bitwise_f.h"
#include "features/possumvibes/mod_lock.h"
#include "features/possumvibes/nshot_mod.h"
#include "features/possumvibes/override_keys.h"
#include "features/possumvibes/smart_layer.h"
#include "features/anantoghosh/skip_bigrams.h"
// #include "features/stasmarkin/sm_td.h"
#include "eristocrates_keycodes.h"
// don't forget to add .c paths to rules.mk!

#ifdef COMBO_ENABLE
#    include "keymap_combo.h"
#endif

// TODO double check if this can be removed
extern void               bspc_finished(tap_dance_state_t *state, void *user_data);
extern void               bspc_reset(tap_dance_state_t *state, void *user_data);
extern tap_dance_action_t tap_dance_actions[];
