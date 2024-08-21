# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml"

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# TODO add logic to draw piercing mods
# Replace all occurrences of the specified string
$content = $content -replace "��", "''" # clean garbled XXXXXXX
$content = $content -replace "L0", "Brainrot"
#$content = $content -replace "LTP ARC", "{t: arcane, s: anti-sfb, h: repeat}"
$content = $content -replace "\bL1\b", "Combo Reference"
$content = $content -replace "\bL2\b", "Shift Gr"
$content = $content -replace "\bL3\b", "Ctrl Gr"
$content = $content -replace "L4", "Alt Gr"
$content = $content -replace "L5", "Gui Gr"
$content = $content -replace "L6", "Pointer"
$content = $content -replace "L7", "Pointer Options"
$content = $content -replace "L8", "Pointer Navigation"
$content = $content -replace "L9", "Math"
$content = $content -replace "L10", "Vim Motion"
$content = $content -replace "L11", "Function"
$content = $content -replace "L12", "Media"
$content = $content -replace "L13", "N-Shot Mods"
$content = $content -replace "L14", "Game"
$content = $content -replace "L15", "Thinqu"
$content = $content -replace "L16", "Thinqu Left"
# LT/LM threshold
$content = $content -replace "L17", "Thinqu Right"
$content = $content -replace "L18", "Keyboard"
$content = $content -replace "L19", "Secret"
$content = $content -replace "L20", "Naginata"
$content = $content -replace "L21", "Shingeta"
$content = $content -replace "L22", "Qwerty"
$content = $content -replace "L23", "Random"
# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
