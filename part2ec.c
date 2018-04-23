#include "cse320_functions.h"
addr_node* head=NULL;



void init_addr_list(){
        if(sem_init(&addr_items,0,0)==-1){
                _exit(-1);
        }
        if(pthread_mutex_init(&addr_lock,NULL)==-1){
                _exit(-1);
        }
}

void* cse320_malloc(size_t size){
	void* addr= malloc(size);
	struct addr_in_use* addr_use=malloc(sizeof(struct addr_in_use));
	addr_node *new_node= malloc(sizeof(addr_node));
	addr_use->addr=addr;
	addr_use->ref_count++;
	new_node->node=addr_use;
	new_node->next=NULL;
	if(head==NULL){
		head=new_node;
		head->prev=NULL;
	}
	else{
		addr_node* temp=head;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=new_node;
		new_node->prev=temp;
	}

}

void cse320_free(void* ptr){
	if(head==NULL){
		write(1,"Free: Illegal address\n",sizeof("Free: Illegal address\n"));
		errno=EFAULT;
		exit(-1);
	}
	else{
		addr_node* temp=head;
		while(temp!=NULL){
			if(temp->node->addr==ptr){
				if(temp->node->ref_count==0){
					write(1,"Free: Double free attempt\n",sizeof("Free: Double free attempt\n"));
					exit(-1);
				}
				if(temp==head){

				
				}
				else{


				}
			}
			temp=temp->next;
		}

	}

}
int main(){


	return 0;
}
