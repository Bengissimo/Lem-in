/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:00:16 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/30 22:54:29 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_room_name_valid(char *line)
{
	if (line[0] == 'L')
		return (FALSE);
	return (TRUE);
}
/*
static int is_room_exist(t_farm *farm, char *str)
{
	t_dblist *temp;

	temp = farm->rooms.head;
	while (temp)
	{
		if (ft_strequ(str, temp->content))
		temp = temp->next;
	}
}*/

char	**get_room_lines(char **line, t_farm *farm)
{
	char	**str;

	if (ft_strlen(*line) == 0)
		return (NULL);
	str = ft_strsplit(*line, ' ');
	if (str == NULL)
		return (NULL);
	if (!is_room_name_valid(str[0]))
		error_free_split_line(farm, NULL, line, ERR_ROOM_L);
	if ((check_int(str[0]) && str[1] == NULL))
		error_free_split_line(farm, NULL, line, ERR_DBL_ANT);
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
	{
		if (str[3])
			error_free_split_line(farm, NULL, line, ERR_COORD_CHAR);
		if (check_int(str[0]) && str[1] == NULL)
			error_free_split_line(farm, NULL, line, ERR_DBL_ANT);
		error_free_split_line(farm, NULL, line, ERR_COORD_INT);
	}
	/*if (is_room_exist(farm, str[0]))
		error_free_split_line(farm, NULL, line, "Duplicate room");*/
	return (str);
}

/*t_list	*ft_lstnew_pointer(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)ft_memalloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	return (lstnew);
}*/

t_room	*create_room(char **str)
{
	t_room	*room;

	if (!str)
		return (NULL);
	room = ft_memalloc(sizeof(*room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(str[0]);
	room->coord.x = ft_atoi(str[1]);
	room->coord.y = ft_atoi(str[2]);
	return (room);
}

int	append_room(t_farm *farm, t_room *room)
{
	t_dblist	*new;

	new = ft_dblstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_dynlstappend(&farm->rooms, new);
	if (!hashmap_set(farm->hashmap, room->name, room))
		return (0);
	return (1);
}

/*
*	if the node is in, is_in_or_out: 1,
*	if the noode is out, is_in_or_out: 0,
*	if the node is start or end, is_in_or_out: 2
*/

t_node	*create_node(char **str, int is_in_or_out)
{
	t_node	*node;

	if (!str)
		return (NULL);
	node = (t_node *)ft_memalloc(sizeof(*node));
	if (is_in_or_out == 1)
		node->name = ft_strjoin(str[0], "_in");
	else if (is_in_or_out == 0)
		node->name = ft_strjoin(str[0], "_out");
	else
		node->name = ft_strdup(str[0]);
	return (node);
}
