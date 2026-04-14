const CHARS: &[u8] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

fn b64_encode(input: &[u8]) -> String {
    let mut result = String::new();
    let mut i = 0;
    while i < input.len() {
        let b0 = input[i] as u32;
        let b1 = if i + 1 < input.len() { input[i+1] as u32 } else { 0 };
        let b2 = if i + 2 < input.len() { input[i+2] as u32 } else { 0 };
        let pad = if i + 1 >= input.len() { 2 } else if i + 2 >= input.len() { 1 } else { 0 };

        result.push(CHARS[((b0 >> 2) & 63) as usize] as char);
        result.push(CHARS[(((b0 & 3) << 4) | ((b1 >> 4) & 15)) as usize] as char);
        if pad == 2 {
            result.push_str("==");
        } else if pad == 1 {
            result.push(CHARS[(((b1 & 15) << 2) | ((b2 >> 6) & 3)) as usize] as char);
            result.push('=');
        } else {
            result.push(CHARS[(((b1 & 15) << 2) | ((b2 >> 6) & 3)) as usize] as char);
            result.push(CHARS[(b2 & 63) as usize] as char);
        }
        i += 3;
    }
    result
}

fn b64_char_index(c: char) -> i32 {
    for (i, &ch) in CHARS.iter().enumerate() {
        if ch as char == c { return i as i32; }
    }
    -1
}

fn b64_decode(input: &str) -> Vec<u8> {
    let chars: Vec<char> = input.chars().collect();
    let mut result = Vec::new();
    let mut i = 0;
    while i < chars.len() {
        let c0 = b64_char_index(chars[i]);
        let c1 = b64_char_index(chars[i+1]);
        let c2 = if chars[i+2] != '=' { b64_char_index(chars[i+2]) } else { -1 };
        let c3 = if chars[i+3] != '=' { b64_char_index(chars[i+3]) } else { -1 };
        result.push(((c0 << 2) | ((c1 >> 4) & 3)) as u8);
        if c2 >= 0 { result.push((((c1 & 15) << 4) | ((c2 >> 2) & 15)) as u8); }
        if c3 >= 0 { result.push((((c2 & 3) << 6) | c3) as u8); }
        i += 4;
    }
    result
}

fn main() {
    let original = "Hello, World!";
    let encoded = b64_encode(original.as_bytes());
    println!("original: {}", original);
    println!("encoded:  {}", encoded);

    let expected = "SGVsbG8sIFdvcmxkIQ==";
    if encoded == expected {
        println!("encoding: correct");
    } else {
        println!("encoding: mismatch (expected {})", expected);
    }

    let decoded_bytes = b64_decode(&encoded);
    let decoded = String::from_utf8(decoded_bytes).unwrap();
    println!("decoded:  {}", decoded);

    if decoded == original {
        println!("round-trip: ok");
    } else {
        println!("round-trip: FAILED");
    }
}
