/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/08/16 11:11:45 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	is_comment(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static void	get_ant_num(t_farm *farm, char **line)
{
	while (TRUE)
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
			error(farm);
		if (is_comment(*line))
			continue ;
		if (check_int(*line) == 0)
			error_free_split_line(farm, NULL, line);
		farm->num_ants = ft_atoi(*line);
		return ;
	}
}

static int	check_gnl(t_farm *farm, int gnl)
{
	if (gnl == -1)
		error(farm);
	if (gnl == 0 && farm->start && farm->end)
		return (1);
	if (gnl == 0)
		error(farm);
	return (0);
}

int	get_rooms_links(t_farm *farm, char *line)
{
	char	**room_lines;
	t_room	*room;

	room_lines = get_room_lines(line);
	if (room_lines && !farm->rooms_done)
	{
		room = create_room(room_lines);
		room->in = create_node(room_lines, 1); //create room_in
		room->out = create_node(room_lines, 0); // create room_out
		room->in->source = room;
		room->out->source = room;
		append_room(farm, room);
		append_edge(room->in, create_edge(room->out)); // create the forward edge within the room
		free_split(&room_lines);
		return (1);
	}
	else if (is_char_in_str('-', line))
	{
		farm->rooms_done = 1;
		if (get_link (farm, &line))
			return (1);
	}
	return (0);
}

void	read_input(t_farm *farm)
{
	char	*line;
	int		gnl;

	line = NULL;
	get_ant_num(farm, &line);
	while (TRUE)
	{
		ft_strdel(&line);
		gnl = get_next_line(0, &line);
		if (check_gnl(farm, gnl))
			return ;
		if (is_comment(line))
		{
			ft_lstappend(&farm->comments, ft_lstnew(line, ft_strlen(line) + 1));
			continue ;
		}
		if (is_command(farm, &line))
			continue ;
		if (get_rooms_links(farm, line))
			continue ;
		error(farm);
	}
}
