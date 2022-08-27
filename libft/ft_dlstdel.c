/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:06:25 by ykot              #+#    #+#             */
/*   Updated: 2022/08/27 01:14:49 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dynlist *alst, void (*del)(void *))
{
	t_dlist	*next;
	t_dlist *temp;
	
	if (alst->size == 0)
		return ;
	temp = alst->head;
	while (temp)
	{
		next = temp->next;
		ft_dlstdelone(&temp, del);
		temp = next;
	}
	alst = NULL;
}
