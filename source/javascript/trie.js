// Trie insert, search, and prefix check
function newTrieNode() { return { children: {}, isEnd: false }; }

function trieInsert(root, word) {
    let node = root;
    for (const ch of word) {
        if (!node.children[ch]) node.children[ch] = newTrieNode();
        node = node.children[ch];
    }
    node.isEnd = true;
}

function trieSearch(root, word) {
    let node = root;
    for (const ch of word) {
        if (!node.children[ch]) return false;
        node = node.children[ch];
    }
    return node.isEnd;
}

function trieStartsWith(root, prefix) {
    let node = root;
    for (const ch of prefix) {
        if (!node.children[ch]) return false;
        node = node.children[ch];
    }
    return true;
}

const root = newTrieNode();
const words = ["apple", "app", "application", "bat", "ball"];
for (const w of words) trieInsert(root, w);

console.log(`search "app": ${trieSearch(root, "app")}`);
console.log(`search "ap": ${trieSearch(root, "ap")}`);
console.log(`search "bat": ${trieSearch(root, "bat")}`);
console.log(`starts_with "app": ${trieStartsWith(root, "app")}`);
console.log(`starts_with "ba": ${trieStartsWith(root, "ba")}`);
console.log(`starts_with "cat": ${trieStartsWith(root, "cat")}`);
