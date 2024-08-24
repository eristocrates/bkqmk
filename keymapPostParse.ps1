# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml"

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# TODO add logic to draw piercing mods
# Replace all occurrences of the specified string
$content = $content -replace "��", "''" # clean garbled XXXXXXX
$content = $content -replace "L0", "AKeyHD"
#$content = $content -replace "LTP ARC", "{t: arcane, s: anti-sfb, h: repeat}"
$content = $content -replace "\bL1\b", "Combo Reference"
$content = $content -replace "\bL2\b", "Piercing Ctrl"
$content = $content -replace "\bL3\b", "Piercing Alt"
$content = $content -replace "L4", "Piercing Gui"
$content = $content -replace "L5", "Pointer"
$content = $content -replace "L6", "Pointer Options"
$content = $content -replace "L7", "Pointer Navigation"
$content = $content -replace "L8", "Math"
$content = $content -replace "L9", "Vim Motion"
$content = $content -replace "L10", "Function"
$content = $content -replace "L11", "Media"
$content = $content -replace "L12", "N-Shot Mods"
$content = $content -replace "L13", "Game"
$content = $content -replace "L14", "Thinqu"
$content = $content -replace "L15", "Thinqu Left"
$content = $content -replace "L16", "Thinqu Right"
# LT/LM threshold
$content = $content -replace "L17", "Keyboard"
$content = $content -replace "L18", "Secret"
$content = $content -replace "L19", "Naginata"
$content = $content -replace "L20", "Shingeta"
$content = $content -replace "L21", "Qwerty"
$content = $content -replace "L22", "Random"
# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
