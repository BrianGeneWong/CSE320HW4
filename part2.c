#include "cse320_functions.h"
int addr_count=0;
int file_count=0;

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
	if(pthread_mutex_init(&addr_lock,NULL)==-2){
		_exit(-1);
	}
}

void init_file_list(){
        int i=0;
        while(i<25){
                struct files_in_use new_file;
                new_file.filename=NULL;
                new_file.ref_count=0;
                new_file.fp=NULL;
                file_list[i]=new_file;
                i++;
        }

	if(pthread_mutex_init(&file_lock,NULL)==-2){
		_exit(-1);
	}
}
void* cse320_malloc(size_t size){
	if(pthread_mutex_lock(&addr_lock)==-1){
		_exit(-1);
	}
        void* ptr=NULL;
        //do stuff with global list
        //iterate through list, find first free one
        int i=0;
        if (addr_count>=25){
                errno=ENOMEM;
                _exit(-1);
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
	if(pthread_mutex_unlock(&addr_lock)==-1){
		_exit(-1);
	}
        return ptr;
}
void cse320_free(void* ptr){
        //traverse throuugh list
	if(addr_count==0){
	//	printf("Free: Illegal Address\n");
		write(1,"Free: Illegal Address\n",sizeof("Free: Illegal Address\n"));
		errno=EFAULT;
		_exit(-1);

	}
		
	if(pthread_mutex_lock(&addr_lock)==-1){
		_exit(-1);
	}
        int i=0;
        while(i<25){
                if(addr_list[i].addr==ptr){
                        if(addr_list[i].ref_count==0){
                               // printf("Free: Double free attempt\n");
				write(1,"Free: Double free attempt\n",sizeof("Free: Double free attempt\n"));
                                errno=EADDRNOTAVAIL;
                                exit(-1);
                        }
                        else{	
                                free(ptr);
                                addr_list[i].ref_count--;
                                addr_count--;
				if(pthread_mutex_unlock(&addr_lock)==-1){
					_exit(-1);
				}
                                return;
                        }
                }
                i++;
        }
	if(pthread_mutex_unlock(&addr_lock)==-1){
		_exit(-1);
	}
       // printf("Free: Illegal Address\n");
	write(1,"Free: Illegal Address\n",sizeof("Free: Illegal Address\n"));
        errno=EFAULT;
        _exit(-1);
       
}

FILE* cse320_fopen(char *pathname,char *mode){

        FILE* fp=NULL;
        int i =0;
        if(file_count>=25){
                errno=ENFILE;
                _exit(-1);
        }
	if(pthread_mutex_lock(&file_lock)==-1){
		_exit(-1);
	}
        while(i<25){
                //check to see if the file descriptor already exists
                if(strcmp(file_list[i].filename,pathname)==0){
                        file_list[i].ref_count++;
			if(pthread_mutex_unlock(&file_lock)==-1){
				_exit(-1);
			}
                        return file_list[i].fp;
                }

        }
        //else, find first occurence of ref_count==0
        i=0;
        while(i<25){
                if(file_list[i].ref_count==0){
       
                        fp=fopen(pathname,mode);
                        file_count++;
                        file_list[i].ref_count++;
                        file_list[i].filename=pathname;
                        file_list[i].fp=fp;
                        i++;
			if(pthread_mutex_unlock(&file_lock)==-1){
				_exit(-1);
			}
                        return fp;
                }

        }
	if(pthread_mutex_unlock(&file_lock)==-1){
		_exit(-1);
	}
        return fp;
}
int cse320_fclose(FILE* fp){
       
	if(pthread_mutex_lock(&file_lock)==-1){
		_exit(-1);
	}
        int i=0;
        while(i<25){
                if(fp=file_list[i].fp){
                        if(file_list[i].ref_count==0){
		
                                errno=EINVAL;
                               // printf("Close: Ref count is zero\n");
				write(1,"Close: Ref count is zero\n",sizeof("Close: Ref count is zero\n"));
				if(pthread_mutex_lock(&file_lock)==-1){
					_exit(-1);
				}
                                exit(-1);
                        }
                        else{
                                file_list[i].ref_count--;
                                if(file_list[i].ref_count==0){
                                        file_count--;
                       			if (file_list[i].fp!=NULL)
                                        	return fclose(fp);
                                }
			if(pthread_mutex_unlock(&file_lock)==-1){
				_exit(-1);
			}
                                return 0;
                        }
                }
       
                i++;
        }
	if(pthread_mutex_unlock(&file_lock)==-1){
		_exit(-1);
	}
       // printf("Close: Illegal filename\n");
	write(1,"Close: Illegal filename\n",sizeof("Close: Illegal filename\n"));
        errno=ENOENT;
        _exit(-1);
}

void cse320_clean(){
        //free malloc stuff first
	
	if(pthread_mutex_lock(&addr_lock)==-1){
		_exit(-1);
	}
	if(pthread_mutex_lock(&file_lock)==-1){
		_exit(-1);
	}

        int i =0;
        while(i<25){
                if (addr_list[i].ref_count==1){

                        free(addr_list[i].addr);
                        addr_list[i].ref_count--;
                }
                if (file_list[i].ref_count>0){
                        if (file_list[i].fp!=NULL)
				fclose(file_list[i].fp);
                        file_list[i].ref_count=0;
                }
                i++;
        }
	if(pthread_mutex_unlock(&file_lock)==-1){
		_exit(-1);
	}
}



int main(){
	init_file_list();
	init_addr_list();
	int i;
        void* a = cse320_malloc(3);
        void* b = cse320_malloc(4);
        void* c = cse320_malloc(5);

        printf("a=%p\n",a);
        printf("b=%p\n",b);
        printf("c=%p\n",c);
        
        //print array;
        i =0;
        printf("---------------\n");
        while(i<25){
                struct addr_in_use a= addr_list[i];
                printf("addr_list[%d],ptr=%p, ref_count=%d \n",i,a.addr,a.ref_count);
                i++;
        }
        cse320_free(b);
        printf("---------------\n");
        i=0;
        while(i<25){
                struct addr_in_use a= addr_list[i];
                printf("addr_list[%d],ptr=%p, ref_count=%d \n",i,a.addr,a.ref_count);
                i++;
        }		

	cse320_clean();
        i=0;
        while(i<25){
                struct addr_in_use a= addr_list[i];
                printf("addr_list[%d],ptr=%p, ref_count=%d \n",i,a.addr,a.ref_count);
                i++;
        }		
	return 0;
}
