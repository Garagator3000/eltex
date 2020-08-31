#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	int* array;
	int shmid;
	int new = 1;
	char pathname[] = "prog1.c";
	key_t key;
	long i;
	int semid;
	key_t semkey;
	struct sembuf seminc;
	struct sembuf semdec;

	seminc.sem_num = 0;
	seminc.sem_op = 1;
	seminc.sem_flg = 0;

	semdec.sem_num = 0;
	semdec.sem_op = -1;
	semdec.sem_flg = 0;

	if((semkey = ftok(pathname, 1)) < 0) 
    {
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666)) < 0) 
    {
		if(errno != EEXIST) 
        {
			printf("Can\'t get semid\n");
			exit(-1);
		}

		if((semid = semget(semkey, 1, 0)) < 0) 
        {
			printf("Can\'t get semid\n");
			exit(-1);
		}
	}
	else 
    {
		struct sembuf initop;
		initop.sem_num = 0;
		initop.sem_op = 1;
		initop.sem_flg = 0;

		if(semop(semid, &initop, 1) < 0) 
        {
			printf("Can\'t wait for condition\n");
			exit(-1);
		}
	}

	if((key = ftok(pathname, 0)) < 0)
    {
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) 
    {
		if(errno != EEXIST) 
        {
			printf("Can\'t create shared memory\n");
			exit(-1);
		}
		
		if((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) 
        {
			printf("Can\'t find shared memory\n");
			exit(-1);
		}

		new = 0;
	}

	if((array = shmat(shmid, NULL, 0)) == (int*) -1) 
    {
		printf("Can\'t find shared memory\n");
		exit(-1);
	}

	if(new) 
    {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}
	else 
    {
		array[0] += 1;

		for(i = 0; i < 10000000000L; i++)

		if(semop(semid, &semdec, 1) < 0) 
        {
			printf("Can\'t wait for condition\n");
            exit(-1);
		}

		array[2] += 1;

		if(semop(semid, &seminc, 1) < 0) 
        {
			printf("Can\'t wait for condition\n");
            exit(-1);
		}
	}

	printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);

	if(shmdt(array) < 0)
    {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

	return 0;
}