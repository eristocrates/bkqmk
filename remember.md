qmk c2json /i/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot/keymap.c > /i/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot/c2.json

keymap parse -c 12 -q I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\c2.json > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.svg

keymap -c I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\config.yaml draw I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.yaml > I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymapDesign.svg
