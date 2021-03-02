#include<signal.h>
#include <errno.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>


void timer_handler(int sig){
	write(1,"Hi\n",3); 
	(void)sig;
}
short SocketCreate(void)
{
	short hSocket;

	printf("Create the socket\n");
	hSocket = socket(AF_INET, SOCK_STREAM, 0);

	return hSocket;
}
int BindCreatedSocket(int hSocket)
{
	int iRetval=-1;
	int ClientPort = 90191;
	struct sockaddr_in  remote= {0};
	/* Internet address family */
	remote.sin_family = AF_INET;
	/* Any incoming interface */
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(ClientPort); /* Local port */
	iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
	return iRetval;
}
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int socket_desc, sock, clientLen;
	struct sockaddr_in client;
	char client_message[200]= {0};
	char message[100] = {0};
	const char *pMessage = "hello aticleworld.com";
	//Create socket
	socket_desc = SocketCreate();
	if (socket_desc == -1)
	{
		printf("Could not create socket");
		return 1;
	}
	printf("Socket created\n");
	//Bind
	if( BindCreatedSocket(socket_desc) < 0)
	{
		//print the error message
		perror("bind failed.");
		return 1;
	}
	printf("bind done\n");
	//Listen
	listen(socket_desc, 3);
	//Accept and incoming connection
	while(1)
	{
		fd_set fd;
		printf("Waiting for incoming connections...\n");
		clientLen = sizeof(struct sockaddr_in);
		//accept connection from an incoming client
		sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
		if (sock < 0)
		{
			perror("accept failed");
			return 1;
		}
		printf("Connection accepted\n");
		memset(client_message, '\0', sizeof client_message);
		memset(message, '\0', sizeof message);
		while (1)
		{
			struct timeval timeout;
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;
			FD_ZERO(&fd);
			FD_SET(sock, &fd);
			//Receive a reply from the client
			if (!select(sock + 1, &fd, NULL, NULL, &timeout)) 
			{
				printf("TImeout!\n");
				continue;
			}
			recv(sock, client_message, 200, 0);
			printf("Client reply : %s\n",client_message);
			if(strcmp(pMessage,client_message)==0)
			{
				strcpy(message,"Hi there !");
			}
			else
			{
				strcpy(message,"Invalid Message !");
			}
			// Send some data
			if( send(sock, message, strlen(message), 0) < 0)
			{
				printf("Send failed");
				//return 1;
			}

			continue;
			errno = 0;
		}
		close(sock);
		sleep(1);
	}
	return 0;
}
