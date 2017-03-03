/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_info1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 19:05:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 19:07:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_putstry(t_e *e, char *str)
{
	e->txt_shift.y += 15;
	mlx_string_put(e->mlx, e->win, e->txt_shift.x, e->txt_shift.y, 0xffffff,
			str);
	free(str);
}

/*
** ft_realloc_str
*/

char			*ft_rs(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

int				calc_kill_rate(t_e *e)
{
	int		i;
	int		count_z;
	int		count_killed_z;

	i = -1;
	count_z = 0;
	count_killed_z = 0;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
			count_z++;
		if (e->spr[i].c == 'Z')
			count_killed_z++;
	}
	if (count_z != 0 && count_killed_z != 0)
		return (((double)count_killed_z / (double)(count_z + count_killed_z))
				* 100);
	else
		return (0);
}
