// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>


	FILE * fp ; /* file struct handler */
    	int server_socketID, child_socketID;



/* port number used by server to litsen for incoming connections */ 
#define PORT 5555

/* buffer size for TX and RX */
#define BUFFER_SIZE 1000 



/* macro fore check file functions */
#define CHECK_FILE(X)   		\
{   					\
	if((X) == NULL){ 		\
	printf("file doen't exist \n");	\
	return -1 ;}  			\
}



/* macro  for check socket standared functions */
#define CHECK_SOCKERROR(X)			\
{						\
	if((X) == -1)				\
	{					\
	printf("error in sockets functions \n");\
	return -2 ;				\
	}					\
}

void Handler_Interruptsignal(int sig)
{

printf("process is resumed \n");


}


void Handler_pusesignal(int seg)
{
printf("process is paused \n");
pause();
}


int main(int argc, char const *argv[])
{


	
	struct sigaction sa1 ;
        sa1.sa_flags = SA_RESTART ;
        sa1.sa_handler = &Handler_Interruptsignal  ;

	/* register action connect with specific signal here we use  ctrl+c as a signal */
        	sigaction(SIGINT , &sa1 ,NULL) ;
    		struct sockaddr_in sock_serveraddr ;



	struct sigaction sa2 ;
        sa2.sa_flags = SA_RESTART ;
        sa2.sa_handler = &Handler_pusesignal  ;

	/* register action connect with specific signal here we use  ctrl+c as a signal */
        	sigaction(SIGTSTP , &sa2 ,NULL) ;







	/* array of strings used to handle TX & RX buffers */
    char  mesg[2][BUFFER_SIZE] = {" from server to client  \n",0};


	/* creeate socket and return Id to handle this created socket */
    CHECK_SOCKERROR(server_socketID = socket(AF_INET , SOCK_STREAM , 0)) ;


    sock_serveraddr.sin_family = AF_INET ;

    sock_serveraddr.sin_port = htons(PORT);

    
    sock_serveraddr.sin_addr.s_addr = INADDR_ANY ;

    /* assign socket address to the server */
    CHECK_SOCKERROR(bind(server_socketID , (struct sockaddr *)&sock_serveraddr , sizeof(sock_serveraddr)));

    /* litsen for incoming  connections */
    CHECK_SOCKERROR(listen(server_socketID,2));
    
	 fork();

    /* block until comming new connection only one socket is handled at atime 
    next task we'll use multithread to handle multiple connections at the same time */
    CHECK_SOCKERROR( child_socketID = accept(server_socketID,NULL,NULL));

   	recv(child_socketID,mesg[1],sizeof(mesg[1]),0);	
   	
   	printf("%s \n",mesg[1]); /* printing required file on a termnal */
   	
   	
 	/* open file with  specific path */
	CHECK_FILE((fp=fopen(mesg[1] , "r"))) ;
	

while (1)
{
    if(feof(fp)) {close(child_socketID); fclose(fp); break;} /* if we reach to end of file then exit with normal way return 0 */
  
    fgets(mesg[0],sizeof(mesg[0]),fp);
   
    send(child_socketID,mesg[0],strlen(mesg[0]),0);
   // recv(child_socketID,mesg[1],sizeof(mesg[1]),0);

	/* give some delay for our appilcation */
		sleep(1);

   //    printf(" the clint send %s \n",mesg[1]);
}
	wait(NULL);
    return 0;
}
