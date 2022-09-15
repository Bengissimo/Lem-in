/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/09/15 14:59:14 by ykot             ###   ########.fr       */
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

void	save_input(t_farm *farm, char **line)
{
	t_dlist	*tempptr;
	char	*str;
	
	str = ft_strdup(*line);
	if (str == NULL)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	tempptr = ft_dlstnew_pointer(str);
	if (tempptr == NULL)
		error_free_split_line(farm, NULL, line, "Memory allocation");
	ft_dynlstappend(&(farm->input_lines), tempptr);
}

static void	get_ant_num(t_farm *farm, char **line)
{
	int		num;

	while (TRUE)
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
			error(farm, "Fail to read a line");
		if (is_comment(*line))
		{
			//ft_lstappend(&farm->comments, ft_lstnew(line, ft_strlen(*line) + 1));
			continue ;
		}
		if (check_int(*line) == 0)
			error_free_split_line(farm, NULL, line, "The number of ants is not an integer");
		num = ft_atoi(*line);
		if (num <= 0)
			error_free_split_line(farm, NULL, line, "The number of ants less or equal to zero");
		save_input(farm, line);		
		farm->num_ants = num;
		return ;
	}
}

static int	check_gnl(t_farm *farm, int gnl)
{
	if (gnl == -1)
		error(farm, "Fail to read a line");
	if (gnl == 0 && farm->start && farm->end)
		return (1);
	if (gnl == 0)
		error(farm, "No start or end");
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

static int	enough_data(t_farm *farm)
{
	if (farm->start && farm->end && farm->rooms && farm->links)
		return (1);
	else
		error(farm, "Invalid map");
}

void	read_input(t_farm *farm)
{
	char	*line;
	int		gnl;

	line = NULL;
	get_ant_num(farm, &line);  //TO DO save if there is a comment in here!
	while (TRUE)
	{
		ft_strdel(&line);
		gnl = get_next_line(0, &line);
		if (check_gnl(farm, gnl))
			return ;
		save_input(farm, &line);
		if (is_comment(line))
		{
			//ft_lstappend(&farm->comments, ft_lstnew(line, ft_strlen(line) + 1));
			continue ;
		}
		if (is_command(farm, &line))
			continue ;
		if (get_rooms_links(farm, line))
			continue ;
		if (enough_data(farm))
			return ;
	}
}
