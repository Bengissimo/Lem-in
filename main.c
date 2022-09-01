/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/01 09:44:46 by bkandemi         ###   ########.fr       */
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
	t_list *sets;
	t_list *second_sets;


	
	ft_bzero(&farm, sizeof(farm));
	farm.hashmap = ft_memalloc(HASH * sizeof(t_list *));
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	print_farm(farm);
	
	sets = better_paths(&farm);
	second_sets = another_set(&farm);
	find_the_best_paths_and_send_ants(sets, &farm);
	find_the_best_paths_and_send_ants(second_sets, &farm);
	free_farm(&farm);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
