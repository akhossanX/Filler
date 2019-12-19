/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scores.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:09:53 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 23:03:17 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_score	*score_new(t_filler *env, int x, int y, int score)
{
	t_score	*node;

	if (!(node = (t_score *)malloc(sizeof(t_score))))
	{
		env->err = errno;
		return (NULL);
	}
	node->point.x = x;
	node->point.y = y;
	node->score = score;
	node->next = NULL;
	return (node);
}

/*
**  Gets a list of ((x,y), score) pairs
**  only if there is points in shape of player
**  where we can place the provided token by
**  the Virtual Machine program
*/

t_score	*get_scores(t_filler *env, t_score *edges)
{
	int		score;
	t_score	*scores;
	t_score	*node;
	t_point	place;

	scores = NULL;
	while (edges)
	{
		set_point(&place, edges->point.x, edges->point.y);
		if ((score = is_placeable(env, place)) > 0)
		{
			if (!(node = score_new(env, env->x_place, env->y_place, score)))
			{
				free(scores);
				return (NULL);
			}
			lstappend(&scores, node);
		}
		edges = edges->next;
	}
	return (scores);
}

/*
**  Checks if the given piece (every '*' char) can be placed in a cell
**  inside the map if yes, it stores a list of scores, containing the cell
**  position and its score. if the piece cant' be placed in all the edges it
**  returns a score of -1 otherwise it returns the minimum scores
**  in the list.
*/

int		is_placeable(t_filler *env, t_point place)
{
	int		i;
	int		j;
	int		new_score;
	t_point	star;

	env->score = INT_MAX;
	i = -1;
	while (++i < env->x_piece)
	{
		j = -1;
		while (++j < env->y_piece)
		{
			if (env->piece[i][j] == PIECE_CHAR && set_point(&star, i, j))
			{
				if ((new_score = safe_placement(env, star, place)) > 0)
					if (new_score < env->score)
					{
						env->score = new_score;
						env->x_place = place.x - i;
						env->y_place = place.y - j;
					}
			}
		}
	}
	return (env->score > 0 && env->score < INT_MAX ? env->score : -1);
}

int		safe_placement(t_filler *env, t_point star, t_point place)
{
	int		score;
	int		i;
	int		j;
	t_point	trans;

	set_point(&trans, place.x - star.x, place.y - star.y);
	score = env->hmap[place.x][place.y];
	i = -1;
	while (++i < env->x_piece)
	{
		j = -1;
		while (++j < env->y_piece)
		{
			if ((i != star.x || j != star.y))
			{
				if (out_of_borders_char(env, env->piece[i][j] == EMPTY, \
					i + trans.x, j + trans.y))
					return (-1);
				if (i + trans.x >= 0 && i + trans.x < env->x \
				&& j + trans.y >= 0 && j + trans.y < env->y)
					score += env->hmap[i + trans.x][j + trans.y];
			}
		}
	}
	return (score);
}

/*
**  Gets the list containing every point
**  having the player pattern
*/

t_score	*get_my_points(t_filler *env)
{
	int		i;
	int		j;
	t_score	*node;
	t_score	*scores;

	scores = NULL;
	i = -1;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (ft_tolower(env->map[i][j]) == ft_tolower(env->me.my_char) ||\
				ft_toupper(env->map[i][j]) == ft_toupper(env->me.my_char))
				if (ft_isedge_point(env, i, j))
				{
					if (!(node = score_new(env, i, j, env->hmap[i][j])))
						return (NULL);
					lstappend(&scores, node);
				}
		}
	}
	return (scores);
}
