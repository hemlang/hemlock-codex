function makeQueue() { return { inbox: [], outbox: [] }; }

function enqueue(q, val) { q.inbox.push(val); }

function dequeue(q) {
    if (q.outbox.length === 0) {
        while (q.inbox.length > 0) q.outbox.push(q.inbox.pop());
    }
    return q.outbox.pop();
}

const q = makeQueue();
enqueue(q, 1); enqueue(q, 2); enqueue(q, 3);

const results = [];
results.push(dequeue(q));
results.push(dequeue(q));

enqueue(q, 4); enqueue(q, 5);

results.push(dequeue(q));
results.push(dequeue(q));
results.push(dequeue(q));

console.log(results.join(" "));
