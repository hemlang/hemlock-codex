use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, TrieNode>,
    is_end: bool,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode { children: HashMap::new(), is_end: false }
    }
}

struct Trie {
    root: TrieNode,
}

impl Trie {
    fn new() -> Self {
        Trie { root: TrieNode::new() }
    }

    fn insert(&mut self, word: &str) {
        let mut node = &mut self.root;
        for ch in word.chars() {
            node = node.children.entry(ch).or_insert_with(TrieNode::new);
        }
        node.is_end = true;
    }

    fn search(&self, word: &str) -> bool {
        let mut node = &self.root;
        for ch in word.chars() {
            match node.children.get(&ch) {
                None => return false,
                Some(n) => node = n,
            }
        }
        node.is_end
    }

    fn starts_with(&self, prefix: &str) -> bool {
        let mut node = &self.root;
        for ch in prefix.chars() {
            match node.children.get(&ch) {
                None => return false,
                Some(n) => node = n,
            }
        }
        true
    }
}

fn main() {
    let mut trie = Trie::new();
    for word in &["apple", "app", "application", "bat", "ball"] {
        trie.insert(word);
    }
    println!("search \"app\": {}", trie.search("app"));
    println!("search \"ap\": {}", trie.search("ap"));
    println!("search \"bat\": {}", trie.search("bat"));
    println!("starts_with \"app\": {}", trie.starts_with("app"));
    println!("starts_with \"ba\": {}", trie.starts_with("ba"));
    println!("starts_with \"cat\": {}", trie.starts_with("cat"));
}
