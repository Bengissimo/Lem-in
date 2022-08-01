/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/31 23:12:00 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void del_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void q_push(t_list *queue, t_room *the_room)
{
	t_list *to_push;

	to_push = lstnew_pointer(the_room);
	ft_lstappend(&queue, to_push);
}

t_room *q_pop(t_list *queue)
{
	t_room *the_room;

	if (!queue)
		return (NULL);
	the_room = queue->content;
	ft_lstdelelem(&queue, 0, del_fn);
	return (the_room);
}

/*
bfs pseudo:
ft_bzero(queue);
q_push(queue, start_room);
while (queue)
{
	q_pop(queue);
	// when the_room poped add it to the path ??? this part depends on the algo
	while (the_room->linked_rooms && the_linked_room is not visited)
	{
		q_push(the_room->linked_rooms->content);
	}
	
}
*/
