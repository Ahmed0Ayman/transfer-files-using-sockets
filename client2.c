#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

/* port number used by client to request to request specific operation from server */ 
#define PORT 5555



/* buffer size for TX and RX */
#define BUFFER_SIZE 100 



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



int main(int argc , char const * argv[])
{

	if(argc < 3) /* check if we received valid arguments from terminal */
	{
		printf("please enter the message to send \n");
		return -3 ;
	}

	FILE * fp ; /* file struct handler */

	/* open file with  specific path */
	CHECK_FILE((fp=fopen(argv[1] , "w"))) ;
	

	int socket_id =0 ;
	struct sockaddr_in server_addr ;
	
	/* array of strings used to handle TX & RX buffers */
  	char  mesg[2][BUFFER_SIZE] = {0,0};

	strcpy(mesg[0],argv[1]);  /* receive message through command line interfane */
	
	
	/* creeate socket and return Id to handle this created socket */
	CHECK_SOCKERROR(socket_id = socket(AF_INET , SOCK_STREAM ,0));
	
	
	/* initialize server socket addr */
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons(PORT) ;
	server_addr.sin_addr.s_addr = INADDR_ANY ;
	
	/* requested connection with  specified server */
		CHECK_SOCKERROR(connect(socket_id , (struct sockaddr *)&server_addr , sizeof(server_addr)));
	
	/* send required file to read to server */
    		send(socket_id,argv[2],strlen(argv[2]),0);
	while(1)
	{
	
	/* receve data from server */
    	if(recv(socket_id,&mesg[1],sizeof(mesg[1]),0)==0)
    	{
		fclose(fp);
		break ;
	};

	/* send data to server */
    	//send(socket_id,mesg[0],sizeof(mesg[0]),0);
    	
    	/* write receive string into file */
		fputs(mesg[1],fp);
		
	/* indication the tx and rx successfully */
		printf("this is received message from server : %s \n",mesg[1]);

	
	}
		
	return 0 ;



}





