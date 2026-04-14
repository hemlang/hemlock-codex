type Tree = Option<Box<Node>>;

struct Node {
    value: i32,
    left: Tree,
    right: Tree,
    height: i32,
}

fn height(root: &Tree) -> i32 {
    root.as_ref().map_or(0, |n| n.height)
}

fn update_height(node: &mut Node) {
    node.height = 1 + height(&node.left).max(height(&node.right));
}

fn right_rotate(mut y: Box<Node>) -> Box<Node> {
    let mut x = y.left.take().unwrap();
    y.left = x.right.take();
    update_height(&mut y);
    x.right = Some(y);
    update_height(&mut x);
    x
}

fn left_rotate(mut x: Box<Node>) -> Box<Node> {
    let mut y = x.right.take().unwrap();
    x.right = y.left.take();
    update_height(&mut x);
    y.left = Some(x);
    update_height(&mut y);
    y
}

fn insert(root: Tree, value: i32) -> Tree {
    let mut node = match root {
        None => return Some(Box::new(Node { value, left: None, right: None, height: 1 })),
        Some(n) => n,
    };
    if value < node.value {
        node.left = insert(node.left, value);
    } else if value > node.value {
        node.right = insert(node.right, value);
    } else {
        return Some(node);
    }
    update_height(&mut node);
    let balance = height(&node.left) - height(&node.right);
    let left_val = node.left.as_ref().map(|n| n.value);
    let right_val = node.right.as_ref().map(|n| n.value);

    if balance > 1 && Some(value) < left_val {
        return Some(right_rotate(node));
    }
    if balance < -1 && Some(value) > right_val {
        return Some(left_rotate(node));
    }
    if balance > 1 && Some(value) > left_val {
        node.left = Some(left_rotate(node.left.take().unwrap()));
        return Some(right_rotate(node));
    }
    if balance < -1 && Some(value) < right_val {
        node.right = Some(right_rotate(node.right.take().unwrap()));
        return Some(left_rotate(node));
    }
    Some(node)
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
    for &v in &[10, 20, 30, 40, 50, 25] {
        root = insert(root, v);
    }
    let mut result = Vec::new();
    inorder(&root, &mut result);
    let s: Vec<String> = result.iter().map(|x| x.to_string()).collect();
    println!("inorder: {}", s.join(" "));
}
