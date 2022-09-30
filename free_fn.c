/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:46:05 by ykot              #+#    #+#             */
/*   Updated: 2022/09/30 19:13:08 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	del_dblfn(void *content)
{
	if (content)
		free(content);
}

void	null_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void	del(void *content, size_t size)
{
	if (content)
		free(content);
	size = 0;
}

static void	del_rooms(void *content)
{
	t_room	*the_room;

	the_room = content;
	ft_strdel(&the_room->name);
	if (the_room->in)
	{
		ft_strdel(&the_room->in->name);
		ft_dblstdel(&the_room->in->edges, del_dblfn);
		ft_memdel((void **)&the_room->in);
	}
	if (the_room->out)
	{
		ft_strdel(&the_room->out->name);
		ft_dblstdel(&the_room->out->edges, del_dblfn);
		ft_memdel((void **)&the_room->out);
	}
	ft_memdel((void **)&the_room);
}

void	free_path_set(t_list **path_set, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (path_set[i])
		{
			ft_lstdel(&path_set[i], null_fn);
		}
		i++;
	}
	free(path_set);
}

void	free_farm(t_farm *farm)
{
	ft_dblstdel(&farm->rooms, del_rooms);
	ft_dblstdel(&farm->input_lines, del_dblfn);
	free_path_set(farm->option1, farm->index.ind1);
	free_path_set(farm->option2, farm->index.ind2);
	free_hashmap(farm->hashmap);
}
