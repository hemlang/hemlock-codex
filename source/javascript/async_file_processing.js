// Async File Processing - process simulated file data in parallel
async function processFile(name, data) {
    let sum = 0, max = data[0];
    for (const v of data) { sum += v; if (v > max) max = v; }
    return { name, sum, max, count: data.length };
}

async function main() {
    const files = [
        { name: "data_a.csv", data: [10, 20, 30, 40, 50] },
        { name: "data_b.csv", data: [5, 15, 25, 35, 45, 55] },
        { name: "data_c.csv", data: [100, 200, 300] }
    ];

    const results = await Promise.all(files.map(f => processFile(f.name, f.data)));
    for (const r of results) console.log(`${r.name}: sum=${r.sum} max=${r.max} count=${r.count}`);
    console.log("all files processed");
}

main();
