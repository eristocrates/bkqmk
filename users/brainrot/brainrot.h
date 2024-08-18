#pragma once

// Features
#include "features/eristocrates/modal_keys.h"
#include "features/empressabyss/arcane_keys.h"
#include "features/drashna/utilities.h"
#include "features/andrewjrae/qmk-vim/mac_mode.h"
#include "features/andrewjrae/qmk-vim/process_func.h"
#include "features/andrewjrae/qmk-vim/numbered_actions.h"
#include "features/andrewjrae/qmk-vim/motions.h"
#include "features/andrewjrae/qmk-vim/actions.h"
#include "features/andrewjrae/qmk-vim/modes.h"
#include "features/andrewjrae/qmk-vim/vim.h"
#include "features/possumvibes/mod_lock.h"
#include "features/possumvibes/nshot_mod.h"
#include "features/possumvibes/override_keys.h"
#include "features/possumvibes/smart_layer.h"

#ifdef COMBO_ENABLE
#    include "keymap_combo.h"
#endif

extern void               bspc_finished(tap_dance_state_t *state, void *user_data);
extern void               bspc_cln_reset(tap_dance_state_t *state, void *user_data);
extern tap_dance_action_t tap_dance_actions[];
