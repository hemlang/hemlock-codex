// gcc -o bit_manipulation bit_manipulation.c
#include <stdio.h>

int set_bit(int n, int pos) { return n | (1 << pos); }
int clear_bit(int n, int pos) { return n & ~(1 << pos); }
int toggle_bit(int n, int pos) { return n ^ (1 << pos); }
int check_bit(int n, int pos) { return (n >> pos) & 1; }

int count_bits(int n) {
    int count = 0;
    while (n) { count += n & 1; n >>= 1; }
    return count;
}

int main(void) {
    int flags = 0;
    flags = set_bit(flags, 0);
    flags = set_bit(flags, 3);
    flags = set_bit(flags, 7);
    printf("after set: %d\n", flags);
    printf("bit 3: %d\n", check_bit(flags, 3));
    printf("bit 2: %d\n", check_bit(flags, 2));
    flags = clear_bit(flags, 0);
    printf("after clear bit 0: %d\n", flags);
    flags = toggle_bit(flags, 3);
    printf("after toggle bit 3: %d\n", flags);
    printf("popcount: %d\n", count_bits(flags));
    printf("left shift: %d\n", 1 << 10);
    printf("right shift: %d\n", 256 >> 3);
    return 0;
}
