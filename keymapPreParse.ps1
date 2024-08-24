# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\c2.json"

# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# Perform the replacements
$content = $content -replace '"layout": "HRM"', '"layout": "LAYOUT"'
$content = $content -replace 'LAYOUT\(\\n  \/\/ ', ''
$content = $content -replace '\\[a-z0-9]{1,5}', ''
$content = $content -replace '\/\/', ''
$content = $content -replace '[\s]+\)', ''
$content = $content -replace '\["[\s]+', '["'
$content = $content -replace ',[\s]+', '", "'
$content = $content -replace '\"\"', '"'
$content = $content -replace '\]\", \"\[', '], ['

# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
