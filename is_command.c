/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/01 11:35:52 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room *room;

	str = get_room_lines(*line);  
	if (!str)
		error_free_split_line(farm, NULL, line);
	room = create_room(str);
	if (!room)
		error_free_split_line(farm, NULL, line);
	farm->num_rooms++;
	if (start_flag)
		farm->start = room;
	else
		farm->end = room;
	if (!append_room_to_list(farm, room))
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
