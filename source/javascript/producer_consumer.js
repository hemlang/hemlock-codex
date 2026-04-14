// Producer-Consumer Pattern using async/await
const { Worker, isMainThread, parentPort, workerData } = require('worker_threads');

// Simple channel implementation
class Channel {
    constructor(cap) {
        this.cap = cap;
        this.buf = [];
        this.closed = false;
        this.waiters = [];
    }
    async send(val) {
        this.buf.push(val);
        if (this.waiters.length > 0) {
            const resolve = this.waiters.shift();
            resolve();
        }
    }
    async recv() {
        if (this.buf.length > 0) return this.buf.shift();
        if (this.closed) return null;
        await new Promise(r => this.waiters.push(r));
        if (this.buf.length > 0) return this.buf.shift();
        return null;
    }
    close() { this.closed = true; while (this.waiters.length > 0) this.waiters.shift()(); }
}

async function producer(ch) {
    for (let i = 1; i <= 10; i++) await ch.send(i);
    ch.close();
}

async function consumer(ch) {
    const results = [];
    while (true) {
        const val = await ch.recv();
        if (val === null) break;
        results.push(val);
    }
    return results;
}

async function main() {
    const ch = new Channel(10);
    const [, results] = await Promise.all([producer(ch), consumer(ch)]);
    console.log(`received: ${results.join(" ")}`);
}

main();
