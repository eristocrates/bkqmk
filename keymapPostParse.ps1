# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\brainrot\keymap.yaml"

# Read the content of the file
$content = Get-Content -Path $filePath

# Replace all occurrences of the specified string
$modifiedContent = $content -replace "��", "''"

# Write the modified content back to the file
Set-Content -Path $filePath -Value $modifiedContent
