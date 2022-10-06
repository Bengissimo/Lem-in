/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:50:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/10/06 16:07:42 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	split_link(char *line, t_farm *farm, char **first, char **second)
{
	int	i;
	int	j;

	if (!line)
		return ;
	if (has_single_dash(line) == FALSE)
		error_free_split_line(farm, NULL, &line, ERR_LINK_DASH);
	i = 0;
	while (line[i] != '-')
		i++;
	j = i;
	*first = ft_strsub(line, 0, i);
	while (line[i] != '\0')
		i++;
	*second = ft_strsub(line, j + 1, i - j - 1);
}

void	parse_links(t_farm *farm, char *line)
{
	char	*first;
	char	*second;
	t_room	*room1;
	t_room	*room2;

	first = NULL;
	second = NULL;
	split_link(line, farm, &first, &second);
	if (!first || !second)
		error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
	if (ft_strequ(first, second))
		error_free_split_line(farm, NULL, &line, ERR_LINK_SAME);
	room1 = (t_room *)hashmap_get(farm->hashmap, first);
	room2 = (t_room *)hashmap_get(farm->hashmap, second);
	ft_strdel(&first);
	ft_strdel(&second);
	if (!room1 || !room2)
		error_free_split_line(farm, NULL, &line, ERR_LINK);
	if (!make_adj_list(room1, room2))
		error_free_split_line(farm, NULL, &line, ERR_MEM_ALLOC);
}

int	get_link(t_farm *farm, char **line)
{
	parse_links(farm, *line);
	return (1);
}
