/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_link_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:15:56 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/15 10:20:24 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char *link_room_names(const char *room1, const char *room2)
{
	char *temp;
	char *dst;
	
	temp = ft_strjoin(room1, "-");
	dst = ft_strjoin(temp, room2);
	ft_strdel(&temp);
	return (dst);
}

/*did it for list but we can update the struct later*/
int is_link_valid(t_list *rooms, char *line)
{
	t_list *i;
	t_list *j;
	char *check;

	i = rooms;
	while (i)
	{
		j = rooms;
		while (j)
		{
			if (i->next != j->next)
			{
				check = link_room_names(i->content, j->content);
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

/*
while reading links
if (!is_link_valid)
	return (exit fn);
*/
