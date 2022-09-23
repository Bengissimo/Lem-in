/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/23 19:06:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// might be organised better, to do later

/*static void	init_start_end_nodes(t_farm *farm, int start_flag, t_room *room, t_node *node)
{
	if (start_flag)
	{
		farm->start = room;
		room->out = node; // start room has just out node
		room->out->source = room;
	}
	else
	{
		farm->end = room;
		room->in = node; //end room has just in node
		room->in->source = room;
	}
}*/

static void	init_start_end_nodes(t_farm *farm, int start_flag, t_room *room, t_node *node_in, t_node *node_out)
{
	if (start_flag)
	{
		farm->start = room;
		room->out = node_out;
		room->in = node_in;
		room->out->source = room;
		room->in->source = room;
	}
	else
	{
		farm->end = room;
		room->out = node_out;
		room->in = node_in;
		room->out->source = room;
		room->in->source = room;
	}
	
}

/*static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room *room;
	t_node *node;

	str = get_room_lines(line, farm);  
	if (!str)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	room = create_room(str);
	node = create_node(str, 2);
	free_split(&str);
	if (!room || !node)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	init_start_end_nodes(farm, start_flag, room, node);
	if (!append_room(farm, room))
		error_free_split_line(farm, NULL, line, "Memory allocation");
}*/

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room *room;
	t_node *node_in;
	t_node *node_out;

	str = get_room_lines(line, farm);  
	if (!str)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	room = create_room(str);
	node_in = create_node(str, 1);
	node_out = create_node(str, 0);
	free_split(&str);
	if (!room || !node_in || !node_out)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	init_start_end_nodes(farm, start_flag, room, node_in, node_out);
	if (!append_room(farm, room))
		error_free_split_line(farm, NULL, line, "Memory allocation");
}

int	is_command(t_farm *farm, char **line)
{
	int	start_flag;

	start_flag = 0;
	if (!(ft_strequ("##start", *line) || ft_strequ("##end", *line)))
		return (0);
	if (ft_strequ("##start", *line) && farm->start)
		error_free_split_line(farm, NULL, line, "More than one start");
	if (ft_strequ("##end", *line) && farm->end)
		error_free_split_line(farm, NULL, line, "More than one end");
	if (ft_strequ("##start", *line))
		start_flag = 1;
	ft_strdel(line);
	if (get_next_line(0, line) != 1)
		error_free_split_line(farm, NULL, line, "Fail to read a line");
	get_command(farm, line, start_flag);
	save_input(farm, line);
	return (1);
}
