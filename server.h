#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define MAX_CLIENT 10
#define PORT 8080

typedef struct	s_srv
{
	int					master_sck;
	struct sockaddr_in	address;
	int					addrlen;
	int					client_sck[MAX_CLIENT];
}				t_srv;