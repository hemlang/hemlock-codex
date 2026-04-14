// Thread-Safe Queue (async simulation) - Multiple producers, single consumer
async function producer(id, items, count) {
    const result = [];
    for (let i = 0; i < count; i++) result.push(`p${id}-${i}`);
    return result;
}

async function main() {
    const numProducers = 3;
    const itemsPerProducer = 5;
    const totalItems = numProducers * itemsPerProducer;

    const producerResults = await Promise.all(
        Array.from({ length: numProducers }, (_, i) => producer(i, [], itemsPerProducer))
    );

    const results = producerResults.flat();
    console.log(`consumed ${results.length} items`);
    results.sort();
    console.log(`values: ${results.join(" ")}`);
}

main();
