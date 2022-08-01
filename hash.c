/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/01 11:24:05 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

unsigned long hash(const char *s, unsigned long m)
{
	unsigned long	h;
	unsigned const char	*us;
	/* cast s to unsigned const char * */
	/* this ensures that elements of s will be treated as having values >= 0 */
	us = (unsigned const char *) s;
	h = 0;
	while(*us != '\0')
	{
		h = (h * 256 + *us) % m;
		us++;
	}
	return h;
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
