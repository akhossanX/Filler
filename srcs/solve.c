/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:06:59 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 20:07:12 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		solve(t_filler *env)
{
	t_score	*lst;
	t_score	*my_points;

	lst = NULL;
	my_points = get_my_points(env);
	lst = get_scores(env, my_points);
	if (!lst)
	{
		ft_printf("0 0\n");
		free_list(my_points);
		env->game_over = 1;
		return (0);
	}
	send_min_score_point(lst);
	free_list(lst);
	free_list(my_points);
	return (1);
}

void	send_min_score_point(t_score *lst)
{
	int	min_score;
	int	optimal_x;
	int	optimal_y;

	min_score = INT_MAX;
	while (lst)
	{
		if (lst->score < min_score)
		{
			min_score = lst->score;
			optimal_x = lst->point.x;
			optimal_y = lst->point.y;
		}
		lst = lst->next;
	}
	ft_printf("%d %d\n", optimal_x, optimal_y);
}
