// Lowest Common Ancestor in BST
function newNode(value) { return { value, left: null, right: null }; }

function insert(root, value) {
    if (root === null) return newNode(value);
    if (value < root.value) root.left = insert(root.left, value);
    else if (value > root.value) root.right = insert(root.right, value);
    return root;
}

function lca(root, p, q) {
    if (root === null) return null;
    if (p < root.value && q < root.value) return lca(root.left, p, q);
    if (p > root.value && q > root.value) return lca(root.right, p, q);
    return root;
}

let root = null;
const values = [50, 30, 70, 20, 40, 60, 80];
for (const v of values) root = insert(root, v);

const r1 = lca(root, 20, 40);
console.log(`lca(20, 40): ${r1.value}`);

const r2 = lca(root, 20, 70);
console.log(`lca(20, 70): ${r2.value}`);

const r3 = lca(root, 60, 80);
console.log(`lca(60, 80): ${r3.value}`);
