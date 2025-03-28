#include <stdio.h>

int main() {
    int a = 5, b = 1;
    int *p;
    
    p = &a;
    p = &b;
    return *p;
}


