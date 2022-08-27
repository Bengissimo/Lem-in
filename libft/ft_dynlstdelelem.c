/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstdelelem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:07:10 by ykot              #+#    #+#             */
/*   Updated: 2022/08/27 02:11:26 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_dynlstdelelem(t_dynlist *alst, size_t elem, void (*del)(void *))
{
	t_dlist *temp;
    t_dlist *next;
    t_dlist *prev;
    
    if (alst->size == 0 || elem > alst->size - 1)
        return ;
    if (elem == 0)
    {
        temp = alst->head;
        next = temp->next;
        ft_dlstdelone(&(temp->prev), del);
        next->prev = NULL;
        alst->head = next;
        alst->size--;
        return ;
    }
    if (elem == alst->size - 1)
    {
        temp = alst->tail;
        prev =temp->prev;
        ft_dlstdelone(&(temp->next), del);
        temp->next = NULL;
        alst->tail = prev;
        alst->size--;
        return ;
    }
    temp = ft_dynlstelem(*alst, elem);
    next = temp->next;
    prev = temp->prev;
    ft_dlstdelone(&temp, del);
    prev->next = next;
    next->prev = prev;
    alst->size--;
}
