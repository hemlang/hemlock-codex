// Manual linked list simulation using JS objects
// (simulating the Hemlock alloc/ptr approach with a simple node model)
let head = null;

function push(val) {
    head = { val, next: head };
}

function traverse() {
    const parts = [];
    let current = head;
    while (current !== null) { parts.push(current.val); current = current.next; }
    process.stdout.write("list:");
    for (const v of parts) process.stdout.write(` ${v}`);
    process.stdout.write("\n");
}

function freeAll() {
    let current = head;
    let count = 0;
    while (current !== null) { const next = current.next; count++; current = next; }
    head = null;
    console.log(`freed ${count} nodes`);
}

push(10); push(20); push(30);
traverse();
freeAll();
