/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:04:46 by akhossan          #+#    #+#             */
/*   Updated: 2019/12/15 20:12:43 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		skip_line(t_filler *env)
{
	env->ret = get_next_line(env->rfd, &env->line);
	ft_strdel(&env->line);
	return (env->ret);
}

void	free_list(t_score *lst)
{
	while (lst)
	{
		free(lst);
		lst = lst->next;
	}
}

int		set_point(t_point *p, int x, int y)
{
	(*p).x = x;
	(*p).y = y;
	return (1);
}

void	lstappend(t_score **lst, t_score *node)
{
	t_score	*tmp;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int		out_of_borders_char(t_filler *env, int empty, int i, int j)
{
	int	flg1;
	int	flg2;

	if ((i < 0 || j < 0 || i >= env->x || j >= env->y))
	{
		if (!empty)
			return (1);
	}
	else
	{
		flg1 = ft_tolower(env->map[i][j]) == ft_tolower(env->me.my_char)\
			|| ft_toupper(env->map[i][j] == ft_toupper(env->me.my_char));
		flg2 = ft_tolower(env->map[i][j]) == ft_tolower(env->me.vs_char)\
			|| ft_toupper(env->map[i][j] == ft_toupper(env->me.vs_char));
		if ((flg1 || flg2) && !empty)
			return (1);
	}
	return (0);
}
