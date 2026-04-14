url_to_short = {}
short_to_url = {}
counter = 1000

def encode_id(n):
    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    result = ""
    while n > 0:
        rem = n % 62
        result = chars[rem] + result
        n = (n - rem) // 62
    return result

def shorten(url):
    global counter
    if url in url_to_short:
        return url_to_short[url]
    counter += 1
    code = encode_id(counter)
    short = f"https://sho.rt/{code}"
    url_to_short[url] = short
    short_to_url[short] = url
    return short

def resolve(short_url):
    return short_to_url.get(short_url)

urls = [
    "https://example.com/long/path",
    "https://docs.hemlock.org/stdlib",
    "https://github.com/hemlang/42",
    "https://example.com/long/path",
]

print("=== URL Shortener ===")
for url in urls:
    short = shorten(url)
    print(f"  {url}")
    print(f"  -> {short}")
    print("")

print("=== Resolve Short URLs ===")
test_short = shorten("https://docs.hemlock.org/stdlib")
resolved = resolve(test_short)
print(f"  {test_short} -> {resolved}")

s1 = shorten("https://example.com/long/path")
s2 = shorten("https://example.com/long/path")
if s1 == s2:
    print("\nDuplicate URL returns same short URL: ok")
