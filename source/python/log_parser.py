logs = [
    "2024-01-15 08:30:12 [INFO] Application started",
    "2024-01-15 08:30:15 [INFO] Loading configuration",
    "2024-01-15 08:30:16 [WARN] Config file not found, using defaults",
    "2024-01-15 08:31:00 [INFO] Processing 150 records",
    "2024-01-15 08:31:05 [ERROR] Failed to parse record #42",
    "2024-01-15 08:31:10 [WARN] Retrying failed operation",
    "2024-01-15 08:31:15 [INFO] Processing complete",
    "2024-01-15 08:31:20 [INFO] Shutting down",
]

def extract_level(line):
    if "[INFO]" in line: return "INFO"
    if "[WARN]" in line: return "WARN"
    if "[ERROR]" in line: return "ERROR"
    if "[DEBUG]" in line: return "DEBUG"
    return "UNKNOWN"

def extract_timestamp(line):
    return line[:19]

def extract_message(line):
    parts = line.split("] ")
    if len(parts) > 1:
        return parts[1]
    return line

info_count = 0
warn_count = 0
error_count = 0

print("=== Log Analysis ===")
for line in logs:
    level = extract_level(line)
    if level == "INFO": info_count += 1
    if level == "WARN": warn_count += 1
    if level == "ERROR": error_count += 1

print(f"Total lines: {len(logs)}")
print(f"INFO: {info_count}")
print(f"WARN: {warn_count}")
print(f"ERROR: {error_count}")

print("\n=== Error Details ===")
for line in logs:
    if "[ERROR]" in line:
        print(f"  {extract_timestamp(line)}: {extract_message(line)}")
