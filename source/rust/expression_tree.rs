enum NodeVal {
    Op(char),
    Num(i32),
}

struct Node {
    val: NodeVal,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn num(n: i32) -> Box<Node> {
        Box::new(Node { val: NodeVal::Num(n), left: None, right: None })
    }
    fn op(op: char, left: Box<Node>, right: Box<Node>) -> Box<Node> {
        Box::new(Node { val: NodeVal::Op(op), left: Some(left), right: Some(right) })
    }
}

fn evaluate(node: &Node) -> i32 {
    match &node.val {
        NodeVal::Num(n) => *n,
        NodeVal::Op(op) => {
            let left = evaluate(node.left.as_ref().unwrap());
            let right = evaluate(node.right.as_ref().unwrap());
            match op {
                '+' => left + right,
                '-' => left - right,
                '*' => left * right,
                _ => 0,
            }
        }
    }
}

fn main() {
    // (2 + 3) * (4 - 1)
    let add_node = Node::op('+', Node::num(2), Node::num(3));
    let sub_node = Node::op('-', Node::num(4), Node::num(1));
    let mul_node = Node::op('*', add_node, sub_node);
    let result = evaluate(&mul_node);
    println!("result: {}", result);
}
