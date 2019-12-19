/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:56:00 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/19 20:42:45 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <errno.h>
# include "ft_printf.h"

# define STDIN			(0)
# define STDOUT			(1)
# define STDERR			(2)
# define MAP_ALLOCATED	(1)
# define PIECE_CHAR		('*')
# define EMPTY			('.')
# define VS_CODE		(-2)

typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef struct		s_player
{
	int		number;
	char	my_char;
	char	vs_char;
}					t_player;

typedef struct		s_score
{
	t_point			point;
	int				score;
	struct s_score	*next;
}					t_score;

typedef struct		s_filler
{
	t_player	me;
	int			x;
	int			y;
	int			x_piece;
	int			y_piece;
	int			x_place;
	int			y_place;
	char		**map;
	char		**piece;
	char		*line;
	int			err;
	int			flag;
	int			stock_done;
	int			i;
	int			ret;
	int			rfd;
	int			wfd;
	int			game_init;
	int			game_over;
	int			score;
	int			**hmap;
	t_point		*coordinates;
	int			coor_size;
}					t_filler;

int					get_piece(t_filler *env);
int					get_map(t_filler *env);
int					get_player(t_filler *env);
void				destroy(char **s, int offset);
void				destroy_hmap(int **arr, int size, int offset);
int					heat_map_init(t_filler *env);
t_point				*new_vs_last_move(t_filler *env);
t_point				*new_vs_edges(t_filler *env);
int					get_vs_last_move(t_filler *env);
int					get_vs_edges(t_filler *env);
void				lstappend(t_score **lst, t_score *node);
t_score				*score_new(t_filler *env, int x, int y, int score);
t_score				*get_scores(t_filler *env, t_score *edges);
t_score				*get_my_points(t_filler *env);
int					is_placeable(t_filler *env, t_point place);
int					safe_placement(t_filler *env, t_point star, t_point place);
int					out_of_borders_char(t_filler *env, int empty, int i, int j);
int					set_point(t_point *p, int x, int y);
int					ft_isedge_point(t_filler *env, int r, int c);
int					solve(t_filler *env);
void				free_list(t_score *lst);
int					free_coordinates_array(t_filler *env);
void				send_min_score_point(t_score *lst);
int					ft_distance(t_filler *env, int r, int c);
void				init(t_filler *env);
int					play(t_filler *env);
void				disp_all(t_filler env);
int					skip_line(t_filler *env);

#endif
