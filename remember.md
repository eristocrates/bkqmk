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
