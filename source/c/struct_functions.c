// gcc -o struct_functions struct_functions.c -lm
#include <stdio.h>
#include <math.h>

typedef struct { double x, y; } Point;
typedef struct { double x, y; } Vector2D;

Point point_add(Point a, Point b) {
    return (Point){a.x + b.x, a.y + b.y};
}

Vector2D vec_scale(Vector2D v, double s) {
    return (Vector2D){v.x * s, v.y * s};
}

double vec_magnitude(Vector2D v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

int main(void) {
    Point a = {1.0, 2.0}, b = {3.0, 4.0};
    Point c = point_add(a, b);
    printf("add: (%.1f, %.1f)\n", c.x, c.y);

    Vector2D v = {3.0, 4.0};
    Vector2D scaled = vec_scale(v, 2.0);
    printf("scale: (%.1f, %.1f)\n", scaled.x, scaled.y);
    printf("magnitude: %.1f\n", vec_magnitude(v));
    return 0;
}
