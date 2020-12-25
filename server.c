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
	// printf("\nClient IP: %s", inet_ntoa(client.sin_addr));
	// printf("\nPort Number: %d\n\n", ntohs(client.sin_port));
	char *u, *p;
	char buff[50];
	FILE *fp;
	char temp[512], u1[50], p1[50];
	char fname[50], fname1[50];

	strcpy(fname,"m1.txt");
	int A[2][2];
	int B[2][2];
	int i = 0, j = 0;

	if( access(fname, F_OK) != -1)
	{
		printf("\nFile1 Exists\n");
		fp = fopen(fname, "r");
		while((fgets(temp, 512, fp)!=NULL))
		{
			printf("\n%s\n", temp);
			A[i][j] = atoi(&temp[0]);
			A[i][j+1] = atoi(&temp[2]);
			i = i+1;
		}
		fclose(fp);
	}

	else
	{
		printf("\nFile1 DOES NOT Exist\n");
	}

	FILE *fp1;
	strcpy(fname1,"m2.txt");
	i = 0;
	j = 0;

	if( access(fname1, F_OK) != -1)
	{
		printf("\nFile2 Exists\n");
		fp1 = fopen(fname1, "r");

		while((fgets(temp, 512, fp1)!=NULL))
		{
			printf("\n%s\n", temp);
			B[i][j] = atoi(&temp[0]);
			B[i][j+1] = atoi(&temp[2]);
			i = i+1;
		}
		fclose(fp1);
	}

	else
	{
		printf("\nFile2 DOES NOT Exist\n");
	}

	printf("\nMatrix A: \n");
	for(i = 0; i<2; i++)
	{
		for(j = 0; j<2; j++)
		{
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix B: \n");
	for(i = 0; i<2; i++)
	{
		for(j = 0; j<2; j++)
		{
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}

	int C[2][2];

	C[0][0] = (A[0][0] * B[0][0]) + (A[0][1] * B[1][0]);
	C[0][1] = (A[0][0] * B[0][1]) + (A[0][1] * B[1][1]);
	C[1][0] = (A[1][0] * B[0][0]) + (A[1][1] * B[1][0]);
	C[1][1] = (A[1][0] * B[0][1]) + (A[1][1] * B[1][1]);

	printf("\nMatrix C: \n");
	for(i = 0; i<2; i++)
	{
		for(j = 0; j<2; j++)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}

	FILE *fp2;
	char fname2[50];
	strcpy(fname2,"result.txt");
	i = 0;
	j = 0;

	if( access(fname2, F_OK) != -1)
	{
		printf("\nResult file Exists\n");
		fp2 = fopen(fname2, "w");
		fprintf(fp2, "%d\t%d\n%d\t%d", C[0][0], C[0][1], C[1][0], C[1][1]);
		fclose(fp2);
	}

	else
	{
		printf("\nResult file DOES NOT Exist\n");
	}

	// char buff[50];
	buff[0] = C[0][0];
	buff[1] = ' ';
	buff[2] = C[0][1];
	buff[3] = '\n'

	sprintf(buff,"%d\t%d\n%d\t%d\n",C[0][0], C[0][1], C[1][0], C[1][1]);

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