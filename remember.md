# MSYS2

qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km akeyhd > qmk-output.log 2>&1; qmk c2json --no-cpp ./keyboards/bastardkb/charybdis/3x6/keymaps/akeyhd/keymap.c > ./keyboards/bastardkb/charybdis/3x6/keymaps/akeyhd/c2.json
qmk compile -c -j 0 -kb bastardkb/charybdis/3x6 -km akeyhd

qmk compile -c -kb bastardkb/charybdis/3x6 -km akeyhd

qmk compile -c -j 0 -kb bastardkb/charybdis/3x6 -km akeyhd > qmk-output.log 2>&1

qmk generate-compilation-database -kb bastardkb/charybdis/3x6 -km akeyhd ;
qmk info -kb bastardkb/charybdis/3x6 -m

# Powershell

.\keymapPreParse.ps1; keymap parse -c 12 -q I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\c2.json > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml ; .\keymapPostParse.ps1 ; keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.svg ; keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymapDesign.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymapDesign.svg

.\keymapPreParse.ps1

keymap parse -c 12 -q I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\c2.json > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml

.\keymapPostParse.ps1

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.svg

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymapDesign.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymapDesign.svg

keymap -c i:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\config.yaml draw i:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml -s random > i:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\blanks.svg

REG ADD HKCU\Software\Classes\ms-officeapp\Shell\Open\Command /t REG_SZ /d rundll32

LED_FLAG_NONE       = 0x00  // Binary: 00000000
LED_FLAG_ALL        = 0xFF  // Binary: 11111111
LED_FLAG_MODIFIER   = 0x01  // Binary: 00000001
LED_FLAG_UNDERGLOW  = 0x02  // Binary: 00000010
LED_FLAG_KEYLIGHT   = 0x04  // Binary: 00000100
LED_FLAG_INDICATOR  = 0x08  // Binary: 00001000

264KB SRAM on the rp2040

// COMB(CB_TH, KC_TH, LH_MDLE, LH_INDX) // testing going from this to a more literal position of t and h
keymap formatting
.,+6s/,\s+([A-Z])/,\1/g

  [XXXXXXXX] = LAYOUT(
  /* ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮ */
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  /* ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤ */
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  /* ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤ */
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  /* ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯ */
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  /*                            ╰───────────────────────────╯ ╰──────────────────╯                                     */
  ),

  [________] = LAYOUT(
  /* ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮ */
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  /* ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤ */
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  /* ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤ */
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  /* ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯ */
                                  _______, _______, _______,    _______, _______
  /*                            ╰───────────────────────────╯ ╰──────────────────╯                                     */
  ),

        /* in all layers, color keycoded keys main and accent 2 otherwise */                                                                \
        if (i == 40 || keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {                                                      \
            MAIN_COLOR                                                                                                                      \
        } else {                                                                                                                            \
            ACCENT_COLOR2                                                                                                                   \
        }                                                                                                                                   \
        /* in default layer track vim emulation through arcane columns and bottom right corner */                                           \
        if (get_highest_layer(default_layer_state) == layer) {                                                                              \
            if (i == 15 || i == 16 || i == 17 || i == 23 || i == 36 || i == 37 || i == 38) {                                                \
                if (vim_emulation) {                                                                                                        \
                    HIGHLIGHT_COLOR2                                                                                                        \
                } else if (vim_emulation) {                                                                                                 \
                    ACCENT_COLOR1                                                                                                           \
                }                                                                                                                           \
            }                                                                                                                               \
            /* in default layer, track insert vs normal mode */                                                                             \
            if (vim_mode_index == INSERT_MODE && (i == 8 || i == 9)) {                                                                      \
                if (vim_emulation) {                                                                                                        \
                    HIGHLIGHT_COLOR1                                                                                                        \
                } else if (vim_emulation) {                                                                                                 \
                    ACCENT_COLOR2                                                                                                           \
                }                                                                                                                           \
            } else if (vim_mode_index == NORMAL_MODE) {                                                                                     \
                if ((i == 35 || i == 30 || i == 29 || i == 24)) {                                                                           \
                    if (vim_emulation) {                                                                                                    \
                        HIGHLIGHT_COLOR1                                                                                                    \
                    } else if (vim_emulation) {                                                                                             \
                        ACCENT_COLOR2                                                                                                       \
                    }                                                                                                                       \
                }                                                                                                                           \
            }                                                                                                                               \
            /* in _VIMFIGHTER layer highlight inner toggle thumb key */                                                                     \
        } else if (IS_LAYER_ON(3)) {                                                                                                        \
            if (i == 39) {                                                                                                                  \
                if (vim_emulation) {                                                                                                        \
                    HIGHLIGHT_COLOR2                                                                                                        \
                } else if (vim_emulation) {                                                                                                 \
                    ACCENT_COLOR1                                                                                                           \
                }                                                                                                                           \
            } else {                                                                                                                        \
                MAIN_COLOR                                                                                                                  \
            }                                                                                                                               \
        } else {                                                                                                                            \
            /*on other layers do not differentiate arcane columns nor bottom right corner */                                                \
            if (i == 15 || i == 16 || i == 17 || i == 23 || i == 36 || i == 37 || i == 38) {                                                \
                ACCENT_COLOR2                                                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
