/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/08/16 20:48:16 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	main(int argc, char **argv)
{
	t_farm	farm;
	int		size;
	t_list	**paths;
	
	ft_bzero(&farm, sizeof(farm));
	farm.hashmap = ft_memalloc(128 * sizeof(t_list *));
	
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	/* algo */
	print_farm(farm);
	paths = edmonds_karp(&farm, &size);  //this fn returns t_list **paths
	send_ants(farm.num_ants, paths, size);
	free_farm(&farm);
	//system("leaks lem-in"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
