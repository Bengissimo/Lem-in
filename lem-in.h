/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/09/01 09:45:09 by bkandemi         ###   ########.fr       */
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
	t_list	*rooms;   // this is the ONLY adj list !!!!
	t_list	*links;
	t_room	*start;
	t_room	*end;
	int		rooms_done; //this flag is 1, once we start reading links, else 0
	t_list	**hashmap; // remove this
	t_list	*comments;
}				t_farm;


typedef struct	s_edge
{
	t_node			*to;
	int				flow;  // 1 or zero, at first it should be 1 but the reverse should be 0
	struct s_edge	*reverse;
}				t_edge;

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
void		parse_links(t_farm *farm, char *line);
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
t_edge *create_edge(t_node *node);
int	append_edge(t_node *node, t_edge *edge);

//int bfs(t_farm *farm);
int bfs(t_farm *farm, int flow);
void update_res_graph(t_room *end);
t_list **edmonds_karp(t_farm *farm, int *size);


int bfs_path(t_farm *farm);
//t_list *update_path_graph(t_farm *farm); 
int bfs_path_2(t_farm *farm);


int	hashmap_node_set(t_list **hashmap_node, t_node *node);
t_node	*hashmap_node_get(t_list **hashmap_node, char *name);


void del_fn(void *content, size_t size);



t_list **shortest_paths(t_farm *farm, int *size);

t_list *reset_graph_save_paths(t_farm *farm);


//t_list *better_paths(t_farm *farm, size_t *ind);

t_list *better_paths(t_farm *farm);


void add_one_more_set(t_list *sets, t_farm *farm, size_t size);

t_list *another_set(t_farm *farm);





void update_fwd_flow(t_farm *farm, int flow);

//printing paths
void print_paths(t_list **paths, size_t flow);
void print_path_sets(t_list *sets);

#endif
