/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/12 16:07:06 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void del_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void q_push(t_list **queue, t_node *the_node)
{
	t_list *to_push;
	to_push = lstnew_pointer(the_node);
	if (!to_push)
		return ;
	ft_lstappend(queue, to_push);
}

t_node *q_pop(t_list **queue)
{
	t_node *the_node;

	if (!queue)
		return (NULL);
	the_node = (*queue)->content;
	ft_lstdelelem(queue, 0, del_fn);
	return (the_node);
}

static void print_shortest_path(t_room *end)
{
	t_node *the_node;

	the_node = end->in;
	while (the_node)
	{
		printf("%s - ", the_node->name);
		the_node = the_node->parent;
	}
	printf("\n\n");
}


int bfs(t_farm *farm)  // if it reaches to end return 1, else 0
{
	t_node *the_node;
	t_node *child;
	//t_edge *the_edge;
	t_list *queue;

	queue = NULL;
	q_push(&queue, farm->start->out);
	farm->start->out->visited = TRUE;
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
		{
			print_shortest_path(farm->end);
			return (1);
		}
		while (the_node->edges)
		{
			//the_edge = the_node->edges->content;
			child = ((t_edge *)(the_node->edges->content))->to;
			if (!child->visited)
			{
				child->parent = the_node;
				q_push (&queue, child);
				child->visited = TRUE;
			}
			the_node->edges = the_node->edges->next;
		}
	}
	return (0);
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