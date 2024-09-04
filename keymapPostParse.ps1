# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml"
$enumFilePath = "I:\coding\bkqmk\users\AKeyHD\akeyhd_keycodes.h"
$comboFilePath = "I:\coding\bkqmk\users\AKeyHD\combos.def"

function Get-StringIndex {
    param (
        [string]$string
    )

    # Check for VM exceptions first
    if ($vimExceptions.ContainsKey($string)) {
        return $vimExceptions[$string]
    }

    # Check the comboRef dictionary
    if ($comboRef.ContainsKey($string)) {
        return $comboRef[$string]
    }
    else {
        Write-Error "String '$string' not found in the list."
        return $null
    }
}

# Define the exceptions
$vimExceptions = @{
    "VM LEFT" = 31
    "VM DOWN" = 32
    "VM RGHT" = 33
    "VM NTRL" = 34
    "VM   UP" = 40
    "VF LEFT" = 31
    "VF DOWN" = 32
    "VF RGHT" = 33
    "VF NTRL" = 34
    "VF   UP" = 40
    "VM_LEFT" = 31
    "VM_DOWN" = 32
    "VM_RGHT" = 33
    "VM_NTRL" = 34
    "VM___UP" = 40
    "VF_LEFT" = 31
    "VF_DOWN" = 32
    "VF_RGHT" = 33
    "VF_NTRL" = 34
    "VF___UP" = 40
}
# Read the content of the file
$content = Get-Content -Path $filePath -Raw

# Read the content of the enum file
$enumContent = Get-Content -Path $enumFilePath -Raw

# Extract the layers enum
$enumPattern = 'enum layers \{([^}]*)\}'
$matches = [regex]::Matches($enumContent, $enumPattern)



if ($matches.Success) {
    $enumBlock = $matches.Groups[1].Value

    # Print the extracted enum block
    #Write-Host "Extracted layers enum:"
    #Write-Host $enumBlock

    # Parse the individual layer names
    $layerNames = @()
    foreach ($line in $enumBlock -split "`n") {
        $line = $line.Trim()
        if ($line -match '^\s*_(\w+),?\s*$') {
            $layerName = $line -replace '^\s*_(\w+),?\s*$', '$1'
            $layerNames += $layerName
        }
    }

    ## Iterate through the layer names and print them
    #Write-Host "Parsed layer names:"
    #for ($i = 0; $i -lt $layerNames.Count; $i++) {
    #    Write-Host "L$i = $($layerNames[$i])"
    #}

    #base layer
    $content = $content -replace "'   ", "'" # remove space padding
    $content = $content -replace "LTP ARC", "{t: '*', s: Arcane}"
    $content = $content -replace "RTP ARC", "{t: '%', s: Arcane}"
    $content = $content -replace "LHM ARC", "{t: '=', s: Arcane}"
    $content = $content -replace "RHM ARC", "{t: ':', s: Arcane}"
    $content = $content -replace "LBM ARC", "{t: '\', s: Arcane}"
    $content = $content -replace "RBM ARC", "{t: '/', s: Arcane}"
    $content = $content -replace "TH   QU", "{t: QU, s: Q}"
    $content = $content -replace "COM ARC", "{t: ',', s: Adaptive, h: OSM Shift}"
    $content = $content -replace "DOT ARC", "{t: '.', s: Adaptive, h: Capsword}"
    $content = $content -replace "VIM TOG", "{t: Vim, s: Genuine, h: Emulation}"
    $content = $content -replace "QK LEAD", "{t: Leader, s: Core}"
    $content = $content -replace "NUM PAD", "{t: Num Pad, h: MO Layer}"
    $content = $content -replace "CTRL  R", "{t: R, h: CTRLR}"
    $content = $content -replace "SML SPC", "{t: Space, h: SML}"
    $content = $content -replace "SMR SPC", "{t: Space, h: SMR}"
    $content = $content -replace "ALT   T", "{t: T, h: ALTT}"



    # Define the regex pattern to match the layers section
    $layerPattern = 'layers:\s*(\w+):\s*-\s*\[([^\]]+)\]\s*-\s*\[([^\]]+)\]\s*-\s*\[([^\]]+)\]\s*-\s*\[([^\]]+)\]'

    # Find the match
    $match = [regex]::Match($content, $layerPattern)

    if ($match.Success) {
        $layerName = $match.Groups[1].Value
        $line1 = $match.Groups[2].Value
        $line2 = $match.Groups[3].Value
        $line3 = $match.Groups[4].Value
        $line4 = $match.Groups[5].Value

        # Print the captured layer name and lines
        #Write-Host "Layer Name: $layerName"
        #Write-Host "Line 1: $line1"
        #Write-Host "Line 2: $line2"
        #Write-Host "Line 3: $line3"
        #Write-Host "Line 4: $line4"
        # Prepare the data to append
        $dataToAppend = @"
  TEST:
  - [$line1]
  - [$line2]
  - [$line3]
  - [$line4]
"@

        # Append the data to the end of the content
        $content += $dataToAppend

        #Write-Host "Data appended successfully."
    }
    else {
        Write-Error "No layers section found in the file."
    }





    # Define the file path
    $comboFilePath = "I:\coding\bkqmk\users\AKeyHD\combos.def"

    # Read the content of the combos file
    $comboContent = Get-Content -Path $comboFilePath -Raw

    # Define the regex pattern to match combos
    $comboPattern = 'COMB\(([^,]+),\s*([^,]+),\s*([^)]+)\)'

    # Find all matches
    $matches = [regex]::Matches($comboContent, $comboPattern)

    # Iterate through the matches and print them
    foreach ($match in $matches) {
        $comboName = $match.Groups[1].Value
        $output = $match.Groups[2].Value
        $params = $match.Groups[3].Value

        #Write-Host "Combo Name: $comboName"
        #Write-Host "Output: $output"
        #Write-Host "Params: $params"
        #Write-Host "-------------------------"
    }



    # Define the regex pattern to match combos starting with VCB_
    $vcbComboPattern = 'COMB\((VCB_[^,]+),\s*([^,]+),\s*([^)]+)\)'

    # Find all matches
    $matches = [regex]::Matches($comboContent, $vcbComboPattern)

    # Initialize the data to append
    $dataToAppend = @(
        "combos:",
        ""
    )

    # Iterate through the matches and translate them
    foreach ($match in $matches) {
        $comboName = $match.Groups[1].Value
        $output = $match.Groups[2].Value
        $params = $match.Groups[3].Value -split ',\s*'

        #Write-Host "Combo Name: $comboName"
        #Write-Host "Output: $output"
        #Write-Host "Params: $params"
        #Write-Host "-------------------------"
        # Get the indices for the parameters
        $paramIndices = @()
        foreach ($param in $params) {
            $paramIndex = Get-StringIndex -string $param
            if ($null -ne $paramIndex) {
                $paramIndices += $paramIndex
            }
        }

        # TODO automate differentiating how combos are drawn https://github.com/caksoylar/keymap-drawer/blob/main/KEYMAP_SPEC.md#combos
        # Append the translated combo to the data
        $dataToAppend += "  - {l: [VIMFIGHTER], p: [$($paramIndices -join ', ')], k: $output}"
    }

    Write-Host "$dataToAppend"
    # Join the data with newlines
    $dataToAppendString = $dataToAppend -join "`n"

    # Append the new data to the existing content
    $content += "`n$dataToAppendString"

    Write-Host "Combos translated and appended successfully."










    # Perform the replacement
    for ($i = 0; $i -lt $layerNames.Count; $i++) {
        $content = $content -replace "\bL$i\b", $layerNames[$i]
    }

    # Write the modified content back to the target file
    Set-Content -Path $filePath -Value $content

    #Write-Host "Replacements completed successfully."
}
else {
    Write-Error "No layers enum found in the file."
}

