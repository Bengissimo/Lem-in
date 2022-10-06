/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/06 16:57:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_edge(t_node *the_node, int flow,
	t_list **queue, t_list **visited)
{
	t_dblist	*edges;
	t_edge		*the_edge;
	t_node		*child;

	edges = the_node->edges.head;
	while (edges)
	{
		the_edge = edges->content;
		child = the_edge->to;
		if (the_edge->flow == flow && !is_in(visited, child->name))
		{
			child->parent = the_node;
			q_push (queue, child);
		}
		edges = edges->next;
	}
}

static void	find_edge_reset(t_node *the_node, t_list **queue, t_list **visited)
{
	t_dblist	*edges;
	t_edge		*the_edge;
	t_node		*child;

	edges = the_node->edges.head;
	while (edges)
	{
		the_edge = edges->content;
		the_edge->flow = 0;
		child = the_edge->to;
		if (!is_in(visited, child->name))
		{
			child->parent = the_node;
			q_push (queue, child);
		}
		edges = edges->next;
	}
}

int	bfs(t_farm *farm, int flow)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		hashmap_set(visited, the_node->name, the_node);
		find_edge(the_node, flow, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}

int	bfs_reset(t_farm *farm)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		hashmap_set(visited, the_node->name, the_node);
		find_edge_reset(the_node, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 1));
}
