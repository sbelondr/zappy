/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_items.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:51:00 by selver            #+#    #+#             */
/*   Updated: 2022/11/03 09:39:00 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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

	if (!strcmp(LOCSIBUR, res_name))
		res = SIBUR;
	else if (!strcmp(LOCMENDIANE, res_name))
		res = MENDIANE;
	else if (!strcmp(LOCPHIRAS, res_name))
		res = PHIRAS;
	else if (!strcmp(LOCFOOD, res_name))
		res = FOOD;
	else if (!strcmp(LOCLINEMATE, res_name))
		res = LINEMATE;
	else if (!strcmp(LOCDERAUMERE, res_name))
		res = DERAUMERE;
	else if (!strcmp(LOCTHYSTAME, res_name))
		res = THYSTAME;
	else
	{
		res = -1;
		printf(ERROR_UNKNOWN_RESSOURCE, res_name);
	}
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
		if (success)
		{
			send_to_all_moniteur(srv, moniteur_pdr(player, res));
			send_to_all_moniteur(srv, moniteur_pin(player));
			send_to_all_moniteur(srv, moniteur_bct(world, player->p_x, player->p_y));
		}
	}
	return (ft_strdup(success ? "ok\n" : "ko\n"));
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
		if (success)
		{
			send_to_all_moniteur(srv, moniteur_pgt(player, res));
			send_to_all_moniteur(srv, moniteur_pin(player));
			send_to_all_moniteur(srv, moniteur_bct(world, player->p_x, player->p_y));
		}
	}
	return (ft_strdup(success ? "ok\n" : "ko\n"));
}
