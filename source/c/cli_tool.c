// gcc -o cli_tool cli_tool.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int verbose;
    char output[64];
    char format[16];
    int count;
} Config;

void parse_option(const char *key, const char *value, Config *cfg) {
    if (strcmp(key, "--verbose") == 0 || strcmp(key, "-v") == 0) cfg->verbose = 1;
    else if (strcmp(key, "--output") == 0 || strcmp(key, "-o") == 0) strncpy(cfg->output, value, 63);
    else if (strcmp(key, "--format") == 0 || strcmp(key, "-f") == 0) strncpy(cfg->format, value, 15);
    else if (strcmp(key, "--count") == 0 || strcmp(key, "-n") == 0) cfg->count = atoi(value);
}

int main(void) {
    Config config = {0, "stdout", "text", 10};

    // Simulated args
    const char *simulated_args[][2] = {
        {"--verbose", ""},
        {"--output", "result.txt"},
        {"--format", "json"},
        {"--count", "25"}
    };
    for (int i = 0; i < 4; i++) parse_option(simulated_args[i][0], simulated_args[i][1], &config);

    printf("hemlock-tool v1.0.0\n");
    printf("Parsed configuration:\n");
    printf("  verbose: %s\n", config.verbose ? "true" : "false");
    printf("  output:  %s\n", config.output);
    printf("  format:  %s\n", config.format);
    printf("  count:   %d\n", config.count);
    printf("Ready to process.\n");
    return 0;
}
