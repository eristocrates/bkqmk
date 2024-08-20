# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml"

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# Replace all occurrences of the specified string
$content = $content -replace "��", "''" # clean garbled XXXXXXX
$content = $content -replace "L0", "Brainrot"
$content = $content -replace "\bL1\b", "Combo Reference"
$content = $content -replace "\bL2\b", "Left Shift Gr"
$content = $content -replace "\bL3\b", "Right Shift Gr"
$content = $content -replace "L4", "Math"
$content = $content -replace "L5", "Vim Motion"
$content = $content -replace "L6", "Vim Numbers"
$content = $content -replace "L7", "Function"
$content = $content -replace "L8", "Media"
$content = $content -replace "L9", "Layer"
$content = $content -replace "L10", "Game"
$content = $content -replace "L11", "Thinqu"
$content = $content -replace "L12", "Thinqu Left Shift Gr"
$content = $content -replace "L13", "Thinqu Right Shift Gr"
$content = $content -replace "L14", "Keyboard"
$content = $content -replace "L15", "Pointer"
$content = $content -replace "L16", "Pointer Options"
# LT/LM threshold
$content = $content -replace "L17", "Secret"
$content = $content -replace "L18", "Naginata"
$content = $content -replace "L19", "Shingeta"
$content = $content -replace "L20", "Qwerty"
$content = $content -replace "L21", "Random"
# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
