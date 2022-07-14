/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:42:05 by ykot              #+#    #+#             */
/*   Updated: 2022/07/04 10:41:29 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdelelem_sub(t_list **lst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*next;

	temp = (*lst)->next;
	next = temp->next;
	ft_lstdelone(&temp, del);
	(*lst)->next = next;
}

void	ft_lstdelelem(t_list **lst, size_t elem, void (*del)(void *, size_t))
{
	t_list	*begin_elem;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	if (!elem)
	{
		next = (*lst)->next;
		ft_lstdelone(&(*lst), del);
		*lst = next;
		return ;
	}
	begin_elem = *lst;
	while ((*lst)->next)
	{
		if (!(elem - 1))
		{
			ft_lstdelelem_sub(&(*lst), del);
			*lst = begin_elem;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = begin_elem;
}
