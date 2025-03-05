#include <stdio.h>

void C ()
{
    printf("C\n");
}

void B ()
{
    C ();
}

void (*func) () = B;
 
int main(int argc, char* argv[]) 
{
    func ();
}

