/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/03 22:09:05 by bkandemi         ###   ########.fr       */
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

typedef struct s_hash
{
	char	*name;
	void	*ptr;
}			t_hash;

/*int	hashmap_set(t_farm *farm, t_room *room)
{
	t_list			*new;
	unsigned long	key;

	key = hash(room->name, HASH);
	new = lstnew_pointer((void *)room);
	if (!new)
		return (0);
	ft_lstappend(&farm->hashmap[key], new);
	return (1);
}*/

int	hashmap_set(t_list **hashmap, char *str, void *ptr)
{
	t_list			*new;
	t_hash			*value;
	unsigned long	key;

	value = (t_hash *)ft_memalloc(sizeof(t_hash));
	value->name = str;
	value->ptr = ptr;
	key = hash(str, HASH);
	new = lstnew_pointer((void *)value);
	if (!new)
		return (0);
	ft_lstappend(&hashmap[key], new);
	return (1);
}

/*int	hashmap_node_set(t_list **hashmap_node, t_node *node)
{
	t_list			*new;
	unsigned long	key;

	key = hash(node->name, HASH);
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

	key = hash(name, HASH);
	curr = farm->hashmap[key];
	while (curr)
	{
		the_room = curr->content;
		if (ft_strequ(the_room->name, name))
			return (the_room);
		curr = curr->next;
	}
	return (NULL);
}*/

void	*hashmap_get(t_list **hashmap, char *str)
{
	unsigned long	key;
	t_list			*curr;
	t_hash			*the_value;

	key = hash(str, HASH);
	curr = hashmap[key];
	while (curr)
	{
		the_value = curr->content;
		if (ft_strequ(the_value->name, str))
			return (the_value->ptr);
		curr = curr->next;
	}
	return (NULL);
}

/*t_node	*hashmap_node_get(t_list **hashmap_node, char *name)
{
	unsigned long	key;
	t_list			*curr;
	t_node			*the_node;

	key = hash(name, HASH);
	curr = hashmap_node[key];
	while (curr)
	{
		the_node = curr->content;
		if (ft_strequ(the_node->name, name))
			return (the_node);
		curr = curr->next;
	}
	return (NULL);
}*/

void	free_hashmap(t_list **hashmap)
{
	size_t	i;

	i = 0;
	while (i < HASH)
	{
		if (hashmap[i])
		{
			ft_lstdel(&hashmap[i], del_fn);
		}
		i++;
	}
	free(hashmap);
}
