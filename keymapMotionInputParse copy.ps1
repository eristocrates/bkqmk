# Define the file path
$filePath = "users\AKeyHD\AKeyHD.c"

# Read the file content
$fileContent = Get-Content -Path $filePath

# Initialize variables
$inFunction = $false
$inSwitchCase = $false
$braceCount = 0
$keycodes = @()
$currentKeycode = ""
$directionCases = @()
$inDirectionSwitch = $false
$currentDirection = ""
$currentLink = ""
$currentDirectionBody = @()

# Iterate through each line of the file
foreach ($line in $fileContent) {
    # Check if we are inside the process_normal_mode_user function
    if ($line -match "uint16_t process_normal_mode_user") {
        $inFunction = $true
    }

    # Check if we are inside the switch case
    if ($inFunction -and $line -match "switch \(keycode\)") {
        $inSwitchCase = $true
    }

    # Collect keycodes inside the switch case
    if ($inSwitchCase) {
        if ($line -match "case (\w+): \{") {
            if ($currentKeycode -ne "") {
                $keycodes += @{
                    Keycode    = $currentKeycode
                    Directions = $directionCases
                }
            }
            $currentKeycode = $matches[1]
            $directionCases = @()
            $braceCount = 1
        }
        elseif ($line -match "default: \{") {
            if ($currentKeycode -ne "") {
                $keycodes += @{
                    Keycode    = $currentKeycode
                    Directions = $directionCases
                }
            }
            $currentKeycode = "default"
            $directionCases = @()
            $braceCount = 1
        }
        elseif ($braceCount -gt 0) {
            if ($line -match "{") {
                $braceCount++
            }
            if ($line -match "}") {
                $braceCount--
            }

            # Check for direction cases within the keycode case
            if ($line -match "switch \(DIRECTIONS\)") {
                $inDirectionSwitch = $true
            }

            if ($inDirectionSwitch) {
                if ($line -match "case (\w+):\s*//\s*(.+)") {
                    if ($currentDirection -ne "") {
                        $directionCases += @{
                            Direction = $currentDirection
                            Link      = $currentLink
                            Keys      = $currentDirectionBody
                        }
                    }
                    $currentDirection = $matches[1]
                    $currentLink = $matches[2]
                    $currentDirectionBody = @()
                }
                elseif ($line -match "case (\w+):") {
                    if ($currentDirection -ne "") {
                        $directionCases += @{
                            Direction = $currentDirection
                            Link      = $currentLink
                            Keys      = $currentDirectionBody
                        }
                    }
                    $currentDirection = $matches[1]
                    $currentLink = ""
                    $currentDirectionBody = @()
                }
                elseif ($line -match "default:\s*//\s*(.+)") {
                    if ($currentDirection -ne "") {
                        $directionCases += @{
                            Direction = $currentDirection
                            Link      = $currentLink
                            Keys      = $currentDirectionBody
                        }
                    }
                    $currentDirection = "default"
                    $currentLink = $matches[1]
                    $currentDirectionBody = @()
                }
                elseif ($line -match "default:") {
                    if ($currentDirection -ne "") {
                        $directionCases += @{
                            Direction = $currentDirection
                            Link      = $currentLink
                            Keys      = $currentDirectionBody
                        }
                    }
                    $currentDirection = "default"
                    $currentLink = ""
                    $currentDirectionBody = @()
                }
                elseif ($line -match "key_\d\s*=\s*(.+);") {
                    $keyValue = $matches[1]
                    if ($keyValue -notmatch "KC_CANCEL" -and $keyValue -notmatch "key_\d\s*=\s*KC_CANCEL") {
                        $currentDirectionBody += $keyValue
                    }
                }
            }

            if ($braceCount -eq 0) {
                $inDirectionSwitch = $false
                if ($currentDirection -ne "") {
                    $directionCases += @{
                        Direction = $currentDirection
                        Link      = $currentLink
                        Keys      = $currentDirectionBody
                    }
                }
                $keycodes += @{
                    Keycode    = $currentKeycode
                    Directions = $directionCases
                }
                $currentKeycode = ""
                $directionCases = @()
                $currentDirection = ""
                $currentLink = ""
                $currentDirectionBody = @()
            }
        }
    }

    # Exit the function when we reach the end
    if ($inFunction -and $line -match "}") {
        $inFunction = $false
    }
}

# Add the last keycode case if it exists
if ($currentKeycode -ne "") {
    $keycodes += @{
        Keycode    = $currentKeycode
        Directions = $directionCases
    }
}

# Display the collected keycodes and their associated direction cases
foreach ($keycode in $keycodes) {
    Write-Output "Keycode Case: $($keycode['Keycode'])"
    foreach ($direction in $keycode['Directions']) {
        Write-Output "  Direction Case: $($direction['Direction'])"
        Write-Output "  Link: $($direction['Link'])"
        foreach ($key in $direction['Keys']) {
            Write-Output "    Key: $key"
        }
    }
}
