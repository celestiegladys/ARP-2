// Writer PROCESS (unnamed pipe)


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

//function for random delay
int generate_random(int l,int o){


		int rand_num=(rand() %(o-l+1))+l;
	        return rand_num;
} // end of random number function


// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the writer process 
int main(int argc, char* argv[])

{  

    char ch;
    //buffers for passing the pipes using exec
    char buffer[20];
    char buffer1[20];
    char buffer2[20];
    char buffer3[20];
   
    
    int count_g1 = 0;
    int count_g2 = 0;
    int count_time_g1 = 0;
    int count_time_g2 = 0;
    //pipes for G1,G2 and M
    int pipe_fd[2],res,pipe_fd1[2],pipe_fd2[2];
    int pid,pid1,pid2;
    
    // structure message
    struct message{
        int x;
        char g[20];
        time_t timestamp;
     }message;
     struct message* g1; 
     struct message* g2;
     g1=(struct message*)malloc(sizeof(struct message));
     g1->x = 1;
     g1->timestamp;
     
     strcpy(g1->g,"G1");
     g2=(struct message*)malloc(sizeof(struct message));
     g2->x = 1;
     g2->timestamp;
     
     strcpy(g2->g,"G2");
     struct message* data;
     struct message* data1;
     data = (struct message*)malloc(sizeof(struct message));
     data1 = (struct message*)malloc(sizeof(struct message));
    int returnstatus = pipe(pipe_fd);
    int returnstatus1 = pipe(pipe_fd1);
    int returnstatus2 = pipe(pipe_fd2);
    
    if (returnstatus == -1)
    {
    	printf("\n pipe creation filed %s\n",strerror(errno));
    	exit(EXIT_FAILURE);
    }
    printf("\n pipe create successfully\n");
    if (returnstatus1 == -1)
    {
    	printf("\n pipe creation filed %s\n",strerror(errno));
    	exit(EXIT_FAILURE);
    }
    printf("\n pipe create successfully\n");
    if (returnstatus2 == -1)
    {
    	printf("\n pipe creation filed %s\n",strerror(errno));
    	exit(EXIT_FAILURE);
    }
    printf("\n pipe create successfully\n");
    pid=fork();
    
     if(pid != 0){ 
     	pid1 =fork();
     if(pid1!=0){
     	pid2=fork();
     	
     	
      
     if(pid2!=0){
     	       
   
           while(1){ //process R
    		 //passing read end of pipes G1,G2 and write end of M
     	   	  sprintf(buffer1,"%d",pipe_fd[0]);
     	   	  sprintf(buffer2,"%d",pipe_fd1[0]);
     	   	  sprintf(buffer3,"%d",pipe_fd2[1]);
        	  execl("./reader","writer",buffer1,buffer2,buffer3,NULL);
      
  
           }    
      }                    	 
     else//child1//g1
     	 {
     	    
     	    int cycl1=0;
     	    int cyc1=0;
     	    
     	    while(cyc1<1000000){
     		//run upto 1 million cycles
     			
     		        cyc1++;
     		        cycl1++;
     			int low=0,off=14;
    			srand(time(0));
    			generate_random(low,off);
    			//random delay function
    			int delay=off+generate_random(low,off); 
     			usleep(10*delay);
     			
     			write(pipe_fd[1],g1,sizeof(*g1)); 
     			time(&g1->timestamp);
     			count_g1++;
     			g1->x = count_g1;
     			  
     			usleep(5);
     			write(pipe_fd[1], &delay, sizeof(delay));
     			
     		
     			
     			
     			
     		
     		
     		usleep(5);
     		write(pipe_fd[1], &cycl1, sizeof(cycl1));
     		
     	 	
     	} 
     	
     	}}else{                          //child2//g2
     	        int cycl2=0; 
     	       int cyc2=0;
     	       
     	   	while(cyc2<1000000){
            
     	   	
     			
     			
     			cyc2++;
     			cycl2++;
     			int lower=0,offset=12;
    			srand(time(0));
    			generate_random(lower,offset);
    			int delay1=offset+generate_random(lower,offset);  
     			usleep(10*delay1);
     			
     			write(pipe_fd1[1],g2,sizeof(*g2));
     			time(&g2->timestamp);
     		        
     		        count_g2++;
     			g2->x = count_g2;
     			  
     			usleep(5);
     			write(pipe_fd1[1], &delay1, sizeof(delay1));
     			
     		usleep(5);
     		write(pipe_fd1[1], &cycl2, sizeof(cycl2));
     	
     	 	
     	} 
     	
     	}}else{   //process M                      //child3
     	     
     	   
     	  while(1){   
        	
     	   //passing read end pipe of process m
     	   sprintf(buffer,"%d",pipe_fd2[0]);
     	   
     	   execl("./m","writer",buffer,NULL);
               
     	   	
           } 
   
	  }
     	   
     	   return 0;
     	}// end of main()

	
