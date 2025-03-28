#include <stdio.h>

void foo(int *x) { *x = 10;}

typedef void (*FP)(int *x);

FP f = foo;

int main(int argc, char** argv) {   
    f (&argc);
    return 0;
}