# Define the list of strings
$list = @(
    "LT OUTR", "LT PNKY", "LT RING", "LT MDLE", "LT INDX", "LT INNR", "RT INNR", "RT INDX", "RT MDLE", "RT RING", "RT PNKY", "RT OUTR",
    "LH OUTR", "LH PNKY", "LH RING", "LH MDLE", "LH INDX", "LH INNR", "RH INNR", "RH INDX", "RH MDLE", "RH RING", "RH PNKY", "RH OUTR",
    "LB OUTR", "LB PNKY", "LB RING", "LB MDLE", "LB INDX", "LB INNR", "RB INNR", "RB INDX", "RB MDLE", "RB RING", "RB PNKY", "RB OUTR",
    "L LTHMB", "L MTHMB", "L RTHMB", "R LTHMB", "R MTHMB"
)

# Create a dictionary to store the comboRef
$comboRef = @{}

# Iterate through the list and associate each string with its index
for ($i = 0; $i -lt $list.Count; $i++) {
    $comboRef[$list[$i]] = $i
}





# combo ref
for ($i = 0; $i -lt $list.Count; $i++) {
    $keycode = $list[$i]
    $index = Get-StringIndex -string $keycode
    $content = $content -replace "$keycode", "{t: $keycode, h: $index}"
}
# vimnav
$content = $content -replace "VM LEFT", "{t: Left, s: h, h: '<'}"
$content = $content -replace "VM DOWN", "{t: Down, s: j, h: 'v'}"
$content = $content -replace "VM   UP", "{t: Up, s: k, h: '^'}"
$content = $content -replace "VM RGHT", "{t: Right, s: l, h: '>'}"
$content = $content -replace "VIMFGHT", "{t: Vim Fighter, h: TO Layer}"

