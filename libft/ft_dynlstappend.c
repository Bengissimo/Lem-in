/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstappend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 23:29:19 by ykot              #+#    #+#             */
/*   Updated: 2022/08/26 23:54:44 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dynlstappend(t_dynlist *alst, t_dlist *new)
{
	if (!new)
		return ;
	if (alst->size == 0)
	{
		alst->head = new;
		alst->tail = new;
		alst->size = 1;
	}
	else
	{
		alst->tail->next = new;
		new->prev = alst->tail;
		alst->tail = new;
		alst->size++;
	}
}
