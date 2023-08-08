// G1 PROCESS (named pipe)


// Including required headers

#include <stdio.h> // stdio. h is a header file which has the necessary information to include 
//the input/output related functions in our program. 
#include <stdlib.h> // header of the general purpose standard library of C programming language 
//which includes functions involving memory allocation, process control, conversions and others. 
#include <string.h> // the predefined functions which are designed to handle strings
#include <unistd.h> // header file that provides access to the POSIX operating system API 
#include <sys/types.h> // defines data types used in system source code
#include <sys/wait.h> // header defines the following symbolic constants for use with waitpid(): WNOHANG: Do not hang if no status is available, return immediately.
#include <time.h> // header file contains definitions of functions to get and manipulate date and time information
#include <errno.h> // defines macros for reporting and retrieving error conditions using the symbol errno (short for "error number").
#include <fcntl.h> // header in the C POSIX library for the C programming language that contains constructs that refer to file control, e.g. opening a file, retrieving and changing the permissions 
//of file, locking a file for edit, etc.
#include <sys/types.h>
#include <sys/stat.h>

// declaraing PIDs and FDs
int pid,pipe_fd[2],pid1,pid2,fd,fd1;

//function to generate random delay
int generate_random(int l,int o){


		int rand_num=(rand() %(o-l+1))+l;
	        return rand_num;
}// end of random number function

int count_g1 = 0,count_g2 = 0;

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the G1 process 
int main(int argc, char* argv[]) {

	//pipe for g1 to r
 
    if (mkfifo("g1", 0666) == -1) {
        if (errno != EEXIST) {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    //struct message g1
     struct message{
        int x;
        char g[20];
        time_t timestamp;
     }message;
     struct message* g1;
     
     // structure message
     g1=(struct message*)malloc(sizeof(struct message));
     g1->x = 1;
     g1->timestamp;
     struct message* data;
     struct message* data1;
     data = (struct message*)malloc(sizeof(struct message));
     
     strcpy(g1->g,"G1");
     
     fd = open("g1", O_WRONLY);
    	if (fd == -1) {
        return 1;
    	}
    int cycl1=0;
    int cyc1=0;
    //1 million cycles to run by g1
    while(cyc1<=1000000){
    	
    
       //cycles completed by g1
      cyc1++;
      cycl1++;
      int low=0,off=14;
      srand(time(0));
      generate_random(low,off);
      //delay function
      int delay=off+generate_random(low,off); 
      usleep(10*delay);
    	 write(fd,g1,sizeof(*g1));
    	 //time stamp to get the time when writig
    	 time(&g1->timestamp);
         count_g1++;
         g1->x = count_g1; 
         usleep(5);
     	write(fd, &delay, sizeof(delay));
     	usleep(5);
     	write(fd, &cycl1, sizeof(cycl1));
   
}// end of while loop
 
      
    
    close(fd); //closind file descriptor 
   
    
    return 0;
}// end of main()

