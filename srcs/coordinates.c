/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:06:03 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 18:09:09 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Fills and returns the array of points
**	around the ennemy's shape
*/

int			get_vs_edges(t_filler *env)
{
	int		i;
	int		j;
	int		k;

	if (!(env->coordinates = new_vs_edges(env)))
		return (0);
	i = -1;
	k = 0;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (env->map[i][j] == env->me.vs_char \
				&& ft_isedge_point(env, i, j))
			{
				env->coordinates[k].x = i;
				env->coordinates[k++].y = j;
			}
		}
	}
	return (1);
}

/*
**	Allocates an array of points
**	According to the number of edge points in
**	the ennemy's shape
*/

t_point		*new_vs_edges(t_filler *env)
{
	int		i;
	int		j;
	t_point	*coor;

	i = -1;
	env->coor_size = 0;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (env->map[i][j] == env->me.vs_char \
				&& ft_isedge_point(env, i, j))
				++env->coor_size;
		}
	}
	if (!(coor = \
		(t_point *)malloc(sizeof(t_point) * env->coor_size)))
	{
		env->err = errno;
		return (NULL);
	}
	return (coor);
}

/*
**	Allocates an array of points
**	According to the number of characters in
**	the last piece placed by the ennemy player
*/

t_point		*new_vs_last_move(t_filler *env)
{
	int		i;
	int		j;
	t_point	*coor;

	i = -1;
	env->coor_size = 0;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (env->map[i][j] == ft_tolower(env->me.vs_char))
				++env->coor_size;
		}
	}
	if (!env->coor_size)
		return (NULL);
	if (!(coor = (t_point *)malloc(sizeof(t_point) * env->coor_size)))
	{
		env->err = errno;
		return (NULL);
	}
	return (coor);
}

/*
**	Fills and returns the array of points
**	lastly placed by the ennemy player
*/

int			get_vs_last_move(t_filler *env)
{
	int		i;
	int		j;
	int		k;

	if (!(env->coordinates = new_vs_last_move(env)))
		return (0);
	k = 0;
	i = -1;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (env->map[i][j] == ft_tolower(env->me.vs_char))
			{
				env->coordinates[k].x = i;
				env->coordinates[k++].y = j;
			}
		}
	}
	return (1);
}

int			ft_isedge_point(t_filler *env, int x, int y)
{
	if (x - 1 >= 0 \
		&& ft_tolower(env->map[x - 1][y]) != ft_tolower(env->map[x][y]))
		return (1);
	else if (x + 1 < env->x \
		&& ft_tolower(env->map[x + 1][y]) != ft_tolower(env->map[x][y]))
		return (1);
	else if (y - 1 >= 0 \
		&& ft_tolower(env->map[x][y - 1]) != ft_tolower(env->map[x][y]))
		return (1);
	else if (y + 1 >= 0 \
		&& ft_tolower(env->map[x][y + 1]) != ft_tolower(env->map[x][y]))
		return (1);
	return (0);
}
