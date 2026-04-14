// Fan-Out Fan-In Pattern
// Distribute numbers 1-20 across workers that square them, collect, sort, print.
async function worker(items) {
    return items.map(v => v * v);
}

async function main() {
    const data = Array.from({ length: 20 }, (_, i) => i + 1);
    // Split into 4 chunks
    const chunkSize = 5;
    const chunks = [];
    for (let i = 0; i < data.length; i += chunkSize) chunks.push(data.slice(i, i + chunkSize));

    const workerResults = await Promise.all(chunks.map(chunk => worker(chunk)));
    const results = workerResults.flat().sort((a, b) => a - b);
    console.log(`results: ${results.join(" ")}`);
}

main();
