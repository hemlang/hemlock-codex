// Log parser: parse log lines, extract levels, aggregate counts
const logs = [
    "2024-01-15 08:30:12 [INFO] Application started",
    "2024-01-15 08:30:15 [INFO] Loading configuration",
    "2024-01-15 08:30:16 [WARN] Config file not found, using defaults",
    "2024-01-15 08:31:00 [INFO] Processing 150 records",
    "2024-01-15 08:31:05 [ERROR] Failed to parse record #42",
    "2024-01-15 08:31:10 [WARN] Retrying failed operation",
    "2024-01-15 08:31:15 [INFO] Processing complete",
    "2024-01-15 08:31:20 [INFO] Shutting down"
];

function extractLevel(line) {
    if (line.includes("[INFO]")) return "INFO";
    if (line.includes("[WARN]")) return "WARN";
    if (line.includes("[ERROR]")) return "ERROR";
    if (line.includes("[DEBUG]")) return "DEBUG";
    return "UNKNOWN";
}

function extractTimestamp(line) { return line.substring(0, 19); }

function extractMessage(line) {
    const parts = line.split("] ");
    return parts.length > 1 ? parts[1] : line;
}

let infoCount = 0, warnCount = 0, errorCount = 0;

console.log("=== Log Analysis ===");
for (const line of logs) {
    const level = extractLevel(line);
    if (level === "INFO") infoCount++;
    if (level === "WARN") warnCount++;
    if (level === "ERROR") errorCount++;
}

console.log(`Total lines: ${logs.length}`);
console.log(`INFO: ${infoCount}`);
console.log(`WARN: ${warnCount}`);
console.log(`ERROR: ${errorCount}`);

console.log("\n=== Error Details ===");
for (const line of logs) {
    if (line.includes("[ERROR]")) {
        console.log(`  ${extractTimestamp(line)}: ${extractMessage(line)}`);
    }
}
