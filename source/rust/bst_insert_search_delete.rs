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
            if value < node.value {
                node.left = insert(node.left, value);
            } else if value > node.value {
                node.right = insert(node.right, value);
            }
            Some(node)
        }
    }
}

fn search(root: &Tree, value: i32) -> bool {
    match root {
        None => false,
        Some(node) => {
            if value == node.value { true }
            else if value < node.value { search(&node.left, value) }
            else { search(&node.right, value) }
        }
    }
}

fn find_min(root: &Tree) -> i32 {
    let mut node = root.as_ref().unwrap();
    while node.left.is_some() {
        node = node.left.as_ref().unwrap();
    }
    node.value
}

fn delete_node(root: Tree, value: i32) -> Tree {
    match root {
        None => None,
        Some(mut node) => {
            if value < node.value {
                node.left = delete_node(node.left, value);
                Some(node)
            } else if value > node.value {
                node.right = delete_node(node.right, value);
                Some(node)
            } else {
                if node.left.is_none() { return node.right; }
                if node.right.is_none() { return node.left; }
                let successor_val = find_min(&node.right);
                node.value = successor_val;
                node.right = delete_node(node.right, successor_val);
                Some(node)
            }
        }
    }
}

fn inorder(root: &Tree, result: &mut Vec<i32>) {
    if let Some(node) = root {
        inorder(&node.left, result);
        result.push(node.value);
        inorder(&node.right, result);
    }
}

fn main() {
    let mut root: Tree = None;
    for &v in &[50, 30, 70, 20, 40, 60, 80] {
        root = insert(root, v);
    }
    if search(&root, 40) { println!("search 40: found"); } else { println!("search 40: not found"); }
    if search(&root, 25) { println!("search 25: found"); } else { println!("search 25: not found"); }
    root = delete_node(root, 30);
    let mut result = Vec::new();
    inorder(&root, &mut result);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("inorder: {}", s.join(" "));
}
