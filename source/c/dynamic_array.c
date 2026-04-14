// gcc -o dynamic_array dynamic_array.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int capacity = 4;
int size = 0;
int *data;

void grow(void) {
    int new_cap = capacity * 2;
    int *new_data = malloc(new_cap * sizeof(int));
    memcpy(new_data, data, size * sizeof(int));
    free(data);
    data = new_data;
    capacity = new_cap;
}

void push(int val) {
    if (size == capacity) grow();
    data[size++] = val;
}

void print_all(void) {
    printf("values:");
    for (int i = 0; i < size; i++) printf(" %d", data[i]);
    printf("\n");
}

int main(void) {
    data = malloc(capacity * sizeof(int));
    for (int i = 1; i <= 10; i++) push(i);
    printf("capacity: %d\n", capacity);
    print_all();
    free(data);
    return 0;
}
