struct BufferBuilder {
    data: Vec<u8>,
    capacity: usize,
    size: usize,
}

impl BufferBuilder {
    fn new(capacity: usize) -> Self {
        BufferBuilder { data: vec![0u8; capacity], capacity, size: 0 }
    }

    fn write_byte(&mut self, b: u8) {
        if self.size >= self.capacity {
            let new_cap = self.capacity * 2;
            self.data.resize(new_cap, 0);
            self.capacity = new_cap;
        }
        self.data[self.size] = b;
        self.size += 1;
    }

    fn read_back(&self) -> String {
        String::from_utf8_lossy(&self.data[..self.size]).to_string()
    }
}

fn main() {
    let mut bb = BufferBuilder::new(4);
    let message = "Hello, World!";
    for &b in message.as_bytes() {
        bb.write_byte(b);
    }
    println!("wrote {} bytes", bb.size);
    println!("capacity: {}", bb.capacity);
    let reconstructed = bb.read_back();
    println!("reconstructed: {}", reconstructed);
}
