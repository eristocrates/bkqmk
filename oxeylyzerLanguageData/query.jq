.bigrams
| to_entries
| map(select(.key | test("^[a-zA-Z]{2}$")))
| map({first_letter: (.key[0]), bigram: .})
| debug
| group_by(.first_letter)



#| map({first_letter: (if type == "string" then .key[0] else null end), bigram: .})
#| map({
#    (.[0].key[0]): map({key: .key, value: .value} | .) | sort_by(-.value)
#})
#| add
