struct Queue {
    inbox: Vec<i32>,
    outbox: Vec<i32>,
}

impl Queue {
    fn new() -> Self { Queue { inbox: vec![], outbox: vec![] } }
    fn enqueue(&mut self, val: i32) { self.inbox.push(val); }
    fn dequeue(&mut self) -> Option<i32> {
        if self.outbox.is_empty() {
            while let Some(x) = self.inbox.pop() {
                self.outbox.push(x);
            }
        }
        self.outbox.pop()
    }
}

fn main() {
    let mut q = Queue::new();
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    let mut results = Vec::new();
    results.push(q.dequeue().unwrap());
    results.push(q.dequeue().unwrap());
    q.enqueue(4); q.enqueue(5);
    results.push(q.dequeue().unwrap());
    results.push(q.dequeue().unwrap());
    results.push(q.dequeue().unwrap());
    let s: Vec<String> = results.iter().map(|x| x.to_string()).collect();
    println!("{}", s.join(" "));
}
