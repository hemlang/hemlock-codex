// Mini test runner framework
const tests = [];
let passed = 0, failed = 0;

function addTest(name, actual, expected) { tests.push({ name, actual, expected }); }

function runTests() {
    console.log("=== Test Results ===");
    for (const t of tests) {
        if (t.actual === t.expected) { console.log(`  PASS: ${t.name}`); passed++; }
        else { console.log(`  FAIL: ${t.name} (expected ${t.expected}, got ${t.actual})`); failed++; }
    }
    const total = passed + failed;
    console.log(`\n${passed}/${total} tests passed`);
    if (failed > 0) console.log(`${failed} test(s) failed`);
}

// String tests
addTest("string length", "hello".length, 5);
addTest("string contains", "hello world".includes("world"), true);
addTest("string upper", "hello".toUpperCase(), "HELLO");

// Array tests
const arr = [1, 2, 3, 4, 5];
addTest("array length", arr.length, 5);
addTest("array first", arr[0], 1);
addTest("array last", arr[arr.length - 1], 5);
addTest("array contains", arr.includes(3), true);

// Math tests
addTest("addition", 2 + 3, 5);
addTest("multiplication", 6 * 7, 42);
addTest("boolean logic", true && !false, true);

runTests();
