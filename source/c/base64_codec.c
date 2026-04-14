// gcc -o base64_codec base64_codec.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64_encode(const unsigned char *input, int len, char *out) {
    int i = 0, j = 0;
    while (i < len) {
        unsigned char b0 = input[i];
        unsigned char b1 = (i+1 < len) ? input[i+1] : 0;
        unsigned char b2 = (i+2 < len) ? input[i+2] : 0;
        int pad = (i+1 >= len) ? 2 : (i+2 >= len) ? 1 : 0;

        out[j++] = chars[(b0 >> 2) & 63];
        out[j++] = chars[((b0 & 3) << 4) | ((b1 >> 4) & 15)];
        if (pad == 2) { out[j++] = '='; out[j++] = '='; }
        else { out[j++] = chars[((b1 & 15) << 2) | ((b2 >> 6) & 3)]; }
        if (pad == 1) out[j++] = '=';
        else if (pad == 0) out[j++] = chars[b2 & 63];

        i += 3;
    }
    out[j] = '\0';
}

int b64_char_index(char c) {
    for (int i = 0; i < 64; i++) if (chars[i] == c) return i;
    return -1;
}

int b64_decode(const char *input, unsigned char *out) {
    int len = strlen(input), j = 0;
    for (int i = 0; i < len; i += 4) {
        int c0 = b64_char_index(input[i]);
        int c1 = b64_char_index(input[i+1]);
        int c2 = (input[i+2] != '=') ? b64_char_index(input[i+2]) : -1;
        int c3 = (input[i+3] != '=') ? b64_char_index(input[i+3]) : -1;
        out[j++] = ((c0 << 2) | ((c1 >> 4) & 3)) & 255;
        if (c2 >= 0) out[j++] = (((c1 & 15) << 4) | ((c2 >> 2) & 15)) & 255;
        if (c3 >= 0) out[j++] = (((c2 & 3) << 6) | c3) & 255;
    }
    return j;
}

int main(void) {
    const char *original = "Hello, World!";
    int olen = strlen(original);

    char encoded[64];
    b64_encode((const unsigned char*)original, olen, encoded);
    printf("original: %s\n", original);
    printf("encoded:  %s\n", encoded);

    const char *expected = "SGVsbG8sIFdvcmxkIQ==";
    if (strcmp(encoded, expected) == 0) printf("encoding: correct\n");
    else printf("encoding: mismatch (expected %s)\n", expected);

    unsigned char decoded_bytes[64];
    int dlen = b64_decode(encoded, decoded_bytes);
    char decoded[64];
    for (int i = 0; i < dlen; i++) decoded[i] = (char)decoded_bytes[i];
    decoded[dlen] = '\0';
    printf("decoded:  %s\n", decoded);

    if (strcmp(decoded, original) == 0) printf("round-trip: ok\n");
    else printf("round-trip: FAILED\n");
    return 0;
}
