// LRU Cache with doubly linked list + Map
function makeLRU(capacity) {
    const head = { key: null, val: null, prev: null, next: null };
    const tail = { key: null, val: null, prev: null, next: null };
    head.next = tail;
    tail.prev = head;
    return { capacity, map: new Map(), head, tail, size: 0 };
}

function removeNode(node) {
    node.prev.next = node.next;
    node.next.prev = node.prev;
}

function addToFront(cache, node) {
    node.next = cache.head.next;
    node.prev = cache.head;
    cache.head.next.prev = node;
    cache.head.next = node;
}

function lruGet(cache, key) {
    const skey = `${key}`;
    if (cache.map.has(skey)) {
        const node = cache.map.get(skey);
        removeNode(node);
        addToFront(cache, node);
        console.log(`get(${key}) -> ${node.val} (hit)`);
        return node.val;
    }
    console.log(`get(${key}) -> miss`);
    return null;
}

function lruPut(cache, key, val) {
    const skey = `${key}`;
    if (cache.map.has(skey)) {
        const node = cache.map.get(skey);
        node.val = val;
        removeNode(node);
        addToFront(cache, node);
        console.log(`put(${key}, ${val}) -> updated`);
    } else {
        const node = { key: skey, val, prev: null, next: null };
        cache.map.set(skey, node);
        addToFront(cache, node);
        cache.size++;
        if (cache.size > cache.capacity) {
            const evict = cache.tail.prev;
            removeNode(evict);
            cache.map.delete(evict.key);
            cache.size--;
            console.log(`put(${key}, ${val}) -> added, evicted key ${evict.key}`);
        } else {
            console.log(`put(${key}, ${val}) -> added`);
        }
    }
}

const cache = makeLRU(3);
lruPut(cache, 1, 10);
lruPut(cache, 2, 20);
lruPut(cache, 3, 30);
lruGet(cache, 2);
lruPut(cache, 4, 40);
lruGet(cache, 1);
lruGet(cache, 3);
lruGet(cache, 4);
