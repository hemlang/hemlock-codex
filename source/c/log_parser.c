// gcc -o log_parser log_parser.c
#include <stdio.h>
#include <string.h>

const char *logs[] = {
    "2024-01-15 08:30:12 [INFO] Application started",
    "2024-01-15 08:30:15 [INFO] Loading configuration",
    "2024-01-15 08:30:16 [WARN] Config file not found, using defaults",
    "2024-01-15 08:31:00 [INFO] Processing 150 records",
    "2024-01-15 08:31:05 [ERROR] Failed to parse record #42",
    "2024-01-15 08:31:10 [WARN] Retrying failed operation",
    "2024-01-15 08:31:15 [INFO] Processing complete",
    "2024-01-15 08:31:20 [INFO] Shutting down"
};
int nlog = 8;

const char *extract_level(const char *line) {
    if (strstr(line, "[INFO]")) return "INFO";
    if (strstr(line, "[WARN]")) return "WARN";
    if (strstr(line, "[ERROR]")) return "ERROR";
    if (strstr(line, "[DEBUG]")) return "DEBUG";
    return "UNKNOWN";
}

// Returns pointer into line for the message after "] "
const char *extract_message(const char *line) {
    const char *p = strstr(line, "] ");
    if (p) return p + 2;
    return line;
}

int main(void) {
    int info_count = 0, warn_count = 0, error_count = 0;
    printf("=== Log Analysis ===\n");
    for (int i = 0; i < nlog; i++) {
        const char *level = extract_level(logs[i]);
        if (strcmp(level, "INFO") == 0) info_count++;
        else if (strcmp(level, "WARN") == 0) warn_count++;
        else if (strcmp(level, "ERROR") == 0) error_count++;
    }

    printf("Total lines: %d\n", nlog);
    printf("INFO: %d\n", info_count);
    printf("WARN: %d\n", warn_count);
    printf("ERROR: %d\n", error_count);

    printf("\n=== Error Details ===\n");
    for (int i = 0; i < nlog; i++) {
        if (strstr(logs[i], "[ERROR]")) {
            char ts[20]; strncpy(ts, logs[i], 19); ts[19] = '\0';
            printf("  %s: %s\n", ts, extract_message(logs[i]));
        }
    }
    return 0;
}
