/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:22:02 by bkandemi          #+#    #+#             */
/*   Updated: 2022/08/04 20:56:54 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static void del_fn(void *content, size_t size)
{
	content = NULL;
	size = 0;
}

void q_push(t_list **queue, t_room *the_room)
{
	t_list *to_push;
	//t_room *temp;
	//printf("q_push\n");
	to_push = lstnew_pointer(the_room);
	if (!to_push){
		//printf("q_push null\n");
		return ;
	}
	ft_lstappend(queue, to_push);
	//temp = queue->content;
	//printf("queue: %s\n", temp->name);
}

t_room *q_pop(t_list **queue)
{
	t_room *the_room;

	if (!queue)
		return (NULL);
	the_room = (*queue)->content;
	ft_lstdelelem(queue, 0, del_fn);
	return (the_room);
}

static void print_shortest_path(t_farm *farm)
{
	t_room *the_room;

	the_room = farm->end;
	//printf("parent of the room %s\n", the_room->parent->name);
	//printf("the room %s\n", the_room->name);
	while (the_room)
	{
		printf("%s - ", the_room->name);
		the_room = the_room->parent;
	}
	printf("\n\n");
}

void bfs(t_farm *farm)
{
	t_room *the_room;
	t_list *links;
	t_room *child;
	int the_end;

	t_room *temp;
	temp = farm->start;
	q_push(&farm->queue, farm->start);
	farm->start->visited = TRUE;
	while (farm->queue)
	{
		the_room = q_pop(&farm->queue);
		if (the_room == farm->end)
		{
			the_end = TRUE;
			break ;
		}
		links = the_room->linked_rooms;
		while (links)
		{
			child = links->content;
			if (!child->visited)
			{
				child->parent = the_room;
				q_push (&farm->queue, child);
				child->visited = TRUE;
			}
			links = links->next;
		}
	}
	print_shortest_path(farm);
	/*if (the_end == FALSE)
		retunr (error);
	*/
}

/*
bfs pseudo:
ft_bzero(queue);
q_push(queue, start_room);
while (queue)
{
	q_pop(queue);
	the_room = 

	if (the_room == end_room)
	{
		found true;
		break ;
	}
	// when the_room poped add it to the path ??? this part depends on the algo
	while (the_room->linked_rooms)
	{
		child_room = the_room->linked_rooms->content;
		child_room->parent = the_room;
		q_push(queue, child_room);
	}
	
	
}
if found == false
	error 

*/
