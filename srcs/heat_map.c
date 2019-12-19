/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:09:24 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/19 20:45:53 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Deallocates the Heat Map
**	if offset is negative the map is totally destroyed
**	otherwise it destroys only the first offset elements.
*/

void		destroy_hmap(int **arr, int size, int offset)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	if (offset < 0)
	{
		while (i < size)
			free(arr[i++]);
	}
	else
	{
		while (i < offset)
			free(arr[i++]);
	}
	free(arr);
}

/*
**	Allocates a new Heap Map
**	with the exact dimensions of the board game.
*/

int			heat_map_new(t_filler *env)
{
	int		i;

	if (!(env->hmap = (int **)malloc(sizeof(int *) * (env->x))))
	{
		env->err = errno;
		return (0);
	}
	i = 0;
	while (i < env->x)
	{
		if (!(env->hmap[i] = (int *)malloc(sizeof(int) * env->y)))
		{
			env->err = errno;
			destroy_hmap(env->hmap, env->x, i);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
**	Creates the Heap map by calculating the distance
**	between the lastly placed points by ennemy, if he placed some,
**	or the edge points of the ennemy's shape, and every empty
**	cell ('.') in the board game.
*/

int			heat_map_init(t_filler *env)
{
	int		i;
	int		j;

	if (!env->hmap && !heat_map_new(env))
		return (-1);
	i = get_vs_last_move(env);
	if (i == 0 && !get_vs_edges(env))
		return (-1);
	i = -1;
	while (++i < env->x)
	{
		j = -1;
		while (++j < env->y)
		{
			if (ft_toupper(env->map[i][j]) != env->me.vs_char)
				env->hmap[i][j] = ft_distance(env, i, j);
			else
				env->hmap[i][j] = VS_CODE;
		}
	}
	return (free_coordinates_array(env));
}

/*
**	Gets the minimun distance between
**	a point (r, c) and every point in an
**	array of coordinates.
*/

int			ft_distance(t_filler *env, int r, int c)
{
	int		x;
	int		y;
	double	distance;
	int		i;

	i = -1;
	distance = INT_MAX;
	while (++i < env->coor_size)
	{
		x = ft_pow(env->coordinates[i].x - r, 2);
		y = ft_pow(env->coordinates[i].y - c, 2);
		x = ft_round(ft_sqrt(x + y));
		distance > x ? distance = x : 0;
	}
	return (distance);
}

int			free_coordinates_array(t_filler *env)
{
	if (env->coordinates)
	{
		free(env->coordinates);
		return (1);
	}
	return (0);
}
