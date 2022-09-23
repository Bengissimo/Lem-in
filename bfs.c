/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/23 19:36:06 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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

static int	set_option(int option, t_list **visited,
	t_edge *the_edge, t_node *child)
{
	if (option == 1)
		return (!is_in(visited, child->name)
			&& the_edge->flow == 1 && the_edge->reverse && the_edge->reverse->flow == 0);
	if (option == 2)
		return (!is_in(visited, child->name)
			&& ((the_edge->flow == 1 && the_edge->reverse && the_edge->reverse->flow == 0)
				|| (the_edge->flow == 0 && !the_edge->reverse)));
	/*if (option == 3)
		return (!is_in(visited, child->name) && the_edge->flow == 0);*/
	return (0);
}

static void	find_edge_set_opt(t_node *the_node, int option,
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
	hashmap_set(visited, farm->start->in->name, farm->start->in);
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

int	bfs_path(t_farm *farm, int option)
{
	t_node	*the_node;
	t_list	*queue;
	t_list	**visited;

	visited = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	hashmap_set(visited, farm->start->in->name, farm->start->in);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, visited, 1));
		hashmap_set(visited, the_node->name, the_node);
		find_edge_set_opt(the_node, option, &queue, visited);
	}
	return (free_and_exit_bfs(&queue, visited, 0));
}

int bfs_level_end(t_farm *farm)
{
	t_node *the_node;
	t_node *child;
	t_dblist *edges;
	t_edge *the_edge;
	t_list *queue;
	t_list **visited;
	visited = ft_memalloc(HASH * sizeof(t_list *));

	queue = NULL;
	q_push(&queue, farm->end->out);
	hashmap_set(visited, farm->end->in->name, farm->end->in);
	hashmap_set(visited, farm->start->out->name, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		hashmap_set(visited, the_node->name, the_node);
		edges = the_node->edges.head;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (!is_in(visited, child->name))
			{
				child->parent = the_node;
				if (!ft_strequ(child->source->name, the_node->source->name))
					child->level_end = the_node->level_end + 1;
				else
					child->level_end = the_node->level_end;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	farm->start->out->level_end = farm->start->in->level_end;
	return (free_and_exit_bfs(&queue, visited, 0));
}


