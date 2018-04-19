#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void printHelp(){
	printf("You can use the following commands:\n");
	printf("exit - exit this application\n");
	printf("run X - execute application X\n");
	printf("help - print help menu \n");

}
int main(int argc, char** argv){	
	printHelp();
	while(1){
		pid_t pid;
		char* args[6]={NULL,NULL,NULL,NULL,NULL,NULL};
		char* command=malloc(255);
		printf("Input Command: ");
		fgets(command,255,stdin);
		char* tok;
		char *replace;
		if((replace=strchr(command,'\n'))!=NULL){
			*replace=0;
		}
		tok=strtok(command," ");
		if(strcmp(tok,"exit")==0){
			return 0;

		}
		else if(strcmp(tok,"help")==0){
			printHelp();
		}
		else if(strcmp(tok,"run")==0){
			tok=strtok(NULL," ");
			args[0]=tok;
			int i=1;
			//put all the flags in args
			while(tok!=NULL){
				tok=strtok(NULL," ");
				args[i]=tok;
				i++;
			}	
			signal(SIGINT, SIG_IGN);
			//block signals then fork	
			if ((pid=fork())==-1){
				perror("Fork Error\n");
				return errno;
			}
			if(pid==0){
				signal(SIGINT, SIG_DFL);
			//	printf("ASDFJASDFKASDFAsdF\n");
				if(execvp(args[0],args)==-1){
					if(execv(args[0],args)==-1)
						exit(-1);

				}
				
				exit(0);
			}
			wait(NULL);
		        signal(SIGINT, SIG_DFL);	
						
		
		}
		else{
			printf("Invalid command, press help for list of commands\n");
		
		}	
	free(command);
	}
}
