/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/08/11 14:56:56 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void	print_rooms(t_farm farm)
{
	t_list	*rooms;
	t_room	*the_room;

	rooms = farm.rooms;
	while (rooms)
	{
		the_room = rooms->content;
		if (ft_strequ(farm.start->name, the_room->name))
		{
			ft_putendl("##start");
		}
		else if (ft_strequ(farm.end->name, the_room->name))
		{
			ft_putendl("##end");
		}
		printf("%s %d %d %lu\n", the_room->name, the_room->coord.x, the_room->coord.y, hash(the_room->name, 128));
		rooms = rooms->next;
	}
}

static void	print_links(t_farm farm)
{
	t_list	*links;

	links = farm.links;
	while (links)
    {
        ft_putendl((char *)links->content);
        links = links->next;
    }
}

/*static void print_links_in_adj_list(t_farm farm) //just to see what we have in adj_list, will be removed later
{
	t_list	*rooms;
	t_room	*the_room;
	t_list	*links;
	t_room	*the_linked_room;

	rooms = farm.rooms;
	while (rooms)
	{
		the_room = rooms->content;
		links = the_room->linked_rooms;
		while (links)
		{
			the_linked_room = links->content;
			printf("%s-%s\n",the_room->name, the_linked_room->name);
			links = links->next;
		}
		rooms = rooms->next;
	}
}*/

static void print_adj_list(t_list *adj_list) //just to see what we have in adj_list, will be removed later
{
	t_node *the_node;
	t_list	*edges;
	t_edge	*the_edge;

	while (adj_list)
	{
		the_node = adj_list->content;
		printf("%10s:", the_node->name);
		edges = the_node->edges;
		while (edges)
		{
			the_edge = edges->content;
			printf(" - %s ", the_edge->to->name);
			edges = edges->next;
		}
		printf("\n");
		adj_list = adj_list->next;
	}
}

void	print_farm(t_farm farm, t_algo algo)
{
	ft_printf("%d\n", farm.num_ants);
	print_rooms(farm);
	print_links(farm);
	ft_putendl("---");
	print_adj_list(algo.adj_list);
	ft_putendl("");
}
