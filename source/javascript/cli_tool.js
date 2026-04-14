// CLI tool with argument parsing (using defaults)
const toolName = "hemlock-tool";
const version = "1.0.0";

let config = { verbose: false, output: "stdout", format: "text", count: 10 };

function parseOption(key, value, cfg) {
    if (key === "--verbose" || key === "-v") cfg.verbose = true;
    else if (key === "--output" || key === "-o") cfg.output = value;
    else if (key === "--format" || key === "-f") cfg.format = value;
    else if (key === "--count" || key === "-n") cfg.count = parseInt(value);
    return cfg;
}

const simulatedArgs = [
    ["--verbose", ""],
    ["--output", "result.txt"],
    ["--format", "json"],
    ["--count", "25"]
];

for (const arg of simulatedArgs) config = parseOption(arg[0], arg[1], config);

console.log(`${toolName} v${version}`);
console.log("Parsed configuration:");
console.log(`  verbose: ${config.verbose}`);
console.log(`  output:  ${config.output}`);
console.log(`  format:  ${config.format}`);
console.log(`  count:   ${config.count}`);
console.log("Ready to process.");
