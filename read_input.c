/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/08/01 11:17:46 by bkandemi         ###   ########.fr       */
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

	room_lines = get_room(line);
	if (room_lines && !farm->rooms_done)
	{
		room = create_room(room_lines);
		append_room_to_list(farm, room);
		farm->num_rooms++;
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
			continue ;
		if (is_command(farm, &line))
			continue ;
		if (get_rooms_links(farm, line))
			continue ;
		error(farm);
	}
}
