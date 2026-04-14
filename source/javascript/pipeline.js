// Pipeline Pattern: generate -> double -> add10 -> collect
async function generate() { return [1, 2, 3, 4, 5]; }
async function doubleStage(values) { return values.map(v => v * 2); }
async function add10Stage(values) { return values.map(v => v + 10); }

async function main() {
    const generated = await generate();
    const doubled = await doubleStage(generated);
    const result = await add10Stage(doubled);
    console.log(result.join(" "));
}

main();
