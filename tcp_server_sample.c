#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h> // for inet_aton(), inet_addr() and inet_ntoa()

	int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char user[50], pswd[50];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.");

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.");

	printf("\nClient IP: %s", inet_ntoa(client.sin_addr));
	printf("\nPort Number: %d\n\n", ntohs(client.sin_port));

	recb=recv(ns,user,sizeof(user),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	printf("\nUsername Recieved: ");
	printf("%s", user);

	recb=recv(ns,pswd,sizeof(pswd),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	printf("\nPassword Recieved: ");
	printf("%s", pswd);
	char fil[50];

	strcat(user,",");
	strcat(pswd,",");

    char *u, *p;
    char buff[50];

	FILE *fp;
	char temp[512], u1[50], p1[50];
	char fname[50];
	strcpy(fname,"f.txt");

	if( access(fname, F_OK) != -1)
	{
		printf("\nFile Exists\n");
		fp = fopen(fname, "r");
		while((fgets(temp, 512, fp)!=NULL))
		{
			// printf("\n%s\n", temp);
			if((u = strstr(temp,user))!=NULL)
			{
				if((p = strstr(u, pswd))!=NULL)
				{
					printf("\nIncome: %s\n", p+strlen(pswd));
					strcpy(buff,p+ strlen(pswd));
					break;
				}
				else
				{
					strcpy(buff,"Incorrect Password");
				}
			}
			else
			{
				strcpy(buff,"Incorrect Username");
			}
		}
	}
	else
	{
		printf("\nFile DOES NOT Exist\n");
	}

	
	// printf("\n\n");
	// printf("Type Message: ");
	// scanf("%s", user);

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}

	close(ns);
	close(s);
}