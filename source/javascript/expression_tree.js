// Expression tree evaluation
// Build tree for (2 + 3) * (4 - 1)
function newNode(value) { return { value, left: null, right: null }; }

function evaluate(node) {
    if (node.left === null && node.right === null) return parseInt(node.value);
    const leftVal = evaluate(node.left);
    const rightVal = evaluate(node.right);
    if (node.value === "+") return leftVal + rightVal;
    if (node.value === "-") return leftVal - rightVal;
    if (node.value === "*") return leftVal * rightVal;
    return 0;
}

const addNode = newNode("+");
addNode.left = newNode("2");
addNode.right = newNode("3");

const subNode = newNode("-");
subNode.left = newNode("4");
subNode.right = newNode("1");

const mulNode = newNode("*");
mulNode.left = addNode;
mulNode.right = subNode;

const result = evaluate(mulNode);
console.log(`result: ${result}`);
