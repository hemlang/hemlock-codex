// Promise.all - run parallel async tasks and collect results
async function square(n) { return n * n; }

async function main() {
    const [r1, r2, r3] = await Promise.all([square(1), square(2), square(3)]);
    console.log(`results: ${r1} ${r2} ${r3}`);
}

main();
