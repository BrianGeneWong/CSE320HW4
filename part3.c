#include "cse320_functions.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t array[200];
int i=0;
int secs=0;
int child_status;
void sigalarm_handler(int sig){
	int oldErrno=errno;
	int j=0;
	//REAP ZOMBIE CHILDREN IN HERE	
	for(j;j<i;j++){
		waitpid(array[j],&child_status,0);
	}
	i=0;
	alarm(secs);
	errno=oldErrno;
}

void cse320_settimer(int n){
	secs=n;
	alarm(secs);
}
pid_t cse320_fork(){	
	pid_t pid;
	signal(SIGALRM,sigalarm_handler);
	pid=fork();
	if(pid==-1){
		perror("Failed fork\n");
		exit(-1);
	}
	if(pid==0){
		return pid;
	}	
	array[i]=pid;
	i++;
//	alarm(secs);
	return pid;
	
	
}
int main(){
	pid_t pid;
	char* arg[2]={"ls",NULL};
	cse320_settimer(7);
	if((pid=cse320_fork())==0){
		execvp("ls",arg);
	}
	if((pid=cse320_fork())==0){
		execvp("ls",arg);
	}
	if((pid=cse320_fork())==0){
		execvp("ls",arg);
	}
	sleep(10);
	return 0;
}
