/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/10 11:02:33 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void del_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void q_push(t_list **queue, t_room *the_room)
{
	t_list *to_push;
	to_push = lstnew_pointer(the_room);
	if (!to_push)
		return ;
	ft_lstappend(queue, to_push);
}

t_room *q_pop(t_list **queue)
{
	t_room *the_room;

	if (!queue)
		return (NULL);
	the_room = (*queue)->content;
	ft_lstdelelem(queue, 0, del_fn);
	return (the_room);
}

static void print_shortest_path(t_farm *farm)
{
	t_room *the_room;

	the_room = farm->end;
	while (the_room)
	{
		printf("%s - ", the_room->name);
		the_room = the_room->parent;
	}
	printf("\n\n");
}

void bfs(t_farm *farm)
{
	t_room *the_room;
	t_list *links;
	t_room *child;
	int the_end;

	t_room *temp;
	temp = farm->start;
	q_push(&farm->queue, farm->start);
	farm->start->visited = TRUE;
	while (farm->queue)
	{
		the_room = q_pop(&farm->queue);
		if (the_room == farm->end)
		{
			the_end = TRUE;
			break ;
		}
		links = the_room->linked_rooms;
		while (links)
		{
			child = links->content;
			if (!child->visited)
			{
				child->parent = the_room;
				q_push (&farm->queue, child);
				child->visited = TRUE;
			}
			links = links->next;
		}
	}
	print_shortest_path(farm);
	/*if (the_end == FALSE)
		return (error);
	*/
}



/*
FordFulkerson(Graph G, Node s, Node t):
    Initialize flow of all edges e to 0.
    while(there is augmenting path(P) from s to t 
    in the residual graph):
        Find augmenting path between s and t.
        Update the residual graph.
        Increase the flow.
    return
*/