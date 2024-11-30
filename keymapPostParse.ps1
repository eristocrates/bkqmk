# Define the file path
$filePath = "E:\uranus\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\eristocrates\keymap.yaml"
$syskeysFilePath = "E:\uranus\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\eristocrates\SYSKEYS.txt"
$bitcomboFilePath = "E:\uranus\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\eristocrates\BITCOMBO.txt"
$comboFilePath = "E:\uranus\coding\bkqmk\users\eristocrates\combos.def"

function Get-StringIndex {
    param (
        [string]$string
    )


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


# Read the content of the file
$content = Get-Content -Path $filePath -Raw



#base layer
$content = $content -replace "LTP ARC", '{t: $$$mdi:arrow-top-left$$$, h: Arcane}'
$content = $content -replace "RTP ARC", '{t: $$$mdi:arrow-top-right$$$, h: Arcane}'
$content = $content -replace "LHM ARC", '{t: $$$mdi:arrow-left$$$, h: Arcane}'
$content = $content -replace "RHM ARC", '{t: $$$mdi:arrow-right$$$, h: Arcane}'
$content = $content -replace "LBM ARC", '{t: $$$mdi:arrow-bottom-left$$$, h: Arcane}'
$content = $content -replace "RBM ARC", '{t: $$$mdi:arrow-bottom-right$$$, h: Arcane}'


$content = $content -replace "LWKEY C", "{t: C, h: Win}"
$content = $content -replace "LTALT S", "{t: S, h: Alt}"
$content = $content -replace "LCTRL T", "{t: T, h: Ctrl}"
$content = $content -replace "LSHFT N", "{t: N, h: Shift}"
$content = $content -replace "LCAG  Y", "{t: Y, h: Yuh}"
$content = $content -replace "LMEH  F", "{t: F, h: Meh}"
$content = $content -replace "LHYPR D", "{t: D, h: Hyper}"
$content = $content -replace "RHYPR O", "{t: O, h: Hyper}"
$content = $content -replace "RMEH DT", "{t: '.', s: '!', h: Meh}"
$content = $content -replace "RCAG  L", "{t: L, h: Yuh}"
$content = $content -replace "RSHFT U", "{t: U, h: Shift}"
$content = $content -replace "RCTRL A", "{t: A, h: Ctrl}"
$content = $content -replace "RTALT I", "{t: I, h: Alt}"
$content = $content -replace "RWKEY H", "{t: H, h: Win}"

$content = $content -replace "PLS FUN", "{t: '+', h: BitFunc }"
$content = $content -replace "COLN", "{t: ':', s: '::'}"
$content = $content -replace "PIPE", "{t: '|', s: '||'}"
$content = $content -replace "LPRN", "{t: '(', s: '/*'}"
$content = $content -replace "RPRN", "{t: ')', s: '*/'}"
$content = $content -replace "LCBR", "{t: '{', s: '{{/*'}"
$content = $content -replace "RCBR", "{t: '}', s: '*/}}'}"
$content = $content -replace "SLSH", "{t: '/', s: '//'}"
$content = $content -replace "MINS", "{t: '-', s: '^'}"
$content = $content -replace "TH   QU", "{t: QU, h: Q}"
$content = $content -replace "DOT ARC", "{t: '.', h: Adpt}"
$content = $content -replace "COM ARC", "{t: ',', h: Adpt}"
$content = $content -replace "PDOT", "{t: '.', s: '!'}"
$content = $content -replace "DOT", "{t: '.', s: '!'}"
$content = $content -replace "QUOT", "{t: '''', s: '`"'}"
$content = $content -replace "LEQL", "{t: '<=', s: '<=='}"
$content = $content -replace "GEQL", "{t: '>=', s: '>=='}"
$content = $content -replace "DEQL", "{t: '==', s: '!=='}"
$content = $content -replace "TEQL", "{t: '===', s: '!==='}"
$content = $content -replace "EQL", "{t: '=', s: '+'}"
$content = $content -replace "COMM", "{t: ', ', s: '?' }"
$content = $content -replace "QK LEAD", "{t: Leader, s: QMK }"

$content = $content -replace "BITWISEZ", "{t: Z, h: Bitwise }"
$content = $content -replace "SFSHL R", "{t: R, h: ShftshL }"
$content = $content -replace "SFSHLCR", "{t: R, h: NGramL }"
$content = $content -replace "ALTLSPC", "{t: Space, h: AltishL }"
$content = $content -replace "ALTRSPC", "{t: Space, h: AltishR }"
$content = $content -replace "SFSHR E", "{t: E, h: ShftshR }"
$content = $content -replace "SFSHRCE", "{t: E, h: NGramR }"
$content = $content -replace "\bNUM SPC\b", "{t: Space, h: NumPad }"
$content = $content -replace "PPLS", "{t: '+', s: '++'}"
$content = $content -replace "LBRC", "{t: '[', s: '/>'}"
$content = $content -replace "TILD", "{t: '~', s: '^'}"
$content = $content -replace "LPRN", "{t: '(', s: '/*'}"
$content = $content -replace "RPRN", "{t: ')', s: '*/'}"
$content = $content -replace "LCBR", "{t: '{', s: '{{/*'}"
$content = $content -replace "RCBR", "{t: '{', s: '*/}}'}"
$content = $content -replace "LABK", "{t: '<', s: '<<'}"
$content = $content -replace "PMNS", "{t: '-', s: '--'}"
$content = $content -replace "RBRC", "{t: ']', s: '\\/'}"
$content = $content -replace "RABK", "{t: '>', s: '>>'}"
$content = $content -replace "SARW", "{t: '->', s: '=>'}"

$content = $content -replace "SKP GRM", "{t: Space, h: NumPad }"
$content = $content -replace "TGRV", '"```"'
$content = $content -replace "GRV", '{t: "`", s: "*"}'

$content = $content -replace "CUR DIR", "{t: './', s: '../' }"
$content = $content -replace "AMPR", "{t: '&', s: '&&' }"
$content = $content -replace "ESLH", "{t: '\/', s: '/>' }"
$content = $content -replace "OS LSFT", "{t: Shift, h: OneShot }"
$content = $content -replace "OS LCTL", "{t: Control, h: OneShot }"
$content = $content -replace "OS LALT", "{t: Alt, h: OneShot }"
$content = $content -replace "OS LGUI", "{t: Win, h: OneShot }"
$content = $content -replace "OS HYPR", "{t: Hyper, h: OneShot }"
$content = $content -replace "OS  MEH", "{t: Meh, h: OneShot }"
$content = $content -replace "OS  CAG", "{t: Yuh, h: OneShot }"
$content = $content -replace "TD\(TBW\)", "{t: BSpc, h: ^Bspc }"

$content = $content -replace "BSESLCE", "{t: Space, h: BSlice}"





$content = $content -replace "VIM TOG", "''"

$content = $content -replace "NUM PAD", "{t: Num Pad, h: MO Layer }"
$content = $content -replace "SML SPC", "{t: Space, h: SML }"
$content = $content -replace "SMR SPC", "{t: Space, h: SMR }"
$content = $content -replace "NUM   Z", "{t: Z, h: Num Pad }"
$content = $content -replace "'   ", "'"

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
    # $content += $dataToAppend

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

# ngrams

# combo ref
for ($i = 0; $i -lt $list.Count; $i++) {
    $keycode = $list[$i]
    $index = Get-StringIndex -string $keycode
    $content = $content -replace "$keycode", "{ t: $keycode, h: $index }"
}



# Read the content of the combos file
$comboContent = Get-Content -Path $comboFilePath -Raw

# Define the regex pattern to match combos
$comboPattern = 'COMB\(([^, ]+), \s*([^, ]+), \s*([^)]+)\)'

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
$vcbComboPattern = 'COMB\((VIM_COMBO_[^, ]+), \s*([^, ]+), \s*([^)]+)\)'
$controlComboPattern = 'COMB\((CONTROL_COMBO_[^, ]+), \s*([^, ]+), \s*([^)]+)\)'

# Find all matches
$matches = [regex]::Matches($comboContent, $controlComboPattern)

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
    $params = $match.Groups[3].Value -split ', \s*'
    #++$offsetAdjustment
    if ($alignmentIndex -gt $alignments.Count - 1) {
        $alignmentIndex = 0
        $offsetAdjustment = $offsetAdjustment + 300
        $slideAdjustment = $slideAdjustment * -1
    }

    # Write-Host "Combo Name: $comboName"
    # Write-Host "Output: $output"
    # Write-Host "Params: $params"
    # Get the indices for the parameters
    $paramAverage = 0
    $paramIndices = @()
    foreach ($param in $params) {
        $param = $param -replace '_', ' '
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



    # TODO automate differentiating how combos are drawn https://github.com/caksoylar/keymap-drawer/blob/main/KEYMAP_SPEC.md#combos
    # Append the translated combo to the data
    #$alignment = $alignments[]
    $dataToAppend += '  - { l: ["SYSKEYS"]' + ", p: [$($paramIndices -join ', ')], k: $output }"
}


#Write-Host "$dataToAppend"
# Join the data with newlines
$dataToAppendString = $dataToAppend -join "`n"

# Save the string to the specified file
Set-Content -Path $syskeysFilePath -Value $dataToAppendString

# Initialize the data to append
$dataToAppend = @(
    "combos:",
    ""
)
$dataToAppend += '  - { l: ["BITCOMBO"]' + ", p: [19, 21], k: 10 }"
$dataToAppendString = $dataToAppend -join "`n"
# Save the string to the specified file
Set-Content -Path $bitcomboFilePath -Value $dataToAppendString
# Append the new data to the existing content
# $content += "`n$dataToAppendString"

#Write-Host "Combos translated and appended successfully."


# vimnav
$content = $content -replace "VM LEFT", "{t: Left, s: h, h: '<' }"
$content = $content -replace "VM DOWN", "{t: Down, s: j, h: 'v' }"
$content = $content -replace "VM   UP", "{t: Up, s: k, h: '^' }"
$content = $content -replace "VM RGHT", "{t: Right, s: l, h: '>' }"
$content = $content -replace "VIMFGHT", "Toggle}"

# vim fighter
$content = $content -replace "VF LEFT", "{t: Left}"
$content = $content -replace "VF DOWN", "{t: Down}"
$content = $content -replace "VF   UP", "{t: Up}"
$content = $content -replace "VF RGHT", "{t: Right}"
$content = $content -replace "VF NTRL", "{t: Neutral}"
$content = $content -replace "VM VERT", "{t: Vert}"
$content = $content -replace "VM HORI", "{t: Hori}"
$content = $content -replace "VM NTRL", "{t: Neutral}"
$content = $content -replace "VM YANK", "{t: Yank}"
$content = $content -replace "VM CHAN", "{t: Change}"
$content = $content -replace "VM DELE", "{t: Delete}"
$content = $content -replace "VM VISU", "{t: Visual}"
$content = $content -replace "VM MRKQ", "{t: Quo}"
$content = $content -replace "VM MRKG", "{t: Grv}"
$content = $content -replace "VM FOLD", "{t: Fold}"
$content = $content -replace "VM SRCH", "{t: Search}"
$content = $content -replace "VM FRMT", "{t: Format}"

# symbol stuff
$content = $content -replace "APP", "{t: Context, s: Windows, h: Menu }"

# pointer
$content = $content -replace "DRGSCRL", "{t: Drag scroll, h: MO }"
$content = $content -replace "SNIPING", "{t: Sniping, h: MO }"
$content = $content -replace "DRG TOG", "{t: Drag scroll, h: TG }"
$content = $content -replace "SCN TOG", "{t: Yomitan Scan, h: TG }"
$content = $content -replace "SNP TOG", "{t: Sniping, h: TG }"
$content = $content -replace "YT  ADD", "{t: Yomitan Add }"
$content = $content -replace "YT VIEW", "{t: Yomitan View }"
$content = $content -replace "YT PLAY", "{t: Yomitan Play }"
$content = $content -replace "SM SNAP", "{t: Firefox Snap }"

# numpad
$content = $content -replace "FNCTION", "{t: Function, h: MO Layer }"
$content = $content -replace "BN2 DC1", "{t: 0b2, h: 1d }"
$content = $content -replace "BN4 DC2", "{t: 0b4, h: 2d }"
$content = $content -replace "BN8 DC3", "{t: 0b8, h: 3d }"
$content = $content -replace "BN16 ET", "{t: 0b16, h: Enter }"
$content = $content -replace "BN1 DOT", "{t: '0b1', h: '.' }"

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
