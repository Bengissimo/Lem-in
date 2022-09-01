/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/01 10:39:18 by bkandemi         ###   ########.fr       */
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
	t_list *option1;
	t_list *option2;

	ft_bzero(&farm, sizeof(farm));
	farm.hashmap = ft_memalloc(HASH * sizeof(t_list *));
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	print_farm(farm);
	option1 = get_paths(&farm, 1);
	option2 = get_paths(&farm, 2);
	find_the_best_paths_and_send_ants(option1, &farm);
	find_the_best_paths_and_send_ants(option2, &farm);
	free_farm(&farm);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
