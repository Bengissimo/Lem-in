/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/08/16 15:28:38 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	lstdel(t_list **alst)
{
	t_list	*curr;
	t_list	*next;

	if (!alst || !*alst)
		return ;
	curr = *alst;
	while (curr)
	{
		next = curr->next;
		if (curr->content_size)
			free(curr->content);
		free(curr);
		curr = next;
	}
	*alst = NULL;
}

static void	del_rooms(void *content, size_t size)
{
	t_room *the_room;

	the_room = content;
	ft_strdel(&the_room->name);
	if (the_room->in)  //node_in
	{
		ft_strdel(&the_room->in->name);
		lstdel(&the_room->in->edges);
		ft_memdel((void **)&the_room->in);
	}
	if (the_room->out)  //node_out
	{
		ft_strdel(&the_room->out->name);
		lstdel(&the_room->out->edges);
		ft_memdel((void **)&the_room->out);
	}
	ft_memdel((void **)&the_room);
	size++;
}

void	free_farm(t_farm *farm)
{
	ft_lstdel(&farm->rooms, del_rooms);
	lstdel(&farm->links);
	free_hashmap(farm->hashmap);
}

void	error(t_farm *farm)
{
	//free_algo
	free_farm(farm);
	ft_putendl_fd("Error", 2);
	exit(1);
}

void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	ft_memdel((void *)str);
}

void	error_free_split_line(t_farm *farm, char ***str, char **line)
{
	free_split(str);
	ft_strdel(line);
	error(farm);
}
