/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:33:40 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/04 20:32:26 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_nodes(char **room_lines, t_room *room)
{
	room->in = create_node(room_lines, 1);
	room->out = create_node(room_lines, 0);
	room->in->source = room;
	room->out->source = room;
	append_edge(room->in, create_edge(room->out));
}

static int	get_rooms(t_farm *farm, char *line)
{
	char	**room_lines;
	t_room	*room;

	if (!farm->flag.rooms_done && !is_char_in_str('-', line))
	{
		room_lines = get_room_lines(&line, farm);
		if (room_lines == NULL)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
		if (is_in(farm->hashmap, room_lines[0]))
			error_free_split_line(farm, NULL, &line, ERR_DBL_ROOM);
		room = create_room(room_lines);
		append_room(farm, room);
		set_nodes(room_lines, room);
		free_split(&room_lines);
		return (1);
	}
	return (0);
}

static int	get_links(t_farm *farm, char *line)
{
	if (is_char_in_str('-', line))
	{
		farm->flag.rooms_done = 1;
		if (farm->rooms.head == NULL)
			error_free_split_line(farm, NULL, &line, ERR_ROOM);
		if (get_link(farm, &line))
		{
			farm->flag.is_links = 1;
			return (1);
		}
	}
	if (farm->flag.rooms_done == 1 && get_room_lines(&line, farm))
		error_free_split_line(farm, NULL, &line, ERR_ROOM_AFT_LINK);
	return (0);
}

int	get_rooms_links(t_farm *farm, char *line)
{
	if (get_rooms(farm, line))
		return (1);
	if (get_links(farm, line))
		return (1);
	return (0);
}
