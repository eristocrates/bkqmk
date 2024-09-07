$comboFilePath = "I:\coding\bkqmk\users\AKeyHD\combos.def"
# Read the content of the combos file
$comboContent = Get-Content -Path $comboFilePath -Raw
$comboTempOutput = "I:\coding\bkqmk\comboTemp.txt"
$jsonOutputPath = "I:\coding\bkqmk\comboKeys.json"
$content = ""
$dataToAppend = @()
$jsonData = @()

function Get-StringIndex {
    param (
        [string]$string
    )

    # Check the comboRef dictionary
    if ($comboRef.ContainsKey($string)) {
        $value = $comboRef[$string]
        return $value
    }
    else {
        Write-Error "String '$string' not found in the list."
        return $null
    }
}

# Define the list of strings
$comboRefKeycodes = @(
    "LT_OUTR", "LT_PNKY", "LT_RING", "LT_MDLE", "LT_INDX", "LT_INNR", "RT_INNR", "RT_INDX", "RT_MDLE", "RT_RING", "RT_PNKY", "RT_OUTR",
    "LH_OUTR", "LH_PNKY", "LH_RING", "LH_MDLE", "LH_INDX", "LH_INNR", "RH_INNR", "RH_INDX", "RH_MDLE", "RH_RING", "RH_PNKY", "RH_OUTR",
    "LB_OUTR", "LB_PNKY", "LB_RING", "LB_MDLE", "LB_INDX", "LB_INNR", "RB_INNR", "RB_INDX", "RB_MDLE", "RB_RING", "RB_PNKY", "RB_OUTR",
    "L_LTHMB", "L_MTHMB", "L_RTHMB", "R_LTHMB", "R_MTHMB"
)

$baseAlphaKeys = @(
    "X", "V", "G", "M", "P", "*", "%", "U", "O", "Y", "B", "Z",
    "J", "K", "S", "N", "D", "=", ":", "A", "E", "I", "H", "QU",
    "Leader", "W", "F", "L", "C", "\", "/", "(", "<Comma>", "<Period>", ")", "Vim",
    "Num Pad", "R", "<Space>", "<Space>", "T"
)

# Create a dictionary to store the comboRef
$comboRef = @{}

# Iterate through the list and associate each string with its index
for ($i = 0; $i -lt $comboRefKeycodes.Count; $i++) {
    $comboRef[$comboRefKeycodes[$i]] = $baseAlphaKeys[$i]
}

# Define the regex pattern to match combos
$comboPattern = 'COMB\((WORD_COMBO_[^,]+),\s*([^,]+),\s*([^)]+)\)'

# Find all matches
$matches = [regex]::Matches($comboContent, $comboPattern)

# Iterate through the matches and process them
foreach ($match in $matches) {
    $comboName = $match.Groups[1].Value
    $output = $match.Groups[2].Value
    $params = $match.Groups[3].Value -split ',\s*'
    $comboKeysArray = @()

    #Write-Host "Combo Name: $comboName"
    #Write-Host "Output: $output"
    foreach ($param in $params) {
        $key = Get-StringIndex -string $param
        $comboKeysArray += $key
    }

    # Sort the array alphabetically and join into a string
    $comboKeys = ($comboKeysArray | Sort-Object) -join ", "

    # Set $word to be the value of $comboName with 'WORD_COMBO_' removed and the remaining text lowercase
    $word = ($comboName -replace 'WORD_COMBO_', '').ToLower()
    # Apply multiple replacements on $word
    $word = $word -replace 'ip', 'i''' -replace 'youp', 'you''' -replace 'pve', '''ve' -replace 'ps', '''s' -replace 'pll', '''ll' -replace 'pd', '''d' -replace 'pre', '''re' -replace 'andl', 'and (left hand)' -replace 'andr', 'and (right hand)' -replace 'inw', 'in (word)'

    #Write-Host "Params: $params"
    #Write-Host "-------------------------"
    $dataToAppend += "COMB($comboName, $output, $comboKeys)"

    # Add the word and comboKeys to the JSON data
    $jsonData += [PSCustomObject]@{
        Word      = $word
        ComboKeys = $comboKeys
    }
}

# Convert the JSON data to a JSON string
$jsonString = $jsonData | ConvertTo-Json -Depth 2

# Save the JSON string to a file
Set-Content -Path $jsonOutputPath -Value $jsonString

$dataToAppendString = $dataToAppend -join "`n"

# Append the new data to the existing content
$content += "`n$dataToAppendString"

# Write the modified content back to the file
Set-Content -Path $comboTempOutput -Value $content
