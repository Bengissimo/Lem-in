/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:47:53 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/30 17:48:19 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	del_fn(void *content, size_t size)
{
	if (content)
		free(content);
	size = 0;
}

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
