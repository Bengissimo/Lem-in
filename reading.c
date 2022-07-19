/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:25:04 by ykot              #+#    #+#             */
/*   Updated: 2022/07/19 12:09:43 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	get_ant_num(t_farm *farm)
{
	char	*line;

	line = NULL;
	while (TRUE)
	{
		if (get_next_line(0, &line) != 1)
			error(farm);
		if (is_comment(line))
		{
			ft_strdel(&line);
			continue;
		}
		if (check_int(line) == 0)
		{
			ft_strdel(&line);
			error(farm);
		}
		farm->num_ants = ft_atoi(line);
		ft_strdel(&line);
		return ;
	}
}

static void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		++i;
	}
	ft_memdel((void *)str);
}

static void	error_free_split_line(t_farm *farm, char ***str, char **line)
{
	free_split(str);
	ft_strdel(line);
	error(farm);	
}

static int get_link(t_farm *farm, char **line)
{
	t_list	*temp;
	
	if (!is_link_valid(farm->rooms, *line))
	{
		ft_strdel(line);
		error(farm);
	}
	temp = ft_lstnew(*line, sizeof(*line));
	if (temp == NULL)
	{
		ft_strdel(line);
		error(farm);
	}
	ft_lstappend(&farm->links, temp);
	return (1);
}

static int	is_char_in_str(char c, char *str)
{
	int	i;
	int	found;

	found = FALSE;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			found = TRUE;
			break ;
		}
		i++;
	}
	return (found);
}

static int	add_start_end_to_room_list(t_farm *farm)
{
	t_list *temp_start;
	t_list *temp_end;

	temp_end = ft_lstnew(&farm->end, sizeof(farm->end));
	if (temp_end == NULL)
		return (0);
	ft_lstadd(&farm->rooms, temp_end);
	temp_start = ft_lstnew(&farm->start, sizeof(farm->start));
	if (temp_start == NULL)
		return (0);
	ft_lstadd(&farm->rooms, temp_start);
	return (1);
}

static int	get_room(t_farm *farm, char **line)
{
	t_room	room;
	t_list	*temp;
	char	**str;
	
	if (ft_strlen(*line) == 0)   //this solved the seg fault in empty line
		error(farm);
	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		error_free_split_line(farm, &str, line);
	if (!is_room_name_valid(*line))
		error_free_split_line(farm, &str, line);
	if (!str[1] && is_char_in_str('-', str[0]))  //might be link, after link no rooms
	{
		/* add start and end to the rooms list */
		if (!add_start_end_to_room_list(farm))
			error_free_split_line(farm, &str, line);
		get_link(farm, line);
		free_split(&str);
		ft_strdel(line);
		return (0);
	}
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
		error_free_split_line(farm, &str, line);
	ft_bzero(&room, sizeof(room));
	room.name = ft_strdup(str[0]);
	room.coord.x = ft_atoi(str[1]);
	room.coord.y = ft_atoi(str[2]);
	temp = ft_lstnew(&room, sizeof(room));
	if (temp == NULL)
		error_free_split_line(farm, &str, line);
	ft_lstappend(&farm->rooms, temp);
	free_split(&str);
	return (1);
}

static void	get_command(t_farm *farm, char **line, int start_flag)
{
	char	**str;

	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		error_free_split_line(farm, &str, line);
	if (!is_room_name_valid(*line))
		error_free_split_line(farm, &str, line);
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
		error_free_split_line(farm, &str, line);
	if (start_flag)
	{
		farm->start.name = ft_strdup(str[0]);
		farm->start.coord.x = ft_atoi(str[1]);
		farm->start.coord.y = ft_atoi(str[2]);
	}
	else
	{
		farm->end.name = ft_strdup(str[0]);
		farm->end.coord.x = ft_atoi(str[1]);
		farm->end.coord.y = ft_atoi(str[2]);
	}
	free_split(&str);
}

static int	check_command(t_farm *farm, char **line)
{
	int	start_flag;

	start_flag = 0;
	if (!(ft_strequ("##start", *line) || ft_strequ("##end", *line)))
		return (0);
	if ((ft_strequ("##start", *line) && farm->start.name) ||
		(ft_strequ("##end", *line) && farm->end.name))
		error_free_split_line(farm, NULL, line);
	if (ft_strequ("##start", *line))
		start_flag = 1;
	ft_strdel(line);
	if (get_next_line(0, line) != 1)
		error_free_split_line(farm, NULL, line);
	get_command(farm, line, start_flag);
	return (1);
}

static int check_result(t_farm *farm, int result)
{
	if (result == -1)
		error(farm);
	if (result == 0 && farm->start.name && farm->end.name)
		return (1);
	if (result == 0)
		error(farm);
	return (0);
}

static void	get_rooms_link(t_farm *farm)
{
	char	*line;
	int		result;
	
	line = NULL;
	while (TRUE)
	{
		ft_strdel(&line);
		result = get_next_line(0, &line);
		if (check_result(farm, result))
			return ;
		if (is_comment(line))
			continue ;
		if (check_command(farm, &line))
			continue ;
		if (get_room(farm, &line))
			continue ;
		/*if (get_link(farm, &line))
			continue ;*/
	}
}

void	read_input(t_farm *farm)
{
	get_ant_num(farm);
	get_rooms_link(farm);
}
