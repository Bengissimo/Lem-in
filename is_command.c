/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/04 14:49:52 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_start_end_nodes(t_farm *farm, int start_flag,
								t_room *room, t_node *node)
{
	if (start_flag)
	{
		farm->start = room;
		room->out = node;
		room->out->source = room;
	}
	else
	{
		farm->end = room;
		room->in = node;
		room->in->source = room;
	}
}

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room	*room;
	t_node	*node;

	str = get_room_lines(line, farm);
	if (!str)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	room = create_room(str);
	node = create_node(str, 2);
	free_split(&str);
	if (!room || !node)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	init_start_end_nodes(farm, start_flag, room, node);
	if (!append_room(farm, room))
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
}

int	is_command(t_farm *farm, char **line)
{
	int	start_flag;

	start_flag = 0;
	if (!(ft_strequ("##start", *line) || ft_strequ("##end", *line)))
		return (0);
	if (ft_strequ("##start", *line) && farm->start)
		error_free_split_line(farm, NULL, line, ERR_EXT_START);
	if (ft_strequ("##end", *line) && farm->end)
		error_free_split_line(farm, NULL, line, ERR_EXT_END);
	if (ft_strequ("##start", *line))
		start_flag = 1;
	ft_strdel(line);
	farm->flag.read_lines++;
	if (get_next_line(0, line) != 1)
		error_free_split_line(farm, NULL, line, ERR_READ);
	if (*line[0] == '#' || is_char_in_str('-', *line))
		error_free_split_line(farm, NULL, line, ERR_AFT_COMMAND);
	if (ft_strlen(*line) == 0 && enough_data(farm, line))
		err_empty_line(farm);
	get_command(farm, line, start_flag);
	save_input(farm, line);
	farm->flag.read_lines--;
	return (1);
}
