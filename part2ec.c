void init_addr_list(){
        int i=0;
        while(i<25){
                struct addr_in_use new_block;
                new_block.addr=NULL;
                new_block.ref_count=0;
                addr_list[i]=new_block;
                i++;
        }
        if(sem_init(&addr_items,0,0)==-1){
                _exit(-1);
        }
        if(sem_init(&addr_slots,0,25)==-1){
                _exit(-1);
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

        if(sem_init(&file_items,0,0)==-1){
                _exit(-1);
        }
        if(sem_init(&file_slots,0,25)==-1){
                _exit(-1);
        }
        if(pthread_mutex_init(&file_lock,NULL)==-2){
                _exit(-1);
        }
}
