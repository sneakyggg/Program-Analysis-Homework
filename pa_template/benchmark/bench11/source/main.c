#include <stdio.h>

void foo(int *x) { *x = 10;}

typedef void (*FP)(int *x);

FP f = foo;
int val = 0;

int main(int argc, char** argv) {
    int *p = &val;  
    f (p);
    return 0;
}