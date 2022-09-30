/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:36 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/30 19:13:08 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	when_to_stop(int *min_num_lines, t_list **path_set,
						int index, t_farm *farm)
{
	int	num_lines;
	int	*queue;

	queue = get_numrooms(path_set, index);
	if (queue == NULL)
	{
		printf("aug_9 TEST\n");
		error(farm, "Memory allocation");
	}
	num_lines = count_printed_lines(farm->num_ants, queue, index);
	//printf("Min\t%d\tCur\t%d\n", *min_num_lines, num_lines);
	//print_paths(farm, path_set, index);
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

static t_list **return_prev_set(t_farm *farm, t_list	**prev_set,
								int option, size_t i)
{
	if (option == 1)
		farm->index.ind1 = i - 1;
	else
		farm->index.ind2 = i - 1;
	return (prev_set);
}

static t_list **return_curr_set(t_farm *farm, t_list **path_set,
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

t_list	**get_paths(t_farm *farm, int option)
{
	t_list	**path_set;
	t_list	**prev_set;
	size_t	i;
	size_t	j;
	int		min_num_lines;

	init_get_paths(&i, &min_num_lines, &path_set, &prev_set);
	if (option == 2)
		reset_all_flow(farm);
	while (bfs(farm, 0))
	{
		update_res_flow(farm);
		path_set = (t_list **)ft_memalloc((i + 1) * sizeof(t_list *));
		j = 0;
		while (j < i + 1 && bfs_path(farm, option))
		{
			path_set[j] = mark_and_save_path(farm, 2);
			j++;
		}
		i++;
		reset_mark(farm);
		if (when_to_stop(&min_num_lines, path_set, i, farm))
		{
			free_path_set(path_set, i);
			return (return_prev_set(farm, prev_set, option, i));
		}
		free_path_set(prev_set, i - 1);
		prev_set = path_set;
	}
	return (return_curr_set(farm, path_set, option, i));
}
