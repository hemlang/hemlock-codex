// Fixed-size slab allocator / object pool
// Pool of 8 slots, each 8 bytes (simulated with DataView)
const SLOT_SIZE = 8;
const POOL_SLOTS = 8;
const poolBuffer = new ArrayBuffer(SLOT_SIZE * POOL_SLOTS);
const poolView = new DataView(poolBuffer);
const used = new Array(POOL_SLOTS).fill(false);
let allocCount = 0;

function poolAlloc() {
    for (let i = 0; i < POOL_SLOTS; i++) {
        if (!used[i]) {
            used[i] = true;
            allocCount++;
            console.log(`alloc slot ${i}`);
            return i; // return slot index as "pointer"
        }
    }
    console.log("pool exhausted!");
    return null;
}

function poolFree(slotIndex) {
    if (used[slotIndex]) {
        used[slotIndex] = false;
        allocCount--;
        console.log(`freed slot ${slotIndex}`);
    }
}

function activeCount() { return used.filter(Boolean).length; }

function writeI64(slot, val) { poolView.setBigInt64(slot * SLOT_SIZE, BigInt(val), true); }

const s0 = poolAlloc(), s1 = poolAlloc(), s2 = poolAlloc(), s3 = poolAlloc(), s4 = poolAlloc();
writeI64(s0, 100); writeI64(s1, 200);

console.log(`active: ${activeCount()}`);
poolFree(1); poolFree(3);
console.log(`active after free: ${activeCount()}`);

const s5 = poolAlloc(), s6 = poolAlloc(), s7 = poolAlloc();
console.log(`final active: ${activeCount()}`);
console.log("pool freed");
