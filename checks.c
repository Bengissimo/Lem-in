/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:15 by ykot              #+#    #+#             */
/*   Updated: 2022/07/18 10:11:43 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	check_int(const char *str) //name suggestion: is_int
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

int	is_room_name_valid(char *line)
{
	if (line[0] == 'L' || line[0] == '#')
		return (FALSE);
	return (TRUE);
}

static char	*link_room_names(const char *room1, const char *room2)
{
	char	*temp;
	char	*dst;

	temp = ft_strjoin(room1, "-");
	dst = ft_strjoin(temp, room2);
	ft_strdel(&temp);
	return (dst);
}

/*did it for list but we can update the struct later*/
int	is_link_valid(t_list *rooms, char *line)
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
					return (1);
				}
				ft_strdel(&check);
			}
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}
