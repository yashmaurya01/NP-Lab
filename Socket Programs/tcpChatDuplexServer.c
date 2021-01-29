#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 


int main() 
{ 
	int sockfd, connfd, len, pid, recvmsg, sendmsg; 
	char buffSend[MAX] = ""; 
	char buffRecv[MAX] = ""; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 

	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Chatting between client and server 
	
	// Create child process
	pid = fork();
	
	while(strncmp("exit", buffRecv, 4) != 0){
		
		if(pid == 0){ // Child process for receive the message
			
			recvmsg = recv(connfd, buffRecv, MAX, 0 );
			printf("From client: %s\n", buffRecv); 
			if (strncmp("exit", buffRecv, 4) == 0) { 
				printf("Server Exit...\n"); 
				break; 
			} 
			bzero(buffRecv, MAX); 
			recvmsg = 0;
		} else {
			bzero(buffSend, sizeof(buffSend)); 
			printf("Enter the string : "); 
			sendmsg = 0; 
			while ((buffSend[sendmsg++] = getchar()) != '\n') 
				; 
			sendmsg = send(connfd, buffSend, MAX, 0 );

			// if msg contains "Exit" then server exit and chat ended. 
			if (strncmp("exit", buffSend, 4) == 0) { 
				printf("Server Exit...\n"); 
				break; 
			} 
		}
 
	}
	// After chatting close the socket 
	close(connfd);	
	close(sockfd); 
	exit(0);
} 

