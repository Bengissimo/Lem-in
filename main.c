/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/09/13 12:39:49 by bkandemi         ###   ########.fr       */
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

static void null_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void	free_set_i(t_list **set_i, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (set_i[i])
		{
			ft_lstdel(&set_i[i], null_fn);
		}
		i++;
	}
	free(set_i);
}

void	free_paths(t_list **alst)
{
	t_list	*curr;
	t_list	*next;

	if (!alst || !*alst)
		return ;
	curr = *alst;
	int i = 0;
	while (curr)
	{
		next = curr->next;
		free_set_i(curr->content, i + 1);
		free(curr);
		curr = next;
		i++;
	}
	*alst = NULL;
}

static void init_farm(t_farm *farm)
{
	ft_bzero(farm, sizeof(*farm));
	farm->hashmap = ft_memalloc(HASH * sizeof(t_list *));
}

int	main(int argc, char **argv)
{
	t_farm	farm;
	//t_list *option1;
	//t_list *option2;
	t_list *new;

	init_farm(&farm);
	if (argc != 1 && argv)
		error(&farm);
	read_input(&farm);
	print_farm(farm);
	bfs_level_end(&farm);
	//print_adj_list(farm);
	bfs_level(&farm);
	
	/*
	* scan the edges of the node while saving paths or while doing bfs
	* if the edge->to level is greater than the node skip that way
	* if the levels are equal, check if they are siblings, if so skip one node. 
	*/
	//print_adj_list(farm);
	/*option1 = get_paths(&farm, 1);
	option2 = get_paths(&farm, 2);
	find_the_best_paths_and_send_ants(option1, &farm);*/
	//find_the_best_paths_and_send_ants(option2, &farm);
	new = get_paths_new(&farm);
	printf("\n\n");
	
	find_the_best_paths_and_send_ants(new, &farm);
	//print_adj_list(farm);

	free_farm(&farm);
	//free_paths(&option1);
	//free_paths(&option2);
	//system("leaks lem-in >> leaks.txt"); //do not run this with make debug or with valgrind, if you do so, first call make fclean and call make re
	return (0);
}
