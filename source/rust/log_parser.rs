fn extract_level(line: &str) -> &'static str {
    if line.contains("[INFO]") { "INFO" }
    else if line.contains("[WARN]") { "WARN" }
    else if line.contains("[ERROR]") { "ERROR" }
    else if line.contains("[DEBUG]") { "DEBUG" }
    else { "UNKNOWN" }
}

fn extract_timestamp(line: &str) -> &str {
    &line[..19]
}

fn extract_message(line: &str) -> &str {
    if let Some(pos) = line.find("] ") {
        &line[pos + 2..]
    } else {
        line
    }
}

fn main() {
    let logs = [
        "2024-01-15 08:30:12 [INFO] Application started",
        "2024-01-15 08:30:15 [INFO] Loading configuration",
        "2024-01-15 08:30:16 [WARN] Config file not found, using defaults",
        "2024-01-15 08:31:00 [INFO] Processing 150 records",
        "2024-01-15 08:31:05 [ERROR] Failed to parse record #42",
        "2024-01-15 08:31:10 [WARN] Retrying failed operation",
        "2024-01-15 08:31:15 [INFO] Processing complete",
        "2024-01-15 08:31:20 [INFO] Shutting down",
    ];

    let mut info_count = 0;
    let mut warn_count = 0;
    let mut error_count = 0;

    println!("=== Log Analysis ===");
    for line in &logs {
        match extract_level(line) {
            "INFO" => info_count += 1,
            "WARN" => warn_count += 1,
            "ERROR" => error_count += 1,
            _ => {}
        }
    }

    println!("Total lines: {}", logs.len());
    println!("INFO: {}", info_count);
    println!("WARN: {}", warn_count);
    println!("ERROR: {}", error_count);

    println!("\n=== Error Details ===");
    for line in &logs {
        if line.contains("[ERROR]") {
            println!("  {}: {}", extract_timestamp(line), extract_message(line));
        }
    }
}
