# MSYS2

qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km brainrot > qmk-output.log 2>&1; qmk c2json --no-cpp ./keyboards/bastardkb/charybdis/3x6/keymaps/brainrot/keymap.c > ./keyboards/bastardkb/charybdis/3x6/keymaps/brainrot/c2.json

# Powershell

.\keymapPreParse.ps1; keymap parse -c 12 -q I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\c2.json > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml ; .\keymapPostParse.ps1 ; keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.svg ; keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.svg

.\keymapPreParse.ps1

keymap parse -c 12 -q I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\c2.json > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml

.\keymapPostParse.ps1

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.svg

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.svg

qmk compile -c -j 0 -kb bastardkb/charybdis/3x6 -km brainrot

qmk compile -c -kb bastardkb/charybdis/3x6 -km brainrot

qmk compile -c -j 0 -kb bastardkb/charybdis/3x6 -km brainrot > qmk-output.log 2>&1

REG ADD HKCU\Software\Classes\ms-officeapp\Shell\Open\Command /t REG_SZ /d rundll32

LED_FLAG_NONE       = 0x00  // Binary: 00000000
LED_FLAG_ALL        = 0xFF  // Binary: 11111111
LED_FLAG_MODIFIER   = 0x01  // Binary: 00000001
LED_FLAG_UNDERGLOW  = 0x02  // Binary: 00000010
LED_FLAG_KEYLIGHT   = 0x04  // Binary: 00000100
LED_FLAG_INDICATOR  = 0x08  // Binary: 00001000

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
