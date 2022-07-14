/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:51:09 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:21:29 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_one_char(const char *str, int i)
{
	ft_putchar(str[i]);
	g_total++;
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_flags	flag;
	int		i;

	i = -1;
	g_total = 0;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			++i;
			if (!str[i])
				break ;
			if (conv_spec(str, &i, &flag, &ap) || print_conv(&flag, &ap))
			{
				va_end(ap);
				return (-1);
			}
		}
		else
			print_one_char(str, i);
	}
	va_end(ap);
	return (g_total);
}
