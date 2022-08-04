/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/01 14:38:37 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

unsigned long	hash(const char *s, unsigned long m)
{
	unsigned long		key;
	unsigned const char	*us;

	us = (unsigned const char *) s;
	key = 0;
	while (*us != '\0')
	{
		key = (key * 256 + *us) % m;
		us++;
	}
	return (key);
}

int	hashmap_set(t_farm *farm, t_room *room)
{
	t_list			*new;
	unsigned long	key;

	key = hash(room->name, 128);
	new = lstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_lstappend(&farm->hashmap[key], new);
	return (1);
}

t_room	*hashmap_get(t_farm *farm, char *name)
{
	unsigned long	key;
	t_list			*curr;
	t_room			*the_room;

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

void	free_hashmap(t_farm *farm)
{
	size_t	i;

	i = 0;
	while (i < 128)
	{
		if (farm->hashmap[i])
		{
			lstdel(&farm->hashmap[i]);
		}
		i++;
	}
	free(farm->hashmap);
}
