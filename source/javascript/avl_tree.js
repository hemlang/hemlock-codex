// AVL tree with rotations
function newNode(value) { return { value, left: null, right: null, height: 1 }; }

function height(node) { return node === null ? 0 : node.height; }
function maxVal(a, b) { return a > b ? a : b; }
function getBalance(node) { return node === null ? 0 : height(node.left) - height(node.right); }

function rightRotate(y) {
    const x = y.left, t2 = x.right;
    x.right = y;
    y.left = t2;
    y.height = maxVal(height(y.left), height(y.right)) + 1;
    x.height = maxVal(height(x.left), height(x.right)) + 1;
    return x;
}

function leftRotate(x) {
    const y = x.right, t2 = y.left;
    y.left = x;
    x.right = t2;
    x.height = maxVal(height(x.left), height(x.right)) + 1;
    y.height = maxVal(height(y.left), height(y.right)) + 1;
    return y;
}

function insert(root, value) {
    if (root === null) return newNode(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    else return root;

    root.height = maxVal(height(root.left), height(root.right)) + 1;
    const balance = getBalance(root);

    if (balance > 1 && value < root.left.value) return rightRotate(root);
    if (balance < -1 && value > root.right.value) return leftRotate(root);
    if (balance > 1 && value > root.left.value) { root.left = leftRotate(root.left); return rightRotate(root); }
    if (balance < -1 && value < root.right.value) { root.right = rightRotate(root.right); return leftRotate(root); }
    return root;
}

function inorder(root, result) {
    if (root === null) return;
    inorder(root.left, result);
    result.push(root.value);
    inorder(root.right, result);
}

let root = null;
const values = [10, 20, 30, 40, 50, 25];
for (const v of values) root = insert(root, v);

const result = [];
inorder(root, result);
console.log(`inorder: ${result.join(" ")}`);
