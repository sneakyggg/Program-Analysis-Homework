int bar(int y) {
    int a=0;
    int x = 0;          
    x = a + 1;          // DEAD 
    int b;
    b= a;
    x = a * 2;          
    return x;

}
int main()
{
    int a=0;
    int x = 0;          
    x = a + 1;          // DEAD 
    int b;
    b= a;
    x = a * 2;         
    return x;
}