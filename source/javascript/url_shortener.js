// URL shortener using in-memory maps
const urlToShort = {};
const shortToUrl = {};
let counter = 1000;

function encodeId(id) {
    const chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    let result = "";
    let n = id;
    while (n > 0) {
        const rem = n % 62;
        result = chars[rem] + result;
        n = Math.floor((n - rem) / 62);
    }
    return result;
}

function shorten(url) {
    if (urlToShort[url] != null) return urlToShort[url];
    counter++;
    const code = encodeId(counter);
    const short = `https://sho.rt/${code}`;
    urlToShort[url] = short;
    shortToUrl[short] = url;
    return short;
}

function resolve(shortUrl) {
    return shortToUrl[shortUrl] != null ? shortToUrl[shortUrl] : null;
}

const urls = [
    "https://example.com/long/path",
    "https://docs.hemlock.org/stdlib",
    "https://github.com/hemlang/42",
    "https://example.com/long/path"
];

console.log("=== URL Shortener ===");
for (const url of urls) {
    const short = shorten(url);
    console.log(`  ${url}`);
    console.log(`  -> ${short}`);
    console.log("");
}

console.log("=== Resolve Short URLs ===");
const testShort = shorten("https://docs.hemlock.org/stdlib");
const resolved = resolve(testShort);
console.log(`  ${testShort} -> ${resolved}`);

const s1 = shorten("https://example.com/long/path");
const s2 = shorten("https://example.com/long/path");
if (s1 === s2) console.log("\nDuplicate URL returns same short URL: ok");
