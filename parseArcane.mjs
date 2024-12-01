import tablemark from "tablemark"
import fs from 'fs';
import path from 'path';




const arcaneKeysPath = path.join("E:", "uranus", "coding", "bkqmk", "users", "eristocrates", "features", "empressabyss", "arcane_keys.c");
const arcaneMarkdownPath = path.join("E:", "uranus", "coding", "bkqmk", "arcane.md");
var magicList = [];
var table;
const lookupTable = {
    "LEFT_TOP_OUTER": "j",
    "LEFT_TOP_PINKY": "y",
    "LEFT_TOP_RING": "f",
    "LEFT_TOP_MIDDLE": "d",
    "LEFT_TOP_INDEX": "b",
    "LEFT_HOME_OUTER": "m",
    "LEFT_HOME_PINKY": "c",
    "LEFT_HOME_RING": "s",
    "LEFT_HOME_MIDDLE": "t",
    "LEFT_HOME_INDEX": "n",
    "LEFT_BOTTOM_OUTER": "",
    "LEFT_BOTTOM_PINKY": "p",
    "LEFT_BOTTOM_RING": "v",
    "LEFT_BOTTOM_MIDDLE": "k",
    "LEFT_BOTTOM_INDEX": "x",
    "RIGHT_TOP_OUTER": "qu",
    "RIGHT_TOP_PINKY": "l",
    "RIGHT_TOP_RING": ".",
    "RIGHT_TOP_MIDDLE": "o",
    "RIGHT_TOP_INDEX": "w",
    "RIGHT_HOME_OUTER": "g",
    "RIGHT_HOME_PINKY": "h",
    "RIGHT_HOME_RING": "i",
    "RIGHT_HOME_MIDDLE": "a",
    "RIGHT_HOME_INDEX": "u",
    "RIGHT_BOTTOM_OUTER": "",
    "RIGHT_BOTTOM_PINKY": "wh",
    "RIGHT_BOTTOM_RING": ",",
    "RIGHT_BOTTOM_MIDDLE": "'",
    "RIGHT_BOTTOM_INDEX": "=",
    "LEFT_INNER_THUMB": "z",
    "LEFT_MIDDLE_THUMB": "r",
    "LEFT_OUTER_THUMB": "space ",
    "RIGHT_OUTER_THUMB": "space ",
    "RIGHT_MIDDLE_THUMB": "e",
    "LEFT_TOP_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-top-left.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
    "LEFT_HOME_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-left.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
    "LEFT_BOTTOM_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-bottom-left.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
    "RIGHT_TOP_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-top-right.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
    "RIGHT_HOME_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-right.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
    "RIGHT_BOTTOM_ARCANE": `<img src="https://raw.githubusercontent.com/eristocrates/bkqmk/85e76f1e98111f4c93a7c8477e1180c1e44d044f/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/arrow-bottom-right.svg" alt="image" width="25" height="25"  style="filter: drop-shadow(0 0 5px white);"></img>`,
}

// Read the file asynchronously
fs.readFile(arcaneKeysPath, 'utf8', (err, data) => {
    if (err) {
        // console.error("Error reading the file:", err);
        return;
    } else {
        // console.log("File read");
    }

    // Split the file content by lines
    const lines = data.split('\n');

    // Define the regex
    const caseRegex = /\(LAST\w* && (LEFT|RIGHT)[_A-Z]*\)/;
    // Regular expression to capture the part starting with "LAST"
    const lastRegex = /LAST_([_A-Z]*)/;  // \b denotes a word boundary to ensure the correct capture
    const arcaneRegex = /(LEFT|RIGHT)[_A-Z]*ARCANE/;

    // Regular expression for "MAGIC" strings
    const magicRegex = /MAGIC_([_A-Z]*)/;

    // Regular expression for quoted strings
    const quoteRegex = /"([^"]*)"/;
    // Store captured lines
    const capturedLines = [];

    lines.forEach((line, index) => {
        let magic = { lastKey: "", arcaneKey: "", output: "" }
        // Determine and extract based on condition
        let output;

        // Check if the current line matches the regex
        if (caseRegex.test(line)) {
            // Capture the current matched line
            capturedLines.push(line);
            magic.lastKey = lookupTable[line.match(lastRegex)[1]] || "Not Found";
            magic.arcaneKey = lookupTable[line.match(arcaneRegex)[0]] || "Not Found";
            // Try to capture the line immediately following the matched line

            if (index + 1 < lines.length) {
                let nextLine = lines[index + 1];
                capturedLines.push(nextLine);

                if (magicRegex.test(nextLine)) {
                    // Extract the MAGIC-related string
                    const magicMatch = lookupTable[nextLine.match(magicRegex)[1]] || "Not Found";
                    output = magicMatch ? magicMatch[0] : "";
                    // console.log("Captured 'MAGIC' string:", output);

                } else if (quoteRegex.test(nextLine)) {
                    // Extract the string inside quotation marks
                    const quoteMatch = nextLine.match(quoteRegex);
                    output = quoteMatch ? quoteMatch[1] : "";
                    // console.log("Captured string within quotes:", output);
                }
                magic.output = magic.lastKey + output;
                magicList.push(magic);
            }
        }
    });
    var arcaneMd = `
# Base Alphas

![image](https://github.com/eristocrates/bkqmk/blob/main/keyboards/bastardkb/charybdis/3x6/keymaps/eristocrates/draw/png/CISTERN.png?raw=true)

# Transformation Table


`;

    // Sort the magicList by the 'last' property
    magicList.sort((a, b) => {
        const lastA = a.lastKey.toUpperCase(); // case-insensitive comparison
        const lastB = b.lastKey.toUpperCase(); // case-insensitive comparison

        if (lastA < lastB) {
            return -1;
        }
        if (lastA > lastB) {
            return 1;
        }
        return 0; // a and b are equal
    });


    arcaneMd += tablemark(magicList);

    // Correct usage with utf8 encoding specified in an options object and a callback
    fs.writeFile(arcaneMarkdownPath, arcaneMd, { encoding: 'utf8' }, (err) => {
        if (err) {
            // console.error('Error writing file:', err);
        } else {
            // console.log('File written successfully.');
        }
    });

});


