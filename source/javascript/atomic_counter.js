// Lock-Free Atomic Counter
// 10 tasks each increment a shared atomic counter 100 times.
// Expected final value: 1000
async function incrementWorker(counter, iterations) {
    for (let i = 0; i < iterations; i++) {
        Atomics.add(counter, 0, 1);
    }
}

async function main() {
    const numTasks = 10;
    const iterations = 100;
    const sharedBuf = new SharedArrayBuffer(4);
    const counter = new Int32Array(sharedBuf);

    const tasks = [];
    for (let i = 0; i < numTasks; i++) tasks.push(incrementWorker(counter, iterations));
    await Promise.all(tasks);

    const finalVal = Atomics.load(counter, 0);
    console.log(`final: ${finalVal}`);
}

main();
