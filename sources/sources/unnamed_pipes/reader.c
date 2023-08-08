// Reader PROCESS (unnamed pipe)


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

#define MSGSIZE 99999

int sum=0,sum1=0;
int count1=0,count2=0;	

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the reader process 
int main(int argc, char* argv[]) {
    
     // declared required variables
     int fd1,fd2,fd3,cycl1,delay,delay1,cycl2;
     // buffere array declared
     char buffer1[20];
     char buffer2[20];
     char buffer3[20];
     
     float av_delay;
     long int lat[MSGSIZE],lat1[MSGSIZE],sum=0,sum1=0;
     float avg,avg1;
     float diff_t;
     memset (buffer1,'\0',sizeof(buffer1));
     memset (buffer2,'\0',sizeof(buffer2));
     memset (buffer3,'\0',sizeof(buffer3));
     sscanf(argv[1],"%d",&fd1);
     sscanf(argv[2],"%d",&fd2);
     sscanf(argv[3],"%d",&fd3);
        struct message{
        
        int x;
        char g[20];
        time_t timestamp;
       }message;
       
        struct message* data;
        struct message* data1;
     	data = (struct message*)malloc(sizeof(struct message));
     	data1 = (struct message*)malloc(sizeof(struct message));
     	
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
       
       
        
	printf("\n executing processes\n");
        fd_set rfds;
    int maxfd, retval;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 5;
    int i=0,j=0;
    //select() to read from both g1 and g2
    while(1){
        		fd_set rfds;
    			int maxfd, retval;
    			struct timeval tv;
    			tv.tv_sec = 1;
    			tv.tv_usec = 0;
        		FD_ZERO(&rfds);
        		FD_SET(fd1, &rfds);
        		FD_SET(fd2, &rfds);
        	FD_SET(0, &rfds);
        		
        		retval = select(FD_SETSIZE + 1, &rfds, NULL, NULL, &tv);
			
        
        

        
       	      if (retval < 0){ 
            		perror("SELECT");
        	     } else if (retval > 0) {
            

            
            		    if (FD_ISSET(fd1, &rfds) || FD_ISSET(fd2, &rfds)){
                		if (FD_ISSET(fd1, &rfds) )
                               {
                               	//put the all read messages in ques
                    			 read(fd1, data, sizeof(*data));
                    			 w1->buf1[i].x=data->x;
	                                strcpy(w1->buf1[i].g,data->g);
	                                w1->buf1[i].timestamp=data->timestamp;
	                               
                    			time(&w1->timestamp[i]);
                    			
                    			 
	                                
                    			//time difference between start and end 
                    			lat[i]=difftime(w1->timestamp[i],w1->buf1[i].timestamp);
                    			//get all the time difference values
                    			for(i=0;i<MSGSIZE;i++)
                    			{
                    			sum+=lat[i];
                    			}
                    			
                    			avg=sum/MSGSIZE;
                    			
                    			
                    					
                                        usleep(5);
                                        i++;
                                        read(fd1, &delay, sizeof(delay));
                                        count1+=delay;
                                        delay=count1;
                                        
                                        usleep(5);
                                     	 read(fd1, &cycl1, sizeof(cycl1));
                                     	 
	                               
	                           	
                    			
                    			
                                }
                		if (FD_ISSET(fd2, &rfds) )
                                {
                    			if (read(fd2, data1, sizeof(*data1)) < 0)  {
                        			perror("Error at data1 ");
                        			return 1;
                    				}
                    			
	       			w2->buf1[j].x=data1->x;
	                               strcpy(w2->buf1[j].g,data1->g); 
                                       w2->buf1[j].timestamp=data1->timestamp;
                    			
                    			time(&w2->timestamp[j]);
                    			
                    			lat1[j]=difftime(w2->timestamp[j],w2->buf1[j].timestamp);
                    			
                    			for(j=0;j<MSGSIZE;j++)
                    			{
                    			sum1+=lat[j];
                    			}
                    			
                    			avg1=sum1/MSGSIZE;
                    			
                    			
                    			usleep(5);
                    			j++;
                                      read(fd2, &delay1, sizeof(delay1));
                                       count2+=delay1;
                                        delay1=count2;
                                      usleep(5);
                                      read(fd2, &cycl2, sizeof(cycl2));
                                    
                    			
                               }
                               
                               
	                       
               }              
               	 
			
               		
                 } 	
                 		
                 	
		
			//after termination qrite to m

			if(cycl1 == 1000000 && cycl2 ==1000000){
					
               			
               			
	        	 		write(fd3,data, sizeof(*data));
	        	 		usleep(2);
	        	 		write(fd3,data1, sizeof(*data1));
	        	 		usleep(2);
	        	 		write(fd3,&delay, sizeof(delay));
	        	 		usleep(2);
	        	 		write(fd3,&delay1, sizeof(delay1));
	        	 		usleep(2);
	        	 		write(fd3,&cycl1, sizeof(cycl1));
	        	 		usleep(2);
	        	 		write(fd3,&cycl2, sizeof(cycl2));
	        	 		usleep(2);
	        	 		write(fd3,&avg, sizeof(avg));
	        	 		usleep(2);
	        	 		write(fd3,&avg1, sizeof(avg1));
	        	 		usleep(2);
	        	 		
	        	 		
	        	 		
	        	 		
	        	 		
	        	 	}
	        	 	//}	
               }
               	
            			
            
            
      return 0;
      
} // end of main()
