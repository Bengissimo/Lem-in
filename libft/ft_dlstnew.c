/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:06:27 by ykot              #+#    #+#             */
/*   Updated: 2022/08/27 00:40:20 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*dlstnew;

	dlstnew = (t_dlist *)malloc(sizeof(t_dlist));
	if (!dlstnew)
		return (NULL);
	if (!content)
	{
		dlstnew->content = NULL;
		dlstnew->content_size = 0;
		dlstnew->next = NULL;
        dlstnew->prev = NULL;
	}
	else
	{
		dlstnew->content = (void *)malloc(content_size);
		if (!dlstnew->content)
		{
			free(dlstnew);
			return (NULL);
		}
		ft_memcpy(dlstnew->content, content, content_size);
		dlstnew->content_size = content_size;
		dlstnew->next = NULL;
        dlstnew->prev = NULL;
	}
	return (dlstnew);
}
