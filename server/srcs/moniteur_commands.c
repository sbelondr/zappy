/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniteur_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:07:00 by selver            #+#    #+#             */
/*   Updated: 2022/03/10 10:40:42 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int asprintf(char **strp, const char *fmt, ...);

//Taille de la carte
char	*moniteur_msz(t_world_state *world)
{
	char	*ret;
	int		error;
	t_param	p;

	p = world->params;
	error = asprintf(&ret, "msz %d %d\n", p.world_width, p.world_height);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Contenu d'une case de la carte 
char	*moniteur_bct(t_world_state *world, int x, int y)
{
	char	*ret;
	int		error;
	int		*quant;

	quant = get_case(world, x, y);	
	error = asprintf(&ret, "bct %d %d %d %d %d %d %d %d %d\n",
			x, y, quant[0], quant[1], quant[2], quant[3], quant[4], quant[5], quant[6]); 
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Contenu de la carte
char	*moniteur_mct(t_world_state *world)
{
	char	*ret;
	char	*dup;
	char	*tmp;
	int		error;
	int		c_x;
	int		c_y;

	c_x = 0;
	c_y = 0;
	ret = ft_strdup("");
	while (c_y < world->params.world_height)
	{
		while (c_x < world->params.world_width)
		{
			tmp = moniteur_bct(world, c_x, c_y);
			error = asprintf(&dup, "%s%s", ret, tmp);
			free(tmp);
			if (error < 0)
				emergency_exit(__FILE__ ": Fatal: asprintf: ");
			free(ret);
			ret = dup;
			++c_x;
		}
		++c_y;
		c_x = 0;
	}
	return (ret);
}

//Unité de temps
char	*moniteur_tac(t_world_state *world)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "tac %d\n", world->params.allowed_clients_amount);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}
//Unité de temps
char	*moniteur_mac(t_world_state *world)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "mac %d\n", world->params.team_hard_limit);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}
//Unité de temps
char	*moniteur_sgt(t_world_state *world)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "sgt %d\n", world->params.time_delta);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Nom des équipes
char	*moniteur_tna(t_world_state *world)
{
	char	*ret;
	int		error;
	t_list	*current;
	char	*dup;

	ret = ft_strdup("");
	current = world->params.team_list;
	while (current)
	{
		error = asprintf(&dup, "%stna %s\n", ret, ((t_team*)current->content)->team_name);
		if (error < 0)
			emergency_exit(__FILE__ ": Fatal: asprintf: ");
		free(ret);
		ret = dup;
		current = current->next;
	}
	return (ret);
}

//Joueur
char	*moniteur_pnw(t_client *client)
{
	char	*ret;
	int		error;

	if (client->team_name != NULL)
		error = asprintf(&ret, "pnw #%d %d %d %d %d %s\n",
				client->id, client->p_x, client->p_y, client->orientation + 1,
				client->lvl, client->team_name);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Oeuf pris
char	*moniteur_ebo(t_egg *egg)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "ebo #%d\n", egg->id);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Oeuf eclot
char	*moniteur_eht(t_egg *egg)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "eht #%d\n", egg->id);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Oeufs
char	*moniteur_enw(t_egg *egg)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "enw #%d #%d %d %d\n",
			egg->id, egg->father_id, egg->p_x, egg->p_y);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Position joueur
char	*moniteur_ppo(t_client *client)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "ppo #%d %d %d %d\n",
			client->id, client->p_x, client->p_y, client->orientation + 1);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//pose une ressource
char	*moniteur_pdr(t_client *client, int ressource)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pdr #%d %d\n", client->id, ressource);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//broadcast
char	*moniteur_pbc(int id, char *msg)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pbc #%d %s\n", id, msg);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Start fork
char	*moniteur_pfk(t_client *client)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pfk #%d\n", client->id);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//prend une ressource
char	*moniteur_pgt(t_client *client, int ressource)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pgt #%d %d\n", client->id, ressource);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//inventaire
char	*moniteur_pin(t_client *client)
{
	char	*ret;
	int		error;
	int		*inv;

	inv = client->ressource;
	error = asprintf(&ret, "pin #%d %d %d %d %d %d %d %d %d %d\n", 
			client->id, client->p_x, client->p_y, inv[FOOD], inv[LINEMATE], inv[DERAUMERE],
			inv[SIBUR], inv[MENDIANE], inv[PHIRAS], inv[THYSTAME]);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Player incantation
char	*moniteur_pic(t_world_state *world, t_client *client)
{
	char		*ret;
	char		*tmp;
	int			error;
	t_list		*current;
	t_client	*c;

	error = asprintf(&ret, "pic %d %d %d", client->p_x, client->p_y, client->lvl);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	current = world->client_list;
	while (current)
	{
		c = current->content;
		if (c->p_x == client->p_x && c->p_y == client->p_y && c->lvl == client->lvl && !is_special_team_member(c))
		{
			tmp = ret;
			error = asprintf(&ret, "%s #%d", tmp, c->id);
			if (error < 0)
				emergency_exit(__FILE__ ": Fatal: asprintf: ");
			free(tmp);
		}
		current = current->next;
	}
	tmp = ret;
	error = asprintf(&ret, "%s\n", tmp);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	free(tmp);
	return (ret);
}

//Death
char	*moniteur_pdi(t_client *client)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pdi #%d\n", client->id);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}
//Kick
char	*moniteur_pex(t_client *client)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pex #%d\n", client->id);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Player level
char	*moniteur_plv(t_client *client)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "plv #%d %d\n", client->id, client->lvl); 
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Egg death
char	*moniteur_edi(t_egg *egg)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "edi #%d\n", egg->id); 
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

//Incantation result
char	*moniteur_pie(int x, int y, int success)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "pie %d %d %d\n", x, y, success); 
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}


//Send msg to all graphic clients connected - free msg afterwards.
void	send_to_all_moniteur(t_srv *srv, char *msg)
{
	t_list		*current;
	t_client	*c;

	current = srv->world->client_list;
	while (current)
	{
		c = current->content;
		if (c && c->team_name && !ft_strcmp(c->team_name, GRAPHIC_TEAM))
			simple_send_no_free(srv, c->id, msg);
		current = current->next;
	}
	if (srv->param->replay_fd)
	{
		dprintf(srv->param->replay_fd, "%ld: %s", srv->frame_nbr, msg);
	}
	free(msg);
}
