/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/01 17:41:59 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"

static void null_fn(void *content, size_t size)
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
	ft_lstdelelem(queue, 0, null_fn);
	return (the_node);
}

static int	free_and_exit_bfs(t_list **queue, t_list **hashmap_node, int exit)
{
	ft_lstdel(queue, null_fn);
	free_hashmap(hashmap_node);
	return (exit);
}

int bfs(t_farm *farm, int flow)  // if it reaches to end return 1, else 0
{
	t_node	*the_node;
	t_node	*child;
	t_list	*edges;
	t_edge	*the_edge;
	t_list	*queue;
	t_list	**hashmap_node;

	hashmap_node = ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, hashmap_node, 1));
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (the_edge->flow == flow && !hashmap_node_get(hashmap_node, child->name))
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	return (free_and_exit_bfs(&queue, hashmap_node, 0));
}

int set_option(int option, t_list **hashmap_node, t_edge *the_edge, t_node *child)
{
	if (option == 1)
		return (!hashmap_node_get(hashmap_node, child->name)
			&& the_edge->flow == 1
			&& the_edge->reverse && the_edge->reverse->flow == 0);
	if (option == 2)
		return (!hashmap_node_get(hashmap_node, child->name)
			&& ((the_edge->flow == 1 && (the_edge->reverse && the_edge->reverse->flow == 0))
			|| (the_edge->flow == 0 && !the_edge->reverse)));
	return (0);
}

int bfs_path_search(t_farm *farm, int option)
{
	t_node *the_node;
	t_node *child;
	t_list *edges;
	t_edge *the_edge;
	t_list *queue;
	t_list **hashmap_node;
	
	hashmap_node = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	queue = NULL;
	the_edge = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
			return (free_and_exit_bfs(&queue, hashmap_node, 1));
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (set_option(option, hashmap_node, the_edge, child))
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	return (free_and_exit_bfs(&queue, hashmap_node, 0));
}

static void create_rev_flow(t_node *the_node, t_list *edges, t_edge *the_edge)
{
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
}

void update_res_flow(t_room *end)
{
	t_node	*the_node;
	t_edge	*the_edge;
	t_list	*edges;
	
	the_node = end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
		create_rev_flow(the_node, edges, the_edge);
		the_node = the_node->parent;
	}
}

static void set_edge_flow(t_node *the_node, t_list *edges, t_edge *the_edge, int flow)
{
	while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node)
			{
				the_edge->flow = flow;
				break ;
			}
			edges = edges->next;
		}
}

void update_fwd_flow(t_farm *farm, int flow)
{
	t_node	*the_node;
	t_edge	*the_edge;
	t_list	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
		set_edge_flow(the_node, edges, the_edge, flow);
		the_node = the_node->parent;
	}
}

t_list *mark_and_save_path(t_farm *farm, int flow)
{
	t_node *the_node;
	t_edge *the_edge;
	t_list *edges;
	t_list *the_path;

	the_node = farm->end->in;
	edges = NULL;
	the_path = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
		set_edge_flow(the_node, edges, the_edge, flow);
		if (the_node->source != farm->start && the_node->source != the_node->parent->source)
			ft_lstadd(&the_path, lstnew_pointer(the_node->source->name));
		the_node = the_node->parent;
	}
	return (the_path);
}

void reset_mark(t_farm *farm)
{
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 1);
	}
}

void reset_all_flows(t_farm *farm)
{
	while (bfs(farm, 1))
	{
		update_fwd_flow(farm, 0);
	}
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 0);
	}
}

t_list *get_paths(t_farm *farm, int option)
{
	t_list	*sets;
	t_list	**set_i;
	size_t	i;
	size_t	j;

	i= 0;
	sets = NULL;
	if (option == 2)
		reset_all_flows(farm);
	while(bfs(farm, 0))
	{
		update_res_flow(farm->end);
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *)); //set_i[0] has 1 path, set_i[1] has 2 paths etc...
		if (i > 0)
			reset_mark(farm);
		j = 0;
		while (j < i + 1 && bfs_path_search(farm, option))
		{
			set_i[j] = mark_and_save_path(farm, 2); //set fwd edge to 2
			j++;
		}
		if (j)
			ft_lstappend(&sets, lstnew_pointer(set_i));
		i++;
	}
	return (sets);
}

// to see void add_one_more_set(t_list *sets, t_farm *farm, size_t size) go to test_one_path_set branch
