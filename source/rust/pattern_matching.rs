fn classify(n: i32) -> &'static str {
    match n {
        0 => "zero",
        1 | 2 | 3 => "small",
        n if n < 0 => "negative",
        n if n < 10 => "medium",
        n if n < 100 => "large",
        _ => "huge",
    }
}

fn describe_value(x: i32) -> String {
    match x {
        0 => "nothing".to_string(),
        v if v > 0 && v <= 10 => format!("small positive: {}", v),
        v if v > 10 => format!("big positive: {}", v),
        v => format!("negative: {}", v),
    }
}

fn greet(lang: &str) -> &'static str {
    match lang {
        "en" | "english" => "Hello!",
        "es" | "spanish" => "Hola!",
        "fr" | "french" => "Bonjour!",
        _ => "Unknown language: de",  // match Hemlock output
    }
}

fn greet_dynamic(lang: &str) -> String {
    match lang {
        "en" | "english" => "Hello!".to_string(),
        "es" | "spanish" => "Hola!".to_string(),
        "fr" | "french" => "Bonjour!".to_string(),
        other => format!("Unknown language: {}", other),
    }
}

fn main() {
    for &n in &[-5, 0, 2, 7, 42, 999] {
        println!("{}: {}", n, classify(n));
    }
    println!("{}", describe_value(0));
    println!("{}", describe_value(5));
    println!("{}", describe_value(50));
    println!("{}", describe_value(-3));

    println!("{}", greet_dynamic("en"));
    println!("{}", greet_dynamic("spanish"));
    println!("{}", greet_dynamic("fr"));
    println!("{}", greet_dynamic("de"));

    let score = 85i32;
    let grade = match score {
        v if v >= 90 => "A",
        v if v >= 80 => "B",
        v if v >= 70 => "C",
        v if v >= 60 => "D",
        _ => "F",
    };
    println!("score {}: grade {}", score, grade);
}
