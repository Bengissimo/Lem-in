/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:49:37 by ykot              #+#    #+#             */
/*   Updated: 2022/10/03 14:38:59 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*strnew;
	size_t	i;

	if (!size)
		return (NULL);
	strnew = (char *)malloc(sizeof(char) * (size + 1));
	if (!strnew)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		strnew[i] = '\0';
		++i;
	}
	return (strnew);
}
