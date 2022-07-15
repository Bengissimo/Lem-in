/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:37:22 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/15 11:39:44 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

# define INVALID -1
# define COMMENT 0
# define START 1
# define END 2
# define ROOM 3
# define LINK 4
# define TRUE 1
# define FALSE 0

int	is_room_name_valid(char *line)
{
	if (line[0] == 'L' || line[0] == '#')
		return (FALSE);
	return (TRUE);
}

int is_room(char *line)
{
	/* to be filled*/
}

int is_link(char *line)
{
	/* to be filled*/
}

int	is_comment_or_command(char *line)
{
	if (line[0] == '#')
	{
		if (ft_strequ(line, "##start"))
			return (START);
		if (ft_strequ(line, "##end"))
			return (END);
		return (COMMENT);
	}
	return (INVALID);
}

int main(void)
{
	char *test1 = "#regular comment";
	char *test2 = "##start";
	char *test3 = "##end";
	char *test4 = "##star";
	char *test5 = "##starta";
	char *test6 = "invalid comment";

}