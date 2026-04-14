// Map-Reduce Pattern
// Map: square each number across workers
// Reduce: sum all squares
// Input: [1, 2, 3, 4, 5, 6, 7, 8]
// Expected: 1+4+9+16+25+36+49+64 = 204
async function mapWorker(chunk) { return chunk.map(v => v * v); }
async function reduceWorker(values) { return values.reduce((sum, v) => sum + v, 0); }

async function main() {
    const data = [1, 2, 3, 4, 5, 6, 7, 8];
    const chunkSize = 2;
    const chunks = [];
    for (let i = 0; i < data.length; i += chunkSize) chunks.push(data.slice(i, i + chunkSize));

    const mapResults = await Promise.all(chunks.map(c => mapWorker(c)));
    const allSquares = mapResults.flat();
    const total = await reduceWorker(allSquares);
    console.log(`sum of squares: ${total}`);
}

main();
