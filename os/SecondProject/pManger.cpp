#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
struct com {
	char type;
	char val1;
	char val2;
	char val3;
}comand;
main(int argc, char *argv[]){
	//Set up the pipe on this side
	int comPipe[2];
	comPipe[0] = atoi(argv[1]);
	comPipe[1] = atoi(argv[2]);
	cout << "In pManger has pid of: " << getpid() << endl;
	for(int i = 0; i < 10; i++){
		com *tCom;
		read(comPipe[0], tCom, sizeof(com));
		cout << "chid I is: " << i << endl;
		cout <<"child " << tCom->type << endl;
		cout << "child index of i is: " <<i <<endl;
	}
	
	//close the pipe
	close(comPipe[0]);
	close(comPipe[1]);

	
}
