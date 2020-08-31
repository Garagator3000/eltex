#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int fd1[2], fd2[2];

    if(pipe(fd1) < 0)
    {
        printf("pipe 1 not created\n");
        exit(-1);
    }
    if(pipe(fd2) < 0)
    {
        printf("pipe 2 not created\n");
        exit(-1);
    }

    pid_t pid = fork();
    int proc1, proc2;

    if(pid < 0)
    {
        ("fork not created\n");
        exit(-2);
    }
    else if(pid == 0)
    {
        proc1 = execl("/home/alexander/eltex/os/homework/task_5_11/proc1", "/home/alexander/eltex/os/homework/task_5_11/proc1", fd1, fd2, NULL);
    }
    else
    {
        proc2 = execl("/home/alexander/eltex/os/homework/task_5_11/proc2", "/home/alexander/eltex/os/homework/task_5_11/proc2", fd1, fd2, NULL);
    }

    exit(0);
}