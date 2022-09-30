/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:43:14 by ykot              #+#    #+#             */
/*   Updated: 2022/09/30 16:25:10 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	ft_memdel((void *)str);
}

void	error(t_farm *farm, char *er_str)
{
	free_farm(farm);
	ft_putstr_fd("Error: ", 2);
	if (!farm->flag.no_errlines)
	{
		ft_putstr_fd("in line ", 2);
		ft_putnbr_fd(farm->flag.read_lines, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(er_str, 2);
	//system("leaks lem-in >> error_leaks.txt");
	exit(1);
}

void	error_free_split_line(t_farm *farm, char ***str,
	char **line, char *er_str)
{
	free_split(str);
	ft_strdel(line);
	error(farm, er_str);
}

void	err_nolines(t_farm *farm, char *str)
{
	farm->flag.no_errlines = 1;
	error(farm, str);
}

void	err_empty_line(t_farm *farm)
{
	farm->flag.read_lines++;
	error(farm, ERR_EMP_LINE);
}
