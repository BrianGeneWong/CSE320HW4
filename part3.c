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
	int j=0;
	//REAP ZOMBIE CHILDREN IN HERE	
	for(j=0;i<i;j++){
		waitpid(array[j],&child_status,0);
	}
	i=0;
	alarm(secs);
	errno=oldErrno;
}

void cse320_settimer(int n){
	secs=n;
}
pid_t cse320_fork(){	
	pid_t pid;
	pid=fork();
	if(pid==-1){
		perror("Failed fork\n");
		exit(-1);
	}
	if(pid==0){
		array[i]=pid;
		i++;
		return pid;
	}	
	alarm(secs);
	pause();
	return pid;
	
	
}
int main(){
	pid_t pid;
	signal(SIGALRM,sigalarm_handler);
	cse320_settimer(3);
	cse320_fork();
	cse320_fork();
	cse320_fork();
	cse320_fork();
	return 0;
}
