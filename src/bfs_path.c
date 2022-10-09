/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:54:35 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/10 00:54:24 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_option(int option, t_list **visited,
	t_edge *the_edge, t_node *child)
{
	if (option == 1)
		return (!is_in(visited, child->name)
			&& the_edge->flow == 1
			&& the_edge->reverse && the_edge->reverse->flow == 0);
	if (option == 2)
		return (!is_in(visited, child->name)
			&& ((the_edge->flow == 1
					&& the_edge->reverse && the_edge->reverse->flow == 0)
				|| (the_edge->flow == 0 && !the_edge->reverse)));
	return (0);
}

static int	find_edge_set_opt(t_node *the_node, int option,
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
		if (set_option(option, visited, the_edge, child))
		{
			child->parent = the_node;
			if (q_push(queue, child) == 0)
				return (0);
		}
		edges = edges->next;
	}
	return (1);
}

int	bfs_path(t_farm *farm, int option)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
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
		if (find_edge_set_opt(the_node, option, &queue, visited) == 0)
			free_err_hashmap(farm, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}
