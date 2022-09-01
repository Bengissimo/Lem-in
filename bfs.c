/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/01 09:44:21 by bkandemi         ###   ########.fr       */
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
		{
			ft_lstdel(&queue, null_fn);
			free_hashmap(hashmap_node);
			return (1);
		}
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
	ft_lstdel(&queue, null_fn);
	free_hashmap(hashmap_node);
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
		/*else
			edges = NULL;*/
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

void print_paths(t_list **paths, size_t flow)
{
	size_t i;
	char *the_room;
	t_list *list;
	size_t len;

	i = 0;
	while (i < flow)
	{
		list = paths[i];
		if (!list)
			break ;
		len = ft_lstsize(paths[i]);
		while (list)
		{
			the_room = list->content;
			printf("%s > ", the_room);
			list = list->next;
		}
		printf(" -path_len: %d- ", (int)len);
		printf("\n\n");
		i++;
	}
}

void print_path_sets(t_list *sets)
{
	size_t i;
	t_list **the_set;
	t_list *curr;

	i = 0;
	curr = sets;
	while (curr)
	{
		the_set = curr->content;
		printf("set %d:\n", (int)i);
		print_paths(the_set, i + 1);
		i++;
		curr = curr->next;
	}
}

int bfs_path(t_farm *farm)
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
		{
			ft_lstdel(&queue, null_fn);
			free_hashmap(hashmap_node);
			return (1);
		}
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (!hashmap_node_get(hashmap_node, child->name) && the_edge->flow == 1 && the_edge->reverse && the_edge->reverse->flow == 0)
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	ft_lstdel(&queue, null_fn);
	free_hashmap(hashmap_node);
	return (0);
}

void update_fwd_flow(t_farm *farm, int flow)
{
	t_node *the_node;
	t_edge *the_edge;
	t_list *edges;

	the_node = farm->end->in;
	edges = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
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
		the_node = the_node->parent;
	}
}

void reset_mark(t_farm *farm)
{
	while (bfs(farm, 2))
	{
		update_fwd_flow(farm, 1);
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
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges;
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
		if (the_node->source != farm->start && the_node->source != the_node->parent->source)
			ft_lstadd(&the_path, lstnew_pointer(the_node->source->name));
		the_node = the_node->parent;
	}
	return (the_path);
}

/*static void print_adj_list(t_farm farm) //just to see what we have in adj_list, will be removed later
{
	t_list *rooms;
	t_room *the_room;
	t_list	*edges;
	t_edge	*the_edge;

	rooms = farm.rooms;
	while (rooms)
	{
		the_room = rooms->content;
		printf("the room %s:\n", the_room->name);
		if (the_room->in)
		{
			printf("%s -> ",the_room->in->name);
			edges = the_room->in->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		if (the_room->out)
		{
			printf("%s -> ", the_room->out->name);
			edges = the_room->out->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		rooms = rooms->next;
	}
}*/

void reset_mark_1(t_farm *farm)
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

t_list *better_paths(t_farm *farm)
{
	t_list *sets;
	t_list **set_i;
	size_t i;
	size_t j;
	i= 0;
	sets = NULL;
	while(TRUE)
	{
		if (bfs(farm, 0))
			update_res_graph(farm->end);
		else
			break;
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *)); //set_i[0] has 1 path, set_i[1] has 2 paths etc...
		//reset fwd flow in sets[i - 1] if i > 0
		if (i > 0)
			reset_mark(farm);
		j = 0;
		while (j < i + 1)
		{
			if (bfs_path(farm))
			{
				set_i[j] = mark_and_save_path(farm, 2); //set fwd edge to 2
				j++;
			}
			else
				break ;
		}
		if (j)
			ft_lstappend(&sets, lstnew_pointer(set_i));
		i++;
	}
	//print_path_sets(sets);
	//print_adj_list(*farm);
	return (sets);
}

int bfs_path_2(t_farm *farm)
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
		{
			ft_lstdel(&queue, null_fn);
			free_hashmap(hashmap_node);
			return (1);
		}
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			if (!hashmap_node_get(hashmap_node, child->name)
				&& ((the_edge->flow == 1 && (the_edge->reverse && the_edge->reverse->flow == 0))
				|| (the_edge->flow == 0 && !the_edge->reverse)))
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	ft_lstdel(&queue, null_fn);
	free_hashmap(hashmap_node);
	return (0);
}

// to see void add_one_more_set(t_list *sets, t_farm *farm, size_t size) go to test_one_path_set branch



t_list *another_set(t_farm *farm)
{
	t_list *sets;
	t_list **set_i;
	size_t i;
	size_t j;
	i= 0;
	sets = NULL;
	reset_mark_1(farm);
	//print_adj_list(*farm);
	while(TRUE)
	{
		if (bfs(farm, 0))
			update_res_graph(farm->end);
		else
			break;
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *)); //set_i[0] has 1 path, set_i[1] has 2 paths etc...
		//reset fwd flow in sets[i - 1] if i > 0
		if (i > 0)
			reset_mark(farm);
		j = 0;
		while (j < i + 1)
		{
			if (bfs_path_2(farm))
			{
				set_i[j] = mark_and_save_path(farm, 2); //set fwd edge to 2
				j++;
			}
			else
				break ;
		}
		if (j)
			ft_lstappend(&sets, lstnew_pointer(set_i));
		i++;
	}
	return (sets);
}
