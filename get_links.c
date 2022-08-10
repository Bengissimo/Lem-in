/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/10 13:54:48 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	append_link_name(t_farm *farm, char *line)
{
	t_list	*link_name;

	link_name = ft_lstnew(line, ft_strlen(line) + 1);
	if (!link_name)
		return (0);
	ft_lstappend(&farm->links, link_name);
	return (1);
}

static int	append_to_adj_list(t_room *room1, t_room *room2)  // rooms will be changed to nodes here
{
	t_list	*link;

	link = lstnew_pointer(room2);
	if (!link)
		return (0);
	ft_lstappend(&room1->linked_rooms, link);
	return (1);
}

static int	make_adj_list(t_room *room1, t_room *room2) // modify this to put room_in room_out links
{
	if (!append_to_adj_list(room1, room2))
		return (FALSE);
	if (!append_to_adj_list(room2, room1))
		return (FALSE);
	return (TRUE);
}

int	parse_links(t_farm *farm, char *line)
{
	size_t	i;
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			first = ft_memalloc(i + 1);
			if (!first)
				return (FALSE);
			ft_strncpy(first, line, i);
			second = line + i + 1;
			room1 = hashmap_get(farm, first);
			room2 = hashmap_get(farm, second);
			ft_strdel(&first);
			if (room1 && room2 && make_adj_list(room1, room2))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	get_link(t_farm *farm, char **line)
{
	if (!parse_links(farm, *line))  //adj_list is created here now
		return (0);
	append_link_name(farm, *line);
	return (1);
}
