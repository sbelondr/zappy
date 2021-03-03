#include "server.h"

void ft_listen_srv(t_srv *srv, fd_set *readfds)
{
	char buff[512];
	int sd;
	int i;
	int	valread;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		sd = srv->client_sck[i];
		if (FD_ISSET(sd, readfds))
		{
			bzero(buff, 512);
			if ((valread = read(sd, buff, 1024)) == 0)
				ft_client_exit(srv, sd, i);
			else
				ft_client_send_data(srv, buff, valread, i);
		}
	}
}