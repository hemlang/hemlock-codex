// Async/await pipeline - sequential chained async operations
async function fetchData() {
    console.log("step 1: fetch data");
    return "raw data";
}

async function processData(data) {
    console.log("step 2: process data");
    return "processed";
}

async function saveResults(data) {
    console.log("step 3: save results");
    return "saved";
}

async function main() {
    const data = await fetchData();
    const processed = await processData(data);
    const status = await saveResults(processed);
    console.log("done");
}

main();
