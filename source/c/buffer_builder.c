// gcc -o buffer_builder buffer_builder.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int capacity = 4;
int size = 0;
unsigned char *buf;

void buf_grow(void) {
    int new_cap = capacity * 2;
    unsigned char *new_buf = malloc(new_cap);
    memcpy(new_buf, buf, size);
    free(buf);
    buf = new_buf;
    capacity = new_cap;
}

void write_byte(unsigned char b) {
    if (size >= capacity) buf_grow();
    buf[size++] = b;
}

int main(void) {
    buf = malloc(capacity);

    const char *message = "Hello, World!";
    int msg_len = strlen(message);
    for (int i = 0; i < msg_len; i++) write_byte((unsigned char)message[i]);

    printf("wrote %d bytes\n", size);
    printf("capacity: %d\n", capacity);

    // Read back
    char reconstructed[64];
    for (int i = 0; i < size; i++) reconstructed[i] = (char)buf[i];
    reconstructed[size] = '\0';
    printf("reconstructed: %s\n", reconstructed);

    free(buf);
    return 0;
}
