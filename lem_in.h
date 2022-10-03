/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:20:47 by ykot              #+#    #+#             */
/*   Updated: 2022/10/03 14:17:15 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include <stdio.h> // DEL LATER

# define HASH 1109
# define INT_MAX 2147483647

# define ERR_MEM_ALLOC "Memory allocation"
# define ERR_INPUT "File is empty or no input"
# define ERR_ANT_NOT_INT "The number of ants is not an integer"
# define ERR_ANT_NB "The number of ants less or equal to zero"
# define ERR_ANT_CHAR "Characters after the number of ants"
# define ERR_DBL_ANT "Double ant number"
# define ERR_ROOM "No rooms"
# define ERR_ROOM_L "Room begins with L"
# define ERR_NO_LINK "No links"
# define ERR_MAP "Invalid map"
# define ERR_EMP_LINE "Empty line"
# define ERR_MLTP_ARGS "More than one argument"
# define ERR_ARGS "Wrong arguments"
# define ERR_NO_PATH "No path to end"
# define ERR_COORD_CHAR "Characters after coordinates"
# define ERR_COORD_INT "Coordinates are not integers"
# define ERR_READ "Fail to read a line"
# define ERR_START "No start"
# define ERR_END "No end"
# define ERR_START_END "No start and end"
# define ERR_LINK "Wrong link"
# define ERR_LINK_SAME "Same room in the link"
# define ERR_ROOM_AFT_LINK "Room after link"

# define USAGE "Usage: ./lem-in [OPTION] < valid map\n\n"
# define HELP " -h\thelp\n"
# define PRINT " -p\tprint sets of possible paths and number of lines to print\n"
# define VISUAL " -v\tused with visualizer\n"
# define VIS_USAGE " \nVisualizer usage: \
./lem-in -v < valid map | python3 visualizer.py [OPTION]\n\n"
# define COORD " --coord\tto use coordinates, random nodes position by default\n"
# define VIS_SLOW " --slow\t\tslow animation of moving ants\n"
# define VIS_FAST " --fast\t\tfast animation of moving ants\n\n"
# define VIS_INFO "Visualizer uses networkx, matplotlib, numpy, scipy. \
Be sure that you have these packages installed\n"

typedef struct s_coord
{
	int	x;
	int	y;
}		t_coord;

typedef struct s_node
{
	char			*name;
	struct s_node	*parent;
	t_dynlist		edges;
	struct s_room	*source;
}					t_node;

typedef struct s_room
{
	char	*name;
	t_coord	coord;
	t_node	*in;
	t_node	*out;
}			t_room;

typedef struct s_ant
{
	int		name;
	t_list	*pathptr;
}			t_ant;

typedef struct s_flag
{
	int	h;
	int	v;
	int	p;
	int	read_lines;
	int	no_errlines;
	int	rooms_done;
	int	is_links;
}		t_flag;

typedef struct s_index
{
	int	ind1;
	int	ind2;
}		t_index;

typedef struct s_farm
{
	int			num_ants;
	t_dynlist	rooms;
	t_dynlist	input_lines;
	t_room		*start;
	t_room		*end;
	t_list		**hashmap;
	t_flag		flag;
	t_index		index;
	t_list		**option1;
	t_list		**option2;
}				t_farm;

typedef struct s_edge
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
int				is_comment(char *line);
int				is_command(t_farm *farm, char **line);
char			**get_room_lines(char **line, t_farm *farm);
void			get_ant_num(t_farm *farm, char **line);
t_room			*create_room(char **str);
int				append_room(t_farm *farm, t_room *room);
int				get_link(t_farm *farm, char **line);
int				get_rooms_links(t_farm *farm, char *line);
void			read_input(t_farm *farm);
void			save_input(t_farm *farm, char **line);
void			err_empty_line(t_farm *farm);
int				enough_data(t_farm *farm, char **line);
void			err_nolines(t_farm *farm, char *str);

/* checks */
int				check_int(const char *str);
void			parse_links(t_farm *farm, char *line);
int				is_char_in_str(char c, char *str);

/* errors */
void			error(t_farm *farm, char *str);
void			free_split(char ***str);
void			error_free_split_line(t_farm *farm, char ***str,
					char **line, char *er_str);
void			err_nolines(t_farm *farm, char *str);
void			err_empty_line(t_farm *farm);

/* del */
void			del_dblfn(void *content);
void			null_fn(void *content, size_t size);
void			del(void *content, size_t size);
void			del_rooms(void *content);

/* free_fn */
void			del_dblfn(void *content);
void			free_farm(t_farm *farm);
void			del(void *content, size_t size);
void			free_path_set(t_list **path_set, size_t size);
void			null_fn(void *content, size_t size);

/* print */
void			print_farm(t_farm farm);
void			print_paths(t_farm *farm, t_list **paths, size_t flow);

/* hashmap */
unsigned long	hash(const char *s, unsigned long m);
void			*hashmap_get(t_list **hashmap, char *str);
int				hashmap_set(t_list **hashmap, char *str, void *ptr);
int				is_in(t_list **hashmap, char *str);
void			free_hashmap(t_list **hashmap);

/* send_ants */
t_ant			*new_ant(t_list *pathptr);
void			move_ant(t_ant *ant);
void			print_ant(t_ant ant);
void			send_ants(t_farm *farm, t_list **paths, int size);
int				ant_push(t_list *path_ptr, t_list **queue);
void			ant_pop(t_list ***queue, t_list **moving_ants,
					int size, int *cur_ant_num);
void			find_the_best_paths_and_send_ants(t_farm *farm);
int				*get_numrooms(t_list **paths, int size);
int				count_printed_lines(int num_ants, int *queue, int size);

/* bfs utils */
void			q_push(t_list **queue, t_node *the_node);
t_node			*q_pop(t_list **queue);
int				free_and_exit_bfs(t_list **queue, t_list **visited, int exit);

/* bfs */
int				bfs(t_farm *farm, int flow);
int				bfs_path(t_farm *farm, int option);

/* algo */
t_node			*create_node(char **str, int is_in_or_out);
t_edge			*create_edge(t_node *node);
int				append_edge(t_node *node, t_edge *edge);

void			update_res_flow(t_farm *farm);
void			update_fwd_flow(t_farm *farm, int flow);

t_list			**get_paths(t_farm *farm, int option);
t_list			*mark_and_save_path(t_farm *farm, int flow);
void			reset_mark(t_farm *farm);
t_list			*reset_graph_save_paths(t_farm *farm);
void			set_edge_flow(t_node *the_node, t_dblist *edges,
					t_edge *the_edge, int flow);

/* update_fwd_flow */
void			reset_all_flow(t_farm *farm);

//printing paths
void			print_paths(t_farm *farm, t_list **paths, size_t flow);
void			print_path_sets(t_list *sets);

/* path_collector.c */
int				new_path(t_list *path, t_list *all_paths);
void			print_all_paths(t_list *all_paths);

#endif
