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


# VPATH += keyboards/gboards
