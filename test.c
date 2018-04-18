#include "cse320_functions.h"
#include <stdio.h>

int main(){

	int i =0;
	
	init_addr_list();
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
	

	return 0;
}
