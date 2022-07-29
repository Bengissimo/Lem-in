/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/29 16:02:07 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	append_link_name(t_farm *farm, char *line)
{
	t_list *link_name;
	
	link_name = ft_lstnew(line, ft_strlen(line));
	if (!link_name)
		return (0);
	ft_lstappend(&farm->links, link_name);
	return (1);
}

int get_link(t_farm *farm, char **line)
{
	if (!is_link_OK(farm, *line))
	{
		printf("islink OK\n");	
		return (0);
	}
	append_link_name(farm, *line);
	//make_adj_list(farm, line);
	return (1);
}