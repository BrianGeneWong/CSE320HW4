#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
int addr_count=0;
int file_count=0;
struct addr_in_use{
	void* addr;
	int ref_count;
	void *nextAddr;

} addr_in_use_default={NULL,0,NULL};


struct files_in_use{
	char* filename;
	int ref_count;
	void* nextFile;
};

struct addr_in_use addr_list[25];
struct files_in_use file_list[25];

void init_addr_list(){
	int i=0;
	while(i<25){
		struct addr_in_use new_block;
		new_block.addr=NULL;
		new_block.ref_count=0;
		addr_list[i]=new_block;
		i++;
	}	
}

void init_file_list(){
	int i=0;
	while(i<25){
		struct files_in_use new_file;
		new_file.filename=NULL;
		new_file.ref_count=0;
		file_list[i]=new_file;
		i++;
	}	
}
void* cse320_malloc(size_t size){
	void* ptr=NULL;
	//do stuff with global list
	//iterate through list, find first free one
	int i=0;
	if (addr_count>=25){
		errno=ENOMEM;
		exit(-1);
	}
	while(i<25){
		if(addr_list[i].ref_count==0){
			ptr=malloc(size);
			addr_list[i].addr=ptr;
			addr_list[i].ref_count++;
			addr_count++;
			return ptr;
		}
		i++;
	}
	return ptr;	
}
void cse320_free(void* ptr){
	//traverse throuugh list
	int i=0;
	while(i<25){
		if(addr_list[i].addr==ptr){
			if(addr_list[i].ref_count==0){
				printf("Free: Double free attempt\n");
				errno=EADDRNOTAVAIL;
				exit(-1);
			}	
			else{
				free(ptr);
				addr_list[i].ref_count--;	
				addr_count--;
				return;
			}
		}
		i++;
	}
	printf("Free: Illegal Address\n");
	errno=EFAULT;
	exit(-1);
	
}
FILE* cse320_fopen(const char *pathname, const char *mode){
	FILE* fp=NULL;
	int i =0;
	if(file_count>=25){
		errno=ENFILE;
		exit(-1);
	}
	fp=fopen(pathname,mode);
	while(i<25){
		//check to see if the file descriptor already exists
		if(strcmp(file_list[i].filename,pathname)==0){
			file_list[i].ref_count++;
			return fp;
		}

	}
	file_count++;
	return fp;
}
void cse320_fclose(){
}
void cse320_clean(){
}
