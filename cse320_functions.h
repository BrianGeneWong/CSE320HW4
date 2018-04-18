#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

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
void* cse320_malloc(size_t size){
	void* ptr=NULL;
	//do stuff with global list
	//iterate through list, find first free one
	int i=0;
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
				return;
			}
		}
		i++;
	}
	printf("Free: Illegal Address\n");
	errno=EFAULT;
	exit(-1);
	
}
void* cse320_fopen(){
}
void cse320_fclose(){
}
void cse320_clean(){
}
