/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/12 12:30:25 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*static void del_fn(void *content, size_t size)
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

static void print_shortest_path(t_farm *farm, t_algo *algo)
{
	t_node *the_node;

	the_node = farm->end->in;
	while (the_node)
	{
		printf("%s - ", the_node->name);
		the_node = (algo->adj_list)->content->parent;
	}
	printf("\n\n");
}*/

/*
void bfs(t_farm *farm, t_algo *algo)
{
	t_node *the_node;
	t_list *edges;
	t_node *child;
	t_edge *the_edge;
	int the_end;

	q_push(&algo->queue, farm->start);
	farm->start->out->visited = TRUE;
	while (algo->queue)
	{
		the_node = q_pop(&algo->queue);
		if (the_node == farm->end->in)
		{
			the_end = TRUE;
			break ;
		}
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (!child->visited)
			{
				child->parent = the_node;
				q_push (&algo->queue, child);
				child->visited = TRUE;
			}
			edges = edges->next;
		}
	}
	print_shortest_path(farm);
	if (the_end == FALSE)
		return (error);
	
}*/

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