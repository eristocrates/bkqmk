# Enable common features
TAP_DANCE_ENABLE = yes
REPEAT_KEY_ENABLE = yes
COMBO_ENABLE = yes

# Disable unused features
VIA_ENABLE = no
CONSOLE_ENABLE = no

INTROSPECTION_KEYMAP_C = brainrot.c

# Add custom features
SRC += features/arcane_keys.c
SRC += features/drashna.c
SRC += features/qmk-vim/mac_mode.c
SRC += features/qmk-vim/process_func.c
SRC += features/qmk-vim/numbered_actions.c
SRC += features/qmk-vim/motions.c
SRC += features/qmk-vim/actions.c
SRC += features/qmk-vim/modes.c
SRC += features/qmk-vim/vim.c


# VPATH += keyboards/gboards
