/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fwd_flow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:09:13 by ykot              #+#    #+#             */
/*   Updated: 2022/09/30 22:24:42 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_fwd_flow(t_farm *farm, int flow)
{
	t_node		*the_node;
	t_edge		*the_edge;
	t_dblist	*edges;

	the_node = farm->end->in;
	edges = NULL;
	the_edge = NULL;
	while (the_node)
	{
		if (the_node->parent)
			edges = the_node->parent->edges.head;
		while (edges)
		{
			the_edge = edges->content;
			if (the_edge->to == the_node)
			{
				if (the_edge->reverse)
					the_edge->flow = flow;
				if (!the_edge->reverse)
					the_edge->flow = flow - 1;
				break ;
			}
			edges = edges->next;
		}
		the_node = the_node->parent;
	}
}

void reset_fwd_flow(t_farm *farm, int flow)
 {
 	t_node	*the_node;
 	t_edge	*the_edge;
 	t_dblist	*edges;

 	the_node = farm->end->in;
 	edges = NULL;
 	the_edge = NULL;
 	while (the_node)
 	{
 		if (the_node->parent)
 			edges = the_node->parent->edges.head;
 		set_edge_flow(the_node, edges, the_edge, flow);
 		the_node = the_node->parent;
 	}
 }


void	reset_all_flow(t_farm *farm)
{
	while (bfs(farm, 1))
	{
		reset_fwd_flow(farm, 0);  //this should be reset_fwd flow
	}
	while (bfs(farm, 2))
	{
		reset_fwd_flow(farm, 0); //this should be reset_fwd flow
	}
}
