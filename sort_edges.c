/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_edges.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:41:04 by bkandemi          #+#    #+#             */
/*   Updated: 2022/09/23 19:41:46 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void swap(t_dblist *a, t_dblist *b)
{
	void *temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void bubblesort(t_dblist *edges)
{
	t_dblist *curr;
	t_dblist *next;
	t_edge *edge1;
	t_edge *edge2;
	int swapped;

	if (!edges)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = edges;
		while (curr->next)
		{
			next = curr->next;
			edge1 = curr->content;
			edge2 = next->content;
			if (edge1->to->level_end > edge2->to->level_end)
			{
				swap(curr, next);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
}
