use std::collections::HashMap;

const CHARS: &[u8] = b"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

fn encode_id(mut id: usize) -> String {
    let mut result = String::new();
    while id > 0 {
        let rem = id % 62;
        result.insert(0, CHARS[rem] as char);
        id = (id - rem) / 62;
    }
    result
}

struct UrlShortener {
    url_to_short: HashMap<String, String>,
    short_to_url: HashMap<String, String>,
    counter: usize,
}

impl UrlShortener {
    fn new() -> Self {
        UrlShortener { url_to_short: HashMap::new(), short_to_url: HashMap::new(), counter: 1000 }
    }

    fn shorten(&mut self, url: &str) -> String {
        if let Some(s) = self.url_to_short.get(url) { return s.clone(); }
        self.counter += 1;
        let code = encode_id(self.counter);
        let short = format!("https://sho.rt/{}", code);
        self.url_to_short.insert(url.to_string(), short.clone());
        self.short_to_url.insert(short.clone(), url.to_string());
        short
    }

    fn resolve(&self, short: &str) -> Option<&str> {
        self.short_to_url.get(short).map(|s| s.as_str())
    }
}

fn main() {
    let mut shortener = UrlShortener::new();
    let urls = [
        "https://example.com/long/path",
        "https://docs.hemlock.org/stdlib",
        "https://github.com/hemlang/42",
        "https://example.com/long/path",
    ];

    println!("=== URL Shortener ===");
    for url in &urls {
        let short = shortener.shorten(url);
        println!("  {}", url);
        println!("  -> {}", short);
        println!();
    }

    println!("=== Resolve Short URLs ===");
    let test_short = shortener.shorten("https://docs.hemlock.org/stdlib");
    let resolved = shortener.resolve(&test_short).unwrap();
    println!("  {} -> {}", test_short, resolved);

    let s1 = shortener.shorten("https://example.com/long/path");
    let s2 = shortener.shorten("https://example.com/long/path");
    if s1 == s2 {
        println!("\nDuplicate URL returns same short URL: ok");
    }
}
