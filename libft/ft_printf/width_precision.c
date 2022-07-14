/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:56:03 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 16:23:19 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_precision(t_flags *flag, int num_dig)
{
	int	i;

	i = 0;
	if (flag->specifier == 'o' && flag->hash && flag->precision > 1)
		flag->precision--;
	while (i++ < flag->precision - num_dig)
	{
		ft_putchar('0');
		g_total++;
		flag->zero_printed = 1;
	}
}

static void	width_first_call(t_flags *flag, int num_dig)
{
	if (flag->negative || flag->plus)
		flag->width--;
	if (flag->arg_zero && !flag->zero && flag->precision == -1)
	{
		flag->width--;
		return ;
	}
	if (flag->specifier == 's' || flag->specifier == '%')
		flag->width -= smaller(flag->precision, num_dig);
	else
		flag->width -= ft_bigger(flag->precision, num_dig);
}

void	putspace(void)
{
	ft_putchar(' ');
	g_total++;
}

void	print_width(t_flags *flag, int num_dig, int first_call)
{
	int	i;

	if (first_call)
		width_first_call(flag, num_dig);
	i = 0;
	if (first_call && !flag->minus)
	{
		while (i++ < flag->width)
		{
			if (flag->zero)
			{
				ft_putchar('0');
				flag->zero_printed = 1;
				g_total++;
			}
			else
				putspace();
		}
	}
	if (!first_call && flag->minus)
	{
		while (i++ < flag->width)
			putspace();
	}
}
