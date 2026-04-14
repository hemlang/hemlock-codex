// Dining Philosophers Problem (deadlock-free via resource ordering)
// Using async mutex simulation
class Mutex {
    constructor() { this.locked = false; this.queue = []; }
    async acquire() {
        if (!this.locked) { this.locked = true; return; }
        await new Promise(r => this.queue.push(r));
    }
    release() {
        if (this.queue.length > 0) { this.queue.shift()(); }
        else this.locked = false;
    }
}

async function philosopher(id, forks, numPhil) {
    const left = id, right = (id + 1) % numPhil;
    const first = Math.min(left, right), second = Math.max(left, right);

    await forks[first].acquire();
    await forks[second].acquire();

    console.log(`philosopher ${id} is eating`);

    forks[second].release();
    forks[first].release();
    return id;
}

async function main() {
    const numPhil = 5;
    const forks = Array.from({ length: numPhil }, () => new Mutex());
    await Promise.all(Array.from({ length: numPhil }, (_, i) => philosopher(i, forks, numPhil)));
    console.log("all philosophers ate");
}

main();
