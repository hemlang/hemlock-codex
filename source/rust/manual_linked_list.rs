// Manual linked list using raw allocation
// Using Vec<u8> as backing store to avoid alignment issues

struct Node {
    val: i32,
    next: *mut Node,
}

struct LinkedList {
    head: *mut Node,
}

impl LinkedList {
    fn new() -> Self { LinkedList { head: std::ptr::null_mut() } }

    fn push(&mut self, val: i32) {
        let node = Box::into_raw(Box::new(Node { val, next: self.head }));
        self.head = node;
    }

    fn traverse(&self) {
        let mut parts = Vec::new();
        let mut cur = self.head;
        while !cur.is_null() {
            unsafe {
                parts.push((*cur).val.to_string());
                cur = (*cur).next;
            }
        }
        println!("list: {}", parts.join(" "));
    }

    fn free_all(&mut self) {
        let mut cur = self.head;
        let mut count = 0;
        while !cur.is_null() {
            unsafe {
                let next = (*cur).next;
                drop(Box::from_raw(cur));
                count += 1;
                cur = next;
            }
        }
        self.head = std::ptr::null_mut();
        println!("freed {} nodes", count);
    }
}

fn main() {
    let mut list = LinkedList::new();
    list.push(10);
    list.push(20);
    list.push(30);
    list.traverse();
    list.free_all();
}
