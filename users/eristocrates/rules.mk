# Enable common features
TAP_DANCE_ENABLE = yes
REPEAT_KEY_ENABLE = yes
COMBO_ENABLE = yes
LEADER_ENABLE = yes
CAPS_WORD_ENABLE = yes
CONSOLE_ENABLE = yes
# AUTO_SHIFT_ENABLE = yes
UNICODE_COMMON = yes
UNICODE_ENABLE = yes
# RGB_MATRIX_CUSTOM_USER = yes
# XAP_ENABLE = yes  # one day
# Disable unused features
VIA_ENABLE = no
#AUTOCORRECT_ENABLE = yes
TOP_SYMBOLS = yes
DEFERRED_EXEC_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

INTROSPECTION_KEYMAP_C = eristocrates.c

# Add custom features
SRC += features/andrewjrae/qmk-vim/actions.c
SRC += features/andrewjrae/qmk-vim/mac_mode.c
SRC += features/andrewjrae/qmk-vim/modes.c
SRC += features/andrewjrae/qmk-vim/motions.c
SRC += features/andrewjrae/qmk-vim/numbered_actions.c
SRC += features/andrewjrae/qmk-vim/process_func.c
SRC += features/andrewjrae/qmk-vim/vim.c
#SRC += features/callum/oneshot.c
SRC += features/callum/swapper.c
SRC += features/drashna/utilities.c
SRC += features/empressabyss/arcane_keys.c
SRC += features/eristocrates/modal_keys.c
SRC += features/eristocrates/rgb_matrix_stuff.c
SRC += features/eristocrates/eristocrates_colors.c
SRC += features/eristocrates/utilities.c
SRC += features/getreuer/layer_lock.c
#SRC += features/getreuer/custom_shift_keys.c
SRC += features/kalabasa/bitwise_num.c
SRC += features/kalabasa/bitwise_f.c
SRC += features/possumvibes/mod_lock.c
SRC += features/possumvibes/nshot_mod.c
SRC += features/possumvibes/override_keys.c
SRC += features/possumvibes/smart_layer.c
SRC += features/anantoghosh/skip_bigrams.c
# don't forget to add .h paths to eristocrates.h!


# VPATH += keyboards/gboards
