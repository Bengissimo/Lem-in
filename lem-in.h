/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/09/04 14:44:27 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include <stdio.h> //DELETE LATER

# define HASH 1109
# define INT_MAX 2147483647

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct	s_node
{
	char		*name;
	struct		s_node *parent;
	t_list		*edges;
	struct		s_room *source;
}				t_node;

typedef struct	s_room
{
	char	*name;
	t_coord	coord;
	t_node *in;
	t_node *out;
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
	int		rooms_done;
	t_list	**hashmap;
	t_list	*comments;
}				t_farm;

typedef struct	s_edge
{
	t_node			*to;
	int				flow;
	struct s_edge	*reverse;
}				t_edge;

typedef struct s_hash
{
	char	*name;
	void	*ptr;
}			t_hash;

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
void	parse_links(t_farm *farm, char *line);
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
void			*hashmap_get(t_list **hashmap, char *str);
int				hashmap_set(t_list **hashmap, char *str, void *ptr);
int				is_in(t_list **hashmap, char *str);
void			free_hashmap(t_list **hashmap);

/* send_ants */
t_ant	*new_ant(t_list *pathptr);
void	move_ant(t_ant *ant);
void	print_ant(t_ant ant);
void	send_ants(int num_ants, t_list **paths, int size);
void	ant_push(t_list *path_ptr, t_list **queue);
void	ant_pop(t_list ***queue, t_list **moving_ants, int size, int *cur_ant_num);
void	find_the_best_paths_and_send_ants(t_list *sets, t_farm *farm);

/* other */
t_list	*lstnew_pointer(void *content);
void	lstdel(t_list **alst);

/* algo */
t_node	*create_node(char **str, int in);
t_edge	*create_edge(t_node *node);
int		append_edge(t_node *node, t_edge *edge);
int		bfs(t_farm *farm, int flow);
void	update_res_flow(t_room *end);
void	update_fwd_flow(t_farm *farm, int flow);
int		bfs_path_search(t_farm *farm, int option);
t_list *reset_graph_save_paths(t_farm *farm);
t_list *get_paths(t_farm *farm, int option);


void del_fn(void *content, size_t size);

//void add_one_more_set(t_list *sets, t_farm *farm, size_t size);

//printing paths
void print_paths(t_list **paths, size_t flow);
void print_path_sets(t_list *sets);


#endif
