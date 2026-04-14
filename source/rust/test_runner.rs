struct Test {
    name: String,
    passed: bool,
    expected: String,
    actual: String,
}

fn run_tests(tests: &[Test]) {
    println!("=== Test Results ===");
    let mut passed = 0;
    let mut failed = 0;
    for t in tests {
        if t.passed {
            println!("  PASS: {}", t.name);
            passed += 1;
        } else {
            println!("  FAIL: {} (expected {}, got {})", t.name, t.expected, t.actual);
            failed += 1;
        }
    }
    let total = passed + failed;
    println!("\n{}/{} tests passed", passed, total);
    if failed > 0 {
        println!("{} test(s) failed", failed);
    }
}

fn test_eq<T: PartialEq + ToString>(name: &str, actual: T, expected: T) -> Test {
    let passed = actual == expected;
    Test {
        name: name.to_string(),
        passed,
        expected: expected.to_string(),
        actual: actual.to_string(),
    }
}

fn main() {
    let hello = "hello";
    let arr = vec![1i32, 2, 3, 4, 5];

    let tests = vec![
        test_eq("string length", hello.len(), 5),
        test_eq("string contains", hello.contains("world"), false), // "hello world".contains("world")
        {
            // Fix: use the right string
            let s = "hello world";
            test_eq("string contains", s.contains("world"), true)
        },
        test_eq("string upper", hello.to_uppercase(), "HELLO".to_string()),
        test_eq("array length", arr.len(), 5),
        test_eq("array first", arr.first().copied().unwrap(), 1),
        test_eq("array last", arr.last().copied().unwrap(), 5),
        test_eq("array contains", arr.contains(&3), true),
        test_eq("addition", 2 + 3, 5),
        test_eq("multiplication", 6 * 7, 42),
        test_eq("boolean logic", true && !false, true),
    ];

    // Filter out duplicates - the Hemlock code has 11 tests
    // Re-create to match: string length, string contains, string upper, array x4, math x2, bool
    let tests2 = vec![
        test_eq("string length", "hello".len(), 5usize),
        test_eq("string contains", "hello world".contains("world"), true),
        test_eq("string upper", "hello".to_uppercase(), "HELLO".to_string()),
        test_eq("array length", arr.len(), 5usize),
        test_eq("array first", *arr.first().unwrap(), 1i32),
        test_eq("array last", *arr.last().unwrap(), 5i32),
        test_eq("array contains", arr.contains(&3), true),
        test_eq("addition", 2 + 3, 5i32),
        test_eq("multiplication", 6 * 7, 42i32),
        test_eq("boolean logic", true && !false, true),
    ];

    run_tests(&tests2);
}
