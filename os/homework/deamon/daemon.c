#include "stdio.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    pid_t pid = getpid();

    pid = fork();

    sigset_t sigset;

    if(pid == -1)
    {
        printf("Error: proc not start\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        setsid();
        chdir("/");
        printf("i'm daemon: %d", getpid());
        close(stdin);
        close(stdout);
        close(stderr);
        chdir("/home/alexander/");
        for(;;)
        {  
            if(fopen("needDelete", "r"))
            {
                remove("needDelete");
            }
        }
    }
    else
    {
        printf("OK: demon with pid %d is created\n", pid);
        return 0;
    }
    
    
}