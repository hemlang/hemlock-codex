function makeNode(val, next) { return { val, next }; }

function buildList(arr) {
    let head = null;
    for (let i = arr.length - 1; i >= 0; i--) head = makeNode(arr[i], head);
    return head;
}

function printList(head, label) {
    const parts = [];
    let curr = head;
    while (curr !== null) { parts.push(curr.val); curr = curr.next; }
    console.log(`${label}: ${parts.join(" ")}`);
}

function reverseList(head) {
    let prev = null, curr = head;
    while (curr !== null) {
        const next = curr.next;
        curr.next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

let head = buildList([1, 2, 3, 4, 5]);
printList(head, "original");
const reversed = reverseList(head);
printList(reversed, "reversed");
