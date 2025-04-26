int foo(int a) {
    int x = 0;          
    x = a + 1;          // DEAD
    int b;
    b= a;
    x = a * 2;          
    return x;
}