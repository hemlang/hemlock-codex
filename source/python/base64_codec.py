import base64

original = "Hello, World!"
encoded = base64.b64encode(original.encode()).decode()
print(f"original: {original}")
print(f"encoded:  {encoded}")

expected = "SGVsbG8sIFdvcmxkIQ=="
if encoded == expected:
    print("encoding: correct")
else:
    print(f"encoding: mismatch (expected {expected})")

decoded = base64.b64decode(encoded).decode()
print(f"decoded:  {decoded}")

if decoded == original:
    print("round-trip: ok")
else:
    print("round-trip: FAILED")
