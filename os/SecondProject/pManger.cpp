#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "QueueArray.cpp"
using namespace std;

struct com {
	char type;
	char cmd;
	int pid;
	int value;
	int Time;
	int rid;
	
};
struct pcb{
	int stime;
	int etime;
	int value;
	int pid;
	int quantum;
	int rtime;
	int priority;
	
};
int Time = 0;
main(int argc, char *argv[]){
	//set up pcb_tabel
	vector<pcb> pcb_table (100);

	pcb* running_proc;	

	//blocking queueArrays
	QueueArray <int> block_reZ(4);
	QueueArray <int> block_re1(4);
	QueueArray <int> block_re2(4);

	//ready queue
	QueueArray <int> ready(4);

	bool isFirst = true; // is this the first process

	//Set up the pipe on this side
	int comPipe[2];
	comPipe[0] = atoi(argv[1]);
	comPipe[1] = atoi(argv[2]);
	//boolean to term
	bool done = false;
	cout << "In pManger has pid of: " << getpid() << endl;
	while(!done){
		com tCom;
		read(comPipe[0], (com *)&tCom, sizeof(com));
		switch(tCom.type){
			case 'S': { //s comand set up process
				pcb process;
				//set fileds in the process
				process.stime = Time;// start time is current time
				process.value = tCom.value;//set the value
				process.pid = tCom.pid;//set the pid
				process.rtime = tCom.Time;//set the run time
				process.priority = 0;//set priorty new process have prority of 0
				process.quantum =1;//process with 0 priorty have quantum of 1
				//break out of switch
				pcb_table.at(process.pid) = process;
				if(isFirst){
					running_proc = &pcb_table.at(process.pid);
				}
				break;
			}
			case 'B': {
				cout << "Found a b" << endl;
				switch(tCom.rid){
					case 0 : {
						cout << "Blocking" << endl;
						//block on resorce 0
						//equeue pid to prorty on block_reZ
						block_reZ.Enqueue(running_proc->pid, running_proc->priority);
						int pid1 = block_reZ.Dequeue();
						pcb* pcb1 = &pcb_table.at(pid1);
						cout << pcb1->pid <<" this is the pid of the blocked proces for re zero" << endl;
						break;
					}
					case 1 : {
						//block on resorce 1
						//equeue pid to prorty on block_reZ
						block_re1.Enqueue(running_proc->pid, running_proc->priority);
						break;
					}
					case 2 : {
						//block on resorce 2
						//equeue pid to prorty on block_reZ
						block_re2.Enqueue(running_proc->pid, running_proc->priority);
						break;
					}
				}
					break;
			}	
			case 'T': {
				done = true;
				break;
			}
			default: 
				break;	
		}
	}
	
	//close the pipe
	close(comPipe[0]);
	close(comPipe[1]);
}
