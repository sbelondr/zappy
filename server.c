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

int main(void)
{
	int	socket_desc;
	int	sock;
	char client_message[200];
	size_t	clientLen;
	char	map[10][10] = {0};
	int		playerx = 5;
	int		playery = 5;
	struct sockaddr_in client;
	fd_set fd;

	clientLen = sizeof(struct sockaddr_in);
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	BindCreatedSocket(socket_desc);
	listen(socket_desc, 3);
	sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
	printf("Accepted client\n");
	while (1)
	{
		struct timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		memset(client_message, 0, 200);
		FD_ZERO(&fd);
		FD_SET(sock, &fd);
		if (!select(sock + 1, &fd, NULL, &fd, &timeout))
		{
			printf("Timeoueted\n");
			continue;
		}
		printf("Temps restant: %ld %ld", timeout.tv_sec, timeout.tv_usec);
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
			char buffer[200];
			sprintf(buffer, "Current pos: %d %d\n", playerx, playery);
			send(sock, buffer, strlen(buffer), 0);

		}
		printf("Client sent: %s\n", client_message);

	}
	close(sock);
}
