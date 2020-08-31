#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argv, char *argc[])
{
    //argc[1], argc[2] - pipes;
    char string[16];

    for(int i = 0; i < 150; i++)//чтобы видеть, что процессы выполняются одновременно
    {
        printf("%s\n", argc[0]);
    }
    write(argc[1][1], "proc1 to proc2\n", 16);
    read(argc[2][0], string, 16);
    for(int i = 0; i < 15; i++)
    {
        printf("%s\n", string);
    }
    exit(0);
}