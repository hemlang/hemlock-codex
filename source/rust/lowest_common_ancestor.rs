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

fn lca<'a>(root: &'a Tree, p: i32, q: i32) -> Option<&'a Node> {
    let node = root.as_ref()?;
    if p < node.value && q < node.value {
        lca(&node.left, p, q)
    } else if p > node.value && q > node.value {
        lca(&node.right, p, q)
    } else {
        Some(node)
    }
}

fn main() {
    let mut root: Tree = None;
    for &v in &[50, 30, 70, 20, 40, 60, 80] {
        root = insert(root, v);
    }
    println!("lca(20, 40): {}", lca(&root, 20, 40).unwrap().value);
    println!("lca(20, 70): {}", lca(&root, 20, 70).unwrap().value);
    println!("lca(60, 80): {}", lca(&root, 60, 80).unwrap().value);
}
