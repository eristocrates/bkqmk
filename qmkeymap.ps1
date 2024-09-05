Import-Module BurntToast

Add-Type -AssemblyName presentationCore
$mediaPlayer = New-Object system.windows.media.mediaplayer

# Define the paths
$mingwPath = "I:\msys2\usr\bin\bash.exe"
$keymapPathMingw = "I:/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/akeyhd"
#$userspacePathMingw = "I:/coding/bkqmk/users/akeyhd"
$keymapPath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd"
# Play an MP3 sound
# https://stackoverflow.com/questions/25895428/how-to-play-mp3-with-powershell-simple
$filesDone = "I:\coding\bkqmk\files-done.mp3"
$baka = "I:\coding\bkqmk\naruto-saying-baka.mp3"


$logFilePath = "./qmk-output.log"
$searchString = "Copying bastardkb_charybdis_3x6_akeyhd.uf2 to userspace folder"

# Define the commands
$compile2jsonCmd = "qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km akeyhd > qmk-output.log 2>&1 ; qmk c2json --no-cpp $keymapPathMingw/keymap.c > $keymapPathMingw/c2.json"
#$compile2jsonCmd = "qmk generate-autocorrect-data $userspacePathMingw/autocorrect_dictionary.txt -kb bastardkb/charybdis/3x6 -km akeyhd ; qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km akeyhd > qmk-output.log 2>&1 ; qmk c2json --no-cpp $keymapPathMingw/keymap.c > $keymapPathMingw/c2.json"


$keymapParseCmd = "keymap -c $keymapPath\config.yaml parse -c 12 -q $keymapPath\c2.json -o $keymapPath\keymap.yaml"
$keymapPostParseCmd = ".\keymapPostParse.ps1"
$keymapDrawCmd1 = "keymap -c $keymapPath\config.yaml draw $keymapPath\keymap.yaml -o $keymapPath\keymap.svg"
$keymapDrawCmd2 = "keymap -c $keymapPath\config.yaml draw $keymapPath\keymapDesign.yaml -o $keymapPath\keymapDesign.svg"
$vimFighterTableCmd = "node .\keymapMotionInputPostParse.mjs"


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
#Invoke-InMinGW $compile2jsonCmd
if (Select-String -Path $logFilePath -Pattern $searchString) {
    # Run the remaining commands in PowerShell
    #Invoke-InMinGW $compile2jsonCmd
    Invoke-Expression $keymapParseCmd
    Invoke-Expression $keymapPostParseCmd
    Invoke-Expression ".\keymapMotionInputParse.ps1"
    Invoke-Expression $vimFighterTableCmd
    Invoke-Expression $keymapDrawCmd1
    Invoke-Expression $keymapDrawCmd2
    Write-Output "Ding! Firmware done."
    New-BurntToastNotification -Text "QMK Compilation", "Ding! Firmware done."
    $mediaPlayer.open($filesDone)
}
else {
    New-BurntToastNotification -Text "QMK Compilation", "You done goofed baka"
    Write-Output "You done goofed baka $(Resolve-Path $logFilePath)"
    $mediaPlayer.open($baka)
}


#$mediaPlayer.Play()
