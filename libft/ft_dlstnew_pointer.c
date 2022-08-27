/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:03:10 by ykot              #+#    #+#             */
/*   Updated: 2022/08/27 09:04:59 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew_pointer(void *content)  //where to put this fn, we are using this in checks.c get_rooms.c and hash.c and bfs.c
{
	t_dlist	*lstnew;

	lstnew = (t_dlist *)ft_memalloc(sizeof(t_dlist));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
        lstnew->prev = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
        lstnew->prev = NULL;
	}
	return (lstnew);
}