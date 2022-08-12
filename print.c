/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:05:24 by ykot              #+#    #+#             */
/*   Updated: 2022/08/12 13:17:22 by bkandemi         ###   ########.fr       */
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

static void print_adj_list(t_farm farm) //just to see what we have in adj_list, will be removed later
{
	t_list *rooms;
	t_room *the_room;
	t_list	*edges;
	t_edge	*the_edge;

	rooms = farm.rooms;
	while (rooms)
	{
		the_room = rooms->content;
		printf("the room %s:\n", the_room->name);
		if (the_room->in)
		{
			printf("%s -> ",the_room->in->name);
			edges = the_room->in->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		if (the_room->out)
		{
			printf("%s -> ", the_room->out->name);
			edges = the_room->out->edges;
			while (edges)
			{
				the_edge = edges->content;
				printf("%s (flow: %d) - ", the_edge->to->name, the_edge->flow);
				edges = edges->next;
			}
			printf("\n");
		}
		rooms = rooms->next;
	}
}

void	print_farm(t_farm farm)
{
	ft_printf("%d\n", farm.num_ants);
	print_rooms(farm);
	print_links(farm);
	ft_putendl("---");
	print_adj_list(farm);
	ft_putendl("");
}
