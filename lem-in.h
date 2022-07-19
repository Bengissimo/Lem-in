/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/07/19 16:04:17 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct	s_room
{
	char	*name;
	t_coord	coord;
	t_list *link;
}				t_room;

typedef struct	s_farm
{
	int		num_ants;
	t_list	*rooms;
	t_list	*links;
	t_room	start;
	t_room	end;
}				t_farm;

void	read_input(t_farm *farm);
void	free_farm(t_farm *farm);
void	error(t_farm *farm);
int		check_int(const char *str);
int		is_comment(char *line);
int		is_room_name_valid(char *line);
int		is_link_valid(t_list *rooms, char *line);

void    print_farm(t_farm farm);

#endif