# vim fighter
$content = $content -replace "MI BACK", "Back"
$content = $content -replace "MI DOWN", "Crouch"
$content = $content -replace "MI JUMP", "Jump"
$content = $content -replace "MI FRNT", "Forward"
$content = $content -replace "VF LEFT", "{t: Left, h: Attack}"
$content = $content -replace "VF DOWN", "{t: Down, h: Attack}"
$content = $content -replace "VF   UP", "{t: Up, h: Attack}"
$content = $content -replace "VF RGHT", "{t: Right, h: Attack}"
$content = $content -replace "VF NTRL", "{t: Neutral, h: Attack}"

# symbol stuff
$content = $content -replace "DEQL", "=="
$content = $content -replace "UP  DIR", "../"
$content = $content -replace "DBSL", "\\"
$content = $content -replace "DSLH", "//"
$content = $content -replace "DAMP", "'**'"
$content = $content -replace "DPIP", "'||'"
$content = $content -replace "ESLH", "'\/'"
$content = $content -replace "APP", "{t: Context, s: Windows, h: Menu}"
$content = $content -replace "ASST", "{t: Aware, s: Conntext, h: Assistant}"
$content = $content -replace "PSCR", "Print Screen"

# pointer
$content = $content -replace "DBCL", "Double Click"
$content = $content -replace "BTN1", "Left Click"
$content = $content -replace "BTN2", "Right Click"
$content = $content -replace "BTN3", "Scroll Wheel Click"
$content = $content -replace "PNTROPT", "{t: Pointer Options, h: OS Layer}"
$content = $content -replace "DRGSCRL", "{t: Drag scroll, h: MO}"
$content = $content -replace "SNIPING", "{t: Sniping, h: MO}"
$content = $content -replace "SD  MOD", "Snipe DPI Up"
$content = $content -replace "SD RMOD", "Snipe DPI Down"
$content = $content -replace "DPI MOD", "DPI Up"
$content = $content -replace "DPI RMD", "DPI Down"
$content = $content -replace "DRG TOG", "{t: Drag scroll, h: TG}"
$content = $content -replace "SCN TOG", "{t: Yomitan Scan, h: TG}"
$content = $content -replace "SNP TOG", "{t: Sniping, h: TG}"

# numpad
$content = $content -replace "SCRL", "Scroll Lock"
$content = $content -replace "PAUS", "Pause"
$content = $content -replace "PSLS", "/"
$content = $content -replace "P7", "7"
$content = $content -replace "P8", "8"
$content = $content -replace "P9", "9"
$content = $content -replace "PAST", "'*'"
$content = $content -replace "FNCTION", "{t: Function, h: MO Layer}"
$content = $content -replace "INS", "Insert"
$content = $content -replace "HOME", "Home"
$content = $content -replace "PGUP", "Page Up"
$content = $content -replace "EQL", "="
$content = $content -replace "PMNS", "'-'"
$content = $content -replace "P4", "4"
$content = $content -replace "P5", "5"
$content = $content -replace "P6", "6"
$content = $content -replace "PPLS", "+"
$content = $content -replace "DEL", "Delete"
$content = $content -replace "END", "End"
$content = $content -replace "PGDN", "Page Down"
$content = $content -replace "LR LOCK", "Layer Lock"
$content = $content -replace "BN2 DC1", "{t: 0b2, h: 1d}"
$content = $content -replace "BN4 DC2", "{t: 0b4, h: 2d}"
$content = $content -replace "BN8 DC3", "{t: 0b8, h: 3d}"
$content = $content -replace "BN16 ET", "{t: 0b16, h: Enter}"
$content = $content -replace "P0", "0"
$content = $content -replace "BN1 DOT", "{t: '0b1', h: '.'}"
$content = $content -replace "F1", "F0b1"
$content = $content -replace "F2", "F0b2"
$content = $content -replace "F3", "F0b4"
$content = $content -replace "F4", "F0b8"
$content = $content -replace "F5", "F0b16"

# media
$content = $content -replace "MSEL", "Launch Media Player"
$content = $content -replace "MRWD", "Previous Track"
$content = $content -replace "BRID", "Brightness Down"
$content = $content -replace "BRIU", "Brightness Up"
$content = $content -replace "MFFD", "Next Track"
$content = $content -replace "MPLY", "Play/ Pause Track"
$content = $content -replace "MPRV", "Previous Track"
$content = $content -replace "VOLU", "Volume Up"
$content = $content -replace "VOLD", "Volume Down" #TODO strangely bugged if i put down before up
$content = $content -replace "MNXT", "Next Track"
$content = $content -replace "MSTP", "Stop Track"
$content = $content -replace "MUTE", "Mute"


## Test the function
#$testStrings = @("LH PNKY", "VM LEFT", "VM DOWN", "RT RING", "VM   UP", "UNKNOWN")
#foreach ($testString in $testStrings) {
#    $index = Get-StringIndex -string $testString
#    Write-Host "The index of '$testString' is $index"
#}
























# Write the modified content back to the file
#Set-Content -Path $filePath -Value $content
