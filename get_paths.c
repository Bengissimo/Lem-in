/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:36 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/05 23:06:57 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void print_adj_list(t_farm farm)
{
	t_dblist *rooms;
	t_room *the_room;
	t_dblist	*edges;
	t_edge	*the_edge;

	rooms = farm.rooms.head;
	while (rooms)
	{
		the_room = rooms->content;
		printf("the room %s:\n", the_room->name);
		if (the_room->in)
		{
			printf("%s -> ",the_room->in->name);
			edges = the_room->in->edges.head;
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
			edges = the_room->out->edges.head;
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
}

static int	when_to_stop(int *min_num_lines, t_list **path_set,
						int index, t_farm *farm)
{
	int	num_lines;
	int	*queue;

	queue = get_numrooms(path_set, index);
	if (queue == NULL)
		return (-1);
	if (check_path_size(queue, index))
	{
		free(queue);
		return (-2);
	}
	num_lines = count_printed_lines(farm->num_ants, queue, index);
	if (num_lines > *min_num_lines)
	{
		free(queue);
		return (1);
	}
	else
		*min_num_lines = num_lines;
	free(queue);
	return (0);
}

static t_list	**return_prev_set(t_farm *farm, t_list **prev_set,
								int option, size_t i)
{
	if (option == 1)
		farm->index.ind1 = i - 1;
	else
		farm->index.ind2 = i - 1;
	return (prev_set);
}

static t_list	**return_curr_set(t_farm *farm, t_list **path_set,
								int option, size_t i)
{
	if (option == 1)
		farm->index.ind1 = i;
	else
		farm->index.ind2 = i;
	return (path_set);
}

static void	init_get_paths(size_t *i, int *min_num_lines,
					t_list ***path_set, t_list ***prev_set)
{
	*i = 0;
	*path_set = NULL;
	*prev_set = NULL;
	*min_num_lines = INT_MAX;
}

static void	free_sets(t_list **path_set, t_list **prev_set, int i, int j)
{
	if (path_set != NULL)
		free_path_set(path_set, i);
	if (prev_set != NULL)
		free_path_set(prev_set, j);
}

t_list	**get_paths(t_farm *farm, int option)
{
	t_list	**path_set;
	t_list	**prev_set;
	size_t	i;
	size_t	j;
	t_list	*all_paths;
	t_list	*temp;
	int		min_num_lines;
	int		res_to_stop;
	
	all_paths = NULL;
	init_get_paths(&i, &min_num_lines, &path_set, &prev_set);
	if (option == 2)
		bfs_reset(farm);
	while (bfs(farm, 0))
	{
		update_res_flow(farm);
		path_set = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *));
		j = 0;
		while (j < i + 1 && bfs_path(farm, option))
		{
			path_set[j] = mark_and_save_path(farm, 2);
			/*if (new_path(path_set[j], all_paths))
			{
				temp = ft_lstnew_pointer(path_set[j]);
				ft_lstadd(&all_paths, temp);
				print_all_paths(all_paths);
			}*/
			j++;
		}
		i++;
		reset_mark(farm);
		res_to_stop = when_to_stop(&min_num_lines, path_set, i, farm);
		if (res_to_stop == -1)
		{
			//free_sets(path_set, prev_set);
			free_sets(path_set, prev_set, i, i - 1);
			err_nolines(farm, ERR_MEM_ALLOC);
		}
		if (res_to_stop == -2)
		{
			free_sets(path_set, prev_set, i, i - 1);
			return (NULL);
		}
		if (res_to_stop == 1)
		{
			//print_all_paths(all_paths);
			free_path_set(path_set, i);
			return (return_prev_set(farm, prev_set, option, i));
		}
		free_path_set(prev_set, i - 1);
		prev_set = path_set;
	}
	//ft_printf("\n--------------------\n\n");
	//print_all_paths(all_paths);
	return (return_curr_set(farm, path_set, option, i));
}
