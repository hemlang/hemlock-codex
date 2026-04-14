// Dynamic array that grows (simulating alloc/realloc pattern)
let capacity = 4;
let size = 0;
let data = new Int32Array(capacity);

function grow() {
    const newCap = capacity * 2;
    const newData = new Int32Array(newCap);
    newData.set(data.subarray(0, size));
    data = newData;
    capacity = newCap;
}

function push(val) {
    if (size === capacity) grow();
    data[size++] = val;
}

function printAll() {
    process.stdout.write("values:");
    for (let i = 0; i < size; i++) process.stdout.write(` ${data[i]}`);
    process.stdout.write("\n");
}

for (let i = 1; i <= 10; i++) push(i);
console.log(`capacity: ${capacity}`);
printAll();
