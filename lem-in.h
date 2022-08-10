/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/08/10 10:59:29 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include <stdio.h> //DELETE LATER

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

/*typedef struct	s_room
{
	char	*name;
	t_coord	coord;
}				t_room;*/


typedef struct	s_room
{
	char	*name;
	t_coord	coord;
	t_list	*linked_rooms;
	struct s_room *parent;
	int		visited;
}				t_room;


typedef struct	s_ant
{
	int		name;
	t_list	*pathptr;
}				t_ant;

typedef struct	s_farm
{
	int		num_ants;
	t_list	*rooms;
	t_list	*links;
	t_room	*start;
	t_room	*end;
	int		rooms_done; //this flag is 1, once we start reading links, else 0
	t_list	**hashmap;
	t_list	*queue;  //for bfs
}				t_farm;

typedef struct	s_node   // or vertex  or  adj_list
{
	t_room		*room;
	struct		s_node *parent;
	int			visited;
}				t_node;

typedef struct	s_edge  // or link 
{
	t_room			*from;
	t_room			*to;
	int				flow;  // 1 or zero, at first it should be 1 but the reverse should be 0
	struct s_edge	*reverse;
}				t_edge;

typedef struct	s_algo  // alternative name s_algo
{
	t_list	*rooms;
	t_list	*edges;
	t_list	*queue;
}				t_graph;



/* read input */
int		is_command(t_farm *farm, char **line);
char	**get_room_lines(char *line);
t_room	*create_room(char **str);
int		append_room(t_farm *farm, t_room *room);
int		get_link(t_farm *farm, char **line);
int		get_rooms_links(t_farm *farm, char *line);
void	read_input(t_farm *farm);

/* checks */
int		check_int(const char *str);
int		parse_links(t_farm *farm, char *line);
int		is_char_in_str(char c, char *str);

/* errors */
void	free_farm(t_farm *farm);
void	error(t_farm *farm);
void	free_split(char ***str);
void	error_free_split_line(t_farm *farm, char ***str, char **line);

/* print */
void			print_farm(t_farm farm);

/* hashmap */
unsigned long	hash(const char *s, unsigned long m);
t_room			*hashmap_get(t_farm *farm, char *name);
int				hashmap_set(t_farm *farm, t_room *room);
int				parse_links(t_farm *farm, char *line);
void			free_hashmap(t_farm *farm);

/* send_ants */
t_ant	*new_ant(t_list *pathptr);
void	move_ant(t_ant *ant);
void	print_ant(t_ant ant);
void	send_ants(int num_ants, t_list **paths);
void	ant_push(t_list *path_ptr, t_list **queue);
void	ant_pop(t_list ***queue, t_list **moving_ants, int size, int *cur_ant_num);

/* other */
t_list	*lstnew_pointer(void *content);
void	lstdel(t_list **alst);

/* algo */
void bfs(t_farm *farm);

#endif
