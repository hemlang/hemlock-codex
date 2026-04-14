class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

def trie_insert(root, word):
    node = root
    for ch in word:
        if ch not in node.children:
            node.children[ch] = TrieNode()
        node = node.children[ch]
    node.is_end = True

def trie_search(root, word):
    node = root
    for ch in word:
        if ch not in node.children:
            return False
        node = node.children[ch]
    return node.is_end

def trie_starts_with(root, prefix):
    node = root
    for ch in prefix:
        if ch not in node.children:
            return False
        node = node.children[ch]
    return True

root = TrieNode()
for word in ["apple", "app", "application", "bat", "ball"]:
    trie_insert(root, word)

print(f'search "app": {str(trie_search(root, "app")).lower()}')
print(f'search "ap": {str(trie_search(root, "ap")).lower()}')
print(f'search "bat": {str(trie_search(root, "bat")).lower()}')
print(f'starts_with "app": {str(trie_starts_with(root, "app")).lower()}')
print(f'starts_with "ba": {str(trie_starts_with(root, "ba")).lower()}')
print(f'starts_with "cat": {str(trie_starts_with(root, "cat")).lower()}')
