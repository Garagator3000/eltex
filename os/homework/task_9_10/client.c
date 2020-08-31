#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_MSG_LEN 4096
#define KEYPATH "server.c"
#define REQUEST_TYPE 1

int main()
{
	pid_t pid;
	key_t key;
	int msgid;
	int len;
	
	struct request 
    {
		long mtype;
		pid_t mpid;
	} myrequest;

	struct response 
    {
		long mtype;
		char mtext[MAX_MSG_LEN];
	} myresponse;

	pid = getpid();
	
	if((key = ftok(KEYPATH, 0)) < 0) 
    {
		printf("Key not was generate\n");
		exit(-1);
	}

	if((msgid = msgget(key, 0)) < 0) 
    {
		printf("No connection to server\n");
		exit(-1);
	}

	myrequest.mtype = REQUEST_TYPE;
	myrequest.mpid = pid;

	if(msgsnd(msgid, &myrequest, sizeof(myrequest.mpid), 0) < 0) 
    {
		printf("Request send error\n");
		exit(-1);
	}
	
	if((len = msgrcv(msgid, &myresponse, MAX_MSG_LEN, pid, 0)) < 0) 
    {
		printf("Response get error\n");
		exit(-1);
	}

	printf("Recieved: %s\n", myresponse.mtext);

	return 0;
}