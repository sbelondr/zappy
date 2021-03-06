#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define BUFF_READ 100

enum	e_ressources {
	LINEMATE,
	DERAUMERE,
	SIBUR,
	LAMENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD
};

typedef struct	s_case_map
{
	int ress[7];
}				t_case_map;

typedef struct	s_map
{
	t_case_map	**map_case;
}				t_map;

typedef struct	s_settings_srv
{
	int		port;
	int		x;
	int		y;
	char	**team;
	int		max_client;
	int		time;
}				t_settings_srv;

typedef struct	s_srv
{
	int						master_sck;
	struct sockaddr_in		address;
	int						addrlen;
	int						*client_sck;
	struct s_settings_srv	*settings_srv;
	t_map					map;
}				t_srv;

typedef struct	s_player
{
	enum e_ressources	*inventory;
	int					lvl;
	int					life;
	int					p_x;
	int					p_y;
	int					orientation;
	struct s_player		nxt;
}				t_player;

typedef struct	s_team
{
	char			*team_name;
	t_player		*players;
	struct s_team	*nxt;
}				t_team;

/*
** server.c
*/

void			ft_quit(int sig);

/*
** init_srv.c
*/

t_srv			*init_srv(t_settings_srv *settings_srv, t_map map);

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


/*
** parse_opt_server.c
*/ 

t_settings_srv	*ft_parse_arg_srv(char **av);

/*
** map.c
*/

t_map			generate_map(void);

