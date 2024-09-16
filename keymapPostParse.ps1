# Define the file path
$filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\eristocrates\keymap.yaml"
$enumFilePath = "I:\coding\bkqmk\users\eristocrates\eristocrates_keycodes.h"
$comboFilePath = "I:\coding\bkqmk\users\eristocrates\combos.def"

function Get-StringIndex {
    param (
        [string]$string
    )

    # Check for VM exceptions first
    if ($vimExceptions.ContainsKey($string)) {
        $value = $vimExceptions[$string]
        if ([int]::TryParse($value, [ref]$null)) {
            return [int]$value
        }
        else {
            Write-Error "Non-numeric value '$value' found in vimExceptions for key '$string'."
            return $null
        }
    }

    # Check the comboRef dictionary
    if ($comboRef.ContainsKey($string)) {
        $value = $comboRef[$string]
        if ([int]::TryParse($value, [ref]$null)) {
            return [int]$value
        }
        else {
            Write-Error "Non-numeric value '$value' found in comboRef for key '$string'."
            return $null
        }
    }
    else {
        Write-Error "String '$string' not found in the list."
        return $null
    }
}

# Define the exceptions
$vimExceptions = @{
    "VM_LEFT" = 31
    "VM_DOWN" = 32
    "VM_RGHT" = 33
    "VM_NTRL" = 34
    "VM___UP" = 40
    "VF_LEFT" = 31
    "VF_DOWN" = 32
    "VF_RGHT" = 33
    "VF_NTRL" = 34
    "VF___UP" = 0
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
    $content = $content -replace "CTRL  S", "{t: S, h: CTRLR}"
    $content = $content -replace "ALT   E", "{t: E, h: ALTT}"
    $content = $content -replace "QK LEAD", "{t: Leader, s: Core}"
    $content = $content -replace "NUM PAD", "{t: Num Pad, h: MO Layer}"
    $content = $content -replace "CTRL  R", "{t: R, h: CTRLR}"
    $content = $content -replace "SML SPC", "{t: Space, h: SML}"
    $content = $content -replace "SMR SPC", "{t: Space, h: SMR}"
    $content = $content -replace "ALT   T", "{t: T, h: ALTT}"
    $content = $content -replace "LWKEY K", "{t: K, h: Left Win}"
    $content = $content -replace "LTALT S", "{t: S, h: Left Alt}"
    $content = $content -replace "LCTRL N", "{t: N, h: Left Ctrl}"
    $content = $content -replace "LSHFT D", "{t: D, h: Left Shift}"
    $content = $content -replace "RSHFT A", "{t: A, h: Right Shift}"
    $content = $content -replace "RCTRL E", "{t: E, h: Right Ctrl}"
    $content = $content -replace "RTALT I", "{t: I, h: Right Alt}"
    $content = $content -replace "RTALT H", "{t: H, h: Right Alt}"
    $content = $content -replace "RCTRL I", "{t: I, h: Right Ctrl}"
    $content = $content -replace "RWKEY H", "{t: H, h: Right Win}"
    $content = $content -replace "RWKEY U", "{t: U, h: Right Win}"
    $content = $content -replace "CTRL  S", "{t: R, h: CTRLR}"
    $content = $content -replace "ALT   E", "{t: T, h: ALTT}"
    $content = $content -replace "LWKEY N", "{t: N, h: Left Win}"
    $content = $content -replace "LWKEY C", "{t: C, h: Left Win}"
    $content = $content -replace "LTALT R", "{t: R, h: Left Alt}"
    $content = $content -replace "LCTRL T", "{t: T, h: Left Ctrl}"
    $content = $content -replace "LSHFT C", "{t: C, h: Left Shift}"
    $content = $content -replace "LSHFT T", "{t: T, h: Left Shift}"
    $content = $content -replace "RSHFT H", "{t: H, h: Right Shift}"
    $content = $content -replace "RCTRL O", "{t: O, h: Right Ctrl}"
    $content = $content -replace "RTALT U", "{t: U, h: Right Alt}"
    $content = $content -replace "RWKEY I", "{t: I, h: Right Win}"
    $content = $content -replace "NUM   Z", "{t: Z, h: Num Pad}"

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


    $alignments = @(
        "top",
        "bottom",
        "left",
        "right"
    )



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



    # Define the regex pattern to match combos starting with VIM_COMBO_
    $vcbComboPattern = 'COMB\((VIM_COMBO_[^,]+),\s*([^,]+),\s*([^)]+)\)'

    # Find all matches
    $matches = [regex]::Matches($comboContent, $vcbComboPattern)

    # Initialize the data to append
    $dataToAppend = @(
        "combos:",
        ""
    )

    $alignmentIndex = 0
    $offsetAdjustment = 1
    $slideAdjustment = -1
    $accumulator = 0
    $offset = 0
    # Iterate through the matches and translate them
    foreach ($match in $matches) {
        ++$accumulator
        $comboName = $match.Groups[1].Value
        $output = $match.Groups[2].Value
        $params = $match.Groups[3].Value -split ',\s*'
        #++$offsetAdjustment
        if ($alignmentIndex -gt $alignments.Count - 1) {
            $alignmentIndex = 0
            $offsetAdjustment = $offsetAdjustment + 300
            $slideAdjustment = $slideAdjustment * -1
        }

        #Write-Host "Combo Name: $comboName"
        #Write-Host "Output: $output"
        #Write-Host "Params: $params"
        # Get the indices for the parameters
        $paramAverage = 0
        $paramIndices = @()
        foreach ($param in $params) {
            $paramIndex = [int](Get-StringIndex -string $param)
            if ([int]::TryParse($paramIndex, [ref]$null)) {
                $paramIndex = [int]$paramIndex
                $paramIndices += $paramIndex
                $paramAverage += $paramIndex

                #Write-Host paramIndex $paramIndex
                #if ($paramIndex -gt $largestIndex) {
                #    $largestIndex = $param
                #}
                #if ([int]$paramIndex -lt $smallestIndex) {
                #    $smallestIndex = $param
                #}
            }
        }

        #Write-Host "-------------------------"
        if ($paramIndices.Count -gt 0) {
            $paramAverage = $paramAverage / $paramIndices.Count
        }
        else {
            $paramAverage = 0
        }
        $paramAverage = $paramAverage / $matches.Count
        # Generate a random integer between 2 and 10
        #$randomInt = Get-Random -Minimum 3 -Maximum 11
        if ($slideAdjustment -gt 0) {
            $offset = ($accumulator + (.15 * $offsetAdjustment / 100)) / 10
        }
        else {
            $offset = ($accumulator + (2 * $offsetAdjustment / 100)) / 10
        }
        $alignment = $alignments[$alignmentIndex++] #[$modResult]
        # Generate a random float between 0 and 1
        #$randomFloat = Get-Random -Minimum 0.0 -Maximum 1.0

        # Scale and shift to get a float between -1 and 0
        $slide = ($offset * (($accumulator * $offset ) / 100) % 1) * $slideAdjustment

        #Write-Host offset $offset
        #Write-Host slide $slide



        # TODO automate differentiating how combos are drawn https://github.com/caksoylar/keymap-drawer/blob/main/KEYMAP_SPEC.md#combos
        # Append the translated combo to the data
        #$alignment = $alignments[]
        $dataToAppend += "  - {l: [VIMFIGHTER], p: [$($paramIndices -join ', ')], k: $output, a: $alignment, o: $offset, s: $slide}"
    }

    #Write-Host "$dataToAppend"
    # Join the data with newlines
    $dataToAppendString = $dataToAppend -join "`n"

    # Append the new data to the existing content
    $content += "`n$dataToAppendString"

    #Write-Host "Combos translated and appended successfully."










    # Perform the replacement
    for ($i = 0; $i -lt $layerNames.Count; $i++) {
        $content = $content -replace "\bL$i\b", $layerNames[$i]
    }

    # Write the modified content back to the target file
    #Set-Content -Path $filePath -Value $content

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
$content = $content -replace "VF LEFT", "{t: Left, h: Attack}"
$content = $content -replace "VF DOWN", "{t: Down, h: Attack}"
$content = $content -replace "VF   UP", "{t: Up, h: Attack}"
$content = $content -replace "VF RGHT", "{t: Right, h: Attack}"
$content = $content -replace "VF NTRL", "{t: Neutral, h: Attack}"
$content = $content -replace "VM VERT", "{t: Vertical, h: Attack}"
$content = $content -replace "VM HORI", "{t: Horizontal, h: Attack}"
$content = $content -replace "VM NTRL", "{t: Neutral, h: Attack}"
$content = $content -replace "VM YANK", "{t: Yank, h: Attack}"
$content = $content -replace "VM CHAN", "{t: Change, h: Attack}"
$content = $content -replace "VM DELE", "{t: Delete, h: Attack}"
$content = $content -replace "VM VISU", "{t: Visual, h: Attack}"
$content = $content -replace "VM MRKQ", "{t: QuoMark, h: Attack}"
$content = $content -replace "VM MRKG", "{t: GrvMark, h: Attack}"
$content = $content -replace "VM FOLD", "{t: Fold, h: Attack}"
$content = $content -replace "VM SRCH", "{t: Search, h: Attack}"
$content = $content -replace "VM FRMT", "{t: Format, h: Attack}"

# symbol stuff
$content = $content -replace "APP", "{t: Context, s: Windows, h: Menu}"
$content = $content -replace "ASST", "{t: Aware, s: Conntext, h: Assistant}"

# pointer
$content = $content -replace "PNTROPT", "{t: Pointer Options, h: OS Layer}"
$content = $content -replace "DRGSCRL", "{t: Drag scroll, h: MO}"
$content = $content -replace "SNIPING", "{t: Sniping, h: MO}"
$content = $content -replace "DRG TOG", "{t: Drag scroll, h: TG}"
$content = $content -replace "SCN TOG", "{t: Yomitan Scan, h: TG}"
$content = $content -replace "SNP TOG", "{t: Sniping, h: TG}"

# numpad
$content = $content -replace "FNCTION", "{t: Function, h: MO Layer}"
$content = $content -replace "BN2 DC1", "{t: 0b2, h: 1d}"
$content = $content -replace "BN4 DC2", "{t: 0b4, h: 2d}"
$content = $content -replace "BN8 DC3", "{t: 0b8, h: 3d}"
$content = $content -replace "BN16 ET", "{t: 0b16, h: Enter}"
$content = $content -replace "BN1 DOT", "{t: '0b1', h: '.'}"

# vim combos
$content = $content -replace "VM_VERT", "Vert Attack"
$content = $content -replace "VM_HORI", "Hori Attack"
$content = $content -replace "VM_YANK", "Yank Attack"
$content = $content -replace "VM_CHAN", "Change Attack"
$content = $content -replace "VM_DELE", "Delete Attack"
$content = $content -replace "VM_VISU", "Visual Attack"
$content = $content -replace "VM_MRKQ", "QuoMark Attack"
$content = $content -replace "VM_MRKG", "GrvMark Attack"
$content = $content -replace "VM_FOLD", "Fold Attack"
$content = $content -replace "VM_SRCH", "Search Attack"
$content = $content -replace "VM_FRMT", "Format Attack"

## Test the function
#$testStrings = @("LH PNKY", "VM LEFT", "VM DOWN", "RT RING", "VM   UP", "UNKNOWN")
#foreach ($testString in $testStrings) {
#    $index = Get-StringIndex -string $testString
#    Write-Host "The index of '$testString' is $index"
#}
























# Write the modified content back to the file
Set-Content -Path $filePath -Value $content
