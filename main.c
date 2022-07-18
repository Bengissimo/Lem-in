/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:22:20 by ykot              #+#    #+#             */
/*   Updated: 2022/07/18 19:53:23 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	main(int argc, char **argv)
{
	t_farm	farm;

	if (argc != 1)
		error(&farm);  //this fn leads to a bus error and aborts program. we can simply return (1) instead
	(void *)argv;
	ft_bzero(&farm, sizeof(farm));
	read_input(&farm);
	/* algo */
	print_farm(farm);
	free_farm(&farm);
	return (0);
}
