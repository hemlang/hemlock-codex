type List = Option<Box<Node>>;

struct Node {
    val: i32,
    next: List,
}

fn build_list(arr: &[i32]) -> List {
    let mut head = None;
    for &x in arr.iter().rev() {
        head = Some(Box::new(Node { val: x, next: head }));
    }
    head
}

fn print_list(head: &List, label: &str) {
    let mut parts = Vec::new();
    let mut cur = head;
    while let Some(node) = cur {
        parts.push(node.val.to_string());
        cur = &node.next;
    }
    println!("{}: {}", label, parts.join(" "));
}

fn reverse_list(head: List) -> List {
    let mut prev: List = None;
    let mut curr = head;
    while let Some(mut node) = curr {
        curr = node.next.take();
        node.next = prev;
        prev = Some(node);
    }
    prev
}

fn main() {
    let head = build_list(&[1, 2, 3, 4, 5]);
    print_list(&head, "original");
    let reversed = reverse_list(head);
    print_list(&reversed, "reversed");
}
