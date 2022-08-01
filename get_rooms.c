/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:00:16 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/01 11:20:34 by bkandemi         ###   ########.fr       */
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
	if (!is_room_name_valid(str[0]))
	{
		free_split(&str);
		return (NULL);
	}
	if (!(check_int(str[1]) && check_int(str[2]) && !str[3]))
	{
		free_split(&str);
		return (NULL);
	}
	return (str);
}

t_list	*lstnew_pointer(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
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
	free_split(&str);
	return (room);
}

int	append_room_to_list(t_farm *farm, t_room *room)
{
	t_list *new;

	new = lstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_lstappend(&farm->rooms, new);
	if (!hashmap_set(farm, room))
		return (0);
	return (1);
}

int hashmap_set(t_farm *farm, t_room *room)
{
	t_list *new;
	unsigned long key;

	key = hash(room->name, 128);
	new = lstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_lstappend(&farm->hashmap[key], new);
	return (1);
}


t_room *find_room_in_hashmap(t_farm *farm, char *name)
{
	unsigned long key;
	t_list *curr;
	t_room *the_room;
	
	key = hash(name, 128);
	curr = farm->hashmap[key];
	while (curr)
	{
		the_room = curr->content;
		if (ft_strequ(the_room->name, name))
			return (the_room);
		curr = curr->next;
	}
	return (NULL);
}
