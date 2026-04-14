text = "the cat sat on the mat the cat"
words = text.split()
freq = {}
for w in words:
    freq[w] = freq.get(w, 0) + 1

for word, count in sorted(freq.items(), key=lambda x: -x[1]):
    print(f"{word}: {count}")
