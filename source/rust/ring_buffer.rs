struct RingBuffer {
    data: Vec<i32>,
    head: usize,
    tail: usize,
    count: usize,
    capacity: usize,
}

impl RingBuffer {
    fn new(capacity: usize) -> Self {
        RingBuffer { data: vec![0; capacity], head: 0, tail: 0, count: 0, capacity }
    }

    fn write(&mut self, val: i32) -> bool {
        if self.count == self.capacity {
            println!("ring full, cannot write {}", val);
            return false;
        }
        self.data[self.tail] = val;
        self.tail = (self.tail + 1) % self.capacity;
        self.count += 1;
        true
    }

    fn read(&mut self) -> Option<i32> {
        if self.count == 0 {
            println!("ring empty");
            return None;
        }
        let val = self.data[self.head];
        self.head = (self.head + 1) % self.capacity;
        self.count -= 1;
        Some(val)
    }
}

fn main() {
    let mut rb = RingBuffer::new(4);
    rb.write(1); rb.write(2); rb.write(3); rb.write(4);
    let mut results = Vec::new();
    results.push(rb.read().unwrap());
    results.push(rb.read().unwrap());
    rb.write(5); rb.write(6);
    results.push(rb.read().unwrap());
    results.push(rb.read().unwrap());
    results.push(rb.read().unwrap());
    results.push(rb.read().unwrap());
    let s: Vec<String> = results.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
