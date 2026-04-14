// gcc -o json_config json_config.c
// Simulates JSON config merge without a JSON library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char host[64];
    int port;
    int debug;
    char log_level[16];
    int max_connections;
    int timeout;
} Config;

void print_config_json(const Config *c) {
    printf("{\n");
    printf("  \"host\": \"%s\",\n", c->host);
    printf("  \"port\": %d,\n", c->port);
    printf("  \"debug\": %s,\n", c->debug ? "true" : "false");
    printf("  \"log_level\": \"%s\",\n", c->log_level);
    printf("  \"max_connections\": %d,\n", c->max_connections);
    printf("  \"timeout\": %d\n", c->timeout);
    printf("}\n");
}

int main(void) {
    Config defaults = {"localhost", 8080, 0, "info", 100, 30};

    // Simulated parsed user_config: port=3000, debug=true, log_level="debug"
    Config user = {"", 3000, 1, "debug", 0, 0};

    // Merge: user overrides defaults
    Config final = defaults;
    if (user.port) final.port = user.port;
    if (strlen(user.host)) strncpy(final.host, user.host, 63);
    // debug is set so always override
    final.debug = user.debug;
    if (strlen(user.log_level)) strncpy(final.log_level, user.log_level, 15);

    printf("=== Default Config ===\n");
    print_config_json(&defaults);
    printf("=== User Overrides ===\n");
    // Print only the override fields
    printf("{\n");
    printf("  \"port\": %d,\n", user.port);
    printf("  \"debug\": %s,\n", user.debug ? "true" : "false");
    printf("  \"log_level\": \"%s\"\n", user.log_level);
    printf("}\n");
    printf("=== Final Config ===\n");
    print_config_json(&final);
    return 0;
}
