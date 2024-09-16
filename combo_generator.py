import nltk
from nltk.corpus import cmudict

# Download the CMU Pronouncing Dictionary if not already downloaded
nltk.download('cmudict')

# Load the CMU Pronouncing Dictionary
d = cmudict.dict()

# List of common digraphs
common_digraphs = ["th", "sh", "ch", "wh"]

# Methodology order (easily configurable)
methodology_order = ['digraph', 'first_syllables', 'first_two', 'first_last']

def get_syllables(word):
    """Return the syllables of a word using the CMU Pronouncing Dictionary."""
    if word.lower() in d:
        return [list(y for y in x if y[-1].isdigit()) for x in d[word.lower()]]
    else:
        return [[word]]

def starts_with_digraph(word):
    """Check if a word starts with a common digraph and return the digraph and the next letter."""
    for digraph in common_digraphs:
        if word.startswith(digraph):
            return digraph[0], word[len(digraph)]
    return None

def generate_combo(word, method):
    """Generate a combo for a word using the specified methodology."""
    if len(word) == 1:
        return word + ' '  # Single character word methodology
    elif method == 'first_two':
        return word[:2]
    elif method == 'first_syllables':
        syllables = get_syllables(word)
        return ''.join([s[0] for s in syllables[0]])
    elif method == 'first_last':
        return word[0] + word[-1]
    elif method == 'digraph':
        digraph_combo = starts_with_digraph(word)
        if digraph_combo:
            return digraph_combo[0] + digraph_combo[1]
        else:
            return word[:2]  # Fallback to first two letters if no digraph is found
    else:
        return word

def generate_unique_combos(words, methodologies):
    """Generate unique combos for a list of words using the specified methodologies."""
    combos = {}
    for word in words:
        for method in methodologies:
            combo = generate_combo(word, method)
            if combo not in combos.values():
                combos[word] = combo
                break
    return combos

# Generate QMK combo definitions
def generate_qmk_combos(combos):
    qmk_combos = []
    for word, combo in combos.items():
        formatted_combo = ', '.join([f'KC_{char.upper()}' if char != ' ' else 'KC_SPC' for char in combo])
        qmk_combos.append(f'COMB(WORD_COMBO_{word.upper()}, MD_{word.upper()}, {formatted_combo})')
    return qmk_combos

def main():
    # List of common English words
    #words = ["the", "be", "to", "of", "and", "a", "in", "that", "have", "I"]
    words = [
"the",
"a",
"be",
"have",
"do",
"to",
"of",
"in",
"for",
"on",
"with",
"as",
"at",
"because",
"when",
"not",
"and",
"that",
"from",
"but",
"'ve",
"'s",
"pt",
"he",
"i",
"it",
"i'd",
"i'll",
"i'm",
"i've",
"you",
"you'd",
"you'll",
"you're",
"you've",
"your",
"their",
"they're",
"they",
"there",
"they'd",
"they'll",
"here",
"where",
"we're",
"were",
"we'd",
"well",
"we'll",
"we've",
"what",
    ]
    # Generate unique combos using the specified methodologies
    unique_combos = generate_unique_combos(words, methodology_order)

    # Print the generated unique combos
    print("Unique Combos:", unique_combos)

    qmk_combos = generate_qmk_combos(unique_combos)

    # Print the QMK combo definitions
    print("\nQMK Combos:")
    print("\n".join(qmk_combos))

if __name__ == "__main__":
    main()
