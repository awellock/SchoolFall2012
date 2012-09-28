#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
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
	int cpu_time;
	bool exists;
};
int Time = 0;
int fProc = 0;
int tProcTime = 0;
bool done;
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
	done = false;
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
				process.cpu_time = 0;//set total time on cpu
				process.exists = true;
				pcb_table.at(process.pid) = process;
				if(isFirst){
					running_proc = &pcb_table.at(process.pid);
					isFirst = false;
				}
				else
					ready.Enqueue(process.pid, process.priority);
				break;
			}
			case 'B': {//block the process
				switch(tCom.rid){
					case 0 : {
						//block on resorce 0
						//equeue pid to prorty on block_reZ
						if(running_proc->priority != 0)
							running_proc->priority--;
						running_proc->quantum = pow(2,running_proc->priority);
						block_reZ.Enqueue(running_proc->pid, running_proc->priority);
						int pid1 = ready.Dequeue();
						running_proc = &pcb_table.at(pid1);
						break;
					}
					case 1 : {
						//block on resorce 1
						if(running_proc->priority != 0)
							running_proc->priority--;
						running_proc->quantum = pow(2,running_proc->priority);
						block_re1.Enqueue(running_proc->pid, running_proc->priority);
						int pid1 = ready.Dequeue();
						running_proc = &pcb_table.at(pid1);
						break;
					}
					case 2 : {
						//block on resorce 2
						if(running_proc->priority != 0)
							running_proc->priority--;
						running_proc->quantum = pow(2,running_proc->priority);
						block_re2.Enqueue(running_proc->pid, running_proc->priority);
						int pid1 = ready.Dequeue();
						running_proc = &pcb_table.at(pid1);
						break;
					}
				}
					break;
			}
			case 'U': {//Unblock the process
				switch(tCom.rid){
					case 0 : {
						//block on resorce 0
						//equeue pid to prorty on block_reZ
						int pid1 = block_reZ.Dequeue();
						pcb* pcb1 = &pcb_table.at(pid1);
						ready.Enqueue(pcb1->pid, pcb1->priority);
						break;
					}
					case 1 : {
						//block on resorce 1
						//equeue pid to prorty on block_reZ
						int pid1 = block_re1.Dequeue();
						pcb* pcb1 = &pcb_table.at(pid1);
						ready.Enqueue(pcb1->pid, pcb1->priority);
						break;
					}
					case 2 : {
						//block on resorce 2
						//equeue pid to prorty on block_reZ
						int pid1 = block_re2.Dequeue();
						pcb* pcb1 = &pcb_table.at(pid1);
						ready.Enqueue(pcb1->pid, pcb1->priority);
						break;
					}
				}
					break;
			}
			case 'C' : {//exacute a comand on the current running process
				switch(tCom.cmd){
					case 'A': {//add the running process value by the value passed by the comand
						running_proc->value = running_proc->value + tCom.value;
						break;
					}
					case 'S': {//sub the running process value by the value passed by the comand
						running_proc->value = running_proc->value - tCom.value;
						break;
					}
					case 'M': {//multiply the running process value by the value passed by the comand
						running_proc->value = running_proc->value * tCom.value;
						break;
					}
					case 'D': {//div the runnig process value by the value passed by the comand
						running_proc->value = running_proc->value / tCom.value;
						break;
					}
				}
			}
			case 'Q': {
				Time++;
				if(!running_proc->exists)
					break;
				running_proc->quantum--;//the process was not done so reduce its quantum
				running_proc->rtime--;
				running_proc->cpu_time++;
				if(running_proc->rtime <= 0){//if done running set finshed time and swap out
					running_proc->etime = Time;
					fProc++;
					tProcTime += running_proc->etime - running_proc->stime;
					int pid1 = ready.Dequeue();//pid of the next ready process
					running_proc = &pcb_table.at(pid1);//set running process to the new one

				}
				else if(running_proc->quantum <=0){//if quantum is now zero lower priority and swap processes
					if(running_proc->priority < 3)
						running_proc->priority++;//set to lower priority
					//reset quantu
					running_proc->quantum = pow(2,running_proc->priority);
					ready.Enqueue(running_proc->pid, running_proc->priority);//replace the current procces on the ready queue
					int pid1 = ready.Dequeue();//get pid of the new process
					running_proc = &pcb_table.at(pid1);//set runnig pocess to the new one
				}
				
				break;		
			}
			case 'P': {
				
				int c1, status; //int for the fork
				if((c1 = fork()) == -1){
					perror("unable to fork for print");
					exit(1);
				}
				else if(c1 == 0){
					//we have great happyness
					cout << "*****************************************************" << endl;
					cout << "The current system state is as follows:" << endl;
					cout << "*****************************************************" << endl;

					cout << "\nCURRENT TIME:\t" << Time << endl;

					cout << "\nRUNNING PROCESS: " << endl;
					cout << "PID\tPriority\tValue\tStart Time\t Total CPU time" << endl;
					cout << running_proc->pid <<"\t" << running_proc->priority << "\t\t" << running_proc->value << "\t\t" << running_proc->stime << "\t\t" << running_proc->cpu_time << endl;

					cout << "\nBLOCKED PROCESS:" << endl;
					cout << "Queue of processes Blocked for resource 0:"<< endl;
					
					cout << "PID\tPriority\tValue\tStart Time\t Total CPU time" << endl;
					int *cbuf;
					for(int j = 0; j < block_reZ.Asize(); j++){//block for resource 0;
						if(block_reZ.Qsize(j)){
	                                                cbuf = block_reZ.Qstate(j);//what is in ready for priorty 0
                                                	for(int i = 0; i < block_reZ.Qsize(j); i++){
                                                        	int pid1 = cbuf[i]; //pid of the process that is in that que
                                                      	 	pcb process = pcb_table.at(pid1);//get the process
								cout << "Should print stuff for process: "<<pid1<<endl;
                                                                cout << process.pid <<"\t" << process.priority << "\t\t" << process.value << "\t\t" << process.stime << "\t\t" << process.cpu_time << endl;
							}
                                                }
					}
					cout << "\nQueue of processes blocked for resource 1:" << endl;
					cout << "PID\tPriority\tValue\tStart Time\t Total CPU time" << endl;
					for(int j = 0; j < block_re1.Asize(); j++){//block for resource 0;
						if(block_re1.Qsize(j)){
	                                                cbuf = block_re1.Qstate(j);//what is in ready for priorty 0
                                                	for(int i = 0; i < block_re2.Qsize(j); i++){
                                                        	int pid1 = cbuf[i]; //pid of the process that is in that que
                                                      	 	pcb process = pcb_table.at(pid1);//get the process
                                                                cout << process.pid <<"\t" << process.priority << "\t\t" << process.value << "\t\t" << process.stime << "\t\t" << process.cpu_time << endl;
							}
                                                }
					}

					cout << "\nQueue of processes blocked for resource 2:"<<endl;
					cout << "PID\tPriority\tValue\tStart Time\t Total CPU time" << endl;
					for(int j = 0; j < block_re2.Asize(); j++){//block for resource 0;
						if(block_re2.Qsize(j)){
	                                                cbuf = block_re2.Qstate(j);//what is in ready for priorty 0
                                                	for(int i = 0; i < block_re2.Qsize(j); i++){
                                                        	int pid1 = cbuf[i]; //pid of the process that is in that que
                                                      	 	pcb process = pcb_table.at(cbuf[i]);//get the process
                                                                cout << process.pid <<"\t" << process.priority << "\t\t" << process.value << "\t\t" << process.stime << "\t\t" << process.cpu_time << endl;
							}
                                                }
                                        }
					cout <<"\nPROCESSES READY TO EXECUTE:" << endl;

					for(int j = 0; j < ready.Asize(); j++){
						if(ready.Qsize(j)){
							cout << "Queue of process with priorty " << j+1 << ":" << endl;
							cbuf = ready.Qstate(j);//what is in ready for priorty 0
							for(int i = 0; i<ready.Qsize(j); i++){
								cout << "PID\tPriority\tValue\tStart Time\t Total CPU time" << endl;
								pcb process = pcb_table.at(cbuf[i]);
								cout << process.pid <<"\t" << process.priority << "\t\t" << process.value << "\t\t" << process.stime << "\t\t" << process.cpu_time << endl;
							}
						}
						else{
							cout << "Queue of processes with priority " << j+1 << " is empty" <<endl;
							continue;
						}
									
					}
					
				}
				wait(&status);
				break;
			}
			case 'T': {
				done = true;
				cout << "Totatl finshed porcesses: " << fProc<< endl;
				cout << "Avarage turn around time: " <<  tProcTime/((float)fProc)<< endl;
				break;
			}
		}
	}
	
	//close the pipe
	close(comPipe[0]);
	close(comPipe[1]);
}
