#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{

	int s,r,recb,sntb,x;
	printf("INPUT port number: ");
	scanf("%d", &x);
	struct sockaddr_in server;
	char buff[50];
	s=socket(AF_INET,SOCK_STREAM,0);

	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}

	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(s,(struct sockaddr*)&server,sizeof(server));

	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}

	printf("\nSocket connected.");

	FILE *fp;
	char temp[512], u1[50], p1[50];
	char fname1[50];
	FILE *fp1;
	strcpy(fname1,"result.txt");

	if( access(fname1, F_OK) != -1)
	{
		printf("\nFile2 Exists\n");
		fp1 = fopen(fname1, "r");
		while((fgets(temp, 512, fp1)!=NULL))
		{
			printf("\n%s\n", temp);
		}
		fclose(fp1);
	}

	else
	{
		printf("\nFile2 DOES NOT Exist\n");
	}

	// char buff[50];

	recb=recv(s,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	printf("Message Recieved: \n%s",buff);
	close(s);
}