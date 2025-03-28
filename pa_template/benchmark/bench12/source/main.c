#include <stdio.h>

void foo(int *x) { *x = 10;}

typedef void (*FP)(int *x);
FP f = NULL;

void run (FP fi, int v)
{
    fi (&v);
}

int main(int argc, char** argv) {
    int *p = &argc;  
    f = foo;

    run (f, *p);
    return 0;
}