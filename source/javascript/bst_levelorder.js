// BST level-order traversal (BFS using array as queue)
function newNode(value) { return { value, left: null, right: null }; }

function insert(root, value) {
    if (root === null) return newNode(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    return root;
}

function levelorder(root) {
    if (root === null) return [];
    const result = [];
    const queue = [root];
    while (queue.length > 0) {
        const node = queue.shift();
        result.push(node.value);
        if (node.left !== null) queue.push(node.left);
        if (node.right !== null) queue.push(node.right);
    }
    return result;
}

let root = null;
const values = [50, 30, 70, 20, 40, 60, 80];
for (const v of values) root = insert(root, v);

const result = levelorder(root);
console.log(`levelorder: ${result.join(" ")}`);
