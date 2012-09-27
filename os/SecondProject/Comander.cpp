#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;

//structs for passing comands easy mode.
struct com {
	char type;
	char val1;
	char val2;
	char val3;
};
main(){
	//some random vars to help with stuf
	int i=0, c1;
	string input;
	//the pipe that will be used to talke to the process manger
	int comPipe[2], status;
	//this char will be used to help pass the pipe address to the process manger
	char comR[10], comW[10]; //R (read) W(write)
	
	//Let's create the pipe to process manger
	if (c1 = pipe(comPipe)) {
		perror("Oh no! The pipe was not created");
		exit(1);
	}
	//The pipe was created YAY
	
	//Now we need to create a string value to pass to the process manger that is the adress of the pipe
	sprintf(comR, "%d", comPipe[0]);
	sprintf(comW, "%d", comPipe[1]);
	
	//Now fun time we get to fork
	if ((c1 = fork()) == -1) {
		perror("Oh no! Mis. Process Manger wanted some spoon action first");
		exit(1);
	}
	else if (c1 == 0){
		//We got to fork YAY!!
		cout << "Comander: we have a child and its name is = " << getpid() << endl;
		//Start up process manger
		execl("pManger", "pManger", comR, comW, NULL);
	}
	//Time for a snack
	cout << "comander pid is = " << getpid() << endl;
	
	//What should we send to the process manger how about some commands
	while(cin){
		com comand;
		i++;
		getline(cin, input);
//		cout << input << endl;
		comand.type = input[0];
		comand.val1 = input[2];
		comand.val2 = input[4];
		comand.val3 = input[6];
	//	cout << "\tThe type is: \t" << comand.type << endl;
	//	cout << "\tVal1 is: \t" << comand.val1 << endl;
	//	cout << "\tVal2 is: \t" << comand.val2 << endl;
	//	cout << "\tVal3 is: \t" << comand.val3 << endl; 
		write(comPipe[1], (void *)&comand, sizeof(com));
	}
	//All comands have been sent
	//close the pipe
	close(comPipe[0]);
	close(comPipe[1]);
	
	//Wait for lover to die
	wait(&status);
	wait(&status);
	
	//Yay we can die now
}
