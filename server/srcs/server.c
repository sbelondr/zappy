/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/15 10:15:57 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "functions.h"

#include <poll.h>

static t_srv **g_srv = NULL;

void	ft_arraydel(char ***line)
{
	int	i;

	i = -1;
	if (*line)
	{
		while ((*line)[++i])
			free((*line)[i]);
		free(*line);
		*line = NULL;
	}
}

void ft_quit(int sig)
{
	printf("Kill all clients\n");
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	if (srv->param->replay_fd)
		close(srv->param->replay_fd);
	while (srv && ++i < srv->param->allowed_clients_amount)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
		{
			red();
			printf("Shutdown client: %d\n", srv->client_sck[i]);
			reset();
			shutdown(sd, SHUT_WR);
			if (close(sd))
				perror("close");
			srv->client_sck[i] = 0;
		}
	}
	free(srv->client_sck);
	if (close(srv->master_sck))
		perror("close");
	free(*g_srv);
	printf("Quit: %d", sig);
	exit(sig);
}

//Returns timeval timeout for select
struct timeval	time_left(struct timeval limit)
{
	struct timeval current;
	struct timeval ret;

	gettimeofday(&current, NULL);
	ret.tv_sec = 0;
	ret.tv_usec = 0;
	if (timercmp(&current, &limit, >) > 0)
		return (ret);
	timersub(&limit, &current, &ret);
	if (ret.tv_sec > 1000)
		timerclear(&ret);
	return (ret);
}

/*
 * use IBM implementation (poll)
 * https://www.ibm.com/docs/en/i/7.2?topic=designs-using-poll-instead-select
 */
int main(int ac, char **av)
{
	t_srv			*srv;
	t_world_state	st;
	t_param			param;
	struct pollfd	fds[200];
	char	buffer[1024];
	int		nfds = 1;
	int		timeout = (3 * 60 * 1000);
	int		rc = 0;
	int		new_sd;
	int		tmp_nfds = nfds;
	int		len = 0;
	int		close_conn = 0;
	int		compress_array = 0;
	int		end_server = 0;


	param = parse_input(ac, av);
	st = init_world(param);
	if (!st.map)
	{
		free_params(&param);
		exit(EXIT_FAILURE);
	}
	srv = init_srv(&param, &st);
	if (!srv)
		return (EXIT_FAILURE);
	g_srv = &srv;
	setup_signal();
	send_to_all_moniteur(srv, moniteur_mct(srv->world));
	yellow();
	printf("Launch srv\n");
	reset();

	// init fds with master socket
	fds[0].fd = srv->master_sck;
	fds[0].events = POLLIN;

	do
	{
		printf("Waiting on poll() nfds = %d ...\n", nfds);
		rc = poll(fds, nfds, timeout);

		if (rc < 0)
		{
			dprintf(STDERR_FILENO, "poll() failled\n");
			break ;
		}
		tmp_nfds = nfds;
		for (int i = 0; i < tmp_nfds; i++)
		{
			if (fds[i].revents == 0)
				continue ;
			if (fds[i].revents != POLLIN)
			{
				continue ;
//				dprintf(STDERR_FILENO, "Error, revents = %d\n", fds[i].revents);
//				end_server = 1;
//				break ;
			}
			if (fds[i].fd == srv->master_sck)
			{
				printf("Listening sck is readable\n");
				do
				{
					new_sd = accept(srv->master_sck,
							(struct sockaddr *)&(srv->address),
							(socklen_t *)&(srv->addrlen));
					//					new_sd = accept(srv->master_sck, NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror(" accept() failed");
							end_server = 1;
						}
						break ;
					}
					printf("New incoming connection - %d\n", new_sd);
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					//					simple_send(srv, i, ft_strdup("BIENVENUE\n"));
					send(new_sd, "BIENVENUE\n", \
							strlen("BIENVENUE\n"), 0);
					new_sd = -1;
					++nfds;
				} while (new_sd != -1);
			}
			else
			{
				printf("Descriptor %d is readable\n", fds[i].fd);
				close_conn = 0;
				do
				{
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						printf("error\n");
						close_conn = 1;
						break ;
					}
					if (rc == 0)
					{
						printf("Connection closed\n");
						close_conn = 1;
						break ;
					}
					len = rc;
					printf("%d bytes received: %s\n", len, buffer);
					rc = 0;
					//					rc = send(fds[i].fd, buffer, len, 0);
					if (rc < 0)
					{
						printf("send failed\n");
						close_conn = 1;
						break ;
					}
				} while (1);
				if (close_conn)
				{
					close(fds[i].fd);
					fds[i].fd = -1;
					compress_array = 1;
				}
			}
		}
		if (compress_array)
		{
			compress_array = 0;
			for (int i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for (int j = i; j < nfds; j++)
					{
						fds[i].fd = fds[j + 1].fd;
					}
					--i;
					--nfds;
				}

			}
		}
	} while (!end_server);
	game_tick(srv);
	ft_quit(0);
	return (EXIT_SUCCESS);
}
