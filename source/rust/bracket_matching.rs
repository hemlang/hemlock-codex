fn is_balanced(s: &str) -> bool {
    let mut stack = Vec::new();
    for c in s.chars() {
        match c {
            '(' | '{' | '[' => stack.push(c),
            ')' => { if stack.pop() != Some('(') { return false; } }
            '}' => { if stack.pop() != Some('{') { return false; } }
            ']' => { if stack.pop() != Some('[') { return false; } }
            _ => {}
        }
    }
    stack.is_empty()
}

fn main() {
    let tests = ["({[]})", "({[}])", ""];
    for t in &tests {
        if is_balanced(t) {
            println!("\"{}\" -> balanced", t);
        } else {
            println!("\"{}\" -> not balanced", t);
        }
    }
}
