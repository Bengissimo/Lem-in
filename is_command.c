/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/15 09:37:43 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// might be organised better, to do later

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room *room;
	t_node *node;

	str = get_room_lines(*line);  
	if (!str)
		error_free_split_line(farm, NULL, line);
	room = create_room(str);
	node = create_node(str, 2);
	free_split(&str);
	if (!room || !node)
		error_free_split_line(farm, NULL, line);
	if (start_flag)
	{
		farm->start = room;
		room->out = node; // start room has just out node
	}
	else
	{
		farm->end = room;
		room->in = node; //end room has just in node
	}
	if (!append_room(farm, room))
		error_free_split_line(farm, NULL, line);
}

int	is_command(t_farm *farm, char **line)
{
	int	start_flag;

	start_flag = 0;
	if (!(ft_strequ("##start", *line) || ft_strequ("##end", *line)))
		return (0);
	if ((ft_strequ("##start", *line) && farm->start) ||
		(ft_strequ("##end", *line) && farm->end))
		error_free_split_line(farm, NULL, line);
	if (ft_strequ("##start", *line))
		start_flag = 1;
	ft_strdel(line);
	if (get_next_line(0, line) != 1)
		error_free_split_line(farm, NULL, line);
	get_command(farm, line, start_flag);
	return (1);
}
