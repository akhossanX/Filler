/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 12:49:43 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/16 11:48:10 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	Deallocates an array of strings.
**	offset is the number of strings allocated.
*/

void		destroy(char **s, int offset)
{
	int		i;

	i = 0;
	if (offset < 0)
	{
		while (s[i])
			free(s[i++]);
		free(s[i]);
	}
	else
	{
		while (i < offset)
			free(s[i++]);
	}
	free(s);
}

int			fill_map(t_filler *env)
{
	int		i;

	i = 0;
	while (i < env->x)
	{
		if ((env->ret = get_next_line(env->rfd, &env->line)) == -1)
		{
			env->err = errno;
			return (-1);
		}
		ft_strcpy(env->map[i], ft_strchr(env->line, ' ') + 1);
		ft_strdel(&env->line);
		i++;
	}
	env->map[i] = NULL;
	return (1);
}

int			init_map(t_filler *env)
{
	int		i;

	if (skip_line(env) == -1)
		return (env->ret);
	if (!(env->map = (char **)malloc(sizeof(char *) * (env->x + 1))))
	{
		free(env->map);
		env->err = errno;
		return (0);
	}
	i = -1;
	while (++i < env->x)
	{
		if (!(env->map[i] = ft_strnew(env->y)))
		{
			env->err = errno;
			destroy(env->map, i);
			return (0);
		}
	}
	if (fill_map(env) <= 0)
		return (env->ret == -1 ? -1 : 0);
	env->flag = MAP_ALLOCATED;
	return (1);
}

int			get_map(t_filler *env)
{
	if ((env->ret = get_next_line(env->rfd, &env->line)) <= 0)
	{
		env->err = env->ret == -1 ? errno : 0;
		return (env->err);
	}
	env->x = ft_atoll(ft_strchr(env->line, ' ') + 1);
	env->y = ft_atoll(ft_strrchr(env->line, ' ') + 1);
	ft_strdel(&env->line);
	if (env->flag == MAP_ALLOCATED)
	{
		if (skip_line(env) == -1 || fill_map(env) <= 0)
			return (env->ret == -1 ? -1 : 0);
	}
	else if (init_map(env) <= 0)
		return (env->ret == -1 ? -1 : 0);
	return (1);
}
