struct Config {
    verbose: bool,
    output: String,
    format: String,
    count: i32,
}

impl Config {
    fn parse_option(&mut self, key: &str, value: &str) {
        match key {
            "--verbose" | "-v" => self.verbose = true,
            "--output" | "-o" => self.output = value.to_string(),
            "--format" | "-f" => self.format = value.to_string(),
            "--count" | "-n" => self.count = value.parse().unwrap_or(self.count),
            _ => {}
        }
    }
}

fn main() {
    let tool_name = "hemlock-tool";
    let version = "1.0.0";

    let mut config = Config {
        verbose: false,
        output: "stdout".to_string(),
        format: "text".to_string(),
        count: 10,
    };

    let simulated_args = [
        ("--verbose", ""),
        ("--output", "result.txt"),
        ("--format", "json"),
        ("--count", "25"),
    ];

    for (key, val) in &simulated_args {
        config.parse_option(key, val);
    }

    println!("{} v{}", tool_name, version);
    println!("Parsed configuration:");
    println!("  verbose: {}", config.verbose);
    println!("  output:  {}", config.output);
    println!("  format:  {}", config.format);
    println!("  count:   {}", config.count);
    println!("Ready to process.");
}
