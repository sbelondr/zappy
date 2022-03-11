/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:11:02 by jayache           #+#    #+#             */
/*   Updated: 2022/03/11 12:55:56 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int			use_localized_string(t_param *param)
{
	return (!(param->flags & FLAG_PEDANTIC) && (param->flags & FLAG_LOCALIZED));
}

const char	*ressource_name(t_ressources ressource_id, int localized)
{
	if (localized)
	{
		switch(ressource_id)
		{
			case FOOD:		return LOCFOOD;			break;
			case LINEMATE:	return LOCLINEMATE;		break;
			case DERAUMERE: return LOCDERAUMERE;	break;
			case SIBUR:		return LOCSIBUR;		break;
			case MENDIANE:	return LOCMENDIANE;		break;
			case PHIRAS:	return LOCPHIRAS;		break;
			case THYSTAME:	return LOCTHYSTAME;		break;
			case PLAYER:	return LOCPLAYER;		break;
			default:	return NULL;			break;
		}
	}
	else
	{
		switch(ressource_id)
		{
			case FOOD:		return STANDARDFOOD;			break;
			case LINEMATE:	return STANDARDLINEMATE;		break;
			case DERAUMERE: return STANDARDDERAUMERE;	break;
			case SIBUR:		return STANDARDSIBUR;		break;
			case MENDIANE:	return STANDARDMENDIANE;		break;
			case PHIRAS:	return STANDARDPHIRAS;		break;
			case THYSTAME:	return STANDARDTHYSTAME;		break;
			case PLAYER:	return STANDARDPLAYER;		break;
			default:	return NULL;			break;
		}
	}
}

const char	*command_name(t_command_type command_id, int localized)
{
	switch(command_id)
	{
		case COMMAND_AVANCE:		return (localized ? LOC_COMMAND_AVANCE		: STANDARD_COMMAND_AVANCE		);	break;
		case COMMAND_GAUCHE:		return (localized ? LOC_COMMAND_GAUCHE		: STANDARD_COMMAND_GAUCHE		); 	break;
		case COMMAND_DROITE:		return (localized ? LOC_COMMAND_DROITE		: STANDARD_COMMAND_DROITE		); 	break;
		case COMMAND_VOIR:			return (localized ? LOC_COMMAND_VOIR		: STANDARD_COMMAND_VOIR			); 	break;
		case COMMAND_EXPULSER:		return (localized ? LOC_COMMAND_KICK		: STANDARD_COMMAND_KICK			); 	break;
		case COMMAND_INCANTATION:	return (localized ? LOC_COMMAND_INCANTATION : STANDARD_COMMAND_INCANTATION	); 	break;
		case COMMAND_INVENTAIRE:	return (localized ? LOC_COMMAND_INVENTAIRE	: STANDARD_COMMAND_INVENTAIRE	); 	break;
		case COMMAND_BROADCAST:		return (localized ? LOC_COMMAND_BROADCAST	: STANDARD_COMMAND_BROADCAST	); 	break;
		case COMMAND_PRENDRE:		return (localized ? LOC_COMMAND_PRENDRE		: STANDARD_COMMAND_PRENDRE		); 	break;
		case COMMAND_POSER:			return (localized ? LOC_COMMAND_POSE		: STANDARD_COMMAND_POSE			); 	break;
		default:					return NULL;																	break;
	}
}
