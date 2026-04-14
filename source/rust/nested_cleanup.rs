struct Cleanup(&'static str);

impl Drop for Cleanup {
    fn drop(&mut self) {
        println!("{} cleanup", self.0);
    }
}

fn inner() {
    let _c = Cleanup("inner");
    println!("inner running");
}

fn middle() {
    let _c = Cleanup("middle");
    println!("middle running");
    inner();
}

fn outer() {
    let _c = Cleanup("outer");
    println!("outer running");
    middle();
}

fn main() {
    outer();
}
