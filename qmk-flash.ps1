# Define the source and destination paths
$sourcePath = "E:\uranus\coding\bkqmk\bastardkb_charybdis_3x6_eristocrates.uf2"
$destinationPath = "I:\bastardkb_charybdis_3x6_eristocrates.uf2"

# Check if the source file exists
if (Test-Path $sourcePath) {
    try {
        # Copy the file to the destination
        Copy-Item -Path $sourcePath -Destination $destinationPath -Force
        Write-Host "File copied successfully to N: drive."
    }
    catch {
        Write-Host "Error copying file: $_"
    }
}
else {
    Write-Host "Source file not found: $sourcePath"
}
