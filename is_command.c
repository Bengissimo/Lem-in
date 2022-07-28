/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/28 11:27:38 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;
	t_room *room;

	str = get_room(*line);  
	if (!str)
		error_free_split_line(farm, NULL, line);
	room = create_room(str);  //free room when when you are done 
	if (!room)
		error_free_split_line(farm, NULL, line);
	farm->num_rooms++;
	if (start_flag)
		farm->start = room;
	else
		farm->end = room;
	if (!append_room_to_list(farm, room))
		error_free_split_line(farm, NULL, line);
	//free_split(&str);
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
