#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_MSG_LEN 4096
#define KEYPATH "server.c"
#define REQ_TYPE 1

int main()
{
	key_t key;
	int msqid;
	int len;
    char message[] = "Hello from server";
	
	struct request 
    {
		long mtype;
		pid_t mpid;
	} myreq;

	struct response 
    {
		long mtype;
		char mtext[MAX_MSG_LEN];
	} myres;

	if((key = ftok(KEYPATH, 0))< 0) 
    {
		printf("Key not was generate\n");
		exit(-1);
	}

	if((msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL)) < 0) 
    {
		printf("No connection to server\n");
		exit(-1);
	}

	strcpy(myres.mtext, message);

	while(1) 
    {
		len = msgrcv(msqid, &myreq, sizeof(myreq.mpid), REQ_TYPE, 0);
		if(len < 0) 
        {
			printf("Request get error\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds*) NULL);
			exit(-1);
		}

		myres.mtype = (long)myreq.mpid;
		if(msgsnd(msqid, &myres, sizeof(message) + 1, 0) < 0) 
        {
			printf("Response send error\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds*) NULL);
			exit(-1);
		}
	}

	return 0;
}