// Simple bump allocator from an ArrayBuffer
const ARENA_SIZE = 1024;
const arenaBuffer = new ArrayBuffer(ARENA_SIZE);
const arenaView = new DataView(arenaBuffer);
let offset = 0;

function arenaAlloc(size) {
    if (offset + size > ARENA_SIZE) {
        console.log("arena out of memory!");
        return null;
    }
    const ptr = offset;
    offset += size;
    return ptr;
}

function arenaReset() { offset = 0; }

function writeI32(ptr, val) { arenaView.setInt32(ptr, val, true); }
function readI32(ptr) { return arenaView.getInt32(ptr, true); }

const a = arenaAlloc(4);
const b = arenaAlloc(4);
const c = arenaAlloc(4);
const d = arenaAlloc(4);
const e = arenaAlloc(4);

writeI32(a, 100); writeI32(b, 200); writeI32(c, 300); writeI32(d, 400); writeI32(e, 500);

console.log(`slot 0: ${readI32(a)}`);
console.log(`slot 1: ${readI32(b)}`);
console.log(`slot 2: ${readI32(c)}`);
console.log(`slot 3: ${readI32(d)}`);
console.log(`slot 4: ${readI32(e)}`);
console.log(`arena used: ${offset} bytes`);
console.log("arena freed");
