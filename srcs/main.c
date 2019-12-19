/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:57:54 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/19 20:44:27 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_filler	env;

	init(&env);
	while (1)
	{
		if (env.game_init == 0 && get_player(&env) <= 0)
		{
			env.ret != 0 ? ft_printf("Error: %s\n", strerror(env.err)) : 0;
			return (env.err);
		}
		if (get_map(&env) <= 0 || get_piece(&env) <= 0 ||\
			play(&env) < 0)
		{
			if (!env.game_over)
				env.err != 0 ? ft_printf("Error: %s\n", strerror(env.err)) : 0;
			destroy(env.map, -1);
			destroy_hmap(env.hmap, env.x, -1);
			return (env.err == -1);
		}
		//disp_all(env);
		ft_dprintf(env.wfd, "\n\n");
		destroy(env.piece, -1);
	}
	return (0);
}

void	init(t_filler *env)
{
	env->rfd = STDIN;
	env->wfd = STDERR;
	env->map = NULL;
	env->hmap = NULL;
	env->piece = NULL;
	env->line = NULL;
	env->flag = 0;
	env->stock_done = 0;
	env->game_init = 0;
	env->ret = -1;
	env->coor_size = 0;
	env->game_over = 0;
}

int		play(t_filler *env)
{
	if (heat_map_init(env) == -1 || solve(env) == 0)
	{
		destroy(env->piece, -1);
		return (-1);
	}
	return (1);
}

void	disp_all(t_filler env)
{
	int		i;
	int		j;

	if (env.hmap)
	{
		i = -1;
		ft_putnchar_fd(env.wfd, '-', 2 * env.y + 4);
		ft_putchar_fd(env.wfd, '\n');
		while (++i < env.x)
		{
			ft_dprintf(env.wfd, "%s", "||");
			j = -1;
			while (++j < env.y)
			{
				if (env.hmap[i][j] == -2)
					ft_dprintf(env.wfd, "{b_black}{red}%2s{eoall}", "X");
				else if (ft_toupper(env.map[i][j]) == env.me.my_char)
					ft_dprintf(env.wfd, "{b_black}{yellow}%2s{eoall}", "O");
				else
					ft_dprintf(env.wfd, "{b_black}{white}%2s{eoall}", ".");
			}
			ft_dprintf(env.wfd, "%s", "||\n");
		}
		ft_putnchar_fd(env.wfd, '-', 2 * env.y + 4);
	}
}
