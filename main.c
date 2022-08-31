/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/08/31 14:19:15 by bkandemi         ###   ########.fr       */
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
	size_t		size;
	t_list *sets;
	t_list **last_set;
	
	ft_bzero(&farm, sizeof(farm));
	farm.hashmap = ft_memalloc(HASH * sizeof(t_list *));
	
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	print_farm(farm);
	sets = better_paths(&farm, &size);
	last_set = add_one_more_set(&farm, size);
	send_ants(farm.num_ants, last_set, (int)size);
	free_farm(&farm);
	//system("leaks lem-in"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
