#include <stdio.h>

int add (int* x)
{
    int a = *x;
    return a+1;
}

int main(int argc, char* argv[]) 
{
    int a = argc;
    return add(&a);
}

