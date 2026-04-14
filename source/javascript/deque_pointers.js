// Double-ended queue using JS objects (simulating pointer-based deque)
let dqHead = null, dqTail = null, dqSize = 0;

function makeNode(val) { return { val, prev: null, next: null }; }

function pushFront(val) {
    const node = makeNode(val);
    if (dqHead === null) { dqHead = node; dqTail = node; }
    else { node.next = dqHead; dqHead.prev = node; dqHead = node; }
    dqSize++;
    console.log(`push_front: ${val}`);
}

function pushBack(val) {
    const node = makeNode(val);
    if (dqTail === null) { dqHead = node; dqTail = node; }
    else { node.prev = dqTail; dqTail.next = node; dqTail = node; }
    dqSize++;
    console.log(`push_back: ${val}`);
}

function popFront() {
    if (dqHead === null) { console.log("deque empty"); return null; }
    const node = dqHead;
    const val = node.val;
    const nxt = node.next;
    if (nxt !== null) nxt.prev = null;
    else dqTail = null;
    dqHead = nxt;
    dqSize--;
    console.log(`pop_front: ${val}`);
    return val;
}

function popBack() {
    if (dqTail === null) { console.log("deque empty"); return null; }
    const node = dqTail;
    const val = node.val;
    const prv = node.prev;
    if (prv !== null) prv.next = null;
    else dqHead = null;
    dqTail = prv;
    dqSize--;
    console.log(`pop_back: ${val}`);
    return val;
}

function printDeque() {
    let cur = dqHead;
    const parts = [];
    while (cur !== null) { parts.push(cur.val); cur = cur.next; }
    process.stdout.write("deque:");
    for (const v of parts) process.stdout.write(` ${v}`);
    process.stdout.write("\n");
}

pushFront(1); pushFront(2); pushBack(3); pushBack(4);
printDeque();
console.log(`size: ${dqSize}`);

popFront(); popBack();
printDeque();
console.log(`size: ${dqSize}`);

while (dqHead !== null) popFront();
console.log("deque cleared");
