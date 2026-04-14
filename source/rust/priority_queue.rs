struct MinHeap {
    heap: Vec<i32>,
}

impl MinHeap {
    fn new() -> Self { MinHeap { heap: vec![] } }

    fn insert(&mut self, val: i32) {
        self.heap.push(val);
        let mut i = self.heap.len() - 1;
        while i > 0 {
            let parent = (i - 1) / 2;
            if self.heap[i] < self.heap[parent] {
                self.heap.swap(i, parent);
                i = parent;
            } else {
                break;
            }
        }
    }

    fn extract_min(&mut self) -> i32 {
        let min = self.heap[0];
        let last = self.heap.pop().unwrap();
        if !self.heap.is_empty() {
            self.heap[0] = last;
            let mut i = 0;
            loop {
                let left = 2 * i + 1;
                let right = 2 * i + 2;
                let mut smallest = i;
                if left < self.heap.len() && self.heap[left] < self.heap[smallest] { smallest = left; }
                if right < self.heap.len() && self.heap[right] < self.heap[smallest] { smallest = right; }
                if smallest != i {
                    self.heap.swap(i, smallest);
                    i = smallest;
                } else {
                    break;
                }
            }
        }
        min
    }
}

fn main() {
    let mut pq = MinHeap::new();
    for &v in &[5, 3, 7, 1, 4, 2] {
        pq.insert(v);
    }
    let mut results = Vec::new();
    for _ in 0..6 {
        results.push(pq.extract_min().to_string());
    }
    println!("{}", results.join(" "));
}
