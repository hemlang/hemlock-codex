// Simple JSON-like config without external crates

#[derive(Clone, Debug)]
struct Config {
    host: String,
    port: i32,
    debug: bool,
    log_level: String,
    max_connections: i32,
    timeout: i32,
}

impl Config {
    fn defaults() -> Self {
        Config {
            host: "localhost".to_string(),
            port: 8080,
            debug: false,
            log_level: "info".to_string(),
            max_connections: 100,
            timeout: 30,
        }
    }

    fn pretty_print(&self) {
        println!("{{");
        println!("  \"host\": \"{}\",", self.host);
        println!("  \"port\": {},", self.port);
        println!("  \"debug\": {},", self.debug);
        println!("  \"log_level\": \"{}\",", self.log_level);
        println!("  \"max_connections\": {},", self.max_connections);
        println!("  \"timeout\": {}", self.timeout);
        println!("}}");
    }
}

fn main() {
    let defaults = Config::defaults();

    // User overrides
    let mut final_config = defaults.clone();
    final_config.port = 3000;
    final_config.debug = true;
    final_config.log_level = "debug".to_string();

    println!("=== Default Config ===");
    defaults.pretty_print();
    println!("=== User Overrides ===");
    println!("{{");
    println!("  \"port\": 3000,");
    println!("  \"debug\": true,");
    println!("  \"log_level\": \"debug\"");
    println!("}}");
    println!("=== Final Config ===");
    final_config.pretty_print();
}
