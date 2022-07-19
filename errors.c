/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/07/19 15:04:13 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	del_links(void *content, size_t size)
{
	ft_memdel(&content);
	size++;
}

static void	del_rooms(void *content, size_t size)
{
	ft_strdel(&((t_room *)content)->name);  //this was giving a double-free error with fsanitize
	ft_memdel(&content);
	size++;
}

void free_farm(t_farm *farm)
{
	ft_lstdel(&farm->links, del_links);
	ft_lstdel(&farm->rooms, del_rooms);
	ft_strdel(&farm->start.name);
	ft_strdel(&farm->end.name);
}

void	error(t_farm *farm)
{
	free_farm(farm);
	ft_putendl_fd("Error", 2);
	exit(1);
}
