// gcc -o reference_counting reference_counting.c
#include <stdio.h>
#include <stdlib.h>

// Object layout: int refcount + int data
typedef struct { int refcount; int data; } Obj;

Obj *rc_new(int data) {
    Obj *obj = malloc(sizeof(Obj));
    obj->refcount = 1; obj->data = data;
    printf("created obj(data=%d, refcount=1)\n", data);
    return obj;
}

Obj *rc_retain(Obj *obj) {
    obj->refcount++;
    printf("retain obj(data=%d, refcount=%d)\n", obj->data, obj->refcount);
    return obj;
}

Obj *rc_release(Obj *obj) {
    obj->refcount--;
    if (obj->refcount == 0) {
        printf("release obj(data=%d, refcount=0) -> freed\n", obj->data);
        free(obj);
        return NULL;
    }
    printf("release obj(data=%d, refcount=%d)\n", obj->data, obj->refcount);
    return obj;
}

int main(void) {
    printf("--- create object ---\n");
    Obj *a = rc_new(42);

    printf("--- share with b ---\n");
    Obj *b = rc_retain(a);

    printf("--- share with c ---\n");
    Obj *c = rc_retain(a);

    printf("data: %d, refcount: %d\n", a->data, a->refcount);

    printf("--- release a ---\n");
    a = rc_release(a);

    printf("--- release b ---\n");
    b = rc_release(b);

    printf("--- release c (last ref, should free) ---\n");
    c = rc_release(c);

    return 0;
}
