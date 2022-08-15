/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/15 11:20:13 by bkandemi         ###   ########.fr       */
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

int	hashmap_node_set(t_list **hashmap_node, t_node *node)
{
	t_list			*new;
	unsigned long	key;

	key = hash(node->name, 128);
	new = lstnew_pointer((void *)node);
	if (!new)
		return (0);
	ft_lstappend(&hashmap_node[key], new);
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

t_node	*hashmap_node_get(t_list **hashmap_node, char *name)
{
	unsigned long	key;
	t_list			*curr;
	t_node			*the_node;

	key = hash(name, 128);
	curr = hashmap_node[key];
	while (curr)
	{
		the_node = curr->content;
		if (ft_strequ(the_node->name, name))
			return (the_node);
		curr = curr->next;
	}
	return (NULL);
}

void	free_hashmap(t_list **hashmap)
{
	size_t	i;

	i = 0;
	while (i < 128)
	{
		if (hashmap[i])
		{
			lstdel(&hashmap[i]);
		}
		i++;
	}
	free(hashmap);
}

/*void	free_hashmap_node(t_list **hashmap_node)
{
	size_t	i;

	i = 0;
	while (i < 128)
	{
		if (hashmap_node[i])
		{
			lstdel(&hashmap_node[i]);
		}
		i++;
	}
	free(hashmap_node);
}*/
