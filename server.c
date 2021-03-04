#include<signal.h>
#include <errno.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

int BindCreatedSocket(int hSocket)
{
	int iRetval=-1;
	int ClientPort = 8080;
	struct sockaddr_in  remote= {0};
	/* Internet address family */
	remote.sin_family = AF_INET;
	/* Any incoming interface */
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(ClientPort); /* Local port */
	iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
	return iRetval;
}

int main(void)
{
	int	sockets[10];
	int	socket_desc;
	int	sock;
	char client_message[200];
	size_t	clientLen;
	char	map[10][10] = {0};
	char	buffer[200];
	int		playerx = 5;
	int		playery = 5;
	struct sockaddr_in client;
	fd_set fd;

	soc
	clientLen = sizeof(struct sockaddr_in);
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	BindCreatedSocket(socket_desc);
	listen(socket_desc, 3);
	printf("Accepted client\n");
	FD_ZERO(&fd);
	FD_SET(socket_desc, &fd);
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	if (select(sock + 1, &fd, NULL, &fd, &timeout))
	{
	printf("accepted\n");
	sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
	printf("accepted\n");
	}
	else
	{
		printf("Timeoueted\n");
		exit(1);
	}
	while (1)
	{
		struct timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		memset(client_message, 0, 200);
		memset(buffer, 0, 200);
		FD_ZERO(&fd);
		FD_SET(sock, &fd);
		FD_SET(socket_desc, &fd);
		if (!select(sock + 1, &fd, NULL, &fd, &timeout))
		{
			printf("Timeoueted\n");
			continue;
		}
		printf("Temps restant: %ld %ld", timeout.tv_sec, timeout.tv_usec);
		if (FD_ISSET(sock, 
		recv(sock, client_message, 200, 0);
		if (!strcmp(client_message, "up"))
		{
			playery--;
			send(sock, "ok", 2, 0);
		}
		else if (!strcmp(client_message, "down"))
		{
			playery++;
			send(sock, "ok", 2, 0);
		}
		else if (!strcmp(client_message, "see"))
		{
			sprintf(buffer, "Current pos: %d %d\n", playerx, playery);
			send(sock, buffer, strlen(buffer), 0);
		}
		else
		{
			send(sock, "invalid command", 7 + 1 + 7, 0);
		}
		printf("Client sent: %s\n", client_message);

	}
	close(sock);
}
