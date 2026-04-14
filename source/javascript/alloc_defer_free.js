// Alloc defer free - allocate buffers, use them, free (via GC in JS)
function main() {
    const a = new Int32Array(2);
    const b = new Int32Array(2);
    const c = new Int32Array(2);

    a[0] = 10;
    b[0] = 20;
    c[0] = 30;

    const va = a[0], vb = b[0], vc = c[0];
    console.log(`${va} ${vb} ${vc}`);
    console.log("all memory freed");
}

main();
