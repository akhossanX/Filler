/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:47:27 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/16 11:47:56 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	fill_piece(t_filler *env)
{
	env->i = 0;
	while (env->i < env->x_piece)
	{
		if (get_next_line(env->rfd, &env->line) == -1)
		{
			destroy(env->piece, env->i);
			env->err = errno;
			return (-1);
		}
		env->piece[env->i++] = env->line;
	}
	env->piece[env->i] = NULL;
	return (1);
}

int			get_piece(t_filler *env)
{
	if ((env->ret = get_next_line(env->rfd, &env->line)) <= 0)
	{
		env->err = env->ret == -1 ? errno : 0;
		return (env->err);
	}
	env->x_piece = ft_atoll(ft_strchr(env->line, ' ') + 1);
	env->y_piece = ft_atoll(ft_strrchr(env->line, ' ') + 1);
	ft_strdel(&env->line);
	if (!(env->piece = (char **)malloc(sizeof(char *) * (env->x_piece + 1))))
	{
		env->err = errno;
		return (0);
	}
	if (fill_piece(env) == -1)
		return (-1);
	return ((env->stock_done = 1));
}
