/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:03:54 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/29 10:17:53 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_room	*find_room(t_farm *farm, char *name)
{
	t_list	*curr;
	t_room	*room;

	curr = farm->rooms;
	while (curr)
	{
		room = curr->content;
		if (ft_strequ(room->name, name))
			return (room);
		curr = curr->next;
	}
	return (NULL);
}

static int	append_link(t_room *room0, t_room *room1)
{
	t_list	*link;

	link = lstnew_pointer(room1);
	if (!link)
	{
		ft_memdel((void **)&link);
		return (0);
	}
	ft_lstappend(&room0->linked_rooms, link);
	return (1);
}

void	make_adj_list(t_farm *farm, char **line)
{
	char	**names;
	t_room	*room0;
	t_room	*room1;

	names = ft_strsplit(*line, '-');
	if (!names)
		error_free_split_line(farm, &names, line);
	room0 = find_room(farm, names[0]);
	if (!room0)
		error_free_split_line(farm, &names, line);
	room1 = find_room(farm, names[1]);
	if (!room1)
		error_free_split_line(farm, &names, line);
	if (!append_link(room0, room1))
		error_free_split_line(farm, &names, line);
	if (!append_link(room1, room0))
		error_free_split_line(farm, &names, line);
	free_split(&names);
}
