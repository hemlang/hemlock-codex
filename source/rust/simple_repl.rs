fn tokenize(expr: &str) -> Vec<String> {
    let mut tokens = Vec::new();
    let mut num = String::new();
    for ch in expr.chars() {
        if ch == ' ' {
            if !num.is_empty() { tokens.push(num.clone()); num.clear(); }
        } else if "+-*/".contains(ch) {
            if !num.is_empty() { tokens.push(num.clone()); num.clear(); }
            tokens.push(ch.to_string());
        } else {
            num.push(ch);
        }
    }
    if !num.is_empty() { tokens.push(num); }
    tokens
}

fn evaluate(expr: &str) -> f64 {
    let tokens = tokenize(expr);
    if tokens.is_empty() { return 0.0; }
    let mut result: f64 = tokens[0].parse().unwrap_or(0.0);
    let mut i = 1;
    while i < tokens.len() {
        let op = &tokens[i];
        let operand: f64 = tokens[i+1].parse().unwrap_or(0.0);
        match op.as_str() {
            "+" => result += operand,
            "-" => result -= operand,
            "*" => result *= operand,
            "/" => result /= operand,
            _ => {}
        }
        i += 2;
    }
    result
}

fn main() {
    let inputs = ["2 + 3", "10 * 4", "100 / 7", "50 - 18", "2 + 3 * 4"];
    println!("=== Simple Calculator ===");
    for input in &inputs {
        let result = evaluate(input);
        let int_result = result as i64;
        if int_result as f64 == result {
            println!("> {} = {}", input, int_result);
        } else {
            println!("> {} = {}", input, result);
        }
    }
    println!("=== Done ===");
}
