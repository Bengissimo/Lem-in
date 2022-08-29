/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/29 22:26:55 by bkandemi         ###   ########.fr       */
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
	t_node *the_node;
	t_node *child;
	t_list *edges;
	t_edge *the_edge;
	t_list *queue;
	t_list **hashmap_node;
	hashmap_node = ft_memalloc(HASH * sizeof(t_list *));

	queue = NULL;
	q_push(&queue, farm->start->out);
	while (queue)
	{
		the_node = q_pop(&queue);
		if (the_node == farm->end->in)
		{
			//free queue
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
	//free queue
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

/*t_list **edmonds_karp(t_farm *farm, int *size) //name: get_max_flow_paths
{
	size_t flow;
	size_t i;
	t_list **paths;

	flow = 0;
	while (bfs(farm, 0))  // if the_flow == 0 
	{
		flow++; 
		update_res_graph(farm->end);
	}
	*size = flow;
	paths = (t_list**)ft_memalloc(flow * sizeof(t_list *));
	if (!paths)
		return (NULL); // or exit (1)
	i = 0;
	while (bfs_path(farm))
	{
		//paths[i] = update_path_graph(farm);
		paths[i] = reset_graph_save_paths(farm);
		i++;
	}
	*size = i;
	printf("max i: %d flow: %d\n", (int)i, (int)flow);
	print_paths(paths, flow);
	return (paths);
}*/

/*void reset_graph(t_farm *farm)
{
	while (bfs(farm, 1))
	{
		update_fwd_flow(farm, 0);
	}
}

size_t calc_max_flow(t_farm *farm)
{
	size_t flow;

	flow = 0;
	while (bfs(farm, 0))  // if the_flow == 0 
	{
		flow++; 
		update_res_graph(farm->end);
	}
	reset_graph(farm);
	return (flow);
}*/

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
			//free_queue
			free_hashmap(hashmap_node);
			return (1);
		}
		hashmap_node_set(hashmap_node, the_node);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			child = the_edge->to;
			/*if (!hashmap_node_get(hashmap_node, child->name)
				&& ((the_edge->flow == 1 && (the_edge->reverse && the_edge->reverse->flow == 0))
				|| (the_edge->flow == 0 && !the_edge->reverse)))*/
			if (!hashmap_node_get(hashmap_node, child->name) && the_edge->flow == 1 && the_edge->reverse && the_edge->reverse->flow == 0)
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	//free_queue
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

/*t_list *reset_graph_save_paths(t_farm *farm)
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
				the_edge->flow = 0;
				break ;
			}
			edges = edges->next;
		}
		if (the_node->source != farm->start && the_node->source != the_node->parent->source)
			ft_lstadd(&the_path, lstnew_pointer(the_node->source->name));
		the_node = the_node->parent;
	}
	return (the_path);
}*/

/*t_list **shortest_paths(t_farm *farm, int *size) //get_shortest_paths
{
	size_t flow;
	size_t i;
	t_list **shorts;

	flow = 0;
	while (bfs(farm, 0))
	{
		flow++;  //2 path
		update_fwd_flow(farm); // make fwd flow 1
	}
	*size = flow;
	shorts = (t_list **)ft_memalloc(flow * sizeof(t_list *));
	if (!shorts)
		return (NULL); // or exit (1)
	i = 0;
	while (bfs(farm, 1))  //the_edge->flow == 1
	{
		shorts[i] = reset_graph_save_paths(farm); //the_edge->flow = 0, 
		i++;
		
	}
	printf("shorts i: %d\n", (int)i);
	print_paths(shorts, flow);
	return (shorts);
}*/

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

t_list *better_paths(t_farm *farm, size_t *size)
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
	*size = j;
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
			//free_queue
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
			//if (!hashmap_node_get(hashmap_node, child->name) && the_edge->flow == 1 && the_edge->reverse && the_edge->reverse->flow == 0)
			{
				child->parent = the_node;
				q_push (&queue, child);
			}
			edges = edges->next;
		}
	}
	//free_queue
	free_hashmap(hashmap_node);
	return (0);
}

/*void add_one_more_set(t_list *sets, t_farm *farm, size_t size)
{
	t_list **last_set;

	last_set = (t_list **)ft_memalloc((size + 1) * sizeof(t_list *));
	int ind = 0;
	while (bfs_path_2(farm))
	{
		last_set[ind] = mark_and_save_path(farm, 3);
		ind++;
	}
	ft_lstappend(&sets, lstnew_pointer(last_set));
	//print_path_sets(sets);
	/*t_list *curr = sets;
	int i = 0;
	while (i < 3)
	{
		curr = curr->next;
		i++;
	}
	print_paths(curr->content, size); */ //just to confirm if I have this final set in the sets
	//printf("the last set of paths:\n");
	//print_paths(last_set, size);
	print_path_sets(sets);
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

/*t_list *another_set(t_farm *farm, size_t size)
{
	t_list *second_sets;
	t_list **set_i;
	size_t i;
	size_t j;
	i= 0;
	second_sets = NULL;
	while(i < size)
	{
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *)); //set_i[0] has 1 path, set_i[1] has 2 paths etc...
		//reset fwd flow in sets[i - 1] if i > 0
		if (i > 0)
			reset_mark_3(farm);
		j = 0;
		while (j < i + 1)
		{
			if (bfs_path_2(farm))
			{
				set_i[j] = mark_and_save_path(farm, 3); //set fwd edge to 3
				j++;
			}
			else
				break ;
		}
		if (j)
			ft_lstappend(&second_sets, lstnew_pointer(set_i));
		i++;
	}
	printf("second sets:\n");
	print_path_sets(second_sets);
	return (second_sets);
}*/

t_list *another_set(t_farm *farm, size_t *size)
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
				set_i[j] = mark_and_save_path(farm, 2); //set fwd edge to 3
				j++;
			}
			else
				break ;
		}
		if (j)
			ft_lstappend(&sets, lstnew_pointer(set_i));
		i++;
	}
	*size = j;
	printf("second sets:\n");
	print_path_sets(sets);
	//print_path_sets(sets);
	//print_adj_list(*farm);
	return (sets);
}