#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
sem_t addr_items;
pthread_mutex_t addr_lock;
sem_t  file_items;
pthread_mutex_t file_lock;
struct addr_in_use{
	void* addr;
	int ref_count;

};


struct files_in_use{
	char* filename;
	int ref_count;
	FILE* fp;
};

typedef struct addr_node{
	struct addr_in_use* node;
	struct addr_node* next;
	struct addr_node* prev;

}addr_node;
void init_addr_list();
void init_file_list();
void* cse320_malloc(size_t size);
void cse320_free(void* ptr);
FILE* cse320_fopen(char *pathname,char *mode);
int cse320_fclose(FILE* fp);
void cse320_clean();
pid_t cse320_fork();
void cse320_settimer(int n);

