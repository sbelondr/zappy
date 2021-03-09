/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:02:56 by jayache           #+#    #+#             */
/*   Updated: 2019/12/09 10:30:23 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_p(void *p, size_t size)
{
	free(p);
	if (p)
		if (size)
			return ;
}

static void		**reconstruct_path(t_hashtable *camefrom, t_algo_input *algo,
		void *goal)
{
	void	**path;
	size_t	path_length;
	void	*current;
	size_t	i;
	void	*last;

	path_length = 1;
	current = goal;
	while ((current = ft_hashtable_search(camefrom, algo->serialize(current))))
		path_length++;
	path = (void**)ft_memalloc((path_length + 1) * sizeof(void*));
	i = 1;
	current = goal;
	path[0] = goal;
	last = goal;
	while ((current = ft_hashtable_search(camefrom, algo->serialize(current))))
	{
		path[i] = current;
		ft_hashtable_sub(camefrom, algo->serialize(last));
		++i;
		last = current;
	}
	return (path);
}

static void		process_neighbor(t_algo_data *data, t_algo_input *algo,
		void *neighbor, void *current)
{
	size_t	tg;

	tg = (size_t)ft_hashtable_search(data->gscore,
			algo->serialize(current)) + 1;
	if (tg < (size_t)ft_hashtable_search(data->gscore,
				algo->serialize(neighbor)))
	{
		ft_hashtable_add(data->camefrom, algo->serialize(neighbor),
				ft_strdup(current));
		ft_hashtable_add(data->gscore, algo->serialize(neighbor), (void*)tg);
		ft_hashtable_add(data->fscore, algo->serialize(neighbor),
				(void*)(tg + algo->heuristic(neighbor)));
		if (!ft_lst_exist(data->openset, neighbor, algo->cmp))
			ft_lst_append(&(data->openset),
					ft_lstnew_no_copy(ft_strdup(neighbor), sizeof(void*)));
	}
	free(neighbor);
}

static void		*astar_loop(t_algo_data *data, t_algo_input *algo,
		t_algo_output *out)
{
	size_t	i;
	void	*current;
	void	**neighbors;
	t_list	*save;

	i = 0;
	current = data->openset->content;
	if (!algo->goal_p && algo->goal_f(current))
		return (current);
	else if (algo->goal_p && !algo->cmp(current, algo->goal_p))
		return (current);
	neighbors = algo->neighbors(current);
	while (neighbors[i])
	{
		process_neighbor(data, algo, neighbors[i], current);
		++i;
	}
	free(neighbors);
	save = data->openset->next;
	ft_lstdelone(&(data->openset), free_p);
	data->openset = save;
	out->otime = ft_max(out->otime, ft_lst_size(data->openset));
	out->osize = ft_max(out->osize, ft_hashtable_size(data->camefrom));
	return (0);
}

t_algo_output	ft_astar(void *start, t_algo_input *algo)
{
	t_algo_data		data;
	void			**path;
	t_algo_output	out;

	ft_bzero(&out, sizeof(t_algo_output));
	data.openset = ft_lstnew_no_copy(start, sizeof(start));
	data.camefrom = ft_hashtable_new(10000, NULL);
	data.gscore = ft_hashtable_new(10000, (void*)-1);
	data.fscore = ft_hashtable_new(10000, (void*)-1);
	ft_hashtable_add(data.gscore, algo->serialize(start),
			(void*)algo->heuristic(start));
	while (data.openset)
	{
		if ((path = astar_loop(&data, algo, &out)))
		{
			out.path = reconstruct_path(data.camefrom, algo, path);
			ft_hashtable_clean(data.camefrom);
			ft_hashtable_free(data.gscore);
			ft_hashtable_free(data.fscore);
			ft_lstdel(&(data.openset->next), free_p);
			free(data.openset);
			return (out);
		}
	}
	return (out);
}
