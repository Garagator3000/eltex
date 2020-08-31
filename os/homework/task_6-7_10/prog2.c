#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char *array; //Указатель на разделяемую память
    int shmid; //IPC дескриптор для области разедяемой памяти
    char pathname[] = "prog1.c";
    key_t key; //IPC key
    ssize_t code;

    if((key = ftok(pathname, 0)) < 0)
    {
        printf("Key not was generate\n");
        exit(-1);
    }

    if((shmid = shmget(key, sizeof(char)*34096, 0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
        if(errno != EEXIST)
        {
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else
        {
            if((shmid = shmget(key, sizeof(char)*4096, 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

	if ((array = shmat(shmid, NULL, 0)) == (char*)-1) {
		printf("SHM ERROR\n");
		exit(-1);
	}

    int i = 0;

    while(array[i] != 0)
    {
		putchar(array[i]);
		i++;
	}
    

    shmdt(array);
    return 0; 
}