/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:15 by ykot              #+#    #+#             */
/*   Updated: 2022/07/29 16:02:57 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	check_int(const char *str)
{
	size_t	i;
	size_t	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	if (len > 11 || (str[0] != '-' && len > 10))
		return (0);
	else if (len == 11 && str[0] == '-')
	{
		str++;
		if (ft_strcmp(str, "2147483648") > 0)
			return (0);
	}
	else if (len == 10 && ft_strcmp(str, "2147483647") > 0)
		return (0);
	i = -1;
	if (str[0] == '-')
		i = 0;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

/*static char	*link_room_names(const char *room1, const char *room2)
{
	char	*temp;
	char	*dst;

	temp = ft_strjoin(room1, "-");
	dst = ft_strjoin(temp, room2);
	ft_strdel(&temp);
	return (dst);
}*/

/*int	is_link_valid(t_list *rooms, char *line)
{
	t_list	*i;
	t_list	*j;
	char	*check;
	t_room *room_i;
	t_room *room_j;
	
	i = rooms;
	while (i)
	{
		j = rooms;
		while (j)
		{
			if (i != j)
			{
				room_i = i->content;
				room_j = j->content;
				check = link_room_names(room_i->name, room_j->name);
				if (ft_strequ(check, line))
				{
					ft_strdel(&check);
					return (TRUE);
				}
				ft_strdel(&check);
			}
			j = j->next;
		}
		i = i->next;
	}
	return (FALSE);
}*/
static int	append_link(t_room *room0, t_room *room1)
{
	t_list	*link;

	link = lstnew_pointer(room1);
	if (!link)
	{
		ft_memdel((void **)&link);
		return (0);
	}
	ft_lstappend(&room0->linked_rooms, link);
	return (1);
}

int is_link_OK(t_farm *farm, char *line)
{
	size_t i;
	char *first;
	char *second;
	t_room *room1;
	t_room *room2;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			first = ft_memalloc(i + 1);
			ft_strncpy(first, line, i);
			second = line + i + 1;
			printf("first %s second %s\n", first, second);
			room1 = find_room_in_hashmap(farm, first);
			room2 = find_room_in_hashmap(farm, second);
			if (room1 && room2)
			{
				if (!append_link(room1, room2))
					return (FALSE);
				if (!append_link(room2, room1))
					return (FALSE);
				ft_strdel(&first);
				return (TRUE);
			}
			ft_strdel(&first);
		}
		i++;
	}
	return (FALSE);
}

int	is_char_in_str(char c, char *str)
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
