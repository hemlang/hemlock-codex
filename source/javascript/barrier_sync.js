// Barrier Synchronization Pattern
// 4 tasks reach a barrier, all proceed after the last arrives.
const { SharedArrayBuffer: SAB } = globalThis;

async function barrierTask(id, counter, total) {
    // Atomically increment
    Atomics.add(counter, 0, 1);
    // Spin-wait until all tasks have arrived
    while (Atomics.load(counter, 0) < total) {
        await new Promise(r => setImmediate(r));
    }
    return id;
}

async function main() {
    const numTasks = 4;
    const sharedBuf = new SharedArrayBuffer(4);
    const counter = new Int32Array(sharedBuf);

    const tasks = [];
    for (let i = 0; i < numTasks; i++) tasks.push(barrierTask(i, counter, numTasks));

    const results = await Promise.all(tasks);
    const count = results.length;
    console.log(`all ${count} tasks passed barrier`);
}

main();
