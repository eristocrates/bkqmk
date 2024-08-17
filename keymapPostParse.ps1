# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml"

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# Replace all occurrences of the specified string
$content = $content -replace "��", "''"
$content = $content -replace "L0", "Brainrot"
$content = $content -replace "\bL1\b", "Pointer"
$content = $content -replace "\bL2\b", "Left Shift Gr"
$content = $content -replace "\bL3\b", "Right Shift Gr"
$content = $content -replace "L4", "Vim Navigation"
$content = $content -replace "L5", "Vim Numbers"
$content = $content -replace "L6", "Naginata"
$content = $content -replace "L7", "Shingeta"
$content = $content -replace "L8", "Qwerty"
$content = $content -replace "L9", "Thinqu"
$content = $content -replace "L10", "Game"
$content = $content -replace "L11", "Layer"
$content = $content -replace "L12", "Shortcut"
$content = $content -replace "L13", "Keyboard"
$content = $content -replace "L14", "Math"
$content = $content -replace "L15", "Media"
$content = $content -replace "L16", "Secret"
$content = $content -replace "L17", "Random"

# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
