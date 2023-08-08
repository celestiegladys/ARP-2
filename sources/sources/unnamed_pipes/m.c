// M PROCESS (unnamed pipe)


// Including required headers

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

// defining message size
#define MSGSIZE 99999

// main ()
// argc stands for argument count and argv stands for argument values. These are variables passed to the main function when it starts executing.
// main() in which we developed the principal code of the M process 
int main(int argc, char* argv[]) {
    int fd;
    int delay,delay1;
    int cycl1,cycl2,bits;
    float avg,avg1;
    long int lat,lat_sec;
    char buffer[20]; // buffere array
    memset (buffer,'\0',sizeof(buffer));
    sscanf(argv[1],"%d",&fd);
    
    // structure message
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
        
        
        time_t timestamp;
       }queue;
        
        
        struct queue* d1;
        struct queue* d2;
     	d1 = (struct queue*)malloc(sizeof(struct queue));
     	d2 = (struct queue*)malloc(sizeof(struct queue));
     	
  
    
    usleep(2);
    read(fd,data,sizeof(*data));
    printf("\n\n\n\n\nFinal bandwidth for G1 and G2 processes to the R process:\n\n");
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n data:%s number of messages recieved  : %d \n",data->g, data->x);
    printf("\n\n\n\n\n---------------------------\n\n");
    usleep(2);
    read(fd,data1,sizeof(*data1));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n data:%s number of messages recieved: %d\n",data1->g,data1->x); 
    printf("\n\n\n\n\n---------------------------\n\n");
    usleep(2);
   
    read(fd, &delay, sizeof(delay));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n offset for g1:%d",delay);
    
    printf("\n\n\n\n\n---------------------------\n\n");
    usleep(2);
  
    read(fd, &delay1, sizeof(delay1));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n offset for g2:%d",delay1);
    printf("\n\n\n\n\n---------------------------\n\n");
   
     usleep(2);
    read(fd, &cycl1, sizeof(cycl1));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n cycles for g1:%d",cycl1);
    printf("\n\n\n\n\n---------------------------\n\n");
    usleep(2);
    read(fd, &cycl2, sizeof(cycl2));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\n cycles for g2:%d",cycl2);
    printf("\n\n\n\n\n---------------------------\n\n");
    usleep(2);
    read(fd, &avg, sizeof(avg));
    usleep(2);
    read(fd, &avg1, sizeof(avg1));
    usleep(2);
    //to get average latency in microseconds 
    lat=(avg+avg1)/2;
    printf("\n avg delay latency:%ld",lat);
    //latency in sec
    lat_sec=((avg/1000000)+(avg1/1000000));
    printf("\n\n\n\n\n---------------------------\n\n");
    printf("\nsize of G1:%lu and G2:%lu",sizeof( *data),sizeof( *data1));
    bits=(sizeof( *data)*8)+(sizeof( *data1)*8);
    //bits/sec
    printf("\nbits %ld",bits%lat_sec);

printf("\n\n\n\n\n---------------------------\n\n");
    
                    

    
  
    
    return 0;

} // end of main()
