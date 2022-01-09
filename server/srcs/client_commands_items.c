/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_items.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:51:00 by selver            #+#    #+#             */
/*   Updated: 2022/01/07 11:48:00 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	attempt_take_item(const char *name, int *quant, int *inv, char *arg)
{
	if (ft_strequ(arg, name) && *quant > 0)
	{
		--*quant;
		++*inv;
		return (1);
	}
	return (0);
}

static int	attempt_put_item(const char *name, int *quant, int *inv, char *arg)
{
	if (ft_strequ(arg, name) && *inv > 0)
	{
		--*inv;
		++*quant;
		return (1);
	}
	return (0);
}

static int	string_to_res_id(char *res_name)
{
	int	res;

	if (!ft_strcmp("SIBUR", res_name))
		res = SIBUR;
	else if (!ft_strcmp("LAMENDIANE", res_name))
		res = LAMENDIANE;
	else if (!ft_strcmp("FOOD", res_name))
		res = FOOD;
	else if (!ft_strcmp("LINEMATE", res_name))
		res = LINEMATE;
	else if (!ft_strcmp("DERAUMERE", res_name))
		res = DERAUMERE;
	else if (!ft_strcmp("THYSTAME", res_name))
		res = THYSTAME;
	else
		res = -1;
	return (res);
}

char	*putdown_item(t_srv *srv, t_world_state *world, t_client *player)
{
	char	*arg;
	int		*square;
	int		success;
	int		*inv;
	int		res;

	success = 0;
	square = get_case(world, player->p_x, player->p_y);
	arg = player->buffer[0].arg;
	inv = player->ressource;
	res = string_to_res_id(arg);
	if (res != -1)
	{
		success |= attempt_put_item(arg, &(square[res]), &inv[res], arg);
		send_to_all_moniteur(srv, moniteur_pdr(player, res));
		send_to_all_moniteur(srv, moniteur_pin(player));
		send_to_all_moniteur(srv, moniteur_bct(world, player->p_x, player->p_y));
	}
	return (ft_strdup(success ? "OK\n" : "KO\n"));
}

char	*pickup_item(t_srv *srv, t_world_state *world, t_client *player)
{
	char	*arg;
	int		*square;
	int		success;
	int		*inv;
	int		res;

	success = 0;
	square = get_case(world, player->p_x, player->p_y);
	inv = player->ressource;
	arg = player->buffer[0].arg;
	res = string_to_res_id(arg);
	if (res != -1)
	{
		success |= attempt_take_item(arg, &(square[res]), &inv[res], arg);
		send_to_all_moniteur(srv, moniteur_pgt(player, res));
		send_to_all_moniteur(srv, moniteur_pin(player));
		send_to_all_moniteur(srv, moniteur_bct(world, player->p_x, player->p_y));
	}
	return (ft_strdup(success ? "OK\n" : "KO\n"));
}
