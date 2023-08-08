// G2 PROCESS (named pipe)


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
int generate_random(int l,int o){


		int rand_num=(rand() %(o-l+1))+l;
	        return rand_num;
}// end of random number function

int count_g2 = 0;

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the G2 process 
int main(int argc, char* argv[]) 
{

   //here, we used mkfifo 
    if (mkfifo("g2", 0666) == -1) {
        if (errno != EEXIST) {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    
    // structure message
    struct message{
        int x;
        char g[20];
        time_t timestamp;
     }message;
     struct message* g2;
     
     g2=(struct message*)malloc(sizeof(struct message));
     g2->x = 1;
     g2->timestamp;
     strcpy(g2->g,"G2");
     struct message* data1;
     data1 = (struct message*)malloc(sizeof(struct message));
     
    
    // NOTE: You will have to create the fifo using the command "mkfifo sum"
    int fd1 = open("g2", O_WRONLY);
    if (fd1 == -1) {
        return 1;
    }
  int cycl2=0; 
  int cyc2=0;
  while(cyc2<=1000000){
     cyc2++;
      cycl2++;
      int low=0,off=14;
      srand(time(0));
      generate_random(low,off);
      int delay1=off+generate_random(low,off); 
      usleep(10*delay1);
    	 write(fd1,g2,sizeof(*g2));
    	 time(&g2->timestamp);
         count_g2++;
         g2->x = count_g2; 
         usleep(5);
     	write(fd1, &delay1, sizeof(delay1));
     	usleep(5);
     	write(fd1, &cycl2, sizeof(cycl2));
    
  }
    
    close(fd1); // closing file descriptor
    
    return 0;
} // end of main()
