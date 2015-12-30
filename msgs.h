#include<stdlib.h>
#include<ucontext.h>
#include<string.h>
#include "sem.h"

#define num_port 100
#define msg_size 10
#define num_msg 10

typedef struct port_t			//Step 1.
{
	int in, out;		
	int msgArr[num_msg][msg_size];

	struct Semaphore_t *semPortFull;
	struct Semaphore_t *semPortEmpty;
	struct Semaphore_t *semPortMutex;
}port_t;

struct port_t portArr[num_port];

void createPort()	//Initialising a port.
{
	int port_num;	
	for (port_num = 0; port_num<100; port_num++)
	{	
		portArr[port_num].in = 0;
		portArr[port_num].out = 0;
		portArr[port_num].semPortFull = CreateSem(0);
		portArr[port_num].semPortEmpty = CreateSem(10);
		portArr[port_num].semPortMutex = CreateSem(1);
	}
}



void send(port_t *portArr, int *msg)
{
	

//	P(portArr[port_num].semPortEmpty);
	P(portArr->semPortMutex);
		int i;
		for(i = 0; i <= msg_size; i++)
		{
			portArr->msgArr[portArr->in][i] = msg[i];
			
		}
		portArr->in++;
		if (portArr->in == 5)
			{
				portArr->in = 0;		
			}

	V(portArr->semPortMutex);
//	V(portArr[port_num].semPortFull);
}

void recv(port_t *portArr, int *msg)
{
	
//	P(portArr[port_num].semPortEmpty);
	P(portArr->semPortMutex);

		int i;
		for(i = 0; i <= msg_size; i++)
		{
			msg[i] = portArr->msgArr[portArr->out][i];
		}
		
		portArr->out++;
		if (portArr->out == 5)
			{
				portArr->out = 0;		
			}

	V(portArr->semPortMutex);
//	V(portArr[port_num].semPortFull);
}


