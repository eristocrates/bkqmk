Import-Module BurntToast

Add-Type -AssemblyName presentationCore
$mediaPlayer = New-Object system.windows.media.mediaplayer

# Define the paths
$mingwPath = "C:\msys64\usr\bin\bash.exe"
$keymapPathMingw = "E:/uranus/coding/bkqmk/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates"
#$userspacePathMingw = "E:/uranus/coding/bkqmk/users/eristocrates"
$keymapPath = "E:\uranus\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\eristocrates"

# Play an MP3 soundi
# https://stackoverflow.com/questions/25895428/how-to-play-mp3-with-powershell-simple
$filesDone = "E:\uranus\coding\bkqmk\files-done.mp3"
$baka = "E:\uranus\coding\bkqmk\naruto-saying-baka.mp3"
$enumFilePath = "E:\uranus\coding\bkqmk\users\eristocrates\eristocrates_keycodes.h"

$logFilePath = "./qmk-output.log"
$searchString = "Copying bastardkb_charybdis_3x6_eristocrates.uf2 to userspace folder"

# Define the commands
$compile2jsonCmd = "qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km eristocrates > qmk-output.log 2>&1 ; qmk c2json --no-cpp $keymapPathMingw/keymap.c > $keymapPathMingw/c2.json"
#$compile2jsonCmd = "qmk generate-autocorrect-data $userspacePathMingw/autocorrect_dictionary.txt -kb bastardkb/charybdis/3x6 -km eristocrates ; qmk compile -j 0 -kb bastardkb/charybdis/3x6 -km eristocrates > qmk-output.log 2>&1 ; qmk c2json --no-cpp $keymapPathMingw/keymap.c > $keymapPathMingw/c2.json"



$keymapPostParseCmd = ".\keymapPostParse.ps1"

$arcaneCmd = "node .\parseArcane.mjs"







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
## Invoke-InMinGW $compile2jsonCmd
if (Select-String -Path $logFilePath -Pattern $searchString) {
    # Run the remaining commands in PowerShell
    $enumContent = Get-Content -Path $enumFilePath -Raw
    $enumPattern = 'enum layers \{([^}]*)\}'
    $matches = [regex]::Matches($enumContent, $enumPattern)
    if ($matches.Success) {
        $enumBlock = $matches.Groups[1].Value

        # Parse the individual layer names
        $keyLayers = @()
        $comboLayers = @(
            "BITCOMBO",
            "SYSKEYS"
        )
        $sliceLayers = @(
            "VIMSLICE",
            "ARROWSLICE",
            "NAVSLICE",
            "BINSLICE"
        )
        foreach ($line in $enumBlock -split "`n") {
            $line = $line.Trim()
            if ($line -match '^\s*_(\w+),?\s*$') {
                $layerName = $line -replace '^\s*_(\w+),?\s*$', '$1'
                $keyLayers += $layerName
            }
        }
        # Join the array into a single string with spaces
        $KeyLayerString = $keyLayers -join " "
        $ComboLayerString = $comboLayers -join " "
        Invoke-Expression "keymap -c $keymapPath\config.yaml parse -c 12 -q $keymapPath\c2.json -l $KeyLayerString -o $keymapPath\keymap.yaml"
        Invoke-Expression "keymap -c $keymapPath\config.yaml draw $keymapPath\keymap.yaml  -o $keymapPath\draw\keymap.svg"

        Invoke-Expression $keymapPostParseCmd

        foreach ($layer in $($keyLayers + $sliceLayers)) {
            Invoke-Expression "keymap -c $keymapPath\config.yaml draw $keymapPath\keymap.yaml -s $layer --keys-only -o $keymapPath\draw\svg\$layer.svg"
            Invoke-Expression "cairosvg -f png -o $keymapPath\draw\png\$layer.png $keymapPath\draw\svg\$layer.svg"
        }
        foreach ($layer in $comboLayers) {
            Invoke-Expression "keymap -c $keymapPath\config.yaml parse -c 12 -q $keymapPath\blank.json --virtual-layers $layer -o $keymapPath\$layer.yaml"
            # Construct the file paths
            $textFilePath = Join-Path -Path $keymapPath -ChildPath "$($layer).txt"
            $yamlFilePath = Join-Path -Path $keymapPath -ChildPath "$($layer).yaml"

            # Read the content from the source text file
            $textContent = Get-Content -Path $textFilePath

            # Append the content to the destination YAML file
            Add-Content -Path $yamlFilePath -Value $textContent
            Invoke-Expression "keymap -c $keymapPath\config.yaml draw $keymapPath\$layer.yaml -s $layer --combos-only -o $keymapPath\draw\svg\$layer.svg"
            Invoke-Expression "cairosvg -f png -o $keymapPath\draw\png\$layer.png $keymapPath\draw\svg\$layer.svg"
        }
    }

    Invoke-Expression $arcaneCmd
    Write-Output "Ding! Firmware done."
    New-BurntToastNotification -Text "QMK Compilation", "Ding! Firmware done."
    $mediaPlayer.open($filesDone)
}
else {
    New-BurntToastNotification -Text "QMK Compilation", "You done goofed baka"
    Write-Output "You done goofed baka $(Resolve-Path $logFilePath)"
    $mediaPlayer.open($baka)
}


$mediaPlayer.Play()
