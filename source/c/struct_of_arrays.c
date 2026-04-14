// gcc -o struct_of_arrays struct_of_arrays.c -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COUNT 5

double *xs, *ys, *zs;

void set_point(int i, double x, double y, double z) {
    xs[i] = x; ys[i] = y; zs[i] = z;
}

double distance(int i) {
    return sqrt(xs[i]*xs[i] + ys[i]*ys[i] + zs[i]*zs[i]);
}

int main(void) {
    xs = malloc(COUNT * sizeof(double));
    ys = malloc(COUNT * sizeof(double));
    zs = malloc(COUNT * sizeof(double));

    set_point(0, 1.0, 0.0, 0.0);
    set_point(1, 0.0, 2.0, 0.0);
    set_point(2, 0.0, 0.0, 3.0);
    set_point(3, 1.0, 1.0, 1.0);
    set_point(4, 3.0, 4.0, 0.0);

    for (int i = 0; i < COUNT; i++) {
        double d = distance(i);
        // Print with same format as Hemlock (removes trailing zeros)
        // Hemlock prints 1 as 1, 1.7320508... as full float
        // Use %g-like formatting
        printf("point %d: (%.1f, %.1f, %.1f) distance = %g\n",
               i, xs[i], ys[i], zs[i], d);
    }

    free(xs); free(ys); free(zs);
    printf("all arrays freed\n");
    return 0;
}
