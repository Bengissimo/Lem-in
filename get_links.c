/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/03 22:01:41 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	append_link_name(t_farm *farm, char *line)
{
	t_list	*link_name;

	link_name = ft_lstnew(line, ft_strlen(line) + 1);
	if (!link_name)
		return (0);
	ft_lstappend(&farm->links, link_name);
	return (1);
}

int	append_edge(t_node *node, t_edge *edge)  // rooms will be changed to nodes here
{
	t_list	*new;

	new = lstnew_pointer(edge);
	if (!new)
		return (0); //TO DO: error exit 
	ft_lstappend(&node->edges, new);
	return (1);
}

/*
	1_in --> 1_out --> 2_in --> 2_out
	 ^							  |
	 |							  |
	  -----------------------------
*/
static int	make_adj_list(t_room *room1, t_room *room2) // modify this to put room_in room_out links
{
	t_edge *edge1_in;
	t_edge *edge2_in;

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

/*int	parse_links(t_farm *farm, char *line)
{
	size_t	i;
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			first = ft_memalloc(i + 1);
			if (!first)
				return (FALSE);
			ft_strncpy(first, line, i);
			second = line + i + 1;
			room1 = hashmap_get(farm, first);
			room2 = hashmap_get(farm, second);
			ft_strdel(&first);
			if (room1 && room2 && make_adj_list(room1, room2))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}*/

void parse_links(t_farm *farm, char *line)
{
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;
	char **split_link;

	split_link = ft_strsplit(line, '-');
	if (!split_link[0] || !split_link[1] || split_link[2])
		error_free_split_line(farm, &split_link, &line);
	first = split_link[0];
	second = split_link[1];
	room1 = (t_room *)hashmap_get(farm->hashmap, first);
	room2 = (t_room *)hashmap_get(farm->hashmap, second);
	if (!room1 || !room2)
		error_free_split_line(farm, &split_link, &line);
	if (!make_adj_list(room1, room2))
		error_free_split_line(farm, &split_link, &line);
	free_split(&split_link);
}

int	get_link(t_farm *farm, char **line)
{
	parse_links(farm, *line);  //adj_list is created here now
	if (!append_link_name(farm, *line))
		return (0);
	return (1);
}

t_edge *create_edge(t_node *node)
{
	t_edge *edge;

	if (!node)
		return (NULL);
	edge = (t_edge *)ft_memalloc(sizeof(t_edge));
	if (!edge)
		return (NULL); // to do error exit
	edge->to = node;
	return (edge);
}
