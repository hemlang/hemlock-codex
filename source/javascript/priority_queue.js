// Min-heap priority queue
function makePQ() { return { heap: [] }; }

function pqSwap(heap, i, j) { [heap[i], heap[j]] = [heap[j], heap[i]]; }

function pqInsert(pq, val) {
    pq.heap.push(val);
    let i = pq.heap.length - 1;
    while (i > 0) {
        const parent = Math.floor((i - 1) / 2);
        if (pq.heap[i] < pq.heap[parent]) { pqSwap(pq.heap, i, parent); i = parent; }
        else break;
    }
}

function pqExtractMin(pq) {
    const min = pq.heap[0];
    const last = pq.heap.pop();
    if (pq.heap.length > 0) {
        pq.heap[0] = last;
        let i = 0;
        while (true) {
            const left = 2 * i + 1, right = 2 * i + 2;
            let smallest = i;
            if (left < pq.heap.length && pq.heap[left] < pq.heap[smallest]) smallest = left;
            if (right < pq.heap.length && pq.heap[right] < pq.heap[smallest]) smallest = right;
            if (smallest !== i) { pqSwap(pq.heap, i, smallest); i = smallest; }
            else break;
        }
    }
    return min;
}

const pq = makePQ();
for (const v of [5, 3, 7, 1, 4, 2]) pqInsert(pq, v);

const results = [];
for (let i = 0; i < 6; i++) results.push(pqExtractMin(pq));
console.log(results.join(" "));
