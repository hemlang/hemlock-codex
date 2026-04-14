// gcc -o url_shortener url_shortener.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URLS 64

typedef struct { char url[256]; char short_url[64]; } UrlEntry;
UrlEntry entries[MAX_URLS];
int entry_count = 0;
int counter = 1000;

char *encode_id(int id, char *out) {
    const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char tmp[32]; int ti = 0;
    int n = id;
    while (n > 0) {
        int rem = n % 62;
        tmp[ti++] = chars[rem];
        n = (n - rem) / 62;
    }
    int oi = 0;
    for (int i = ti - 1; i >= 0; i--) out[oi++] = tmp[i];
    out[oi] = '\0';
    return out;
}

const char *shorten(const char *url) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].url, url) == 0) return entries[i].short_url;
    }
    counter++;
    char code[32];
    encode_id(counter, code);
    UrlEntry *e = &entries[entry_count++];
    strncpy(e->url, url, 255);
    snprintf(e->short_url, 63, "https://sho.rt/%s", code);
    return e->short_url;
}

const char *resolve(const char *short_url) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].short_url, short_url) == 0) return entries[i].url;
    }
    return NULL;
}

int main(void) {
    const char *urls[] = {
        "https://example.com/long/path",
        "https://docs.hemlock.org/stdlib",
        "https://github.com/hemlang/42",
        "https://example.com/long/path"
    };

    printf("=== URL Shortener ===\n");
    for (int i = 0; i < 4; i++) {
        const char *s = shorten(urls[i]);
        printf("  %s\n", urls[i]);
        printf("  -> %s\n", s);
        printf("\n");
    }

    printf("=== Resolve Short URLs ===\n");
    const char *test_short = shorten("https://docs.hemlock.org/stdlib");
    const char *resolved = resolve(test_short);
    printf("  %s -> %s\n", test_short, resolved);

    const char *s1 = shorten("https://example.com/long/path");
    const char *s2 = shorten("https://example.com/long/path");
    if (strcmp(s1, s2) == 0) printf("\nDuplicate URL returns same short URL: ok\n");
    return 0;
}
