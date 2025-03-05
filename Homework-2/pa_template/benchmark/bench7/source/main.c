#include <stdio.h>

int add (int* x)
{
    return *x;
}

typedef int (*FP) (int* x);

int main(int argc, char* argv[]) 
{
    FP f = add;
    return f(&argc);
}

