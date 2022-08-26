/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/08/26 11:04:58 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*static size_t total_path_size(t_list **path, size_t size)
{
	size_t i;
	size_t result;

	i = 0;
	result = 0;
	while (i < size)
	{
		result += ft_lstsize(path[i]);
		i++;
	}
	return (result);
}*/

int	main(int argc, char **argv)
{
	t_farm	farm;
	//int		size;
	//t_list	**all;
	//t_list **shorts;
	t_list *sets;
	size_t size;

	
	ft_bzero(&farm, sizeof(farm));
	farm.hashmap = ft_memalloc(HASH * sizeof(t_list *));
	
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	print_farm(farm);
	/*shorts = shortest_paths(&farm, &size);
	if (farm.num_ants > (int)total_path_size(shorts, size))
	{
		all = edmonds_karp(&farm, &size);  //this fn returns t_list **paths
		send_ants(farm.num_ants, all, size);
	}
	else
		send_ants(farm.num_ants, shorts, size);*/
	sets = better_paths(&farm, &size);
	add_one_more_set(sets, &farm, size);
	//find_the_best_paths_and_send_ants(sets, &farm);
	free_farm(&farm);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
