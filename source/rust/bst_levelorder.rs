use std::collections::VecDeque;

type Tree = Option<Box<Node>>;

struct Node {
    value: i32,
    left: Tree,
    right: Tree,
}

fn insert(root: Tree, value: i32) -> Tree {
    match root {
        None => Some(Box::new(Node { value, left: None, right: None })),
        Some(mut node) => {
            if value < node.value { node.left = insert(node.left, value); }
            else if value > node.value { node.right = insert(node.right, value); }
            Some(node)
        }
    }
}

fn levelorder(root: &Tree) -> Vec<i32> {
    let mut result = Vec::new();
    if root.is_none() { return result; }
    let mut queue: VecDeque<&Node> = VecDeque::new();
    queue.push_back(root.as_ref().unwrap());
    while let Some(node) = queue.pop_front() {
        result.push(node.value);
        if let Some(l) = &node.left { queue.push_back(l); }
        if let Some(r) = &node.right { queue.push_back(r); }
    }
    result
}

fn main() {
    let mut root: Tree = None;
    for &v in &[50, 30, 70, 20, 40, 60, 80] {
        root = insert(root, v);
    }
    let result = levelorder(&root);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("levelorder: {}", s.join(" "));
}
