/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/29 13:23:04 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int	append_edge(t_node *node, t_edge *edge)
{
	t_dblist	*new;

	if (!node || !edge)
		return (0);
	new = ft_dblstnew_pointer(edge);
	if (!new)
		return (0);
	ft_dynlstappend(&node->edges, new);
	return (1);
}

static int	make_adj_list(t_room *room1, t_room *room2)
{
	t_edge	*edge1_in;
	t_edge	*edge2_in;

	edge1_in = NULL;
	edge2_in = NULL;
	if (room1->out && room2->in)
	{
		edge2_in = create_edge(room2->in);
		if (!append_edge(room1->out, edge2_in))
			return (FALSE);
	}
	if (room2->out && room1->in)
	{
		edge1_in = create_edge(room1->in);
		if (!append_edge(room2->out, edge1_in))
			return (FALSE);
	}
	return (TRUE);
}

void	parse_links(t_farm *farm, char *line)
{
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;
	char	**split_link;

	split_link = ft_strsplit(line, '-');
	if (split_link[0] && split_link[1] && split_link[2])
		error_free_split_line(farm, &split_link, &line, "Wrong link");
	if (!split_link[0] || !split_link[1] || split_link[2])
		error_free_split_line(farm, &split_link, &line, "Memory allocation");
	first = split_link[0];
	second = split_link[1];
	if (ft_strequ(first, second))
		error_free_split_line(farm, &split_link, &line, "Same room in the link");
	room1 = (t_room *)hashmap_get(farm->hashmap, first);
	room2 = (t_room *)hashmap_get(farm->hashmap, second);
	if (!room1 || !room2)
		error_free_split_line(farm, &split_link, &line, "Wrong link");
	if (!make_adj_list(room1, room2))
		error_free_split_line(farm, &split_link, &line, "Memory allocation");
	free_split(&split_link);
}

int	get_link(t_farm *farm, char **line)
{
	parse_links(farm, *line);
	return (1);
}

t_edge	*create_edge(t_node *node)
{
	t_edge	*edge;

	if (!node)
		return (NULL);
	edge = (t_edge *)ft_memalloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->to = node;
	return (edge);
}
