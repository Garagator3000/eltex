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

    FILE *file = fopen(pathname, "r");
    if(file == NULL)
    {
        printf("FILE ERROR!\n");
        exit(-1);
    }

    code = read(file, array, 4096);

    if(code < 0)
    {
        printf("READ FILE ERROR!\n");
        exit(-1);
    }

    close(file);
    shmdt(array);
    return 0; 
}