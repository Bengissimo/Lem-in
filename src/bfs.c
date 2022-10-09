/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 00:46:50 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_edge(t_node *the_node, int flow,
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
			if (q_push(queue, child) == 0)
				return (0);
		}
		edges = edges->next;
	}
	return (1);
}

static int	find_edge_reset(t_node *the_node, t_list **queue, t_list **visited)
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
			if (q_push(queue, child) == 0)
				return (0);
		}
		edges = edges->next;
	}
	return (1);
}

int	bfs(t_farm *farm, int flow)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = ft_memalloc(HASH * sizeof(t_list *));
	if (visited == NULL)
		err_nolines(farm, ERR_MEM_ALLOC);
	queue = NULL;
	if (q_push(&queue, farm->start->out) == 0)
		free_err_hashmap(farm, &queue, visited);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		if (hashmap_set(visited, the_node->name, the_node) == 0)
			free_err_hashmap(farm, &queue, visited);
		if (find_edge(the_node, flow, &queue, visited) == 0)
			free_err_hashmap(farm, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}

int	bfs_reset(t_farm *farm)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = ft_memalloc(HASH * sizeof(t_list *));
	if (visited == NULL)
		err_nolines(farm, ERR_MEM_ALLOC);
	queue = NULL;
	if (q_push(&queue, farm->start->out) == 0)
		free_err_hashmap(farm, &queue, visited);;
	while (queue)
	{
		the_node = q_pop(&queue);
		if (hashmap_set(visited, the_node->name, the_node) == 0)
			free_err_hashmap(farm, &queue, visited);
		if (find_edge_reset(the_node, &queue, visited) == 0)
			free_err_hashmap(farm, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 1));
}
