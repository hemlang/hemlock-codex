// Ring buffer using Int32Array
function makeRing(capacity) {
    return { data: new Int32Array(capacity), capacity, head: 0, tail: 0, count: 0 };
}

function ringWrite(rb, val) {
    if (rb.count === rb.capacity) {
        console.log(`ring full, cannot write ${val}`);
        return false;
    }
    rb.data[rb.tail] = val;
    rb.tail = (rb.tail + 1) % rb.capacity;
    rb.count++;
    return true;
}

function ringRead(rb) {
    if (rb.count === 0) {
        console.log("ring empty");
        return null;
    }
    const val = rb.data[rb.head];
    rb.head = (rb.head + 1) % rb.capacity;
    rb.count--;
    return val;
}

const rb = makeRing(4);
ringWrite(rb, 1); ringWrite(rb, 2); ringWrite(rb, 3); ringWrite(rb, 4);

const results = [];
results.push(ringRead(rb));
results.push(ringRead(rb));

ringWrite(rb, 5); ringWrite(rb, 6);

results.push(ringRead(rb));
results.push(ringRead(rb));
results.push(ringRead(rb));
results.push(ringRead(rb));

console.log(results.join(" "));
