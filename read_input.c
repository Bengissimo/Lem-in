/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/09/30 15:53:05 by bkandemi         ###   ########.fr       */
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
	t_dblist	*tempptr;
	char		*str;

	str = ft_strdup(*line);
	if (str == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	tempptr = ft_dblstnew_pointer(str);
	if (tempptr == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	ft_dynlstappend(&(farm->input_lines), tempptr);
	farm->flag.read_lines++;
}

static void	ant_num_checks(t_farm *farm, char **line, int *num)
{
	char	**str;

	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		error_free_split_line(farm, NULL, line, ERR_MEM_ALLOC);
	if (str[0] && str[1] != NULL)
		error_free_split_line(farm, &str, line, ERR_ANT_CHAR);
	free_split(&str);
	if (check_int(*line) == 0)
		error_free_split_line(farm, NULL, line, ERR_ANT_NOT_INT);
	*num = ft_atoi(*line);
	if (*num <= 0)
		error_free_split_line(farm, NULL, line, ERR_ANT_NB);
}

static void	get_ant_num(t_farm *farm, char **line)
{
	int		num;

	while (TRUE)
	{
		ft_strdel(line);
		if (get_next_line(0, line) != 1)
		{
			if (farm->input_lines.head == NULL)
				err_nolines(farm, ERR_INPUT);
			else
				err_empty_line(farm);
		}
		if (ft_strlen(*line) == 0)
			err_empty_line(farm);
		save_input(farm, line);
		if (is_comment(*line))
			continue ;
		ant_num_checks(farm, line, &num);
		farm->num_ants = num;
		return ;
	}
}

static int	check_gnl(t_farm *farm, int gnl, char **line)
{
	if (gnl == -1)
		error(farm, "Fail to read a line");
	if (gnl == 0 && farm->start && farm->end)
	{
		ft_strdel(line);
		return (1);
	}
	if (gnl == 0)
	{
		farm->flag.no_errlines = 1;
		if (farm->start == NULL && farm->end == NULL)
			error(farm, "No start and end");
		if (farm->start == NULL)
			error(farm, "No start");
		if (farm->end == NULL)
			error(farm, "No end");
	}
	return (0);
}

int	get_rooms_links(t_farm *farm, char *line)
{
	char	**room_lines;
	t_room	*room;

	if (!farm->flag.rooms_done && !is_char_in_str('-', line))
	{
		room_lines = get_room_lines(&line, farm);
		if (room_lines == NULL)
			error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
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
		farm->flag.rooms_done = 1;
		if (farm->rooms.head == NULL)
			error_free_split_line(farm, NULL, &line, ERR_ROOM);
		if (get_link (farm, &line))
		{
			farm->flag.is_links = 1;
			return (1);
		}
	}
	return (0);
}

int	enough_data(t_farm *farm, char **line)
{
	if (farm->start && farm->end && farm->rooms.head && farm->flag.is_links)
	{
		ft_dynlstdelelem(&farm->input_lines, farm->input_lines.size - 1, del_dblfn);
		ft_strdel(line);
		return (1);
	}
	else if (farm->flag.is_links == 0)
		error(farm, ERR_LINK);
	else
	{
		farm->flag.no_errlines = 1;
		error(farm, ERR_MAP);
	}
	return (0);
}

void	err_nolines(t_farm *farm, char *str)
{
	farm->flag.no_errlines = 1;
	error(farm, str);
}

void	err_empty_line(t_farm *farm)
{
	farm->flag.read_lines++;
	error(farm, ERR_EMP_LINE);
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
		if (check_gnl(farm, gnl, &line))
			return ;
		if (ft_strlen(line) == 0 && !enough_data(farm, &line))
			err_empty_line(farm);
		save_input(farm, &line);
		if (is_comment(line))
			continue ;
		if (is_command(farm, &line))
			continue ;
		if (get_rooms_links(farm, line))
			continue ;
		if (enough_data(farm, &line))
			return ;
	}
	ft_strdel(&line);
}
