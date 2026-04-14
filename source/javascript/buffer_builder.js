// Growing buffer that doubles when full
// Write "Hello, World!" as bytes, then read back
let capacity = 4;
let size = 0;
let buf = new Uint8Array(capacity);

function bufGrow() {
    const newCap = capacity * 2;
    const newBuf = new Uint8Array(newCap);
    newBuf.set(buf.subarray(0, size));
    capacity = newCap;
    buf = newBuf;
}

function writeByte(b) {
    if (size >= capacity) bufGrow();
    buf[size++] = b;
}

function readBack() {
    return Buffer.from(buf.subarray(0, size)).toString('utf8');
}

const message = "Hello, World!";
const bytes = Buffer.from(message, 'utf8');
for (const b of bytes) writeByte(b);

console.log(`wrote ${size} bytes`);
console.log(`capacity: ${capacity}`);
const reconstructed = readBack();
console.log(`reconstructed: ${reconstructed}`);
