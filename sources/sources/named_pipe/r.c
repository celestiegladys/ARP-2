// R PROCESS (named pipe)

#include <stdio.h> // stdio. h is a header file which has the necessary information to include 
//the input/output related functions in our program. 
#include <string.h> // the predefined functions which are designed to handle strings
#include <fcntl.h> // header in the C POSIX library for the C programming language that contains constructs that refer to file control, e.g. opening a file, retrieving and changing the permissions 
//of file, locking a file for edit, etc.
#include <sys/stat.h> // functions that have arguments or return values of type mode_t, so that symbolic values for that type can be used
#include <sys/types.h> // defines data types used in system source code
#include <unistd.h> // header file that provides access to the POSIX operating system API
#include <stdlib.h> // header of the general purpose standard library of C programming language 
//which includes functions involving memory allocation, process control, conversions and others. 
#include <signal.h> // header file defined in the C Standard Library to specify how a program handles signals while it executes.
#include <errno.h> // defines macros for reporting and retrieving error conditions using the symbol errno (short for "error number").
#include <math.h> // header file declares a set of functions to perform mathematical operations such as: sqrt() to calculate the square root, log() to find natural logarithm of a number etc.
#include <time.h> // header file contains definitions of functions to get and manipulate date and time information

#define MSGSIZE 99999

// declared required varibales
int count1=0,count2=0;
char ch;
int x;

int pid,cycl1,delay,delay1,cycl2;
long int lat[MSGSIZE],lat1[MSGSIZE],sum=0,sum1=0;
float diff_t,avg,avg1;

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the M process 
int main(int argc, char* argv[]) {

int pid;
    //pipe for r to m to send the bandwidth
   if (mkfifo("monitor", 0666) == -1) {
        if (errno != EEXIST) {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    //opening pipes of G1,G2 for reading and monitor for writing to the M process
    int fd = open("g1", O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    int fd1 = open("g2", O_RDONLY);
    if (fd1 == -1) {
        return 1;
    }
     int fd2 = open("monitor", O_WRONLY);
    if (fd2 == -1) {
        return 1;
    }
    
    struct message{
        
        int x;
        char g[20];
        time_t timestamp;
       }message;
       
        struct message* data;
        struct message* data1;
     	data = (struct message*)malloc(sizeof(struct message));
     	data1 = (struct message*)malloc(sizeof(struct message));
        //queue message for putting the messages in queue recieved from G1 and G2
    struct queue{
       struct message buf1[MSGSIZE];
        
        
        time_t timestamp[MSGSIZE];
       }queue;
        
        
        struct queue* w1;
        struct queue* w2;
     	w1 = (struct queue*)malloc(sizeof(struct queue));
     	w2 = (struct queue*)malloc(sizeof(struct queue));
        w1->buf1[MSGSIZE];
        w2->buf1[MSGSIZE];
        w1->timestamp[MSGSIZE];
        w2->timestamp[MSGSIZE];
   
    
    fd_set rfds;
    int maxfd, retval;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
     int i=0,j=0;


    

     while(1){
        
    //select function to read the data from g1 and g2 randomly
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        FD_SET(fd1, &rfds);
        FD_SET(0, &rfds);
        retval = select(FD_SETSIZE + 1, &rfds, NULL, NULL, &tv);

        
        

        
        if (retval < 0){ 
            perror("SELECT");
        } else if (retval > 0) {
            

            
            if (FD_ISSET(fd, &rfds) || FD_ISSET(fd1, &rfds)) {
                //for G1 process
                if (FD_ISSET(fd, &rfds))
                {
                    if (read(fd, data, sizeof(*data)) < 0) {
                        perror("Error at read  ");
                        return 1;
                        
                    }
                    w1->buf1[i].x=data->x;
	            strcpy(w1->buf1[i].g,data->g);
	            w1->buf1[i].timestamp=data->timestamp;
	            time(&w1->timestamp[i]);
	            
                    			
                    			 
	                                
                    			
                    lat[i]=difftime(w1->timestamp[i],w1->buf1[i].timestamp);
                    			
                    for(i=0;i<MSGSIZE;i++)
                    {
                    	sum+=lat[i];
                    	
                    }
                    			
                    avg=sum/MSGSIZE;
                    usleep(5);
                    i++;
                    read(fd, &delay, sizeof(delay));
                    count1+=delay;
                    delay=count1;
                                        
                    usleep(5);
                    read(fd, &cycl1, sizeof(cycl1));
	        
                   
                    
                }
                //For G2 process
                if (FD_ISSET(fd1, &rfds))
                {
                    if(read(fd1, data1, sizeof(*data1)) < 0) {
                        perror("Error at read ");
                        return 1;
                        
                       
                    }
                    w2->buf1[j].x=data1->x;
	             strcpy(w2->buf1[j].g,data1->g); 
                     w2->buf1[j].timestamp=data1->timestamp;
                     time(&w2->timestamp[j]);
                    			
                    lat1[j]=difftime(w2->timestamp[j],w2->buf1[j].timestamp);
                    //calculate the time of recieving and sending to calculate the latency
                    for(j=0;j<MSGSIZE;j++)
                    {
                    	sum1+=lat[j];
                    }
                    			
                    avg1=sum1/MSGSIZE;
                    usleep(5);
                    j++;
                     read(fd1, &delay1, sizeof(delay1));
                     count2+=delay1;
                                        delay1=count2;
                     usleep(5);
                     read(fd1, &cycl2, sizeof(cycl2));
		      
                }
                
               
            }

}

			//after 1 millon cycles the R gets terminated and the bandwidth is sent to M

			if(cycl1 == 1000000 && cycl2 ==1000000){
					
               			
	        	 		write(fd2,data, sizeof(*data));
	        	 	usleep(2);
	        	 		write(fd2,data1, sizeof(*data1));
	        	 		usleep(2);
	        	 		write(fd2,&x, sizeof(x));
	        	 		usleep(2);
	        	 		write(fd2,&delay, sizeof(delay));
	        	 		usleep(2);
	        	 		write(fd2,&delay1, sizeof(delay1));
	        	 		usleep(2);
	        	 		write(fd2,&cycl1, sizeof(cycl1));
	        	 		usleep(2);
	        	 		write(fd2,&cycl2, sizeof(cycl2));
	        	 		usleep(2);
	        	 		write(fd2,&avg, sizeof(avg));
	        	 		usleep(2);
	        	 		write(fd2,&avg1, sizeof(avg1));
	        	 		usleep(2);
	        	 		
	        	 		
	        	 	
	        	 	}	
}

     	   
   // closing fds 
    close(fd);
    close(fd1);
    close(fd2);
    //close(fd2);
    
  
    
    return 0;
} // end of main()
