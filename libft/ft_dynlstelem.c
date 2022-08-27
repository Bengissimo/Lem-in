/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:29:26 by ykot              #+#    #+#             */
/*   Updated: 2022/08/27 01:57:54 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist *ft_dynlstelem(t_dynlist alst, size_t elem)
{
    t_dlist *temp;
    
    if (alst.size == 0 || elem > alst.size - 1)
        return (NULL);
    if (alst.size / 2 > elem)
        temp =alst.head;
    else
        temp = alst.tail;
    while (elem)
    {
        if (alst.size / 2 > elem)
            temp = temp->next;
        else
            temp = temp->prev;
        elem--;
    }
    return (temp);
}
