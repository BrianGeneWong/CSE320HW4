# Homework #4
Do not cheat and good luck!

It will be great (and useful for you) if you will document your work in this README and write a sort of documentation for your homework. We may give few extra credits for good documentation.

---Documentation---
To make part1, use "make part1" to create "part1" executable
To make part2, use "make part2" to create "part2" executable
to make part3, use "make part3" to create "part3" executable
to make part2 extra creidt, use "make part2ec" to make "part2ec"  executable
You make also use "make all" to make all the parts".
"Make clean" will delete all the executeables.
Part1 is contained in part1.c and contains executable part1.
Since there will not be more than 5 flags, I initialize my args[6] with size 6, one for the executeable name, 5 for flags.
I used scanf() to get the user input. The problem I had however, was that it left a trailing \n character since the user 
presses enter.
I fixed this by using strchr() to replace the \n with a null character.
Then I used strtok() to tokenize the string and compared it to the valid functions.
If it matched exit or help, it exited the program or printed the help menu respectively.
If it matched run, it got the next token as the executable string, and got the remaining tokens as flags.
All of these were also stored in args[].
Then I called execvp, and if that failed, execv.
Since we needed to handle both executable names and paths, I used 2 different exec functions.
If they both failed, that means the user did not give a valid appplication, so I exited with -1;


Part2
For the most part, I followed the homework documentation when creating cse320_functions.h.
I added extra declarations for sempahores and mutexes, one of each for each array.
For struct files_in_use, I added an extra field for a FILE* since our fopen implementation
requires us to return the same file descriptor if we open the same file twice.

functions are defined in part2.c and creates executble part2.
Since part 2 must be thread safe, we just write() to print to stdout instead of printf.
The way I impletemented part 2, extra credit 2 is also implemented.

For Part 2, please call init_addr_list() and init_file_list() before using the arrays.
These functions will initialize all ref_counts to 0 and initialize the respective mutexes.
Instead of using semaphores, I simply had a global count on how many files and addresses I've stored.
However, for the extra credit using linked lists, I will a semaphore.

at the beginning of each of the following functions, I lock the mutex for either addr_list or file_list, and
unlock it before I exit the function. This makes sure that only one thread is writing to the global arrays
at any given time.

void* cse320_malloc(size_t size)
I kept the argument and return type as malloc(). If there are 25 files in the list, throw an error.
Else, search the array for the first occurence of ref_count==0, and place the file in that index.
Increment the global file count.

void cse320_free(void* ptr)
I kepy the argument and return type the same as free(). First, if there are no files in the array,
throw an error. Next iterate through the array and check each addr_in_use.addr to see if it is the same
as ptr. If they match, check ref_count. If ref_count==-, throw a double free error. Else, call free() on 
that addr_in_use.addr and set ref_count==0 and decrement global file count. 
If a matching address cannot be found, throw an illegal free error.

FILE* cse320_fopen(char* pathname,char* mode)
The arguments and return type are the same as fopen(). If the file count is greater than 25, throw an error.
We iterate through file_list and if we can find a file_in_use with a matching name, we return that file_in_use.fp.
Else, we iterate through the array again and find the first occurence of ref_count==0. Then we fopen(pathname) and
store both pathname and the returned filepointer in that index of the array.

int cse320_fclose(FILE*fp)
The arguments and return type are the same as fclose(). We simply search file_list for a file_in_use struct that
has the same file pointer as the argument. If they match, then decrement the ref_count of that struct. If that ref_count
hits 0, then fclose(fp) and decrement file_count.

void cse320_clean()
This function goes through both file_list and addr_list. Iterating through both of them, if ref_count is greater
than 0 at index i for their respective lists, call fclose() or free() appropriately and set ref_count=0; 


Part3
Functions are defined in part3.c
For part3, please call cse320_settimer before calling cse320_fork().
We will keep our pids in an array so that every n seconds, we can iterate through the array and waitpid()
everything insde.
We use int i to keep track of how many pids we store
void sigalarm_handler(int sig)
This is our sigalarm handler. Inside we will iterate through our pid_t array and use waitpid on each index of the array
with a pid. We have a global count on the amount of pids in the array so that we dont unnecesarily call waitpid..

void cse320_settimer(int n)
This functions sets the global seconds int to n. Then it calls alarm(seconds), setting an alarm.

pid_t cse320_fork()
First declare pid and set the alarm signal handler. Then handle fork as we normally would. In the parent,
We store the returned pid from fork in the global pid_t array. Increment i.

In my main program, I was not getting zombie children because the program was ending too early. So during testing,
I used sleep() and top in combination to make sure my program was working normally.

