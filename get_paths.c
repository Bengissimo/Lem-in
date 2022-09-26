/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:36 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/26 11:22:01 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	update_fwd_flow(t_farm *farm, int flow)
{
	t_node		*the_node;
	t_edge		*the_edge;
	t_dblist	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node)
			{
				if (the_edge->reverse)
					the_edge->flow = flow;
				if (!the_edge->reverse)
					the_edge->flow = flow - 1;
				break ;
			}
			edges = edges->next;
		}
		the_node = the_node->parent;
	}
}

void reset_fwd_flow(t_farm *farm, int flow)
{
	t_node	*the_node;
	t_edge	*the_edge;
	t_dblist	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		set_edge_flow(the_node, edges, the_edge, flow);
		the_node = the_node->parent;
	}
}

void	reset_all_flow(t_farm *farm)
{
	while (bfs(farm, 1))
	{
		reset_fwd_flow(farm, 0);
	}
	while (bfs(farm, 2))
	{
		reset_fwd_flow(farm, 0);
	}
}

static int	when_to_stop(int *min_num_lines, t_list **set_i,
	int index, t_farm *farm)
{
	int	num_lines;
	int	*queue;

	queue = get_numrooms(set_i, index);
	num_lines = count_printed_lines(farm->num_ants, queue, index);
	/*for (int i = 0; i < index; i++)
	    printf("%d\n", queue[i]);
	printf("\n");*/
	if (num_lines >= *min_num_lines)
		return (1);
	else
		*min_num_lines = num_lines;
	return (0);
}

t_list	**get_paths(t_farm *farm, int option)
{
	t_list	**set_i;
	t_list	**prev_set;
	size_t	i;
	size_t	j;
	int		min_num_lines;

	i = 0;
	prev_set = NULL;
	min_num_lines = INT_MAX;
	if (option == 2)
		//reset_mark(farm);
		reset_all_flow(farm);
	while (bfs(farm, 0))
	{
		update_res_flow(farm);
		set_i = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *));
		j = 0;
		while (j < i + 1 && bfs_path(farm, option))
		{
			set_i[j] = mark_and_save_path(farm, 2);
			j++;
		}
		i++;
		reset_mark(farm);
		if (when_to_stop(&min_num_lines, set_i, j, farm))
		{
			if (option == 1)
				farm->index1 = i - 1;
			else
				farm->index2 = i - 1;
			return (prev_set);
		}
		prev_set = set_i;
	}
	if (option == 1)
		farm->index1 = i;
	else
		farm->index2 = i;
	return (set_i);
}
