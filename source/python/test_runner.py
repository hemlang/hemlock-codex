tests = []
passed = 0
failed = 0

def add_test(name, actual, expected):
    tests.append({"name": name, "actual": actual, "expected": expected})

def run_tests():
    global passed, failed
    print("=== Test Results ===")
    for t in tests:
        if t["actual"] == t["expected"]:
            print(f"  PASS: {t['name']}")
            passed += 1
        else:
            print(f"  FAIL: {t['name']} (expected {t['expected']}, got {t['actual']})")
            failed += 1
    total = passed + failed
    print(f"\n{passed}/{total} tests passed")
    if failed > 0:
        print(f"{failed} test(s) failed")

# String tests
add_test("string length", len("hello"), 5)
add_test("string contains", "world" in "hello world", True)
add_test("string upper", "hello".upper(), "HELLO")

# Array tests
arr = [1, 2, 3, 4, 5]
add_test("array length", len(arr), 5)
add_test("array first", arr[0], 1)
add_test("array last", arr[-1], 5)
add_test("array contains", 3 in arr, True)

# Math tests
add_test("addition", 2 + 3, 5)
add_test("multiplication", 6 * 7, 42)
add_test("boolean logic", True and not False, True)

run_tests()
