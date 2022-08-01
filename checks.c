/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:15 by ykot              #+#    #+#             */
/*   Updated: 2022/08/01 11:51:27 by bkandemi         ###   ########.fr       */
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

static int	make_adj_list(t_room *room1, t_room *room2)
{
	t_list	*link;

	link = lstnew_pointer(room2);
	if (!link)
	{
		ft_memdel((void **)&link);
		return (0);
	}
	ft_lstappend(&room1->linked_rooms, link);
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
			//printf("first %s second %s\n", first, second);
			room1 = hashmap_get(farm, first);
			room2 = hashmap_get(farm, second);
			if (room1 && room2)
			{
				if (!make_adj_list(room1, room2))
					return (FALSE);
				if (!make_adj_list(room2, room1))
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
