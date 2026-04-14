// BST in-order traversal
function newNode(value) { return { value, left: null, right: null }; }

function insert(root, value) {
    if (root === null) return newNode(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    return root;
}

function inorder(root, result) {
    if (root === null) return;
    inorder(root.left, result);
    result.push(root.value);
    inorder(root.right, result);
}

let root = null;
const values = [50, 30, 70, 20, 40, 60, 80];
for (const v of values) root = insert(root, v);

const result = [];
inorder(root, result);
console.log(`inorder: ${result.join(" ")}`);
