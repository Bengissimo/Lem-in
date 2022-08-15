/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/15 10:12:24 by bkandemi         ###   ########.fr       */
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

int bfs(t_farm *farm)  // if it reaches to end return 1, else 0
{
	t_node *the_node;
	t_node *child;
	t_list *edges;
	t_edge *the_edge;
	t_list *queue;
	t_list **hashmap_node;
	hashmap_node = ft_memalloc(128 * sizeof(t_list *));

	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
		{
			free_hashmap_node(hashmap_node);
			return (1);
		}
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (the_edge->flow == 0 && !hashmap_node_get(hashmap_node, child->name))
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	free_hashmap_node(hashmap_node);
	return (0);
}

void update_res_graph(t_room *end)
{
	t_node *the_node;
	t_edge *the_edge;
	t_list *edges;

	the_node = end->in;
	edges = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
		else
			edges = NULL;
		while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node)
			{
				the_edge->flow = 1;
				if (!the_edge->reverse)
				{
					the_edge->reverse = create_edge(the_node->parent);
					if (!append_edge(the_node, the_edge->reverse))
						exit (1);
					the_edge->reverse->reverse = the_edge;
				}
				break ;
			}
			edges = edges->next;
		}
		the_node = the_node->parent;
	}
}

static void print_paths(t_list **paths, size_t flow)
{
	size_t i;
	t_room *the_room;
	t_list *list;

	i = 0;
	while (i < flow)
	{
		list = paths[i];
		while (list)
		{
			the_room = list->content;
			printf("%s > ", the_room->name);
			list = list->next;
		}
		printf("\n\n");
		i++;
	}
}

t_list **edmonds_karp(t_farm *farm)
{
	size_t flow;
	size_t i;
	t_list **paths;

	flow = 0;
	while (bfs(farm))
	{
		flow++;
		update_res_graph(farm->end);
	}
	paths = ft_memalloc(flow * sizeof(t_list *));
	if (!paths)
		return (NULL); // or exit (1)
	i = 0;
	while (bfs_path(farm))
	{
		paths[i] = update_path_graph(farm);
		i++;
	}
	print_paths(paths, flow);
	return (paths);
}

int bfs_path(t_farm *farm)
{
	t_node *the_node;
	t_node *child;
	t_list *edges;
	t_edge *the_edge;
	t_list *queue;
	t_list **hashmap_node;
	
	hashmap_node = ft_memalloc(128 * sizeof(t_list *));
	queue = NULL;
	the_edge = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
		{
			free_hashmap_node(hashmap_node);
			return (1);
		}
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (the_edge->flow == 1 && the_edge->reverse->flow == 0 && !hashmap_node_get(hashmap_node, child->name))
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	free_hashmap_node(hashmap_node);
	return (0);
}

t_list *update_path_graph(t_farm *farm)
{
	t_node *the_node;
	t_edge *the_edge;
	t_list *edges;
	t_list *the_path;

	the_node = farm->end->in;
	edges = NULL;
	the_path = NULL;
	while (the_node)
	{
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node->parent)
			{
				the_edge->flow = 1;
				break ;
			}
			edges = edges->next;
		}
		if (the_node->source != farm->start && the_node->source != the_node->parent->source)
			ft_lstadd(&the_path, lstnew_pointer(the_node->source));
		the_node = the_node->parent;
	}
	return (the_path);
}

