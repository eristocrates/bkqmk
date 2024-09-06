

// $filePath = "I:\coding\bkqmk\keyboards\bastardkb\charybdis\3x6\keymaps\akeyhd\keymap.yaml"
//
// # Read the content of the file
// $content = Get-Content -Path $filePath -Raw
//
// $content = $content -replace "KC_", ""
// # Write the modified content back to the file
// Set-Content -Path $filePath -Value $content
import tablemark from "tablemark"
import { promises as fs } from 'fs';
import path from 'path';
import { escape } from "querystring";
// Define the path to the output Markdown file
const outputFilePath = path.join('I:', 'coding', 'bkqmk', 'vimFighter.md');
// Define the path to the quick reference file
const indexFilePath = path.join('I:', 'coding', 'bkqmk', 'index.txt');
const quickrefFilePath = path.join('I:', 'coding', 'bkqmk', 'quickref.txt');
const motionFilePath = path.join('I:', 'coding', 'bkqmk', 'motion.txt');
const changeFilePath = path.join('I:', 'coding', 'bkqmk', 'change.txt');


// Define the mapping
const mappings = [
    { keycode: "VM_LEFT", name: "Left Attack" },
    { keycode: "VM_DOWN", name: "Down Attack" },
    { keycode: "VM___UP", name: "Up Attack" },
    { keycode: "VM_RGHT", name: "Right Attack" },
    { keycode: "VM_VERT", name: "Vertical Attack" },
    { keycode: "VM_HORI", name: "Horizontal Attack" },
    { keycode: "VM_NTRL", name: "Neutral Attack" },
    { keycode: "VM_YANK", name: "Yank Attack" },
    { keycode: "VM_CHAN", name: "Change Attack" },
    { keycode: "VM_DELE", name: "Delete Attack" },
    { keycode: "VM_VISU", name: "Visual Attack" },
    { keycode: "VM_MRKQ", name: "QuoMark Attack" },
    { keycode: "VM_MRKG", name: "GrvMark Attack" },
    { keycode: "VM_FOLD", name: "Fold Attack" },
    { keycode: "VM_SRCH", name: "Search Attack" },
    { keycode: "VM_FRMT", name: "Format Attack" },
    { keycode: "BACK_HELD", name: "(4) Hold Back" },
    { keycode: "BB_MOTION", name: "(44) Back Dash" },
    { keycode: "BF_MOTION", name: "(46) Back Forward" },
    { keycode: "DD_MOTION", name: "(22) Double Down" },
    { keycode: "default", name: "(5) No direction" },
    { keycode: "DJ_MOTION", name: "(28) Super Jump" },
    { keycode: "DOWN_HELD", name: "(2) Crouch" },
    { keycode: "DPB_MOTION", name: "(421) Reverse Dragon Punch" },
    { keycode: "DPF_MOTION", name: "(623) Dragon Punch" },
    { keycode: "DQCB_MOTION", name: "(214214) Double Quarter Circle Back" },
    { keycode: "FB_MOTION", name: "(64) Back Forward" },
    { keycode: "FF_MOTION", name: "(66) Dash" },
    { keycode: "FRNT_HELD", name: "(6) Forward" },
    { keycode: "HCBF_MOTION", name: "(632146) Half Circle Back Forward" },
    { keycode: "HCB_MOTION", name: "(63214) Half Circle Back" },
    { keycode: "HCFB_MOTION", name: "(412364) Half Circle Forward Back" },
    { keycode: "HCF_MOTION", name: "(41236) Half Circle Forward" },
    { keycode: "JD_MOTION", name: "(82) Jump Down" },
    { keycode: "JJ_MOTION", name: "(88) Double Jump" },
    { keycode: "JUMP_HELD", name: "(8) Jump" },
    { keycode: "QCB_MOTION", name: "(214) Quarter Circle Back" },
    { keycode: "QCF_MOTION", name: "(236) Quarter Circle Forward" },
    { keycode: "astr", name: "*" },
    { keycode: "bar", name: "|" },
    { keycode: "circ", name: "^" },
    { keycode: "comma", name: "," },
    { keycode: "dlr", name: "$" },
    { keycode: "dot", name: "." },
    { keycode: "dquo", name: "\"" },
    { keycode: "end", name: "End" },
    { keycode: "esc", name: "Escape" },
    { keycode: "grv", name: "`" },
    { keycode: "hash", name: "#" },
    { keycode: "is_text_object ? lbrc : kc_n", name: "[ for text objects, n otherwise" },
    { keycode: "is_text_object ? p : kc_lcbr", name: "p for paragraph text objects, [ otherwise" },
    { keycode: "is_text_object ? p : kc_rcbr", name: "p for paragraph text objects, ] otherwise" },
    { keycode: "is_text_object ? s : kc_lprn", name: "s for sentence text objects, ( otherwise" },
    { keycode: "is_text_object ? s : kc_rprn", name: "s for sentence text objects, ) otherwise" },
    { keycode: "labk", name: "<" },
    { keycode: "lbrc", name: "[" },
    { keycode: "lcbr", name: "{" },
    { keycode: "lprn", name: "(" },
    { keycode: "minus", name: "-" },
    { keycode: "perc", name: "%" },
    { keycode: "plus", name: "+" },
    { keycode: "quot", name: "\'" },
    { keycode: "rabk", name: ">" },
    { keycode: "rbrc", name: "]" },
    { keycode: "rcbr", name: "}" },
    { keycode: "rprn", name: ")" },
    { keycode: "scln", name: ":" },
    { keycode: "tild", name: "~" },
    { keycode: "tilde", name: "~" },
    { keycode: "unds", name: "_" },
    { keycode: "c(a)", name: "C-a" },
    { keycode: "c(i)", name: "C-i" },
    { keycode: "c(rbrc)", name: "C-]" },
    { keycode: "c(t)", name: "C-t" },
    { keycode: "c(v)", name: "C-v" },
    { keycode: "c(x)", name: "C-x" },
    { keycode: "s(a)", name: "A" },
    { keycode: "s(b)", name: "B" },
    { keycode: "s(c)", name: "C" },
    { keycode: "s(d)", name: "D" },
    { keycode: "s(e)", name: "E" },
    { keycode: "s(f)", name: "F" },
    { keycode: "s(g)", name: "G" },
    { keycode: "s(i)", name: "I" },
    { keycode: "s(j)", name: "J" },
    { keycode: "s(m)", name: "M" },
    { keycode: "s(n)", name: "N" },
    { keycode: "s(o)", name: "O" },
    { keycode: "s(p)", name: "P" },
    { keycode: "s(r)", name: "R" },
    { keycode: "s(s)", name: "S" },
    { keycode: "s(t)", name: "T" },
    { keycode: "s(u)", name: "U" },
    { keycode: "s(v)", name: "V" },
    { keycode: "s(w)", name: "W" },
    { keycode: "s(x)", name: "X" },
    { keycode: "s(y)", name: "Y" },


];

