# Define the paths
$mingwPath = "I:\msys2\usr\bin\bash.exe"
$keymapPathMingw = "I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/brainrot"
$userspacePathMingw = "I:/coding/bkqmk/users/brainrot"
$keymapPath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot"

# Define the commands
$compile2jsonCmd = "qmk generate-autocorrect-data $userspacePathMingw/autocorrect_dictionary.txt -kb bastardkb/charybdis/3x6 -km brainrot ; qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km brainrot > qmk-output.log 2>&1 ; qmk c2json --no-cpp $keymapPathMingw/keymap.c > $keymapPathMingw/c2.json"


#$keymapPreParseCmd = ".\keymapPreParse.ps1"
$keymapParseCmd = "keymap parse -c 12 -q $keymapPath\c2.json > $keymapPath\keymap.yaml"
$keymapPostParseCmd = ".\keymapPostParse.ps1"
$keymapDrawCmd1 = "keymap -c $keymapPath\config.yaml draw $keymapPath\keymap.yaml > $keymapPath\keymap.svg"
$keymapDrawCmd2 = "keymap -c $keymapPath\config.yaml draw $keymapPath\keymapDesign.yaml > $keymapPath\keymapDesign.svg"

# Function to run a command in MinGW
function Invoke-InMinGW {
    param (
        [string]$command
    )
    $env:MSYSTEM = "MINGW64"
    $env:CHERE_INVOKING = "1"
    Start-Process -FilePath $mingwPath -ArgumentList "--login", "-i", "-c", "`"$command`"" -NoNewWindow -Wait
}
# Run the commands
Invoke-InMinGW $compile2jsonCmd

# Run the remaining commands in PowerShell
#Invoke-Expression $keymapPreParseCmd
Invoke-Expression $keymapParseCmd
Invoke-Expression $keymapPostParseCmd
Invoke-Expression $keymapDrawCmd1
Invoke-Expression $keymapDrawCmd2
