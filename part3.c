#include "cse320_functions.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t array[255];
int i=0;
int secs=0;
int child_status;
void sigalarm_handler(int sig){
	int oldErrno=errno;
	//REAP ZOMBIE CHILDREN IN HERE	
	for(i=0;i<255;i++){
		waitpid(array[i],&child_status,0);
	}
	errno=oldErrno;
}

void cse320_settimer(int n){

	secs=n;
}
pid_t cse320_fork(){	
	pid_t pid;
	if((pid=fork())==-1){
		exit(-1);
	}
	if(pid==0){
		array[i]=pid;
		i++;
		return pid;
	}
	else{
		signal(SIGALRM,sigalarm_handler);
		alarm(secs);
		return pid;
	}
	
}
int main(){

	return 0;
}
