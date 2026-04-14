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
    let mut result = Vec::new();
    inorder(&root, &mut result);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("inorder: {}", s.join(" "));
}