// Function to check and return the corresponding right string
function getKeycodeName(input) {
    const mapping = mappings.find(map => map.keycode === input);
    return mapping ? mapping.name : null;
}


// Function to escape special Markdown characters and remove strings between pipes
function escapeMarkdownCharacters(str) {
    // Remove any string between two pipes, including the pipes themselves
    str = str.replace(/\|[^|]*\|/g, '');
    // Escape special Markdown characters
    return str.replace(/([()[\]])/g, '\\$1');
}


// Function to search for a string in a file and return the entire line, excluding lines where the string starts with '*'
async function searchStringInFile(filePath, searchString) {
    try {
        const data = await fs.readFile(filePath, 'utf8');
        const lines = data.split('\n');
        for (const line of lines) {
            // Check if the line contains the search string and does not start with '*'
            if (line.includes(searchString) && !line.trim().startsWith('*')) {
                return line;
            }
        }
        return null;
    } catch (error) {
        console.error('Error reading file:', error);
        return null;
    }
}











// Define the path to the JSON file
const jsonFilePath = path.join('I:', 'coding', 'bkqmk', 'keycodes_and_directions.json');
var parsedData = []

// Read and parse the JSON file
async function loadJsonFile() {
    try {
        const data = await fs.readFile(jsonFilePath, 'utf8');
        const jsonData = JSON.parse(data);
        // Reference the first object in the JSON data
        // Loop through the jsonData using the forEach method
        for (const object of jsonData) {
            var button = getKeycodeName(object.Keycode)
            for (const direction of object.Directions) {
                var motion = getKeycodeName(direction.Direction)
                var command = ""
                for (const key of direction.Keys) {
                    var keys = getKeycodeName(key.replace("KC_", "").toLowerCase())
                    if (keys == null) {
                        keys = key.replace("KC_", "").toLowerCase()
                    }
                    command += keys
                }
                // Assuming direction.Link is a URL string
                const link = direction.Link;

                // Extract the string after the #
                const hashIndex = link.indexOf('#');
                let hashString = '';
                if (hashIndex !== -1) {
                    hashString = link.substring(hashIndex + 1);
                }

                // Decode any percent-encoded characters
                const decodedHashString = decodeURIComponent(hashString);
                var reference = await searchStringInFile(quickrefFilePath, `|${command}|`);
                if (reference === null) {
                    reference = await searchStringInFile(indexFilePath, `|${decodedHashString}|`);
                }
                if (reference === null) {
                    reference = await searchStringInFile(motionFilePath, `${command}`);
                }
                if (reference === null) {
                    reference = await searchStringInFile(changeFilePath, `${command}`);
                }
                if (reference !== null) {
                    reference = escapeMarkdownCharacters(reference);
                    // Remove the first instance of a single digit followed by a space
                    reference = reference.replace(/\d\s/, '');
                    if (command !== "N") {
                        reference = reference.replace(/N\s/g, '{count} ');
                    }
                }
                // TODO actually deal with parsing these properly later
                if (command === "gqq") {
                    reference = "Format the current line.  With a count format that many lines."
                }
                if (command === "g~~") {
                    reference = "Switch case of current line."
                }
                if (command === "guu") {
                    reference = "Make current line lowercase."
                }
                if (command === "gUU") {
                    reference = "Make current line uppercase."
                }
                if (command === '\'' && button == "Neutral Attack") {
                    reference = "Text object: Selects the text from the previous single quote until the next quote."
                }
                if (command === "[ for text objects, n otherwise") {
                    reference = "n repeat last search"
                }
                if (command === "Escape") {
                    reference = "If for any reason you do not know which mode you are in, you can always get back to Normal mode by typing <Esc> twice."
                }
                if (command === "ca" || command === "da" || command === "ya" || command === "va" || command === "gwa" || command === "gqa") {
                    reference = "Button command around text object"
                }
                if (command === "ci" || command === "di" || command === "yi" || command === "vi" || command === "gwi" || command === "gqi") {
                    reference = "Button command in text object"
                }
                if (command === '\'' && button == "QuoMark Attack") {
                    reference = "Jump to the mark {a-z} in the current buffer."
                }
                if (command === '\'.' && button == "QuoMark Attack") {
                    reference = "To the position where the last change was made."
                }
                if (command === '%') {
                    reference = "Find the next item in this line after or under the cursor and jump to its match."
                }
                parsedData.push({ motion: motion, button: button, command: command, reference: reference, link: link });
            }
        }
    } catch (error) {
        console.error('Error reading JSON file:', error);
    }
}

await loadJsonFile();

var vimFighterMd = tablemark(parsedData)
// Write the Markdown content to the output file
await fs.writeFile(outputFilePath, vimFighterMd, 'utf8');
console.log(`Markdown file saved to ${outputFilePath}`);
// Your additional code here

