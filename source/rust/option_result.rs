fn find_user(id: i32) -> Option<String> {
    match id {
        1 => Some("Alice".to_string()),
        2 => Some("Bob".to_string()),
        _ => None,
    }
}

fn parse_port(s: &str) -> Result<u16, String> {
    let n: i32 = s.parse().map_err(|_| format!("invalid number: {}", s))?;
    if n < 1 || n > 65535 {
        Err(format!("port out of range: {}", n))
    } else {
        Ok(n as u16)
    }
}

fn main() {
    match find_user(1) {
        Some(name) => println!("found: {}", name),
        None => println!("not found"),
    }
    match find_user(99) {
        Some(name) => println!("found: {}", name),
        None => println!("not found"),
    }
    match parse_port("8080") {
        Ok(p) => println!("port: {}", p),
        Err(e) => println!("error: {}", e),
    }
    match parse_port("abc") {
        Ok(p) => println!("port: {}", p),
        Err(e) => println!("error: {}", e),
    }
    match parse_port("99999") {
        Ok(p) => println!("port: {}", p),
        Err(e) => println!("error: {}", e),
    }
}
