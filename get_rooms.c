/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:00:16 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/27 18:33:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	is_room_name_valid(char *line)
{
	if (line[0] == 'L')
		return (FALSE);
	return (TRUE);
}

char **get_room(char *line)
{
	char **str;

	if (ft_strlen(line) == 0)
		return (NULL);
	str = ft_strsplit(line, ' ');
	if (str == NULL)
		return (NULL);
	if (!is_room_name_valid(str[0]))  //now we are doing name and coord checks inside this function
		return (NULL);
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
		return (NULL);
	return (str);
}

t_room	*create_room(char **str)
{
	t_room *room;
	
	if (!str)
		return (NULL);;
	room = ft_memalloc(sizeof(*room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(str[0]);
	room->coord.x = ft_atoi(str[1]);
	room->coord.y = ft_atoi(str[2]);
	return (room);
}

int	append_room_to_list(t_farm *farm, t_room *room)
{
	t_list *new;

	new = ft_lstnew(room, sizeof(*room));
	if (!new)
		return (0);
	ft_lstappend(&farm->rooms, new);
	return (1);
}
