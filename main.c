/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/08/11 12:41:42 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	main(int argc, char **argv)
{
	t_farm	farm;
	t_algo	algo;

	ft_bzero(&farm, sizeof(farm));
	ft_bzero(&algo, sizeof(algo));
	farm.hashmap = ft_memalloc(128 * sizeof(t_list *));
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm, &algo);
	/* algo */
	print_farm(farm, algo);
	//bfs(&farm);
	free_farm(&farm);
	//system("leaks lem-in"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
