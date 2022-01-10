#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "struct.h"
#include "functions.h"

#define BUFF_READ 2048

typedef struct	s_case_map
{
	int ress[7];
}				t_case_map;

/*
** server.c
*/

void			ft_quit(int sig);

/*
** init_srv.c
*/

t_srv			*init_srv(t_param *param, t_world_state *st);

/*
** act_client.c
*/

void			ft_client_exit(t_srv *srv, int sd, int i);
void			ft_client_send_data(t_srv *srv, char *buff, int valread, int i);

/*
** act_server.c
*/

void			ft_add_new_client(t_srv *srv, fd_set *readfds);
int				ft_set_max_sd(t_srv *srv, fd_set *readfds);

/*
** color.c
*/

void			red(void);
void			blue(void);
void			yellow(void);
void			green(void);
void			reset(void);

/*
** listen.c
*/

void			ft_listen_srv(t_srv *srv, fd_set *readfds);

/*
** termcaps.c
*/

void			reset_term(void);
