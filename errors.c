/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/07/26 10:37:52 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	lstdel(t_list **alst)
{
	t_list	*curr;
	t_list	*next;

	if (!alst || !*alst)
		return ;
	curr = *alst;
	while (curr)
	{
		next = curr->next;
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
	lstdel(&the_room->linked_rooms);
	ft_memdel((void **)&the_room);
	size++;
}

void free_farm(t_farm *farm)
{
	ft_lstdel(&farm->rooms, del_rooms);
}

void	error(t_farm *farm)
{
	free_farm(farm);
	ft_putendl_fd("Error", 2);
	exit(1);
}

void	free_split(char ***str)
{
	size_t	i;

	i = -1;
	while ((*str)[++i])
		ft_strdel(&((*str)[i]));
	ft_memdel((void *)str);
}

void	error_free_split_line(t_farm *farm, char ***str, char **line)
{
	free_split(str);
	ft_strdel(line);
	error(farm);
}
