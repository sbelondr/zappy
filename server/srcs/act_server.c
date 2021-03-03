#include "server.h"

void ft_add_new_client(t_srv *srv, fd_set *readfds)
{
	int new_socket;

	if (FD_ISSET(srv->master_sck, readfds))
	{
		int i;
		if ((new_socket = accept(srv->master_sck,
								 (struct sockaddr *)&(srv->address),
								 (socklen_t *)&(srv->addrlen))) < 0)
		{
			red();
			dprintf(STDERR_FILENO, "La secte... socket ne t'accepte pas\n");
			reset();
			return; // (EXIT_FAILURE);
		}
		yellow();
		printf("New connection: fd -> %d\n", new_socket);
		reset();
		i = -1;
		while (++i < MAX_CLIENT)
		{
			if (srv->client_sck[i] == 0)
			{
				srv->client_sck[i] = new_socket;
				yellow();
				printf("Add new client\n");
				reset();
				break;
			}
		}
	}
}

int ft_set_max_sd(t_srv *srv, fd_set *readfds)
{
	int sd, max_sd;
	int i;

	max_sd = srv->master_sck;
	i = -1;
	while (++i < MAX_CLIENT)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
			FD_SET(sd, readfds);
		// increase sd
		if (sd > max_sd)
			max_sd = sd;
	}
	return (max_sd);
}