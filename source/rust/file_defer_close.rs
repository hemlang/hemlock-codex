use std::fs;
use std::io::Read;

fn main() {
    let path = "/tmp/rust_defer_test.txt";
    fs::write(path, "hello from defer").unwrap();

    let mut f = fs::File::open(path).unwrap();
    let mut contents = String::new();
    f.read_to_string(&mut contents).unwrap();
    // File closed automatically when f drops (RAII = defer)

    if contents == "hello from defer" {
        println!("wrote and read back successfully");
    }
}
