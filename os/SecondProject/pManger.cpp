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
	char val1;
	char val2;
	char val3;
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
main(int argc, char *argv[]){
	//set up pcb_tabel
	vector<pcb> pcb_table (100);
	//blocking queueArrays
	QueueArray <int> block_reone(3);
	QueueArray <int> block_retwo(3);
	QueueArray <int> block_rethree(3);
	//ready queue
	QueueArray <int> ready(3);

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
			case 'S': {
				
		}	}
	}
	
	//close the pipe
	close(comPipe[0]);
	close(comPipe[1]);
}
