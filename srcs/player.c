/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 11:58:11 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/16 12:03:05 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			get_player(t_filler *env)
{
	env->ret = get_next_line(env->rfd, &env->line);
	if (env->ret <= 0)
	{
		env->err = env->ret < 0 ? errno : 0;
		return (env->ret < 0 ? env->ret : 0);
	}
	if (ft_strstr(env->line, "exec"))
	{
		if (ft_strstr(env->line, "p1"))
		{
			env->me.my_char = 'O';
			env->me.vs_char = 'X';
		}
		else
		{
			env->me.my_char = 'X';
			env->me.vs_char = 'O';
		}
		ft_strdel(&env->line);
		env->game_init = 1;
		return (1);
	}
	ft_strdel(&env->line);
	return (0);
}
