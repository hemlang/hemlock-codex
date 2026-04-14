// BST with insert, search, and delete operations
function newNode(value) { return { value, left: null, right: null }; }

function insert(root, value) {
    if (root === null) return newNode(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    return root;
}

function search(root, value) {
    if (root === null) return false;
    if (value === root.value) return true;
    if (value < root.value) return search(root.left, value);
    return search(root.right, value);
}

function findMin(root) {
    let current = root;
    while (current.left !== null) current = current.left;
    return current;
}

function deleteNode(root, value) {
    if (root === null) return null;
    if (value < root.value) root.left = deleteNode(root.left, value);
    else if (value > root.value) root.right = deleteNode(root.right, value);
    else {
        if (root.left === null) return root.right;
        if (root.right === null) return root.left;
        const successor = findMin(root.right);
        root.value = successor.value;
        root.right = deleteNode(root.right, successor.value);
    }
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

console.log(search(root, 40) ? "search 40: found" : "search 40: not found");
console.log(search(root, 25) ? "search 25: found" : "search 25: not found");

root = deleteNode(root, 30);

const result = [];
inorder(root, result);
console.log(`inorder: ${result.join(" ")}`);
