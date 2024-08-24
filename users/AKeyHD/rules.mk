# Enable common features
TAP_DANCE_ENABLE = yes
REPEAT_KEY_ENABLE = yes
COMBO_ENABLE = yes
LEADER_ENABLE = yes
CAPS_WORD_ENABLE = yes
CONSOLE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

# Disable unused features
VIA_ENABLE = no
#AUTOCORRECT_ENABLE = yes

INTROSPECTION_KEYMAP_C = akeyhd.c

# Add custom features
SRC += features/andrewjrae/qmk-vim/mac_mode.c
SRC += features/andrewjrae/qmk-vim/process_func.c
SRC += features/andrewjrae/qmk-vim/numbered_actions.c
SRC += features/andrewjrae/qmk-vim/motions.c
SRC += features/andrewjrae/qmk-vim/actions.c
SRC += features/andrewjrae/qmk-vim/modes.c
SRC += features/andrewjrae/qmk-vim/vim.c
SRC += features/drashna/utilities.c
SRC += features/empressabyss/arcane_keys.c
SRC += features/eristocrates/modal_keys.c
SRC += features/eristocrates/utilities.c
SRC += features/possumvibes/mod_lock.c
SRC += features/possumvibes/nshot_mod.c
SRC += features/possumvibes/override_keys.c
SRC += features/possumvibes/smart_layer.c


# VPATH += keyboards/gboards
